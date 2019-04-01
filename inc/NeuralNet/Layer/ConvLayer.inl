/**
*
*   TIGINET
*   Copyright (C) 2018-2019  BACHELOT Dorian
*
*   For contact see CONTACT.md file.
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*
*	See LICENSE file for more.
*
*/

#ifndef TN_NEURALNET_CONVLAYER_INL
#define TN_NEURALNET_CONVLAYER_INL

namespace TN
{
	/// @private
	template<typename T>
	Kernel<T>::Kernel(Kernel const& ref)
	{
		this->m_kernel = ref.GetKernel()->Copy();
	}

	/// @private
	template<typename T>
	Kernel<T>::~Kernel()
	{
		if (m_kernel != NULL)
			delete m_kernel;
	}

	/// @private
	template<typename T>
	std::shared_ptr<Tensor<T>>& Kernel<T>::GetKernel()
	{
		return m_kernel;
	}

	/// @private
	template<typename T>
	std::shared_ptr<Tensor<T>> Kernel<T>::GetKernel() const
	{
		return m_kernel;
	}

	/// @private
	template<typename T>
	std::shared_ptr<Kernel<T>> Kernel<T>::Copy()
	{
		std::shared_ptr<Kernel<T>> res = std::make_shared<Kernel2D<T>>(m_kernel);
		res->GetKernel() = m_kernel->Copy();
		return res;
	}

	/// @private
	template<typename T>
	Kernel<T>& Kernel<T>::operator=(const Kernel<T>& ref)
	{
		this->m_kernel = ref.GetKernel()->Copy();
		return *this;
	}

	/// @private
	template<typename T>
	Kernel2D<T>::Kernel2D(const Tensor<T>& kernel)
	{
		if (kernel.GetRank() == 2)
			this->m_kernel = kernel.GetKernel()->Copy();
		else
			TN_WARNING("NEURALNET", "Wrong tensor size for 2D kernel, need 2-tensor (matrix)");
	}

	/// @private
	template<typename T>
	Kernel2D<T>::~Kernel2D()
	{

	}

	/// @private
	template<typename T>
	void Kernel2D<T>::Setup(unsigned int depth)
	{
		if (depth == 0)
			return;

		unsigned int* shape = new unsigned int[3];
		shape[0] = this->m_kernel->GetDimension(1);
		shape[1] = this->m_kernel->GetDimension(2);
		shape[2] = depth;
		std::shared_ptr<Tensor<T>> res = std::make_shared<Tensor<T>>(3, TensorShape(shape), 3);
		delete[] shape;

		for (unsigned int i = 0; i < depth; i++)
			CopySubTensors(*(this->m_kernel), res[i]);

		this->m_kernel = res;
	}

	/// @private
	template<typename T>
	Kernel3D<T>::Kernel3D(const Tensor<T>& kernel)
	{
		if (kernel.GetRank() == 3)
			this->m_kernel = kernel.GetKernel()->Copy();
		else
			TN_WARNING("NEURALNET", "Wrong tensor size for 3D kernel, need 3-tensor");
	}

	/// @private
	template<typename T>
	Kernel3D<T>::~Kernel3D()
	{

	}

	/// @private
	template<typename T>
	void Kernel3D<T>::Setup(unsigned int depth)
	{
		if (depth == 0)
		{
			TN_WARNING("NEURALNET", "Using a 3D kernel over a 2-tensor (matrix) input");
			return;
		}

		unsigned int kernelDepth = this->m_kernel->GetDimension(3);
		if (kernelDepth != depth)
		{
			TN_WARNING("NEURALNET", "Wrong tensor depth for 3D kernel, automatic fit by replication");

			unsigned int* shape = new unsigned int[3];
			shape[0] = this->m_kernel->GetDimension(1);
			shape[1] = this->m_kernel->GetDimension(2);
			shape[2] = depth;
			std::shared_ptr<Tensor<T>> res = std::make_shared<Tensor<T>>(3, TensorShape(shape), 3);
			delete[] shape;

			for (unsigned int i = 0; i < depth; i++)
				CopySubTensors(*(this->m_kernel[i % kernelDepth]), res[i]);

			this->m_kernel = res;
		}
	}

	/// @private
	template<typename T>
	KernelHolder<T>::KernelHolder()
	{

	}

	/// @private
	template<typename T>
	KernelHolder<T>::~KernelHolder()
	{

	}

	/// @private
	template<typename T>
	void KernelHolder<T>::Add(const Kernel<T>& kernel)
	{
		if (x == -1)
			x = kernel.GetKernel()->GetDimension(1);

		if (y == -1)
			y = kernel.GetKernel()->GetDimension(2);

		if (z == -1 && kernel.GetKernel()->GetRank() == 3)
			z = kernel.GetKernel()->GetDimension(3);

		if (x == kernel.GetKernel()->GetDimension(1) && y == kernel.GetKernel()->GetDimension(2) && (kernel.GetKernel()->GetRank() <= 2 || z == kernel.GetKernel()->GetDimension(3)))
			m_kernels.push_back(kernel.Copy());
		else
			TN_WARNING("NEURALNET", "Wrong kernel size when trying to add it to a kernel holder");
	}

	/// @private
	template<typename T>
	std::shared_ptr<Kernel<T>> KernelHolder<T>::Get(unsigned int index)
	{
		return m_kernels.at(index);
	}

	/// @private
	template<typename T>
	void KernelHolder<T>::Setup(unsigned int depth)
	{
		for (unsigned int i = 0; i < m_kernels.size(); i++)
			m_kernels.at(i)->Setup(depth);
	}

	/// @private
	template<typename T>
	std::shared_ptr<KernelHolder<T>> KernelHolder<T>::Copy()
	{
		std::shared_ptr<KernelHolder<T>> res = std::make_shared<KernelHolder<T>>();
		res->m_kernels = m_kernels;
		res->x = x;
		res->y = y;
		res->z = z;

		return res;
	}

	/// @private
	template<typename T>
	ConvLayer<T>::ConvLayer(const ActivatorConfig<T>& activator, const Initializer<T>& initializer, const Optimizer<T>& optimizer, const KernelHolder<T>& kernels, unsigned int stride , unsigned int zeroPadding)
		: Layer<T>(activator, initializer, optimizer)
	{
		TN_ASSERT(kernels.GetRank() == 1, "NEURALNET", "Wrong kernels tensor rank, need to be a vector");

		m_kernels = kernels.Copy();
	}

	/// @private
	template<typename T>
	ConvLayer<T>::~ConvLayer()
	{
		if (m_bias != NULL)
			delete m_bias;

		if (m_grad != NULL)
			delete m_grad;
	}

	/// @private
	template<typename T>
	void ConvLayer<T>::Link(Layer<T>& layer)
	{
		Layer<T>::Link(layer);
		Link(*this->m_in);
	}

	/// @private
	template<typename T>
	void ConvLayer<T>::Link(Tensor<T>& in)
	{
		Layer<T>::Link(in);

		unsigned int depth;

		if (in.GetRank() == 3)
			depth = in.GetDimension(3);
		else
			depth = 0;

		m_kernels->Setup(depth);

		//TODO: initialize bias, gradient and output tensors.
	}

	/// @private
	template<typename T>
	void ConvLayer<T>::Activate()
	{
		//TODO: Make the activate function.
	}

	/// @private
	template<typename T>
	void ConvLayer<T>::Update()
	{
		//TODO: Make the update function.
	}

	/// @private
	template<typename T>
	void ConvLayer<T>::Update(Tensor<T>& result, const CostFunction<T>& costFunction)
	{
		//TODO: Make the update function.
	}
}

#endif
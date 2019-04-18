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
	Kernel<T>::Kernel()
	{
		
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
	std::shared_ptr<Tensor<T>>& Kernel<T>::GetKernelGradient()
	{
		return m_kernelGradient;
	}

	/// @private
	template<typename T>
	std::shared_ptr<Tensor<T>> Kernel<T>::GetKernelGradient() const
	{
		return m_kernelGradient;
	}

	/// @private
	template<typename T>
	Kernel2D<T>::Kernel2D(const Tensor<T>& kernel)
	{
		if (kernel.GetRank() == 2)
			this->m_kernel = kernel.Copy();
		else
			TN_WARNING("NEURALNET", "Wrong tensor size for 2D kernel, need 2-tensor (matrix)");
	}

	/// @private
	template<typename T>
	void Kernel2D<T>::Setup(unsigned int depth)
	{
		if (depth != 0)
		{
			unsigned int* shape = new unsigned int[3];
			shape[0] = this->m_kernel->GetDimension(1);
			shape[1] = this->m_kernel->GetDimension(2);
			shape[2] = depth;
			std::shared_ptr<Tensor<T>> res = std::make_shared<Tensor<T>>(3, TensorShape(shape), 3);
			this->m_kernelGradient = std::make_shared<Tensor<T>>(3, TensorShape(shape), 3);
			delete[] shape;

			for (unsigned int i = 0; i < depth; i++)
				CopySubTensors(*(this->m_kernel), (*res)[i]);

			this->m_kernel = res;
		}
		else
		{
			this->m_kernelGradient = std::make_shared<Tensor<T>>(2, this->m_kernel->GetShape(), 2);
		}
	}

	/// @private
	template<typename T>
	std::shared_ptr<Kernel<T>> Kernel2D<T>::Copy() const
	{
		std::shared_ptr<Kernel<T>> res = std::make_shared<Kernel2D<T>>();
		res->GetKernel() = this->m_kernel->Copy();
		if(this->m_kernelGradient != NULL)
			res->GetKernelGradient() = this->m_kernelGradient->Copy();
		return res;
	}

	/// @private
	template<typename T>
	Kernel3D<T>::Kernel3D(const Tensor<T>& kernel)
	{
		if (kernel.GetRank() == 3)
			this->m_kernel = kernel->Copy();
		else
			TN_WARNING("NEURALNET", "Wrong tensor size for 3D kernel, need 3-tensor");
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
			this->GetKernelGradient = std::make_shared<Tensor<T>>(3, TensorShape(shape), 3);
			delete[] shape;

			for (unsigned int i = 0; i < depth; i++)
				CopySubTensors(*(this->m_kernel[i % kernelDepth]), res[i]);

			this->m_kernel = res;
		}
	}

	/// @private
	template<typename T>
	std::shared_ptr<Kernel<T>> Kernel3D<T>::Copy() const
	{
		std::shared_ptr<Kernel<T>> res = std::make_shared<Kernel3D<T>>();
		res->GetKernel() = this->m_kernel->Copy();
		if (this->m_kernelGradient != NULL)
			res->GetKernelGradient() = this->m_kernelGradient->Copy();
		return res;
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
	std::shared_ptr<KernelHolder<T>> KernelHolder<T>::Copy() const
	{
		std::shared_ptr<KernelHolder<T>> res = std::make_shared<KernelHolder<T>>();
		for (unsigned int i = 0; i < m_kernels.size(); i++)
			res->m_kernels.push_back(m_kernels.at(i)->Copy());
		res->x = x;
		res->y = y;
		res->z = z;

		return res;
	}

	/// @private
	template<typename T>
	unsigned int KernelHolder<T>::GetSize()
	{
		return static_cast<unsigned int>(m_kernels.size());
	}

	/// @private
	template<typename T>
	unsigned int KernelHolder<T>::GetKernelsDimension(unsigned int rank)
	{
		switch (rank)
		{
		case 1:
			if (x < 0)
				TN_WARNING("NEURALNET", "Trying to get kernels dimension with an empty kernel holder.");
			else
				return static_cast<unsigned int>(x);
			break;
		case 2:
			if (y < 0)
				TN_WARNING("NEURALNET", "Trying to get kernels dimension with an empty kernel holder.");
			else
				return static_cast<unsigned int>(y);
			break;
		case 3:
			if (z < 0)
				TN_WARNING("NEURALNET", "Trying to get kernels dimension with an empty kernel holder.");
			else
				return static_cast<unsigned int>(z);
			break;
		default:
			TN_WARNING("NEURALNET", "Trying to get kernels dimension in a kernel holder with wrong rank.");
			return 0;
			break;
		}

		return 0;
	}

	/// @private
	template<typename T>
	void KernelHolder<T>::ResetGradient(const Initializer<T>& initializer)
	{
		for (unsigned int i = 0; i < m_kernels.size(); i++)
			initializer.Initialize(*m_kernels.at(i)->GetKernelGradient());
	}

	/// @private
	template<typename T>
	ConvLayer<T>::ConvLayer(const Initializer<T>& initializer, const Optimizer<T>& optimizer, const KernelHolder<T>& kernels, unsigned int stride , unsigned int zeroPadding)
		: Layer<T>(initializer, optimizer)
	{
		m_kernels = kernels.Copy();

		m_stride = stride;

		if (zeroPadding < m_kernels->GetKernelsDimension(1) || zeroPadding < m_kernels->GetKernelsDimension(2))
			m_zeroPadding = zeroPadding;
		else
		{
			TN_WARNING("NEURALNET", "Wrong zero padding value, too big (it become useless)");
			m_zeroPadding = 0;
		}
	}

	/// @private
	template<typename T>
	ConvLayer<T>::~ConvLayer()
	{
		if (m_bias != NULL)
			delete m_bias;
	}

	/// @private
	template<typename T>
	void ConvLayer<T>::Link(Layer<T>& layer)
	{
		Layer<T>::Link(layer);
		Link(*(this->m_in));
	}

	/// @private
	template<typename T>
	void ConvLayer<T>::Link(Tensor<T>& in)
	{
		Layer<T>::Link(in);

		TN_ASSERT(in.GetRank() <= 3 && in.GetRank() >= 2, "NEURALNET", "Wrong rank for the input");

		unsigned int depth;

		if (in.GetRank() == 3)
			depth = in.GetDimension(3);
		else
			depth = 0;

		m_kernels->Setup(depth);

		TN_ASSERT(m_kernels->GetKernelsDimension(1) <= in.GetDimension(1) && m_kernels->GetKernelsDimension(2) <= in.GetDimension(2), "NEURALNET", "Wrong kernels size for that input");
		TN_ASSERT((in.GetDimension(1) - m_kernels->GetKernelsDimension(1) + 2 * m_zeroPadding) % m_stride == 0 && (in.GetDimension(2) - m_kernels->GetKernelsDimension(2) + 2 * m_zeroPadding) % m_stride == 0, "NEURALNET", "Wrong padding");

		unsigned int* biasShape = new unsigned int[1];
		biasShape[0] = m_kernels->GetSize();
		m_bias = new Tensor<T>(1, TensorShape(biasShape), 1);
		delete[] biasShape;

		unsigned int* outShape = new unsigned int[3];
		outShape[0] = (in.GetDimension(1) - m_kernels->GetKernelsDimension(1) + 2 * m_zeroPadding) / m_stride + 1;
		outShape[1] = (in.GetDimension(2) - m_kernels->GetKernelsDimension(2) + 2 * m_zeroPadding) / m_stride + 1;
		outShape[2] = m_kernels->GetSize();
		this->m_out = new Tensor<T>(3, TensorShape(outShape), 3);
		delete[] outShape;

		this->m_initializer->Initialize(*m_bias);

		// The input gradient get the same shape as the input tensor
		this->m_gradIn = new Tensor<T>(this->m_in->GetRank(), this->m_in->GetShape(), this->m_in->GetRank());

		this->m_optimizer->Setup(m_kernels->GetSize() * m_kernels->GetKernelsDimension(1) * m_kernels->GetKernelsDimension(2) + m_kernels->GetSize());
	}

	/// @private
	template<typename T>
	void ConvLayer<T>::Activate()
	{
		unsigned int dim1 = 0, dim2 = 0, dim3 = 0;
		unsigned int dim1_out = 0, dim2_out = 0;
		unsigned int fx_size = 0, fy_size = 0;
		T sum = 0;

		switch (this->m_in->GetRank())
		{
		case 2:

			dim1 = this->m_in->GetDimension(1);
			dim2 = this->m_in->GetDimension(2);

			dim1_out = this->m_out->GetDimension(1);
			dim2_out = this->m_out->GetDimension(2);

			fx_size = m_kernels->GetKernelsDimension(1);
			fy_size = m_kernels->GetKernelsDimension(2);

			for (unsigned int f = 0; f < m_kernels->GetSize(); f++) // filters
			{
				for (unsigned int x = 0; x < dim1_out; x++) // out.x
				{
					for (unsigned int y = 0; y < dim2_out; y++) // out.y
					{
						sum = 0;
						for (unsigned int fx = 0; fx < fx_size; fx++) // filters.x
						{
							for (unsigned int fy = 0; fy < fy_size; fy++) // filters.y
							{
								if (((x * m_stride + fx) < m_zeroPadding || (y * m_stride + fy) < m_zeroPadding) || ((x * m_stride + fx) >= dim1 + m_zeroPadding || (y * m_stride + fy) >= dim2 + m_zeroPadding))
									continue;
								else
									sum += (*this->m_in)[y * m_stride + fy - m_zeroPadding](x * m_stride + fx - m_zeroPadding) * (*m_kernels->Get(f)->GetKernel())[fy](fx);
							}
						}
						(*this->m_out)[f][y](x) = sum + (*m_bias)(f);
					}
				}
			}

			break;
		case 3:

			dim1 = this->m_in->GetDimension(1);
			dim2 = this->m_in->GetDimension(2);
			dim3 = this->m_in->GetDimension(3);

			dim1_out = this->m_out->GetDimension(1);
			dim2_out = this->m_out->GetDimension(2);

			fx_size = m_kernels->GetKernelsDimension(1);
			fy_size = m_kernels->GetKernelsDimension(2);

			for (unsigned int f = 0; f < m_kernels->GetSize(); f++) // filters count
			{
				for (unsigned int x = 0; x < dim1_out; x++) // out.x
				{
					for (unsigned int y = 0; y < dim2_out; y++) // out.y
					{
						sum = 0;
						for (unsigned int fx = 0; fx < fx_size; fx++) // filters.x
						{
							for (unsigned int fy = 0; fy < fy_size; fy++) // filters.y
							{
								for (unsigned int fz = 0; fz < dim3; fz++) // filter.fz == in.fz
								{
									if (((x * m_stride + fx) < m_zeroPadding || (y * m_stride + fy) < m_zeroPadding) || ((x * m_stride + fx) >= dim1 + m_zeroPadding || (y * m_stride + fy) >= dim2 + m_zeroPadding))
										continue;
									else
										sum += (*this->m_in)[fz][y * m_stride + fy - m_zeroPadding](x * m_stride + fx - m_zeroPadding) * (*m_kernels->Get(f)->GetKernel())[fz][fy](fx);
								}
							}
						}
						(*this->m_out)[f][y](x) = sum + (*m_bias)(f);
					}
				}
			}

			break;
		}

		if (this->m_nextLayer != NULL)
			this->m_nextLayer->Activate();
		
	}

	/// @private
	template<typename T>
	void ConvLayer<T>::Update()
	{
		Tensor<T>* gradIn = this->m_nextLayer->GetInputGradient();
		
		unsigned int dim1 = 0, dim2 = 0, dim3 = 0;
		unsigned int dim1_out = 0, dim2_out = 0;
		unsigned int fx_size = 0, fy_size = 0;
		T sum = 0;

		m_kernels->ResetGradient(this->m_zeroInitializer);
		this->m_zeroInitializer.Initialize(*this->m_gradIn);

		switch (this->m_in->GetRank())
		{
		case 2:

			dim1 = this->m_in->GetDimension(1);
			dim2 = this->m_in->GetDimension(2);

			dim1_out = this->m_out->GetDimension(1);
			dim2_out = this->m_out->GetDimension(2);

			fx_size = m_kernels->GetKernelsDimension(1);
			fy_size = m_kernels->GetKernelsDimension(2);

			for (unsigned int f = 0; f < m_kernels->GetSize(); f++) // filters count
			{
				sum = 0;
				for (unsigned int fx = 0; fx < fx_size; fx++) // filters.x
				{
					for (unsigned int fy = 0; fy < fy_size; fy++) // filters.y
					{
						for (unsigned int x = 0; x < dim1_out; x++) // out.x
						{
							for (unsigned int y = 0; y < dim2_out; y++) // out.y
							{
								if (((x * m_stride + fx) < m_zeroPadding || (y * m_stride + fy) < m_zeroPadding) || ((x * m_stride + fx) >= dim1 + m_zeroPadding || (y * m_stride + fy) >= dim2 + m_zeroPadding))
									continue;

								(*this->m_gradIn)[y * m_stride + fy - m_zeroPadding](x * m_stride + fx - m_zeroPadding) += (*m_kernels->Get(f)->GetKernel())[fy](fx) * (*gradIn)[f][y](x);
								(*m_kernels->Get(f)->GetKernelGradient())[fy](fx) += (*this->m_in)[y * m_stride + fy - m_zeroPadding](x * m_stride + fx - m_zeroPadding) * (*gradIn)[f][y](x);
								sum += (*gradIn)[f][y](x);
							}
						}

						this->m_optimizer->Update((*m_kernels->Get(f)->GetKernel())[fy](fx), (*m_kernels->Get(f)->GetKernelGradient())[fy](fx), 1);
					}
				}

				this->m_optimizer->Update((*m_bias)(f), sum, 1);
			}

			break;
		case 3:

			dim1 = this->m_in->GetDimension(1);
			dim2 = this->m_in->GetDimension(2);
			dim3 = this->m_in->GetDimension(3);

			dim1_out = this->m_out->GetDimension(1);
			dim2_out = this->m_out->GetDimension(2);

			fx_size = m_kernels->GetKernelsDimension(1);
			fy_size = m_kernels->GetKernelsDimension(2);
			
			for (unsigned int f = 0; f < m_kernels->GetSize(); f++) // filters count
			{
				sum = 0;
				for (unsigned int fx = 0; fx < fx_size; fx++) // filters.x
				{
					for (unsigned int fy = 0; fy < fy_size; fy++) // filters.y
					{
						for (unsigned int fz = 0; fz < dim3; fz++) // filter.fz == in.fz
						{
							for (unsigned int x = 0; x < dim1_out; x++) // out.x
							{
								for (unsigned int y = 0; y < dim2_out; y++) // out.y
								{
									if (((x * m_stride + fx) < m_zeroPadding || (y * m_stride + fy) < m_zeroPadding) || ((x * m_stride + fx) >= dim1 + m_zeroPadding || (y * m_stride + fy) >= dim2 + m_zeroPadding))
										continue;

									(*this->m_gradIn)[fz][y * m_stride + fy - m_zeroPadding](x * m_stride + fx - m_zeroPadding) += (*m_kernels->Get(f)->GetKernel())[fz][fy](fx) * (*gradIn)[f][y](x);
									(*m_kernels->Get(f)->GetKernelGradient())[fz][fy](fx) += (*this->m_in)[fz][y * m_stride + fy - m_zeroPadding](x * m_stride + fx - m_zeroPadding) * (*gradIn)[f][y](x);
									sum += (*gradIn)[f][y](x);
								}
							}

							this->m_optimizer->Update((*m_kernels->Get(f)->GetKernel())[fz][fy](fx), (*m_kernels->Get(f)->GetKernelGradient())[fz][fy](fx), 1);
						}
					}
				}

				this->m_optimizer->Update((*m_bias)(f), sum, 1);
			}

			break;
		}

		if (this->m_previousLayer != NULL)
			this->m_previousLayer->Update();
	}

	/// @private
	template<typename T>
	KernelHolder<T> ConvLayer<T>::GetKernelHolder()
	{
		return *m_kernels;
	}
}

#endif
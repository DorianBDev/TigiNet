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

#ifndef TN_NEURALNET_CONVLAYER_HPP
#define TN_NEURALNET_CONVLAYER_HPP

#include <NeuralNet/Layer.hpp>

#include <vector>

namespace TN
{
	/**
	* @class Kernel
	* @brief A kernel/filter for convolutional layer.
	*
	* A kernel can be setup with a specific depth, this will make it fit to. Need to be at least a 2-tensor (matrix).
	*
	* @see ConvLayer
	*
	*/
	template<typename T>
	class Kernel
	{
	public:
		Kernel(Kernel const& ref);
		~Kernel();

		/**
		* @brief Setup the kernel to make it fit to a specific depth. 0 if 2D.
		*
		* @param depth : the desired depth.
		*
		*/
		virtual void Setup(unsigned int depth) = 0;

		/**
		* @brief Get the kernel tensor.
		*
		* @return Return the kernel tensor.
		*
		*/
		std::shared_ptr<Tensor<T>>& GetKernel();

		/**
		* @brief Get the kernel tensor.
		*
		* @return Return the kernel tensor.
		*
		*/
		std::shared_ptr<Tensor<T>> GetKernel() const;

		/**
		* @brief Copy a kernel.
		*
		* @return Return the new shared_ptr kernel.
		*
		*/
		std::shared_ptr<Kernel<T>> Copy();
		Kernel<T>& operator=(const Kernel<T>& ref);

	protected:
		std::shared_ptr<Tensor<T>> m_kernel = NULL;

	};


	/**
	* @class Kernel2D
	* @brief A 2D kernel/filter for 2D convolutional layer.
	*
	* Create a 2D convolutional layer.
	*
	* @see Kernel
	* @see ConvLayer
	*
	*/
	template<typename T>
	class Kernel2D : public Kernel<T>
	{
	public:

		/**
		* @brief Create a 2D kernel with a tensor.
		*
		* @param kernel : the filter 2-tensor.
		*
		*/
		Kernel2D(const Tensor<T>& kernel);
		~Kernel2D();

		/**
		* @brief Setup the kernel to make it fit to a specific depth. 0 if 2D.
		*
		* @param depth : the desired depth.
		*
		*/
		void Setup(unsigned int depth);
		
	};

	/**
	* @class Kernel3D
	* @brief A 3D kernel/filter for 3D convolutional layer.
	*
	* The depth of the 3-tensor passed when created the kernel need to be the same as the 3-tensor input depth of the convolution layer.
	*
	* @see Kernel
	* @see ConvLayer
	*
	*/
	template<typename T>
	class Kernel3D : public Kernel<T>
	{
	public:

		/**
		* @brief Create a 3D kernel with a tensor.
		*
		* The depth of the 3-tensor passed when created the kernel need to be the same as the 3-tensor input depth of the convolution layer.
		*
		* @param kernel : the filter 3-tensor.
		*
		*/
		Kernel3D(const Tensor<T>& kernel);
		~Kernel3D();

		/**
		* @brief Setup the kernel to make it fit to a specific depth. 0 if 2D.
		*
		* @param depth : the desired depth.
		*
		*/
		void Setup(unsigned int depth);

	};

	/**
	* @class KernelHolder
	* @brief Kernel holder class.
	*
	* 1-tensor(vector) of kernels, all the kernels need to have the same size(e.g. for a 3x3 2D kernel, all others kernels need to be 3x3 2d kernel). You can mix 2D and 3D kernels, but they need the same matrix size.
	*
	* @see Kernel
	*
	*/
	template<typename T>
	class KernelHolder
	{
	public:

		/**
		* @brief Create a kernel holder.
		*
		*/
		KernelHolder();
		~KernelHolder();

		/**
		* @brief Add a new kernel to the kernel holder.
		*
		* @param kernel : the kernel to add.
		*
		*/
		void Add(const Kernel<T>& kernel);

		/**
		* @brief Get a kernel from the kernel holder.
		*
		* @param index : the index of the kernel in the kernel holder.
		*
		* @return Return a shared_ptr to the selected kernel.
		*
		*/
		std::shared_ptr<Kernel<T>> Get(unsigned int index);

		/**
		* @brief Setup all kernels to make them fit to a specific depth. 0 if 2D.
		*
		* @param depth : the desired depth.
		*
		*/
		void Setup(unsigned int depth);

		/**
		* @brief Copy a kernel holder.
		*
		* @return Return a shared_ptr to the new kernel holder.
		*
		*/
		std::shared_ptr<KernelHolder<T>> Copy();

	protected:
		std::vector<std::shared_ptr<Kernel<T>>> m_kernels;
		int x = -1, y = -1, z = -1;

	};

	/**
	* @class ConvLayer
	* @brief Convolutional layer.
	*
	* Create a convolutional layer.
	*
	* @see Layer
	*
	*/
	template<typename T>
	class ConvLayer : public Layer<T>
	{
	public:
		
		/**
		* @brief Create a new convolutional layer.
		*
		* @param activator : the activator config.
		* @param initializer : the inializer.
		* @param optimizer : the optimizer.
		* @param kernels : the kernel holder.
		* @param stride : controls the number of steps that you move the filter over the input image.
		* @param zeroPadding : refers to padding the input volume with zeros around the border. In the 7x7input image example, if we use a stride of 1 and a zero padding of 1, then the output volume is also equal to 7x7.
		*
		* @see ActivatorConfig
		* @see Initializer
		* @see Optimizer
		* @see Kernel
		* @see KernelHolder
		*
		*/
		ConvLayer(const ActivatorConfig<T>& activator, const Initializer<T>& initializer, const Optimizer<T>& optimizer, const KernelHolder<T>& kernels, unsigned int stride = 1, unsigned int zeroPadding = 0);
		~ConvLayer();

		/**
		* @brief Link a layer to this layer.
		*
		* @param layer : the layer to link with.
		*
		*/
		void Link(Layer<T>& layer);

		/**
		* @brief Link an input tensor to this layer.
		*
		* @param in : the input tensor to link with.
		*
		*/
		void Link(Tensor<T>& in);

		/**
		* @brief Forward propagation.
		*
		*/
		void Activate();

		/**
		* @brief Backward propagation.
		*
		*/
		void Update();

		/**
		* @brief Backward propagation with the expected results (only if the layer is the output one).
		*
		* @param result : expected results.
		* @param costFunction : the cost function.
		*
		* @see CostFunction
		*
		*/
		void Update(Tensor<T>& result, const CostFunction<T>& costFunction);

	private:
		Tensor<T>* m_bias = NULL;
		Tensor<T>* m_grad = NULL;
		std::shared_ptr<KernelHolder<T>> m_kernels = NULL;
		
	};
}

#include <NeuralNet/Layer/ConvLayer.inl>

#endif
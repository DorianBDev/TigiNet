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

#ifndef TN_NEURALNET_POOLINGLAYER_HPP
#define TN_NEURALNET_POOLINGLAYER_HPP

#include <NeuralNet/Layer.hpp>

namespace TN
{
	/*! All different pooling methods you can use with the pooling layer */
	typedef enum PoolingMethod_e
	{
		PM_MAX,    /*!< Use the max pooling method */
		PM_AVERAGE /*!< Use the average pooling method */
	}PoolingMethod;

	/**
	* @struct PoolingKernel
	* @brief A struct that store kernel size of a pooling layer.
	*
	* @see PoolingLayer
	*
	*/
	typedef struct PoolingKernel_s
	{
		unsigned int m_x; /*!< The first dimension of the kernel */
		unsigned int m_y; /*!< The second dimension of the kernel */

		PoolingKernel_s(const unsigned int x, const unsigned int y)
		{
			m_x = x;
			m_y = y;
		}

		PoolingKernel_s(const PoolingKernel_s& poolingKernel)
		{
			m_x = poolingKernel.m_x;
			m_y = poolingKernel.m_y;
		}
	}PoolingKernel;

	/**
	* @class PoolingLayer
	* @brief Pooling layer.
	*
	* Create a pooling layer.
	*
	* @see Layer
	*
	*/
	template<typename T>
	class PoolingLayer : public Layer<T>
	{
	public:

		/**
		* @brief Create a new convolutional layer.
		*
		* @param method : the pooling method.
		* @param kernel : the kernel of the pooling layer.
		* @param stride : controls the number of steps that you move the filter over the input image.
		* @param zeroPadding : refers to padding the input volume with zeros around the border. In the 7x7input image example, if we use a stride of 1 and a zero padding of 1, then the output volume is also equal to 7x7.
		*
		* @see PoolingMethod
		*
		*/
		PoolingLayer(const PoolingMethod method, const PoolingKernel kernel, unsigned int stride = 1, unsigned int zeroPadding = 0);
		~PoolingLayer();

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
		* @brief Save the layer in a file.
		*
		* The layer topology need to be exactly the same (pre-linked layer). The function will only save trainable data and not the topology.
		*
		* @param file : the file to save in.
		*
		*/
		void SaveInFile(std::ofstream& file);

		/**
		* @brief Load the layer from a file.
		*
		* The layer topology need to be exactly the same (pre-linked layer). The function will only load trainable data and not the topology.
		*
		* @param file : the file to load from.
		*
		*/
		void LoadFromFile(std::ifstream& file);

	private:
		PoolingMethod m_method;
		unsigned int m_stride;
		unsigned int m_zeroPadding;
		PoolingKernel m_kernel;

	};

}

#include <NeuralNet/Layer/PoolingLayer.inl>

#endif
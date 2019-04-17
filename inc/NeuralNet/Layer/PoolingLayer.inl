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

#ifndef TN_NEURALNET_POOLINGLAYER_INL
#define TN_NEURALNET_POOLINGLAYER_INL

namespace TN
{
	/// @private
	template<typename T>
	PoolingLayer<T>::PoolingLayer(const ActivatorConfig<T>& activator, const Initializer<T>& initializer, const Optimizer<T>& optimizer, const PoolingMethod method, const PoolingKernel kernel, unsigned int stride)
		: Layer<T>(activator, initializer, optimizer)
	{
		TN_ASSERT(stride >= 1, "NEURALNET", "Wronde stride value");

		m_stride = stride;
		m_method = method;
		m_kernel.m_x = kernel.m_x;
		m_kernel.m_y = kernel.m_y;
	}

	/// @private
	template<typename T>
	PoolingLayer<T>::~PoolingLayer()
	{
		
	}

	/// @private
	template<typename T>
	void PoolingLayer<T>::Link(Layer<T>& layer)
	{
		Layer<T>::Link(layer);
		Link(*(this->m_in));
	}

	/// @private
	template<typename T>
	void PoolingLayer<T>::Link(Tensor<T>& in)
	{
		Layer<T>::Link(in);

		TN_ASSERT(in.GetRank() <= 3 && in.GetRank() >= 2, "NEURALNET", "Wrong rank for the input");
		TN_ASSERT(in.GetDimension(1) >= m_kernel.m_x && in.GetDimension(2) >= m_kernel.m_y, "NEURALNET", "Wrong kernel size");
		TN_ASSERT((in.GetDimension(1) - m_kernel.m_x) % m_stride == 0 && (in.GetDimension(2) - m_kernel.m_y) % m_stride == 0, "NEURALNET", "Wrong padding");

		unsigned int* outShape = NULL;
		switch (in.GetRank())
		{
		case 2:

			outShape = new unsigned int[2];
			outShape[0] = (in.GetDimension(1) - m_kernel.m_x) / m_stride + 1;
			outShape[1] = (in.GetDimension(2) - m_kernel.m_y) / m_stride + 1;
			this->m_out = new Tensor<T>(2, TensorShape(outShape), 2);

			break;
		case 3:

			outShape = new unsigned int[3];
			outShape[0] = (in.GetDimension(1) - m_kernel.m_x) / m_stride + 1;
			outShape[1] = (in.GetDimension(2) - m_kernel.m_y) / m_stride + 1;
			outShape[2] = in.GetDimension(3);
			this->m_out = new Tensor<T>(3, TensorShape(outShape), 3);

			break;
		default:
			TN_WARNING("NEURALNET", "Wrong input size");
			break;
		}

		// The input gradient get the same shape as the input tensor
		this->m_gradIn = new Tensor<T>(this->m_in->GetRank(), this->m_in->GetShape(), this->m_in->GetRank());
	}

	/// @private
	template<typename T>
	void PoolingLayer<T>::Activate()
	{
		//TODO
	}

	/// @private
	template<typename T>
	void PoolingLayer<T>::Update()
	{
		//TODO
	}

	/// @private
	template<typename T>
	void PoolingLayer<T>::Update(Tensor<T>& result, const CostFunction<T>& costFunction)
	{

	}

}

#endif
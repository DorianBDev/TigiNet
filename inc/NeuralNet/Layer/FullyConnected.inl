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

#ifndef TN_NEURALNET_FULLYCONNECTED_INL
#define TN_NEURALNET_FULLYCONNECTED_INL

#include <Core/Error.hpp>

namespace TN
{
	/// @private
	template<typename T>
	TN::FCLayer<T>::FCLayer(ActivatorConfig<T> & config, unsigned int neuronsCount)
		: Layer<T>(config)
	{
		m_neuronsCount = neuronsCount;
	}

	/// @private
	template<typename T>
	TN::FCLayer<T>::~FCLayer()
	{
		if (m_weight != NULL)
			delete m_weight;

		if (m_bias != NULL)
			delete m_bias;
	}

	/// @private
	template<typename T>
	void TN::FCLayer<T>::Link(Layer<T> & layer)
	{
		//Layer<T>::Link(layer);
		Link(layer.m_in);
	}

	/// @private
	template<typename T>
	void TN::FCLayer<T>::Link(Tensor<T> & in)
	{
		Layer<T>::Link(in);

		TN_ASSERT(this->m_in->GetRank() <= 4, "Wrong input tensor rank");
		
		unsigned int D = 0; // Linear size, number of unique input.
		unsigned int N = 0; // Batch size.
		unsigned int* weightShape;
		unsigned int* biasShape = new unsigned int[1];
		unsigned int* outShape;

		switch (this->m_in->GetRank())
		{
		case 0: // Scalar
			D = 1;
			N = 1;
			break;
		case 1: // Vector
			D = this->m_in->GetDimension(1);
			N = 1;
			break;
		case 2: // Matrix
			D = this->m_in->GetDimension(1) * this->m_in->GetDimension(2);
			N = 1;
			break;
		case 3: // 3-tensor
			D = this->m_in->GetDimension(1) * this->m_in->GetDimension(2) * this->m_in->GetDimension(3);
			N = 1;
			break;
		case 4: // 3-tensor with N batch
			D = this->m_in->GetDimension(1) * this->m_in->GetDimension(2) * this->m_in->GetDimension(3);
			N = this->m_in->GetDimension(4);
			break;
		default:
			D = 0;
			TN_WARNING("Wrong tensor rank");
			return;
			break;
		}
		weightShape = new unsigned int[2];
		weightShape[0] = D;
		weightShape[1] = m_neuronsCount;
		
		m_weight = new Tensor<T>(2, TensorShape(weightShape), 2); //TODO: gradient tensor.
		delete[] weightShape;

		biasShape[0] = m_neuronsCount;
		m_bias = new Tensor<T>(1, TensorShape(biasShape), 1);
		delete[] biasShape;

		if (N == 1)
		{
			outShape = new unsigned int[1];
			outShape[0] = m_neuronsCount;
			this->m_out = new Tensor<T>(1, TensorShape(outShape), 1);
		}
		else
		{
			outShape = new unsigned int[2];
			outShape[0] = m_neuronsCount;
			outShape[1] = N;
			this->m_out = new Tensor<T>(2, TensorShape(outShape), 2);
		}
		delete[] outShape;
	}

	/// @private
	template<typename T>
	void TN::FCLayer<T>::Activate()
	{
		//TODO
	}

	/// @private
	template<typename T>
	void TN::FCLayer<T>::Update()
	{
		//TODO
	}

}

#endif
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
	FCLayer<T>::FCLayer(const ActivatorConfig<T> & config, const Initializer<T> & initializer, unsigned int neuronsCount)
		: Layer<T>(config, initializer)
	{
		m_neuronsCount = neuronsCount;
	}

	/// @private
	template<typename T>
	FCLayer<T>::~FCLayer()
	{
		if (m_weight != NULL)
			delete m_weight;

		if (m_bias != NULL)
			delete m_bias;
	}

	/// @private
	template<typename T>
	void FCLayer<T>::Link(Layer<T> & layer)
	{
		//Layer<T>::Link(layer);
		Link(layer.m_in);
	}

	/// @private
	template<typename T>
	void FCLayer<T>::Link(Tensor<T> & in)
	{
		Layer<T>::Link(in);

		TN_ASSERT(this->m_in->GetRank() <= 4, "NEURALNET", "Wrong input tensor rank");
		
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
			TN_WARNING("NEURALNET", "Wrong tensor rank");
			return;
			break;
		}
		weightShape = new unsigned int[2];
		weightShape[0] = m_neuronsCount;
		weightShape[1] = D;
		
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

		this->m_initializer.Initialize(*m_weight);
		this->m_initializer.Initialize(*m_bias);
		this->m_initializer.Initialize(*(this->m_out));

		this->m_weight->Print();
		this->m_bias->Print();
		this->m_out->Print();
	}

	/// @private
	template<typename T>
	void FCLayer<T>::Activate()
	{
		T sum = 0;
		unsigned int dim1 = 0, dim2 = 0, dim3 = 0, dim4 = 0; // Optimization

		switch (this->m_in->GetRank())
		{
		case 0: // Scalar

			for (unsigned int i = 0; i < m_neuronsCount; i++)
			{
				(*this->m_out)(i) = this->m_activator.ActivationFunction((*this->m_in)() * (*this->m_weight)[0](i) + (*this->m_bias)(i));
			}

			break;
		case 1: // Vector

			dim1 = this->m_in->GetDimension(1);

			for (unsigned int i = 0; i < m_neuronsCount; i++)
			{
				sum = 0;
				for (unsigned int j = 0; j < dim1; j++)
				{
					sum += (*this->m_in)(j) * (*this->m_weight)[j](i);
				}
				(*this->m_out)(i) = this->m_activator.ActivationFunction(sum + (*this->m_bias)(i));
			}

			break;
		case 2: // Matrix

			dim1 = this->m_in->GetDimension(1);
			dim2 = this->m_in->GetDimension(2);

			for (unsigned int i = 0; i < m_neuronsCount; i++)
			{
				sum = 0;
				for (unsigned int j = 0; j < dim1; j++)
				{
					for (unsigned int k = 0; k < dim2; k++)
					{
						sum += (*this->m_in)[k](j) * (*this->m_weight)[j + k * dim2](i);
					}
				}
				(*this->m_out)(i) = this->m_activator.ActivationFunction(sum + (*this->m_bias)(i));
			}

			break;
		case 3: // 3-tensor

			dim1 = this->m_in->GetDimension(1);
			dim2 = this->m_in->GetDimension(2);
			dim3 = this->m_in->GetDimension(3);

			for (unsigned int i = 0; i < m_neuronsCount; i++)
			{
				sum = 0;
				for (unsigned int j = 0; j < dim1; j++)
				{
					for (unsigned int k = 0; k < dim2; k++)
					{
						for (unsigned int l = 0; l < dim3; l++)
						{
							sum += (*this->m_in)[l][k](j) * (*this->m_weight)[j + k * dim2 + l * dim3](i);
						}
					}
				}
				(*this->m_out)(i) = this->m_activator.ActivationFunction(sum + (*this->m_bias)(i));
			}

			break;
		case 4: // 3-tensor with N batch

			dim1 = this->m_in->GetDimension(1);
			dim2 = this->m_in->GetDimension(2);
			dim3 = this->m_in->GetDimension(3);
			dim4 = this->m_in->GetDimension(4);

			for (unsigned int b = 0; b < dim4; b++)
			{
				for (unsigned int i = 0; i < m_neuronsCount; i++)
				{
					sum = 0;
					for (unsigned int j = 0; j < dim1; j++)
					{
						for (unsigned int k = 0; k < dim2; k++)
						{
							for (unsigned int l = 0; l < dim3; l++)
							{
								sum += (*this->m_in)[b][l][k](j) * (*this->m_weight)[j + k * dim2 + l * dim3](i);
							}
						}
					}
					(*this->m_out)[b](i) = this->m_activator.ActivationFunction(sum + (*this->m_bias)(i));
				}
			}

			break;
		default:
			TN_WARNING("NEURALNET", "Wrong tensor rank");
			return;
			break;
		}
	}

	/// @private
	template<typename T>
	void FCLayer<T>::Update()
	{
		//TODO
	}

}

#endif
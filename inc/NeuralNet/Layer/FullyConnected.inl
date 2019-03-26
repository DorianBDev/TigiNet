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
	FCLayer<T>::FCLayer(const ActivatorConfig<T> & activator, const Initializer<T> & initializer, const Optimizer<T> & optimizer, unsigned int neuronsCount)
		: Layer<T>(activator, initializer, optimizer)
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

		if (m_grad != NULL)
			delete m_grad;
	}

	/// @private
	template<typename T>
	void FCLayer<T>::Link(Layer<T> & layer)
	{
		Layer<T>::Link(layer);
		Link(*this->m_in);
	}

	/// @private
	template<typename T>
	void FCLayer<T>::Link(Tensor<T> & in)
	{
		Layer<T>::Link(in);

		TN_ASSERT(this->m_in->GetRank() <= 3, "NEURALNET", "Wrong input tensor rank");
		
		unsigned int D = 0; // Linear size, number of unique input.
		unsigned int* weightShape;
		unsigned int* biasShape = new unsigned int[1];
		unsigned int* outShape;

		switch (this->m_in->GetRank())
		{
		case 0: // Scalar
			D = 1;
			break;
		case 1: // Vector
			D = this->m_in->GetDimension(1);
			break;
		case 2: // Matrix
			D = this->m_in->GetDimension(1) * this->m_in->GetDimension(2);
			break;
		case 3: // 3-tensor
			D = this->m_in->GetDimension(1) * this->m_in->GetDimension(2) * this->m_in->GetDimension(3);
			break;
		default:
			D = 0;
			TN_WARNING("NEURALNET", "Wrong tensor rank for fully connected layer.");
			return;
			break;
		}
		weightShape = new unsigned int[2];
		weightShape[0] = m_neuronsCount;
		weightShape[1] = D;
		
		this->m_weight = new Tensor<T>(2, TensorShape(weightShape), 2);
		delete[] weightShape;

		biasShape[0] = m_neuronsCount;
		this->m_bias = new Tensor<T>(1, TensorShape(biasShape), 1);
		delete[] biasShape;

		outShape = new unsigned int[1];
		outShape[0] = m_neuronsCount;
		this->m_out = new Tensor<T>(1, TensorShape(outShape), 1);
		this->m_grad = new Tensor<T>(1, TensorShape(outShape), 1);
		delete[] outShape;

		// The input gradient get the same shape as the input tensor
		this->m_gradIn = new Tensor<T>(this->m_in->GetRank(), this->m_in->GetShape(), this->m_in->GetRank());

		this->m_initializer->Initialize(*(this->m_weight));
		this->m_initializer->Initialize(*(this->m_bias));

		this->m_optimizer->Setup(m_neuronsCount * D + m_neuronsCount);
	}

	/// @private
	template<typename T>
	void FCLayer<T>::Activate()
	{
		T sum = 0;
		unsigned int dim1 = 0, dim2 = 0, dim3 = 0; // Optimization

		switch (this->m_in->GetRank())
		{
		case 0: // Scalar

			for (unsigned int i = 0; i < m_neuronsCount; i++)
			{
				(*this->m_out)(i) = this->m_activator->Activation((*this->m_in)() * (*this->m_weight)[0](i) + (*this->m_bias)(i));
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
				(*this->m_out)(i) = this->m_activator->Activation(sum + (*this->m_bias)(i));
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
				(*this->m_out)(i) = this->m_activator->Activation(sum + (*this->m_bias)(i));
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
				(*this->m_out)(i) = this->m_activator->Activation(sum + (*this->m_bias)(i));
			}

			break;
		default:
			TN_WARNING("NEURALNET", "Wrong tensor rank for fully connected layer.");
			return;
			break;
		}

		if(this->m_nextLayer != NULL)
			this->m_nextLayer->Activate();
	}

	/// @private
	template<typename T>
	void FCLayer<T>::Update()
	{
		Tensor<T>* gradIn = this->m_nextLayer->GetInputGradient();

		for (unsigned int i = 0; i < m_neuronsCount; i++)
		{
			(*this->m_grad)(i) = (*gradIn)(i) * this->m_activator->Derivation((*this->m_out)(i));
		}

		this->m_zeroInitializer.Initialize(*this->m_gradIn);

		unsigned int dim1, dim2, dim3;
		switch (this->m_in->GetRank())
		{
		case 0: // Scalar

			for (unsigned int i = 0; i < m_neuronsCount; i++)
			{
				this->m_optimizer->Update((*m_weight)[0](i), (*this->m_grad)(i), (*this->m_in)());
				this->m_optimizer->Update((*m_bias)(i), (*this->m_grad)(i), 1);
				(*this->m_gradIn)() += (*this->m_grad)(i) * (*m_weight)[0](i);
			}

			break;
		case 1: // Vector

			dim1 = this->m_in->GetDimension(1);

			for (unsigned int i = 0; i < m_neuronsCount; i++)
			{
				for (unsigned int j = 0; j < dim1; j++)
				{
					this->m_optimizer->Update((*m_weight)[j](i), (*this->m_grad)(i), (*this->m_in)(j));
					(*this->m_gradIn)(j) += (*this->m_grad)(i) * (*m_weight)[j](i);
				}
				this->m_optimizer->Update((*m_bias)(i), (*this->m_grad)(i), 1);
			}

			break;
		case 2: // Matrix

			dim1 = this->m_in->GetDimension(1);
			dim2 = this->m_in->GetDimension(2);

			for (unsigned int i = 0; i < m_neuronsCount; i++)
			{
				for (unsigned int j = 0; j < dim1; j++)
				{
					for (unsigned int k = 0; k < dim2; k++)
					{
						this->m_optimizer->Update((*m_weight)[j + k * dim2](i), (*this->m_grad)(i), (*this->m_in)[k](j));
						(*this->m_gradIn)[k](j) += (*this->m_grad)(i) * (*m_weight)[j + k * dim2](i);
					}
				}
				this->m_optimizer->Update((*this->m_bias)(i), (*this->m_grad)(i), 1);
			}

			break;
		case 3: // 3-tensor

			dim1 = this->m_in->GetDimension(1);
			dim2 = this->m_in->GetDimension(2);
			dim3 = this->m_in->GetDimension(3);

			for (unsigned int i = 0; i < m_neuronsCount; i++)
			{
				for (unsigned int j = 0; j < dim1; j++)
				{
					for (unsigned int k = 0; k < dim2; k++)
					{
						for (unsigned int l = 0; l < dim3; l++)
						{
							this->m_optimizer->Update((*m_weight)[j + k * dim2 + l * dim3](i), (*this->m_grad)(i), (*this->m_in)[l][k](j));
							(*this->m_gradIn)[l][k](j) += (*this->m_grad)(i) * (*m_weight)[j + k * dim2 + l * dim3](i);
						}
					}
				}
				this->m_optimizer->Update((*this->m_bias)(i), (*this->m_grad)(i), 1);
			}

			break;
		default:
			TN_WARNING("NEURALNET", "Wrong tensor rank for fully connected layer.");
			return;
			break;
		}

		if (this->m_previousLayer != NULL)
			this->m_previousLayer->Update();
	}

	/// @private
	template<typename T>
	void FCLayer<T>::Update(Tensor<T>& result, const CostFunction<T>& costFunction)
	{
		if (this->m_nextLayer != NULL) // If not an output layer.
		{
			Update();
			return;
		}

		TN_ASSERT(result.GetRank() == this->m_out->GetRank(), "NEURALNET", "Wrong rank for the result tensor");

		this->m_error = costFunction.Activation((*this->m_out), result);

		for (unsigned int i = 0; i < m_neuronsCount; i++)
		{
			(*this->m_grad)(i) = this->m_activator->Derivation((*this->m_out)(i)) * costFunction.Derivation((*this->m_out)(i), result(i));
		}

		this->m_zeroInitializer.Initialize(*this->m_gradIn);

		unsigned int dim1, dim2, dim3;
		switch (this->m_in->GetRank())
		{
		case 0: // Scalar

			for (unsigned int i = 0; i < m_neuronsCount; i++)
			{
				this->m_optimizer->Update((*m_weight)[0](i), (*this->m_grad)(i), (*this->m_in)());
				this->m_optimizer->Update((*m_bias)(i), (*this->m_grad)(i), 1);
				(*this->m_gradIn)() += (*this->m_grad)(i) * (*m_weight)[0](i);
			}

			break;
		case 1: // Vector

			dim1 = this->m_in->GetDimension(1);

			for (unsigned int i = 0; i < m_neuronsCount; i++)
			{
				for (unsigned int j = 0; j < dim1; j++)
				{
					this->m_optimizer->Update((*m_weight)[j](i), (*this->m_grad)(i), (*this->m_in)(j));
					(*this->m_gradIn)(j) += (*this->m_grad)(i) * (*m_weight)[j](i);
				}
				this->m_optimizer->Update((*m_bias)(i), (*this->m_grad)(i), 1);
			}

			break;
		case 2: // Matrix

			dim1 = this->m_in->GetDimension(1);
			dim2 = this->m_in->GetDimension(2);

			for (unsigned int i = 0; i < m_neuronsCount; i++)
			{
				for (unsigned int j = 0; j < dim1; j++)
				{
					for (unsigned int k = 0; k < dim2; k++)
					{
						this->m_optimizer->Update((*m_weight)[j + k * dim2](i), (*this->m_grad)(i), (*this->m_in)[k](j));
						(*this->m_gradIn)[k](j) += (*this->m_grad)(i) * (*m_weight)[j + k * dim2](i);
					}
				}
				this->m_optimizer->Update((*this->m_bias)(i), (*this->m_grad)(i), 1);
			}

			break;
		case 3: // 3-tensor

			dim1 = this->m_in->GetDimension(1);
			dim2 = this->m_in->GetDimension(2);
			dim3 = this->m_in->GetDimension(3);

			for (unsigned int i = 0; i < m_neuronsCount; i++)
			{
				for (unsigned int j = 0; j < dim1; j++)
				{
					for (unsigned int k = 0; k < dim2; k++)
					{
						for (unsigned int l = 0; l < dim3; l++)
						{
							this->m_optimizer->Update((*m_weight)[j + k * dim2 + l * dim3](i), (*this->m_grad)(i), (*this->m_in)[l][k](j));
							(*this->m_gradIn)[l][k](j) += (*this->m_grad)(i) * (*m_weight)[j + k * dim2 + l * dim3](i);
						}
					}
				}
				this->m_optimizer->Update((*this->m_bias)(i), (*this->m_grad)(i), 1);
			}

			break;
		default:
			TN_WARNING("NEURALNET", "Wrong tensor rank for fully connected layer.");
			return;
			break;
		}

		if (this->m_previousLayer != NULL)
			this->m_previousLayer->Update();
	}

}

#endif
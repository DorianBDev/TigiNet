#include "Layer.hpp"
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

#ifndef TN_NEURALNET_LAYER_INL
#define TN_NEURALNET_LAYER_INL

namespace TN
{
	/// @private
	template<typename T>
	ActivatorConfig<T>::ActivatorConfig(double(&activationFunction)(double))
	{
		m_activationFunction = &activationFunction;
		m_activationFunctionDerivative = NULL;
	}

	/// @private
	template<typename T>
	ActivatorConfig<T>::ActivatorConfig(double(&activationFunction)(double), double(&activationFunctionDerivative)(double))
	{
		m_activationFunction = &activationFunction;
		m_activationFunctionDerivative = &activationFunctionDerivative;
	}

	/// @private
	template<typename T>
	T ActivatorConfig<T>::Activation(T value) const
	{
		return static_cast<T>(m_activationFunction(static_cast<double>(value)));
	}

	/// @private
	template<typename T>
	T ActivatorConfig<T>::Derivation(T value) const
	{
		if (m_activationFunctionDerivative == NULL)
			return static_cast<T>(DerivativeApproximation(*m_activationFunction, static_cast<double>(value)));
		else
			return static_cast<T>(m_activationFunctionDerivative(static_cast<double>(value)));
	}

	/// @private
	template<typename T>
	std::shared_ptr<ActivatorConfig<T>> ActivatorConfig<T>::Copy() const
	{
		return std::make_shared<ActivatorConfig<T>>(*m_activationFunction, *m_activationFunctionDerivative);
	}

	/// @private
	template<typename T>
	Layer<T>::Layer(const ActivatorConfig<T> & activator, const Initializer<T> & initializer, const Optimizer<T> & optimizer)
	{
		m_activator = activator.Copy();
		m_initializer = initializer.Copy();
		m_optimizer = optimizer.Copy();
	}

	/// @private
	template<typename T>
	Layer<T>::Layer(const ActivatorConfig<T>& activator)
	{
		m_activator = activator.Copy();
	}

	/// @private
	template<typename T>
	Layer<T>::Layer(const Initializer<T>& initializer)
	{
		m_initializer = initializer.Copy();
	}

	/// @private
	template<typename T>
	Layer<T>::Layer(const Optimizer<T>& optimizer)
	{
		m_optimizer = optimizer.Copy();
	}

	/// @private
	template<typename T>
	Layer<T>::Layer(const ActivatorConfig<T>& activator, const Initializer<T>& initializer)
	{
		m_activator = activator.Copy();
		m_initializer = initializer.Copy();
	}

	/// @private
	template<typename T>
	Layer<T>::Layer(const ActivatorConfig<T>& activator, const Optimizer<T>& optimizer)
	{
		m_activator = activator.Copy();
		m_optimizer = optimizer.Copy();
	}

	/// @private
	template<typename T>
	Layer<T>::Layer(const Initializer<T>& initializer, const Optimizer<T>& optimizer)
	{
		m_initializer = initializer.Copy();
		m_optimizer = optimizer.Copy();
	}

	/// @private
	template<typename T>
	Layer<T>::Layer()
	{
	}

	/// @private
	template<typename T>
	Layer<T>::~Layer()
	{
		if (m_out != NULL)
			delete m_out;

		if (m_gradIn != NULL)
			delete m_gradIn;
	}

	/// @private
	template<typename T>
	void Layer<T>::Link(Layer<T> & layer)
	{
		this->m_in = layer.m_out;
		layer.m_nextLayer = this;
		this->m_previousLayer = &layer;
	}

	/// @private
	template<typename T>
	void Layer<T>::Link(Tensor<T> & in)
	{
		this->m_in = &in;
	}

	/// @private
	template<typename T>
	Tensor<T>& Layer<T>::GetOutput()
	{
		return (*m_out);
	}

	/// @private
	template<typename T>
	double Layer<T>::GetError() const
	{
		return m_error;
	}

	/// @private
	template<typename T>
	double Layer<T>::GetError(const CostFunction<T>& costFunction, const Tensor<T>& prediction, const Tensor<T>& result)
	{
		m_error = costFunction.Activation(prediction, result);
		return m_error;
	}

	/// @private
	template<typename T>
	Tensor<T>* Layer<T>::GetInputGradient()
	{
		return m_gradIn;
	}

	/// @private
	template<typename T>
	void Layer<T>::ResetInput(Tensor<T>& tensor)
	{
		if (m_in != NULL)
		{
			if (tensor.GetRank() != m_in->GetRank())
			{
				TN_WARNING("NEURALNET", "Wrong new input tensor");
				return;
			}

			for (unsigned int i = 1; i <= tensor.GetRank(); i++)
			{
				if (tensor.GetDimension(i) != m_in->GetDimension(i))
				{
					TN_WARNING("NEURALNET", "Wrong new input tensor");
					return;
				}
			}
		}

		m_in = &tensor;
	}
}

#endif
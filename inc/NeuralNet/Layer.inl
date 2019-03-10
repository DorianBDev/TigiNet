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
	TN::ActivatorConfig<T>::ActivatorConfig(double(&activationFunction)(double))
	{
		m_activationFunction = &activationFunction;
		m_activationFunctionDerivative = NULL;
	}

	/// @private
	template<typename T>
	TN::ActivatorConfig<T>::ActivatorConfig(double(&activationFunction)(double), double(&activationFunctionDerivative)(double))
	{
		m_activationFunction = &activationFunction;
		m_activationFunctionDerivative = &activationFunctionDerivative;
	}

	/// @private
	template<typename T>
	T TN::ActivatorConfig<T>::ActivationFunction(T value)
	{
		return static_cast<T>(m_activationFunction(static_cast<double>(value)));
	}

	/// @private
	template<typename T>
	T TN::ActivatorConfig<T>::ActivationDerivative(T value)
	{
		if (m_activationFunctionDerivative == NULL)
			return static_cast<T>(DerivativeApproximation(*m_activationFunction, static_cast<double>(value)));
		else
			return static_cast<T>(m_activationFunctionDerivative(static_cast<double>(value)));
	}

	/// @private
	template<typename T>
	TN::Layer<T>::Layer(ActivatorConfig<T> & config)
	{
		m_activator = &config;
	}

	/// @private
	template<typename T>
	TN::Layer<T>::~Layer()
	{
		if (m_out != NULL)
			delete m_out;

		if (m_grad != NULL)
			delete m_grad;
	}

	/// @private
	template<typename T>
	void TN::Layer<T>::Link(Layer<T> & layer)
	{
		this->m_in = layer.m_out;
	}

	/// @private
	template<typename T>
	void TN::Layer<T>::Link(Tensor<T> & in)
	{
		this->m_in = &in;
	}
}

#endif
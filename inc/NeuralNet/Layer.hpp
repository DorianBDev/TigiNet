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

#ifndef TN_NEURALNET_LAYER_HPP
#define TN_NEURALNET_LAYER_HPP

#include <NeuralNet/Config.hpp>
#include <Utility/Tensor.hpp>
#include <Utility/Math.hpp>

namespace TN
{

	template<typename T>
	class ActivatorConfig
	{
	public:
		ActivatorConfig(double(&activationFunction)(double));
		ActivatorConfig(double(&activationFunction)(double), double(&activationFunctionDerivative)(double));
		~ActivatorConfig() = default;

		T ActivationFunction(T value);
		T ActivationDerivative(T value);

	private:
		double(*m_activationFunction)(double);
		double(*m_activationFunctionDerivative)(double);
	};

	template<typename T>
	class Layer
	{
	public:
		Layer(ActivatorConfig<T> & config);
		virtual void Activate() = 0;
		virtual void Update() = 0;

	private:
		ActivatorConfig<T>* m_activator = NULL;
		Tensor<T>* m_in = NULL;
		Tensor<T>* m_out = NULL;
	};

}

#include <NeuralNet/Layer.inl>

#endif
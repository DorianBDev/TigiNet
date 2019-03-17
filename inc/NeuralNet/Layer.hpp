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
#include <NeuralNet/Initializer.hpp>
#include <Utility/Tensor.hpp>
#include <Utility/Math.hpp>
#include <Utility/Gradient.hpp>

namespace TN
{
	/**
	* @class ActivatorConfig
	* @brief Define an activator function and possibly his derivative.
	*
	* A class that handle an activator function for use with a layer. If no derivative is passed, it will use approximation.
	*
	* @see Layer
	*
	*/
	template<typename T>
	class ActivatorConfig
	{
	public:

		/**
		* @brief Create an activator config.
		*
		* @param activationFunction : the activator function.
		*
		*/
		ActivatorConfig(double(&activationFunction)(double));

		/**
		* @brief Create an activator config.
		*
		* @param activationFunction : the activator function.
		* @param activationFunctionDerivative : the activator derivative function.
		*
		*/
		ActivatorConfig(double(&activationFunction)(double), double(&activationFunctionDerivative)(double));
		~ActivatorConfig() = default;

		/**
		* @brief Use the activator function.
		*
		* @param value : the value to use with the function.
		*
		* @return Return the result of f(value).
		*
		*/
		T ActivationFunction(T value) const;

		/**
		* @brief Use the activator derivative function.
		*
		* @param value : the value to use with the function.
		*
		* @return Return the result of f'(value).
		*
		*/
		T ActivationDerivative(T value) const;

	private:
		double(*m_activationFunction)(double);
		double(*m_activationFunctionDerivative)(double);
	};

	/**
	* @class Layer
	* @brief Neural network virtual class.
	*
	* This is the base class to create a new Layer type.
	*
	*/
	template<typename T>
	class Layer
	{
	public:

		/**
		* @brief Create a new Layer.
		*
		* @param activator : the activator config.
		* @param initializer : the inializer.
		*
		* @see ActivatorConfig
		* @see Initializer
		*
		*/
		Layer(const ActivatorConfig<T> & activator, const Initializer<T> & initializer);
		~Layer();

		/**
		* @brief Link a layer to this layer.
		*
		* @param layer : the layer to link with.
		*
		*/
		void Link(Layer<T> & layer);

		/**
		* @brief Link an input tensor to this layer.
		*
		* @param in : the input tensor to link with.
		*
		*/
		void Link(Tensor<T> & in);

		/**
		* @brief Forward propagation.
		*
		*/
		virtual void Activate() = 0;

		/**
		* @brief Backward propagation.
		*
		*/
		virtual void Update() = 0;

		/**
		* @brief Get the output tensor of the layer.
		*
		* @return Return the output tensor of the layer.
		*
		*/
		Tensor<T>& GetOutput();

	protected:
		const ActivatorConfig<T>& m_activator;
		const Initializer<T>& m_initializer;
		Tensor<T>* m_in = NULL;
		Tensor<T>* m_out = NULL;
		Tensor<gradient_t<T>>* m_grad = NULL;
		Layer<T>* m_nextLayer = NULL;
	};

}

#include <NeuralNet/Layer.inl>

#endif
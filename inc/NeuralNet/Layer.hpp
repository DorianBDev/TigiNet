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
#include <NeuralNet/Optimizer.hpp>
#include <NeuralNet/Cost.hpp>
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
		T Activation(T value) const;

		/**
		* @brief Use the activator derivative function.
		*
		* @param value : the value to use with the function.
		*
		* @return Return the result of f'(value).
		*
		*/
		T Derivation(T value) const;

		/**
		* @brief Copy an activator config.
		*
		* @return Return a shared pointer of the new activator config copy.
		*
		*/
		std::shared_ptr<ActivatorConfig<T>> Copy() const;

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
		* @param optimizer : the optimizer.
		*
		* @see ActivatorConfig
		* @see Initializer
		* @see Optimizer
		*
		*/
		Layer(const ActivatorConfig<T>& activator, const Initializer<T>& initializer, const Optimizer<T>& optimizer);

		/**
		* @brief Create a new Layer.
		*
		* @param activator : the activator config.
		*
		* @see ActivatorConfig
		*
		*/
		Layer(const ActivatorConfig<T>& activator);

		/**
		* @brief Create a new Layer.
		*
		* @param initializer : the inializer.
		*
		* @see Initializer
		*
		*/
		Layer(const Initializer<T>& initializer);

		/**
		* @brief Create a new Layer.
		*
		* @param optimizer : the optimizer.
		*
		* @see Optimizer
		*
		*/
		Layer(const Optimizer<T>& optimizer);

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
		Layer(const ActivatorConfig<T>& activator, const Initializer<T>& initializer);

		/**
		* @brief Create a new Layer.
		*
		* @param activator : the activator config.
		* @param optimizer : the optimizer.
		*
		* @see ActivatorConfig
		* @see Optimizer
		*
		*/
		Layer(const ActivatorConfig<T>& activator, const Optimizer<T>& optimizer);

		/**
		* @brief Create a new Layer.
		*
		* @param initializer : the inializer.
		* @param optimizer : the optimizer.
		*
		* @see Initializer
		* @see Optimizer
		*
		*/
		Layer(const Initializer<T>& initializer, const Optimizer<T>& optimizer);
		Layer();
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

		/**
		* @brief Get the error of the layer.
		*
		* @return Return the error.
		*
		*/
		double GetError() const;

		/**
		* @brief Get the error of the layer.
		*
		* @param costFunction : the cost function.
		* @param prediction : your prediction.
		* @param result : your expected result.
		*
		* @return Return the error.
		*
		*/
		double GetError(const CostFunction<T>& costFunction, const Tensor<T>& prediction, const Tensor<T>& result);

		/**
		* @brief Get the input gradient of the layer.
		*
		* @return Return the input gradient tensor.
		*
		*/
		Tensor<T>* GetInputGradient();

		/**
		* @brief Change the input tensor by a new one with the same shape.
		*
		* @param tensor : the new input tensor.
		*
		*/
		void ResetInput(Tensor<T>& tensor);

		/**
		* @brief Save the layer in a file.
		*
		* The layer topology need to be exactly the same (pre-linked layer). The function will only save trainable data and not the topology.
		*
		* @param file : the file to save in.
		*
		*/
		virtual void SaveInFile(std::ofstream& file) = 0;

		/**
		* @brief Load the layer from a file.
		*
		* The layer topology need to be exactly the same (pre-linked layer). The function will only load trainable data and not the topology.
		*
		* @param file : the file to load from.
		*
		*/
		virtual void LoadFromFile(std::ifstream& file) = 0;

	protected:
		std::shared_ptr<ActivatorConfig<T>> m_activator = NULL;
		std::shared_ptr<Initializer<T>> m_initializer = NULL;
		std::shared_ptr<Optimizer<T>> m_optimizer = NULL;
		ZeroInitializer<T> m_zeroInitializer;
		Tensor<T>* m_in = NULL; // Input tensor
		Tensor<T>* m_out = NULL; // Output tensor
		Tensor<T>* m_gradIn = NULL; // Input gradients
		Layer<T>* m_nextLayer = NULL;
		Layer<T>* m_previousLayer = NULL;
		double m_error = 0;
	};

}

#include <NeuralNet/Layer.inl>

#endif
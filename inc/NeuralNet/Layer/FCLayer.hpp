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

#ifndef TN_NEURALNET_FCLAYER_HPP
#define TN_NEURALNET_FCLAYER_HPP

#include <NeuralNet/Layer.hpp>

namespace TN
{

	/**
	* @class FCLayer
	* @brief Fully connected layer.
	*
	* Create a fully connected layer.
	*
	* @see Layer
	*
	*/
	template<typename T>
	class FCLayer : public Layer<T>
	{
	public:

		/**
		* @brief Create a Fully connected layer.
		*
		* @param activator : the activator config.
		* @param initializer : the inializer.
		* @param optimizer : the optimizer.
		* @param neuronsCount : the number of neurons for this layer.
		*
		* @see ActivatorConfig
		* @see Initializer
		* @see Optimizer
		*
		*/
		FCLayer(const ActivatorConfig<T> & activator, const Initializer<T> & initializer , const Optimizer<T> & optimizer, unsigned int neuronsCount);
		~FCLayer();

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
		void Activate();

		/**
		* @brief Backward propagation.
		*
		*/
		void Update();

		/**
		* @brief Backward propagation with the expected results (only if the layer is the output one).
		*
		* @param result : expected results.
		* @param costFunction : the cost function.
		*
		* @see CostFunction
		*
		*/
		void Update(Tensor<T>& result, const CostFunction<T>& costFunction);

	private:
		unsigned int m_neuronsCount;
		Tensor<T>* m_weight = NULL; // First parameter
		Tensor<T>* m_bias = NULL; // Second parameter (last)
		Tensor<T>* m_grad = NULL; // Always a vector

	};
}

#include <NeuralNet/Layer/FCLayer.inl>

#endif
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

#ifndef TN_NEURALNET_OPTIMIZER_HPP
#define TN_NEURALNET_OPTIMIZER_HPP

#include <Utility/Gradient.hpp>
#include <Utility/Tensor.hpp>

namespace TN
{

	/**
	* @class Optimizer
	* @brief Virtual class to update variables with corresponding gradients.
	*
	* A pure virtual class to update variables (tensor) with corresponding gradients (tensor).
	*
	*/
	template<typename T>
	class Optimizer
	{
	public:

		/**
		* @brief Update a tensor of variables with his tensor of corresponding gradients.
		*
		* The tensor of variables and the tensor of gradients needs to get the same rank.
		*
		* @param variableTensor : the tensor of variables.
		* @param gradientTensor : the tensor of corresponding gradients.
		*
		*/
		virtual void Update(Tensor<T>& variableTensor, Tensor<gradient_t<T>>& gradientTensor) = 0;
	};

	/**
	* @class StochasticGradientDescent
	* @brief Use the Stochastic Gradient Descent method.
	*
	* Use the SGD method to update a tensor of variables with his tensor of corresponding gradients.
	*
	* @see Optimizer
	*
	*/
	template <typename T>
	class StochasticGradientDescent : public Optimizer<T>
	{
	public:

		/**
		* @brief Create a new SGD object.
		*
		* @param learningRate : the learning rate to use with the SGD method.
		*
		*/
		StochasticGradientDescent(double learningRate = 0.001);

		/**
		* @brief Update a tensor of variables with his tensor of corresponding gradients.
		*
		* The tensor of variables and the tensor of gradients needs to get the same rank.
		*
		* @param variableTensor : the tensor of variables.
		* @param gradientTensor : the tensor of corresponding gradients.
		*
		*/
		void Update(Tensor<T>& variableTensor, Tensor<T>& gradientTensor);

	private:
		Tensor<T>* m_oldGradientTensor = NULL;
		double m_learningRate = 0;
	};
}

#include <NeuralNet/Optimizer.inl>

#endif
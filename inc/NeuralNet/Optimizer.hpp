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
	* @brief Virtual class to update variable with corresponding gradient.
	*
	* A pure virtual class to update a variable with corresponding gradient.
	*
	*/
	template<typename T>
	class Optimizer
	{
	public:

		/**
		* @brief Setup the optimizer with the number of variables per iteration.
		*
		* @param variableCount : the number of variables that the optimizer will treat per iteration.
		*
		*/
		virtual void Setup(unsigned int variableCount);

		/**
		* @brief Update a variable with his corresponding gradient and entry.
		*
		* @param variable : the variable.
		* @param gradient : the corresponding gradient.
		* @param entry : the corresponding entry.
		*
		*/
		virtual void Update(T& variable, T gradient, T entry) = 0;

		/**
		* @brief Copy an optimizer.
		*
		* @return Return a shared pointer of the new optimizer copy.
		*
		*/
		virtual std::shared_ptr<Optimizer<T>> Copy() const = 0;

	protected:
		void UpdateCounter();

		unsigned int m_variableCount = 0;
		unsigned int m_counter = 0;

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
		StochasticGradientDescent(double learningRate = 0.001, double momentum = 0.9);
		~StochasticGradientDescent();

		/**
		* @brief Setup the optimizer with the number of variables per iteration.
		*
		* @param variableCount : the number of variables that the optimizer will treat per iteration.
		*
		*/
		void Setup(unsigned int variableCount);

		/**
		* @brief Update a variable with his corresponding gradient and entry.
		*
		* @param variable : the variable.
		* @param gradient : the corresponding gradient.
		* @param entry : the corresponding entry.
		*
		*/
		void Update(T& variable, T gradient, T entry);

		/**
		* @brief Copy an optimizer.
		*
		* @return Return a shared pointer of the new optimizer copy.
		*
		*/
		std::shared_ptr<Optimizer<T>> Copy() const;

	private:
		double m_learningRate;
		double m_momentum;
		Tensor<T>* m_oldDelta = NULL;
	};
}

#include <NeuralNet/Optimizer.inl>

#endif
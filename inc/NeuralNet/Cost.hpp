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

#ifndef TN_NEURALNET_COST_HPP
#define TN_NEURALNET_COST_HPP

#include <Utility/Tensor.hpp>

namespace TN
{
	/**
	* @class CostFunction
	* @brief This virtual class hold a cost function and its derivative.
	*
	* A pure virtual class that handle a cost function and its derivative.
	*
	*/
	template<typename T>
	class CostFunction
	{
	public:

		/**
		* @brief Calculate error.
		*
		* @param prediction : your prediction.
		* @param result : your expected result.
		*
		* @return Return the error.
		*
		*/
		virtual T Activation(const T& prediction, const T& result) const = 0;

		/**
		* @brief Calculate error from tensors.
		*
		* @param prediction : your prediction.
		* @param result : your expected result.
		*
		* @return Return the error.
		*
		*/
		virtual T Activation(const Tensor<T>& prediction, const Tensor<T>& result) const = 0;

		/**
		* @brief Measures the importance of a prediction in the error.
		*
		* @param prediction : your prediction.
		* @param result : your expected result.
		*
		* @return Return the measurement.
		*
		*/
		virtual T Derivation(const T& prediction, const T& result) const = 0;
	};

	/**
	* @class MeanSquaredError
	* @brief MSE cost function class.
	*
	* MSE : 1/2(sum(pow(prediction - result))
	*
	*/
	template<typename T>
	class MeanSquaredError : public CostFunction<T>
	{
	public:

		/**
		* @brief Calculate error.
		*
		* @param prediction : your prediction.
		* @param result : your expected result.
		*
		* @return Return the error.
		*
		*/
		T Activation(const T& prediction, const T& result) const;

		/**
		* @brief Calculate error from tensors.
		*
		* @param prediction : your prediction.
		* @param result : your expected result.
		*
		* @return Return the error.
		*
		*/
		T Activation(const Tensor<T>& prediction, const Tensor<T>& result) const;

		/**
		* @brief Measures the importance of a prediction in the error.
		*
		* @param prediction : your prediction.
		* @param result : your expected result.
		*
		* @return Return the measurement.
		*
		*/
		T Derivation(const T& prediction, const T& result) const;
	};
}

#include <NeuralNet/Cost.inl>

#endif
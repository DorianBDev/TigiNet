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

#ifndef TN_UTILITY_MATH_HPP
#define TN_UTILITY_MATH_HPP

#include <Utility/Config.hpp>
#include <Utility/Tensor.hpp>

#include <random>

namespace TN
{

	/**
	* @brief Approximation of the derivative of a certain function.
	*
	* @param function : the fonction.
	* @param value : the value.
	*
	* @return Return the result.
	*
	*/
	TN_UTILITY double DerivativeApproximation(double(&function)(double), double value);

	/**
	* @brief The Sigmoide function.
	*
	* @param value : the value.
	*
	* @return Return the result.
	*
	*/
	TN_UTILITY double Sigmoide(double value);

	/**
	* @brief The Sigmoide derivative function.
	*
	* @param value : the value.
	*
	* @return Return the result.
	*
	*/
	TN_UTILITY double SigmoideDerivative(double value);

	/**
	* @brief The Tangente function.
	*
	* @param value : the value.
	*
	* @return Return the result.
	*
	*/
	TN_UTILITY double Tangente(double value);

	/**
	* @brief The Heaviside function.
	*
	* @param value : the value.
	*
	* @return Return the result.
	*
	*/
	TN_UTILITY double Heaviside(double value);

	/**
	* @brief Matrix product function.
	*
	* @param tensor1 : the first tensor.
	* @param tensor2 : the second tensor.
	*
	* @return Return the result in a new tensor (dynamic allocation).
	*
	*/
	template<typename T>
	TN::Tensor<T>* MatrixProduct(const TN::Tensor<T> & tensor1, const TN::Tensor<T> & tensor2);

	/**
	* @brief Get a random number.
	*
	* @param min : the first minimum boundary.
	* @param max : the second maximum boundary.
	*
	* @return Return the random result between [a,b].
	*
	*/
	template<typename T, typename G = std::mt19937>
	T Random(T min, T max);
}

#include <Utility/Math.inl>

#endif
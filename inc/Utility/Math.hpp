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

namespace TN
{

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

}

#endif
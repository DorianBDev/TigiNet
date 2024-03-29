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

#ifndef TN_UTILITY_GRADIENT_HPP
#define TN_UTILITY_GRADIENT_HPP

#include <Utility/Config.hpp>

namespace TN
{

	/**
	* @struct gradient_t
	* @brief Gradient type.
	*
	* This is the base type for gradient, hold actual and old gradients.
	*
	*/
	template <typename T>
	struct gradient_t
	{
		T actual;
		T old;
		gradient_t()
		{
			actual = 0;
			old = 0;
		}
	};
}

#endif
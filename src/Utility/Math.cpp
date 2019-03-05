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

#include <Utility/Math.hpp>

#include <math.h>

double TN::Sigmoide(double value)
{
	return (double)1 / ((double)1 + exp((double)-1 * value));
}

double TN::Tangente(double value)
{
	return 1.7159 * tanh((2 / 3) * value);
}

double TN::Heaviside(double value)
{
	if (value >= (double)0)
		return (double)1;
	else
		return (double)0;
}
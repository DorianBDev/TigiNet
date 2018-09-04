/**
*
*   TIGINET
*   Copyright (C) 2018  BACHELOT Dorian
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

#include <Core/Error.hpp>
#include <Core/Log.hpp>

#include <cstdlib>
#include <stdio.h>

void TN::Error::Send(ErrorType_e errorType, const char* message, unsigned int line, const char* file, const char* function, ...)
{
	va_list _va;
	char * _res;

	va_start(_va, function);
	va_list _vab;
	va_copy(_vab, _va);
	int _size = vsnprintf(NULL, 0, message, _vab);
	va_end(_vab);

	_res = new char[_size + 1];

	vsnprintf(_res, _size + 1, message, _va);
	va_end(_va);

	switch (errorType)
	{
	default:
		goto WARNING;
		break;

	case ET_ERROR:

		TN_LOGGER.Print("ERROR", "(In file '%s' in function '%s' in line '%d') %s", file, function, line, _res);

		std::exit(-1);
		break;

	case ET_ASSERTION_FAILED:

		TN_LOGGER.Print("ASSERT ERROR", "(In file '%s' in function '%s' in line '%d') %s", file, function, line, _res);

		std::exit(-1);
		break;

	case ET_WARNING:
		WARNING:

		TN_LOGGER.Print("WARNING", "(In file '%s' in function '%s' in line '%d') %s", file, function, line, _res);

		break;
	}

	delete[] _res;

}
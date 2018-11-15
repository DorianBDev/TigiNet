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

void TN::Error::Send(ErrorType_e errorType, String message, unsigned int line, const char* file, const char* function, ...)
{
	va_list vaList;
	char * finalMessage;

	va_start(vaList, function);
	va_list vaListBis;
	va_copy(vaListBis, vaList);
	int size = vsnprintf(NULL, 0, message.ToCString(), vaListBis);
	va_end(vaListBis);

	finalMessage = new char[size + 1];

	vsnprintf(finalMessage, size + 1, message.ToCString(), vaList);
	va_end(vaList);

	switch (errorType)
	{
	default:
		goto WARNING;
		break;

	case ET_ERROR:

		#if TN_DEBUG
		TN_LOGGER.Print("ERROR", "(In file '%s' in function '%s' in line '%d') %s", file, function, line, finalMessage);
		#else
		TN_LOGGER.Print("ERROR", finalMessage);
		#endif

		std::exit(-1);
		break;

	case ET_ABORT:

		#if TN_DEBUG
		TN_LOGGER.Print("ABORT", "(In file '%s' in function '%s' in line '%d') %s", file, function, line, finalMessage);
		#else
		TN_LOGGER.Print("ABORT", finalMessage);
		#endif

		std::abort();
		break;

	case ET_ASSERTION_FAILED:

		#if TN_DEBUG
		TN_LOGGER.Print("ASSERT ERROR", "(In file '%s' in function '%s' in line '%d') %s", file, function, line, finalMessage);
		#else
		TN_LOGGER.Print("ASSERT ERROR", finalMessage);
		#endif

		std::exit(-1);
		break;

	case ET_WARNING:
		WARNING:

		#if TN_DEBUG
		TN_LOGGER.Print("WARNING", "(In file '%s' in function '%s' in line '%d') %s", file, function, line, finalMessage);
		#else
		TN_LOGGER.Print("WARNING", finalMessage);
		#endif

		break;
	}

	delete[] finalMessage;

}
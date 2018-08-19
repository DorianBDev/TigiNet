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

void TN::Error::Send(ErrorType_e errorType, const char* message, unsigned int line, const char* file, const char* function, ...)
{
	va_list _va;

	switch (errorType)
	{
	default:
		goto WARNING;
		break;

	case ET_ERROR:

		va_start(_va, function);
		TN_LOGGER.PrintConsole("ERROR", "(In file '%s' in function '%s' in line '%d') %s", file, function, line, message, _va);
		va_end(_va);

		va_start(_va, function);
		TN_LOGGER.PrintFile("ERROR", "(In file '%s' in function '%s' in line '%d') %s", file, function, line, message, _va);
		va_end(_va);

		std::abort();
		break;

	case ET_ASSERTION_FAILED:

		va_start(_va, function);
		TN_LOGGER.PrintConsole("ASSERT ERROR", "(In file '%s' in function '%s' in line '%d') %s", file, function, line, message, _va);
		va_end(_va);

		va_start(_va, function);
		TN_LOGGER.PrintFile("ASSERT ERROR", "(In file '%s' in function '%s' in line '%d') %s", file, function, line, message, _va);
		va_end(_va);

		std::abort();
		break;

	case ET_WARNING:
		WARNING:

		va_start(_va, function);
		TN_LOGGER.PrintConsole("WARNING", "(In file '%s' in function '%s' in line '%d') %s", file, function, line, message, _va);
		va_end(_va);

		va_start(_va, function);
		TN_LOGGER.PrintFile("WARNING", "(In file '%s' in function '%s' in line '%d') %s", file, function, line, message, _va);
		va_end(_va);

		break;
	}

}
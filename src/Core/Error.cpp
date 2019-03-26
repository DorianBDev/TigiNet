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

#include <Core/Error.hpp>

TN::TigiNetLogger& TN::Error::Send(ErrorType_e errorType, const char* moduleName, unsigned int line, const char* file, const char* function, const char* message)
{
	switch (errorType)
	{
	default:
		goto WARNING;
		break;

	case ET_ERROR:

#if TN_DEBUG
		TN::TigiNetLogger::GetInstance() << std::endl << TN::GetLogHeader(moduleName, "ERROR") << "(In file '" << file << "' in function '" << function << "' in line '" << line << "') " << message;
#else
		TN::TigiNetLogger::GetInstance() << std::endl << TN::GetLogHeader(moduleName, "ERROR") << message;
#endif

		std::exit(-1);
		break;

	case ET_ABORT:

#if TN_DEBUG
		TN::TigiNetLogger::GetInstance() << std::endl << TN::GetLogHeader(moduleName, "ABORT") << "(In file '" << file << "' in function '" << function << "' in line '" << line << "') " << message;
#else
		TN::TigiNetLogger::GetInstance() << std::endl << TN::GetLogHeader(moduleName, "ABORT") << message;
#endif

		std::abort();
		break;

	case ET_ASSERTION_FAILED:

#if TN_DEBUG
		TN::TigiNetLogger::GetInstance() << std::endl << TN::GetLogHeader(moduleName, "ASSERT ERROR") << "(In file '" << file << "' in function '" << function << "' in line '" << line << "') " << message;
#else
		TN::TigiNetLogger::GetInstance() << std::endl << TN::GetLogHeader(moduleName, "ASSERT ERROR") << message;
#endif

		std::exit(-1);
		break;

	case ET_WARNING:
	WARNING:

#if TN_DEBUG
		TN::TigiNetLogger::GetInstance() << std::endl << TN::GetLogHeader(moduleName, "WARNING") << "(In file '" << file << "' in function '" << function << "' in line '" << line << "') " << message;
#else
		TN::TigiNetLogger::GetInstance() << std::endl << TN::GetLogHeader(moduleName, "WARNING") << message;
#endif

		break;
	}

	return TigiNetLogger::GetInstance();
}
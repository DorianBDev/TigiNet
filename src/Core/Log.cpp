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

#define _CRT_SECURE_NO_WARNINGS 1

#include <Core/Log.hpp>

#include <ctime>
#include <iomanip>

TN::Logger::Logger(std::ostream* stream)
	: m_stream(stream)
{
	m_open = true;
}

TN::FileLogger::FileLogger(const std::string & path)
	: m_file(new std::fstream(path, std::fstream::out | std::fstream::trunc)), Logger()
{
	this->m_open = m_file->is_open();
	Logger::m_stream = m_file;

	if (this->m_open)
	{
		*m_file << GetLogHeader("CORE", "INFO") << "BEGIN FILE LOGGING";
		*m_file << std::endl << GetLogHeader("CORE", "INFO") << "----------";
	}
}

TN::FileLogger::~FileLogger()
{
	if (this->m_open)
	{
		(*this) << std::endl << GetLogHeader("CORE", "INFO") << "----------";
		(*this) << std::endl << GetLogHeader("CORE", "INFO") << "END FILE LOGGING" << std::endl;
		m_file->close();
	}

	delete m_file;
}

TN::ConsoleLogger::ConsoleLogger()
	: Logger(&std::cout)
{
	(*this) << GetLogHeader("CORE", "INFO") << "BEGIN CONSOLE LOGGING";
	(*this) << std::endl << GetLogHeader("CORE", "INFO") << "----------";
}

TN::ConsoleLogger::~ConsoleLogger()
{
	(*this) << std::endl << GetLogHeader("CORE", "INFO") << "----------";
	(*this) << std::endl << GetLogHeader("CORE", "INFO") << "END CONSOLE LOGGING" << std::endl;
}

TN::TigiNetLogger::TigiNetLogger()
	: ConsoleLogger(), FileLogger("TigiNet.log")
{

}

TN::TigiNetLogger::~TigiNetLogger()
{
	if (m_mutex.IsLock())
		m_mutex.Unlock();
}

std::string TN::GetLogHeader(const char* mod, const char* type)
{
	std::string res;

	std::time_t     now = time(NULL);
	char			buf[80];

	strftime(buf, sizeof(buf), "%Y-%m-%d %X", localtime(&now));
	
	res = buf;
	res += " - [";
	res += type;
	res += "] [";
	res += mod;
	res += "] : ";

	return res;
}
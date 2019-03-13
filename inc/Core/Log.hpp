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

#ifndef TN_CORE_LOG_HPP
#define TN_CORE_LOG_HPP

#include <Core/Config.hpp>
#include <Core/Singleton.hpp>
#include <Core/Mutex.hpp>

#include <iostream>
#include <fstream>
#include <string>

/**
* @brief Write a message in the log.
*
* @param mod : the module name where come the log.
*
*/
#define TN_LOG(mod) TN::TigiNetLogger::GetInstance() << std::endl << TN::GetLogHeader(mod, "INFO")


namespace TN
{

	/**
	* @brief Get the TigiNet default log header.
	*
	* @param mod : the module name.
	* @param type : the log type.
	*
	* @return Return the log header.
	*
	*/
	TN_CORE std::string GetLogHeader(const char* mod, const char* type);


	/**
	* @class Logger
	* @brief Logger class.
	*
	* A simple logger.
	*
	*/
	class TN_CORE Logger
	{

	public:

		/**
		* @brief Logger constructor.
		*
		* @param stream : the log stream.
		*
		*/
		Logger(std::ostream* stream);
		Logger() = default;
		~Logger() = default;

		inline Logger& operator<<(std::ostream& (*arg)(std::ostream&))
		{
			if (m_open)
				(*m_stream) << arg;

			return (*this);
		}

		template<class T>
		Logger& operator<<(const T & arg)
		{
			if(m_open)
				(*m_stream) << arg;

			return (*this);
		}

	protected:

		std::ostream* m_stream;
		bool m_open = false;
	};


	/**
	* @class FileLogger
	* @brief A file logger class.
	*
	* Log in a file with std::ofstream.
	*
	*/
	class TN_CORE FileLogger : public Logger
	{
	public:

		/**
		* @brief File logger constructor.
		*
		* @param path : the path of the file stream.
		*
		*/
		FileLogger(const std::string & path);
		~FileLogger();

	private:
		std::fstream* m_file;

	};


	/**
	* @class ConsoleLogger
	* @brief A console logger class.
	*
	* Log in the console with std::cout.
	*
	*/
	class TN_CORE ConsoleLogger : public Logger
	{
	public:

		/**
		* @brief Console logger constructor.
		*
		*/
		ConsoleLogger();
		~ConsoleLogger();

	};


	/**
	* @class TigiNetLogger
	* @brief The default TigiNet logger class.
	*
	* Log in the console and in a file.
	*
	*/
	class TN_CORE TigiNetLogger : public FileLogger, public ConsoleLogger, public Singleton<TigiNetLogger>
	{
		friend class Singleton<TigiNetLogger>;

	public:

		/**
		* @brief TigiNet logger constructor.
		*
		*/
		TigiNetLogger();
		~TigiNetLogger();

		inline TigiNetLogger& operator<<(std::ostream& (*arg)(std::ostream&))
		{
#if TN_THREAD_SAFE
			LockGuard lock(&m_mutex);
#endif

			if (FileLogger::m_open)
				(*FileLogger::m_stream) << arg;

			if(ConsoleLogger::m_open)
				(*ConsoleLogger::m_stream) << arg;

			return (*this);
		}

		template<class T>
		TigiNetLogger& operator<<(const T & arg)
		{
#if TN_THREAD_SAFE
			LockGuard lock(&m_mutex);
#endif

			if (FileLogger::m_open)
				(*FileLogger::m_stream) << arg;

			if (ConsoleLogger::m_open)
				(*ConsoleLogger::m_stream) << arg;

			return (*this);
		}

	private:
		Mutex m_mutex;
	};

}

#endif
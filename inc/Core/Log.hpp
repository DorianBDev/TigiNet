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
#include <Core/File.hpp>
#include <Core/String.hpp>
#include <Core/Singleton.hpp>
#include <Core/Mutex.hpp>

#include <stdarg.h>


/**
* @brief Get the logger.
*
*/
#define TN_LOGGER TN::Logger()

/**
* @brief Write a message in the log.
*
* @param msg : the message to write.
*
*/
#define TN_LOG(msg, ...) TN::Log::GetInstance().Write(msg, ## __VA_ARGS__);

/**
* @brief Write a message in the console.
*
* @param msg : the message to write.
*
*/
#define TN_LOG_CONSOLE(msg, ...) TN::Log::GetInstance().PrintConsole("INFO", msg, ## __VA_ARGS__);

/**
* @brief Write a message in the log file.
*
* @param msg : the message to write.
*
*/
#define TN_LOG_FILE(msg, ...) TN::Log::GetInstance().PrintFile("INFO", msg, ## __VA_ARGS__);


namespace TN
{

	/**
	* @class Log
	* @brief Log class.
	*
	* A simple logger.
	*
	*/
	class TN_CORE Log : public Singleton<Log>
	{
		friend class Singleton<Log>;

	public:

		/**
		* @brief Print a log, in console and in file.
		*
		* @param messageType : the type of the message (e.g. INFO or WARNING...).
		* @param message : the message.
		*
		*/
		void Print(String messageType, String message, ...);

		/**
		* @brief Print a log, in console and in file.
		*
		* @param messageType : the type of the message (e.g. INFO or WARNING...).
		* @param message : the message.
		* @param va : list of arguments.
		*
		*/
		void Print(String messageType, String message, va_list va);

		/**
		* @brief Print in a file.
		*
		* @param messageType : the type of the message (e.g. INFO or WARNING...).
		* @param message : the message.
		*
		*/
		void PrintFile(String messageType, String message, ...);

		/**
		* @brief Print in a file.
		*
		* @param messageType : the type of the message (e.g. INFO or WARNING...).
		* @param message : the message.
		* @param va : list of arguments.
		*
		*/
		void PrintFile(String messageType, String message, va_list va);

		/**
		* @brief Print in the console.
		*
		* @param messageType : the type of the message (e.g. INFO or WARNING...).
		* @param message : the message.
		*
		*/
		void PrintConsole(String messageType, String message, ...);

		/**
		* @brief Print in the console.
		*
		* @param messageType : the type of the message (e.g. INFO or WARNING...).
		* @param message : the message.
		* @param va : list of arguments.
		*
		*/
		void PrintConsole(String messageType, String message, va_list va);

		/**
		* @brief Write a message in log.
		*
		* @param message : the message.
		*
		*/
		void Write(String message, ...);


	private:

		Log();
		~Log();

		String Form(String messageType, String message, bool endl);

		File * m_pFile = NULL;

		Mutex m_fileMutex;
		Mutex m_consoleMutex;

		bool m_fileReady = false;
	};

	/**
	* @brief Get the logger instance.
	*
	* @return Return the logger instance.
	*
	*/
	inline Log& Logger()
	{
		return Log::GetInstance();
	}
}

#endif
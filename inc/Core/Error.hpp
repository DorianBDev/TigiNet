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

#ifndef TN_CORE_ERROR_HPP
#define TN_CORE_ERROR_HPP

#include <Core/Config.hpp>
#include <Core/Log.hpp>

/**
* @brief Test an expression and send error if the expression is false.
*
* @param test : the expression to test.
* @param mod : the module name where come the assertion.
* @param message : the message to send with error.
*
*/
#if TN_ENABLE_ASSERT
#define TN_ASSERT(test, mod, message) if(!(test)) TN::Error::Send(TN::ErrorType_e::ET_ASSERTION_FAILED, mod, TN_LINE_NUMBER, TN_FILE_PATH, TN_FUNCTION_NAME, message)
#else
#define TN_ASSERT(test, mod, message)
#endif

/**
* @brief Send an error with his message.
*
* @param mod : the module name where come the error.
* @param message : the message to send with error.
*
*/
#define TN_ERROR(mod, message) TN::Error::Send(TN::ErrorType_e::ET_ERROR, mod, TN_LINE_NUMBER, TN_FILE_PATH, TN_FUNCTION_NAME, message) 

/**
* @brief Send an error with his message and abort.
*
* @param mod : the module name where come the abort.
* @param message : the message to send with error.
*
*/
#if TN_ENABLE_ABORT
#define TN_ABORT(mod, message) TN::Error::Send(TN::ErrorType_e::ET_ABORT, mod, TN_LINE_NUMBER, TN_FILE_PATH, TN_FUNCTION_NAME, message) 
#else
#define TN_ABORT(mod, message) TN::Error::Send(TN::ErrorType_e::ET_ERROR, mod, TN_LINE_NUMBER, TN_FILE_PATH, TN_FUNCTION_NAME, message) 
#endif

/**
* @brief Send a warning with his message.
*
* @param mod : the module name where come the warning.
* @param message : the message to send with warning.
*
*/
#if TN_ENABLE_WARNING
#define TN_WARNING(mod, message) TN::Error::Send(TN::ErrorType_e::ET_WARNING, mod, TN_LINE_NUMBER, TN_FILE_PATH, TN_FUNCTION_NAME, message) 
#else
#define TN_WARNING(mod, message)
#endif


namespace TN
{
	/*! Error types */
	typedef enum __error_type_e
	{
		ET_ERROR,				/*!< For error */
		ET_ASSERTION_FAILED,	/*!< For assertion failed, if enable */
		ET_ABORT,				/*!< For error with abortion */
		ET_WARNING				/*!< For warning */
	}ErrorType_e;

	/**
	* @class Error
	* @brief To manage errors easily.
	*
	*/
	class TN_CORE Error
	{
	public:
		Error() = delete;
		~Error() = delete;

		/**
		* @brief Send an error.
		*
		* @param errorType : the error type see ErrorType_e for more.
		* @param moduleName : the module name where come the error.
		* @param line : the line of the error (use TN_LINE_NUMBER).
		* @param file : the file path where the error is (use TN_FILE_PATH).
		* @param function : the function name where the error is (use TN_FUNCTION_NAME).
		*
		*/
		static TigiNetLogger& Send(ErrorType_e errorType, const char* moduleName, unsigned int line, const char* file, const char* function, const char* message = "");
	};
}

#endif
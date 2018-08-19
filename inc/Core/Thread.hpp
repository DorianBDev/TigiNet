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

#ifndef TN_CORE_THREAD_HPP
#define TN_CORE_THREAD_HPP

#include <Core/Config.hpp>
#include <Core/Functor.hpp>

namespace TN
{

	/**
	* @class Thread
	* @brief Create and manage a thread.
	*
	* To create a thread and manage him like a std::thread.
	*
	*/
	class TN_CORE Thread
	{
	public:

		/**
		* @brief Thread constructor with no argument.
		*
		*/
		Thread();

		/**
		* @brief Thread constructor with function without argument.
		*
		* @param function : the function.
		*
		*/
		template<typename F>
		Thread(F function);

		/**
		* @brief Thread constructor with function and his arguments.
		*
		* @param function : the function.
		* @param args : arguments.
		*
		*/
		template<typename F, typename... Args>
		Thread(F function, Args&&... args);

		/**
		* @brief Thread constructor with name, function and function arguments.
		*
		* @param name : the thread name.
		* @param function : the function.
		* @param args : arguments.
		*
		*/
		template<typename F, typename... Args>
		Thread(char* name, F function, Args&&... args);

		~Thread();

		/**
		* @brief Checks if the thread object identifies an active thread of execution.
		*
		*/
		bool IsJoinable();

		/**
		* @brief Separates the thread of execution from the thread object, allowing execution to continue independently. Any allocated resources will be freed once the thread exits.
		*
		*/
		void Detach();

		/**
		* @brief Block the execution thread and wait this thread to finish.
		*
		*/
		void Join();

		/**
		* @brief Get the thread ID (size_t).
		*
		*/
		size_t GetID();

		/**
		* @brief Set the thread name
		*
		* @param name : the thread name.
		*
		*/
		void SetName(char* name);

	private:

		void CreateThread(AFunctor * functor);

		void* m_thread;
		char* m_name;
		size_t m_id;

	};
}

#include <Core/Thread.inl>

#endif
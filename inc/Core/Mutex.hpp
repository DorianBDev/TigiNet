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

#ifndef TN_CORE_MUTEX_HPP
#define TN_CORE_MUTEX_HPP

#include <Core/Config.hpp>

namespace TN
{

	/**
	* @class Mutex
	* @brief Protect shared data from being simultaneously accessed by multiple threads.
	*
	* To create make a function thread safe, lock the execution to only one thread per time, care with exception : without LockGuard any exception can make a mutex stuck indefinitely.
	*
	* Example :
	* @code
	* mutex.Lock();
	* // Your code thread safe here, but without exception safe
	* mutex.Unlock();
	* @endcode
	*
	* @see Thread
	*
	*/
	class TN_CORE Mutex
	{
	public:

		/**
		* @brief Mutex constructor.
		*
		*/
		Mutex();
		~Mutex();

		/**
		* @brief Lock a mutex.
		*
		* Lock the mutex and block other thread until Unlock.
		*
		* @see Unlock
		*
		*/
		void Lock();

		/**
		* @brief Tries to lock the mutex.
		*
		* @return true if lock sucess, false otherwise.
		*
		*/
		bool TryLock();

		/**
		* @brief Unlock a mutex.
		*
		* Unlock the mutex and deblock other thread (they can continue their execution).
		*
		*/
		void Unlock();

		/**
		* @brief Is the mutex locked ?
		*
		* @return Return true if the mutex is locked or false if isn't.
		*
		*/
		bool IsLock();

	private:


		void* m_mutex;

		bool m_isLock = false;

	};

	/**
	* @class LockGuard
	* @brief To make a function thread safe and manage exception.
	*
	* The class LockGuard is a Mutex wrapper that provides a convenient RAII-style mechanism for owning a Mutex for the duration of a scoped block.
	*
	* Example :
	* @code
	* TN::LockGuard lockGuard(&mutex);
	* // Your thread safe code here
	* @endcode
	*
	* @see Mutex
	*
	*/
	class TN_CORE LockGuard
	{
	public:

		/**
		* @brief LockGuard constructor.
		*
		* @param mutex : The mutex to lock and guard against exceptions.
		*
		*/
		LockGuard(Mutex * mutex);

		~LockGuard();

	private:

		void* m_mutex;
	};
}

#endif
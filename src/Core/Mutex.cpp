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

#include <Core/Mutex.hpp>

#include <mutex>

#define M_STDMUTEX static_cast<std::mutex*>(m_mutex)
#define M_MUTEX static_cast<Mutex*>(m_mutex)

TN::Mutex::Mutex()
{
	m_mutex = new std::mutex();
}

TN::Mutex::~Mutex()	// No force unlock.
{
	delete M_STDMUTEX;
}

void TN::Mutex::Lock()
{
	M_STDMUTEX->lock();
	m_isLock = true;
}

bool TN::Mutex::TryLock()
{
	bool res = M_STDMUTEX->try_lock();

	if (res)
		m_isLock = true;

	return res;
}

void TN::Mutex::Unlock()
{
	M_STDMUTEX->unlock();
	m_isLock = false;
}

bool TN::Mutex::IsLock()
{
	return m_isLock;
}

TN::LockGuard::LockGuard(Mutex * mutex)
{
	m_mutex = mutex;
	M_MUTEX->Lock();
}

TN::LockGuard::~LockGuard()
{
	M_MUTEX->Unlock();
}
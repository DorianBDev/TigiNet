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

#include <Core/Thread.hpp>

#include <thread>

#define M_THREAD static_cast<std::thread*>(m_thread)

TN::Thread::Thread()
{
	m_thread = new std::thread();
	m_id = GetID();
}

TN::Thread::~Thread()
{
	M_THREAD->~thread();
}

bool TN::Thread::IsJoinable()
{
	return M_THREAD->joinable();
}

void TN::Thread::Detach()
{
	M_THREAD->detach();
}

void TN::Thread::Join()
{
	M_THREAD->join();
}

size_t TN::Thread::GetID()
{
	return std::hash<std::thread::id>()(M_THREAD->get_id());
}

void TN::Thread::SetName(char* name)
{
	m_name = name;
}

void TN::Thread::CreateThread(AFunctor * functor)
{
	m_thread = new std::thread(&AFunctor::Run, functor);
}
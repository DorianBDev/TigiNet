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

#include <utility>

namespace TN
{
	template<typename F>
	TN::Thread::Thread(F function)
	{
		CreateThread(new TN::Functor<F>(function));
		m_id = GetID();
	}

	template<typename F, typename... Args>
	TN::Thread::Thread(F function, Args&&... args)
	{
		CreateThread(new TN::Functor<F, Args...>(function, std::forward<Args>(args)...));
		m_id = GetID();
	}

	template<typename F, typename... Args>
	TN::Thread::Thread(char* name, F function, Args&&... args)
	{
		m_name = name;
		CreateThread(new TN::Functor<F, Args...>(function, std::forward<Args>(args)...));
		m_id = GetID();
	}
}
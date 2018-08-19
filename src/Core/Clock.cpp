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

#include <Core/Clock.hpp>

#include <chrono>

TN::Clock::Clock(ClockPrecision_e clockPrecision)
{
	m_timeStart = GetActualTime(clockPrecision);
	m_stop = false;
	m_clockPrecision = clockPrecision;
}

TN::Clock::~Clock()
{

}

void TN::Clock::Start()
{
	m_timeStart = GetActualTime(m_clockPrecision);
	m_stop = false;
}

void TN::Clock::Stop()
{
	m_timeEnd = GetActualTime(m_clockPrecision);
	m_stop = true;
}

long long TN::Clock::GetElapsedTime()
{
	if (m_stop)
		return m_timeEnd - m_timeStart;
	else
		return GetActualTime(m_clockPrecision) - m_timeStart;
}

long long TN::GetActualTime(ClockPrecision_e clockPrecision)
{
	switch (clockPrecision)
	{
	case CP_HOURS:
		return static_cast<long long>(std::chrono::duration_cast<std::chrono::hours>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		break;

	case CP_MINUTES:
		return static_cast<long long>(std::chrono::duration_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		break;

	case CP_SECONDS:
		return static_cast<long long>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		break;

	case CP_MILLISECONDS:
		return static_cast<long long>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		break;

	case CP_MICROSECONDS:
		return static_cast<long long>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		break;

	case CP_NANOSECONDS:
		return static_cast<long long>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		break;

	default:
		return static_cast<long long>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		break;
	}
}
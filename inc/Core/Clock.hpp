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

#ifndef TN_CORE_CLOCK_HPP
#define TN_CORE_CLOCK_HPP

#include <Core/Config.hpp>

namespace TN
{

	/*! Clock precision */
	typedef enum __clock_precision_e
	{
		CP_HOURS,			/*!< Hours precision */
		CP_MINUTES,			/*!< Minutes precision */
		CP_SECONDS,			/*!< Seconds precision */
		CP_MILLISECONDS,	/*!< Milliseconds precision */
		CP_MICROSECONDS,	/*!< microseconds precision */
		CP_NANOSECONDS		/*!< nanoseconds precision */
	}ClockPrecision_e;

	/**
	* @class Clock
	* @brief Clock class.
	*
	* A simple clock.
	*
	*/
	class TN_CORE Clock
	{

	public:

		/**
		* @brief The clock constructor.
		*
		* @param clockPrecision : the precision of the clock.
		*
		* @see ClockPrecision_e
		*
		*/
		Clock(ClockPrecision_e clockPrecision);
		~Clock();

		/**
		* @brief Start the clock
		*
		*/
		void Start();
		
		/**
		* @brief Stop the clock
		*
		*/
		void Stop();

		/**
		* @brief Get the elapsed time between the Start and Stop calls.
		*
		* @return Return the elapsed time.
		*
		*/
		long long GetElapsedTime();

	private:
		long long m_timeStart;
		long long m_timeEnd;
		bool m_stop;
		ClockPrecision_e m_clockPrecision;

	};

	/**
	* @brief Get the actual time.
	*
	* @param clockPrecision : clock precision.
	*
	* @return Return the actual time.
	*
	* @see ClockPrecision_e
	*
	*/
	TN_CORE long long GetActualTime(ClockPrecision_e clockPrecision);
}

#endif
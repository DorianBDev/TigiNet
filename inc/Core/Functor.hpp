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

#ifndef TN_CORE_FUNCTOR_HPP
#define TN_CORE_FUNCTOR_HPP

#include <Core/Config.hpp>

#include <tuple>

namespace TN
{

	/**
	* @class AFunctor
	* @brief Functor virtual class.
	*
	* The virtual class to create a functor.
	*
	*/
	class TN_CORE AFunctor
	{
	public:

		inline virtual ~AFunctor() {};

		virtual void Run() = 0;
	};

	/**
	* @class Functor
	* @brief Store and call a function.
	*
	* Store a function with his arguments (or not) and allow the function to be call with all stored arguments with the Run function.
	*
	* @see Run
	*
	*/
	template<typename F, typename... Args>
	class Functor : public AFunctor
	{
	public:

		/**
		* @brief Functor constructor.
		*
		* @param function : the function.
		* @param args : arguments.
		*
		*/
		Functor(F function, Args&&... args);

		~Functor() override = default;

		/**
		* @brief Run the function with all the arguments stored.
		*
		*/
		void Run() override;


	private:

		F m_function;
		std::tuple<Args...> m_args;
	};
}

#include <Core/Functor.inl>


namespace TN
{
	/**
	* @brief Call a function with his turple (list of arguments).
	*
	* @param function : the function.
	* @param args : turple.
	*
	* @return the function result.
	*
	*/
	#if !(TN_CPP14)
		template<typename F, typename Tuple>
		auto Apply(F function, Tuple args) -> decltype(ApplyImplFunc(function, args, std::declval<typename CallIndices<Tuple>::type>()));
	#else
		template<typename F, typename Tuple>
		decltype(auto) Apply(F&& function, Tuple&& tuple);
	#endif
}

#endif
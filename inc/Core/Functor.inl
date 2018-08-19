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

#include <tuple>
#include <utility>

namespace TN
{

#if !(TN_CPP14)

	/// @private
	template<unsigned... Indices>
	struct IndexSeq 
	{
		template<unsigned N> using append = IndexSeq<Indices..., N>;
	};

	/// @private
	template<unsigned Size>
	struct MakeIndexSeq
	{
		using type = typename MakeIndexSeq<Size - 1>::type::template append<Size - 1>;
	};

	/// @private
	template<>
	struct MakeIndexSeq<0u>
	{
		using type = IndexSeq<>;
	};

	/// @private
	template<typename Tuple>
	struct CallIndices 
	{
		using type = typename MakeIndexSeq<std::tuple_size<Tuple>::value>::type;
	};

	/// @private
	template<typename F, typename Tuple, unsigned... I>
	auto ApplyImplFunc(F function, Tuple&& tuple, IndexSeq<I...>) -> decltype(function(std::get<I>(tuple)...))
	{
		return function(std::get<I>(tuple)...);
	}

	template<typename F, typename Tuple>
	auto Apply(F function, Tuple args) -> decltype(ApplyImplFunc(function, args, std::declval<typename CallIndices<Tuple>::type>()))
	{
		using indices = typename CallIndices<Tuple>::type;
		return ApplyImplFunc(function, args, indices());
	}

#else

	/// @private
	template<typename F, typename Tuple, size_t... S>
	decltype(auto) ApplyImplFunc(F&& function, Tuple&& tuple, std::index_sequence<S...>)
	{
		return std::forward<F>(function)(std::get<S>(std::forward<Tuple>(tuple))...);
	}

	template<typename F, typename Tuple>
	decltype(auto) Apply(F&& function, Tuple&& tuple)
	{
		const std::size_t tSize = std::tuple_size<typename std::remove_reference<Tuple>::type>::value;
		return ApplyImplFunc(std::forward<F>(function), std::forward<Tuple>(tuple), std::make_index_sequence<tSize>());
	}

#endif

	template<typename F, typename... Args>
	TN::Functor<F, Args...>::Functor(F function, Args&&... args) :
		m_function(function),
		m_args(std::forward<Args>(args)...)
	{

	}

	template<typename F, typename... Args>
	void TN::Functor<F, Args...>::Run()
	{
		Apply(m_function, m_args);
	}

}

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

#ifndef TN_CORE_STRING_HPP
#define TN_CORE_STRING_HPP

#include <Core/Config.hpp>

#define TN_MAX_CONVERTIBLE_MESSAGE_SIZE 100

namespace TN
{
	/**
	* @brief The null character in a variable.
	*
	*/
	static char nullCharacter = '\0';

	/**
	* @class String
	* @brief String class.
	*
	* Manipulate string easily.
	*
	*/
	class TN_CORE String
	{
	public:

		/**
		* @brief String constructor.
		*
		*/
		String();

		/**
		* @brief Initialize a string with a character.
		*
		* @param txt : a const character.
		*
		*/
		String(const char txt);

		/**
		* @brief Initialize a string with a string of characters (cstring).
		*
		* @param txt : the string of characters (cstring).
		*
		*/
		String(const char* txt);

		/**
		* @brief Initialize a string with another string.
		*
		* @param txt : the string.
		*
		*/
		String(const String& txt);

		/**
		* @brief Default string destructor.
		*
		*/
		~String();

		/**
		* @brief Getter of the length of the string.
		*
		* @return Return the length of the string.
		*
		*/
		unsigned int GetLength() const;

		/**
		* @brief Get the indice of a character in the string.
		*
		* @param character : the character we looking for.
		*
		* @return Return the index of the character in the string.
		*
		*/
		int GetIndex(char character) const;

		/**
		* @brief Upcase all characters of the string.
		*
		*/
		void Upcase();

		/**
		* @brief Upcase all characters of the string in an interval.
		*
		* @param first : Indice of the first character that will be upcased.
		* @param last : Indice of the last character that will be upcased.
		*
		*/
		void Upcase(unsigned int first, unsigned int last);

		/**
		* @brief Downcase all characters of the string.
		*
		*/
		void Downcase();

		/**
		* @brief Downcase all characters of the string in an interval.
		*
		* @param first : Indice of the first character that will be downcased.
		* @param last : Indice of the last character that will be downcased.
		*
		*/
		void Downcase(unsigned int first, unsigned int last);

		/**
		* @brief Get the cstring equivalent of the string.
		*
		* @return Return the cstring equivalent of the string (const).
		*
		*/
		const char* ToCString();

		char operator[] (unsigned int index) const;
		char& operator[] (unsigned int index);

		String& operator= (const String& string);

		String& operator+= (const String& string);


	private:
		char* m_data;
		unsigned int m_length;

	};

	TN_CORE String operator+  (const String& first, const String& last);
	TN_CORE String operator+  (const String& first, const char    last);
	TN_CORE String operator+  (const String& first, const char*   last);
	TN_CORE String operator+  (char		    first, const String& last);
	TN_CORE String operator+  (const char*   first, const String& last);

	TN_CORE bool operator== (const String& first, const String& last);
	TN_CORE bool operator== (const String& first, const char    last);
	TN_CORE bool operator== (const String& first, const char*   last);
	TN_CORE bool operator== (char		   first, const String& last);
	TN_CORE bool operator== (const char*   first, const String& last);

	TN_CORE bool operator!= (const String& first, const String& last);
	TN_CORE bool operator!= (const String& first, const char    last);
	TN_CORE bool operator!= (const String& first, const char*   last);
	TN_CORE bool operator!= (char		   first, const String& last);
	TN_CORE bool operator!= (const char*   first, const String& last);

	TN_CORE String ToString(const char* msg, ...);
}

#endif
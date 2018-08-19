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

#include <Core/String.hpp>
#include <Core/Error.hpp>

#include <cstdio>
#include <stdarg.h>

TN::String::String()
{
	m_data = new char[0];
	m_length = 0;
}

TN::String::String(const char txt)
{
	m_data   = new char(txt);
	m_length = 0;
}

TN::String::String(const char* txt)
{
	if (txt != NULL)
	{
		unsigned int count = 0;

		while (txt[count] != '\0')
			count++;

		m_length = count;
		m_data = new char[count + 1];

		for (count = 0; count < m_length; count++)
			m_data[count] = txt[count];

		m_data[m_length] = '\0';
	}
	else
	{
		m_data = new char[0];
		m_length = 0;
	}
}

TN::String::String(const String& txt)
{
	m_length = txt.GetLength();
	m_data   = new char[m_length + 1];
	
	unsigned int count = 0;
	for (count = 0; count < m_length; count++)
		m_data[count] = txt[count];

	m_data[m_length] = '\0';
}

TN::String::~String()
{
	delete[] m_data;
}

unsigned int TN::String::GetLength() const
{
	return m_length;
}

int TN::String::GetIndex(char character) const
{
	unsigned int count = 0;
	for (count = 0; count < m_length; count++)
		if (m_data[count] == character) return static_cast<int>(count);
	return -1;
}

void TN::String::Upcase()
{
	unsigned int count = 0;
	for (count = 0; count < m_length; count++)
		if ('a' <= m_data[count] && m_data[count] <= 'z') m_data[count] -= ('a' - 'A');
}

void TN::String::Upcase(unsigned int first, unsigned int last)
{
	if ((first > last) || (last > m_length))
	{
		TN_WARNING("Try to upcase a string in a wrong interval")
		return;
	}

	unsigned int count = 0;
	for (count = first; count < last; count++)
		if ('a' <= m_data[count] && m_data[count] <= 'z') m_data[count] -= ('a' - 'A');
}

void TN::String::Downcase()
{
	unsigned int count = 0;
	for (count = 0; count < m_length; count++)
		if ('A' <= m_data[count] && m_data[count] <= 'Z') m_data[count] += ('a' - 'A');
}

void TN::String::Downcase(unsigned int first, unsigned int last)
{
	if ((first > last) || (last > m_length))
	{
		TN_WARNING("Try to downcase a string in a wrong interval")
		return;
	}

	unsigned int count = 0;
	for (count = first; count < last; count++)
		if ('A' <= m_data[count] && m_data[count] <= 'Z') m_data[count] += ('a' - 'A');
}

const char* TN::String::ToCString()
{
	return m_data;
}

char TN::String::operator[] (unsigned int index) const
{
	if (index > m_length)
	{
		TN_WARNING("Wrong index when trying to get a character of a string, index out of range")
		return nullCharacter;
	}

	return m_data[index];
}

char& TN::String::operator[] (unsigned int index)
{
	if (index > m_length)
	{
		TN_WARNING("Wrong index when trying to get a character of a string, index out of range")
		return nullCharacter;
	}

	return m_data[index];
}

TN::String& TN::String::operator= (const String& string)
{
	if (this == &string) return *this;

	delete[] m_data;
	m_length = string.GetLength();
	m_data = new char[m_length + 1];

	unsigned int count = 0;
	for (count = 0; count < m_length; count++)
		m_data[count] = string[count];

	m_data[m_length] = '\0';

	return *this;
}

TN::String& TN::String::operator+= (const String& string)
{
	unsigned int new_length = m_length + string.GetLength();
	char* final_data = new char[new_length + 1];

	unsigned int count = 0;
	for (count = 0; count < m_length; count++)
		final_data[count] = m_data[count];

	for (count = 0; count < string.GetLength(); count++)
		final_data[m_length + count] = string[count];

	final_data[new_length] = '\0';

	delete[] m_data;
	m_length = new_length;
	m_data = final_data;
	return *this;
}




/* OPERATORS */

TN::String TN::operator+ (const String& first, const String& last)
{
	return String(first) += last;
}

TN::String TN::operator+ (const String& first, const char last)
{
	return String(first) += String(last);
}

TN::String TN::operator+ (const String& first, const char* last)
{
	return String(first) += String(last);
}

TN::String TN::operator+ (char first, const String& last)
{
	return String(first) += last;
}

TN::String TN::operator+ (const char* first, const String& last)
{
	return String(first) += last;
}


bool TN::operator== (const String& first, const String& last)
{
	if (first.GetLength() != last.GetLength()) return false;

	unsigned int count = 0;
	while ((count < first.GetLength()) && (first[count] == last[count])) count++;
	return (count == first.GetLength());
}

bool TN::operator== (const String& first, const char last)
{
	return (first == String(last));
}

bool TN::operator== (const String& first, const char* last)
{
	return (first == String(last));
}

bool TN::operator== (char first, const String& last)
{
	return (String(first) == last);
}

bool TN::operator== (const char* first, const String& last)
{
	return (String(first) == last);
}


bool TN::operator!= (const String& first, const String& last)
{
	return !(first == last);
}

bool TN::operator!= (const String& first, const char last)
{
	return !(first == last);
}

bool TN::operator!= (const String& first, const char* last)
{
	return !(first == last);
}

bool TN::operator!= (char first, const String& last)
{
	return !(first == last);
}

bool TN::operator!= (const char* first, const String& last)
{
	return !(first == last);
}

TN_CORE TN::String TN::ToString(const char* msg, ...)
{
	char temp[TN_MAX_CONVERTIBLE_MESSAGE_SIZE];

	va_list _va;
	va_start(_va, msg);
	std::vsnprintf(temp, TN_MAX_CONVERTIBLE_MESSAGE_SIZE, msg, _va);
	va_end(_va);

	return temp;
}
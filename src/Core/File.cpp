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

#define _CRT_SECURE_NO_WARNINGS 1
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include <Core/File.hpp>
#include <Core/Log.hpp>
#include <Core/Error.hpp>

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define M_FILE static_cast<FILE*>(m_file)

TN::File::File(String path, FileMode_e mode)
{
	String sMode;

	switch (mode)
	{
	case FM_READ:
		sMode = "r";
		break;

	case FM_WRITE:
		sMode = "a+";
		break;

	case FM_OVERWRITE :
		sMode = "w+";
		break;
	
	case FM_READ_BINARY:
		sMode = "rb";
		break;

	case FM_WRITE_BINARY:
		sMode = "ab+";
		break;

	case FM_OVERWRITE_BINARY:
		sMode = "wb+";
		break;

	default:
		sMode = "r";
		break;
	}

	m_file = fopen(path.ToCString(), sMode.ToCString());
	m_mode = mode;

	if (m_file == NULL)
	{
		TN_ERROR("Can't open the file '%s' with mode '%s'...", path.ToCString(), sMode.ToCString());
	}
}

TN::File::~File()
{
	if(IsFileOpen())
		fclose(M_FILE);
}

void TN::File::Close()
{
	fclose(M_FILE);
	m_file = NULL;
}

void TN::File::Write(String text, ...)
{
	va_list vaList;
	va_start(vaList, text);
	vfprintf(M_FILE, text.ToCString(), vaList);
	va_end(vaList);
}

void TN::File::Write(long cursorPosition, String text, ...)
{
	SetCursorPosition(cursorPosition);

	va_list vaList;
	va_start(vaList, text);
	vfprintf(M_FILE, text.ToCString(), vaList);
	va_end(vaList);
}

void TN::File::Read(int size, String& buffer)
{
	fgets((char*)buffer.ToCString(), size, M_FILE);
}

void TN::File::Read(long cursorPosition, String& buffer, int size)
{
	SetCursorPosition(cursorPosition);

	fgets((char*)buffer.ToCString(), size, M_FILE);
}

void TN::File::Read(String form, ...)
{
	va_list vaList;
	va_start(vaList, form);
	vfscanf(M_FILE, form.ToCString(), vaList);
	va_end(vaList);
}

void TN::File::Read(long cursorPosition, String form, ...)
{
	SetCursorPosition(cursorPosition);

	va_list vaList;
	va_start(vaList, form);
	vfscanf(M_FILE, form.ToCString(), vaList);
	va_end(vaList);
}

long TN::File::GetCursorPosition()
{
	return ftell(M_FILE);
}

void TN::File::SetCursorPosition(long pos)
{
	fseek(M_FILE, pos, SEEK_SET);
}

bool TN::File::IsFileOpen()
{
	if (m_file == NULL)
		return false;
	else
		return true;
}

void TN::File::Flush()
{
	fflush(M_FILE);
}

void TN::File::SkipLines(size_t count)
{
	size_t i;

	for (i = 0; i < count; i++)
	{
		if (m_mode == FileMode_e::FM_READ || m_mode == FileMode_e::FM_READ_BINARY)
			fscanf(M_FILE, "%*[^\n]\n");
		else
			fprintf(M_FILE, "\n");
	}
}
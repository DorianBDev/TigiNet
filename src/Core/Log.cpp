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

#define _CRT_SECURE_NO_WARNINGS 1
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1 
#include <Core/Log.hpp>
#include <Core/Error.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <time.h>

#define MESSAGE_DATE_MAX_LENGTH 25

TN::Log::Log()
{
	m_pFile = NULL;
	m_pFile = new TN::File("Tiginet.log", TN::FileMode_e::FM_OVERWRITE);

	if (m_pFile == NULL)
	{
		Print("INFO", "Logger on...");
		TN_WARNING("Can't create 'Tiginet.log', no file logger...")
	}
	else
	{
		m_fileReady = true;
		Print("INFO", "Logger on...");
	}

	Print("INFO", "---------------------------------------------------");
}

TN::Log::~Log()
{
	Print("INFO", "---------------------------------------------------");
	Print("INFO", "Logger off...");

	if (m_fileMutex.IsLock())
		m_fileMutex.Unlock();

	if (m_consoleMutex.IsLock())
		m_consoleMutex.Unlock();

	m_pFile->Close();

	delete m_pFile;
}

TN::String TN::Log::Form(String messageType, String message, bool endl)
{	
	String res_end;

	if (endl)
		res_end = "\n";
	else
		res_end = "";

	String res_header;
	res_header = "[" + messageType + "] : ";

	/* Date */
	char * date;
	date = (char*)calloc(MESSAGE_DATE_MAX_LENGTH, sizeof(char));

	time_t t = time(NULL);
	struct tm now_tm = *localtime(&t);

	strftime(date, MESSAGE_DATE_MAX_LENGTH, "(%m-%d-%Y %T) - ", &now_tm);

	String dates;
	dates = date;

	free(date);

	String res;

	res = dates + res_header + message + res_end;

	return res;
}

void TN::Log::Print(String messageType, String message, ...)
{
	va_list _va;
	va_start(_va, message);
	PrintFile(messageType, message, _va);
	va_end(_va);

	va_start(_va, message);
	PrintConsole(messageType, message, _va);
	va_end(_va);
}

void TN::Log::Print(String messageType, String message, va_list va)
{
	PrintFile(messageType, message, va);
	PrintConsole(messageType, message, va);
}

void TN::Log::PrintFile(String messageType, String message, ...)
{
#if TN_THREAD_SAFE
	TN::LockGuard lock(&m_fileMutex);
#endif

	if (!m_fileReady)
		return;

	messageType.Upcase();

	char * _res = new char[TN_MESSAGE_MAX_LENGTH];
	va_list _va;
	va_start(_va, message);
	vsnprintf(_res, TN_MESSAGE_MAX_LENGTH, message.ToCString(), _va);
	va_end(_va);

	m_pFile->Write(Form(messageType, _res, true));

	delete[] _res;
}

void TN::Log::PrintFile(String messageType, String message, va_list va)
{
#if TN_THREAD_SAFE
	TN::LockGuard lock(&m_fileMutex);
#endif

	if (!m_fileReady)
		return;

	messageType.Upcase();

	char * _res = new char[TN_MESSAGE_MAX_LENGTH];

	vsnprintf(_res, TN_MESSAGE_MAX_LENGTH, message.ToCString(), va);

	m_pFile->Write(Form(messageType, _res, true));

	delete[] _res;
}

void TN::Log::PrintConsole(String messageType, String message, ...)
{
#if TN_THREAD_SAFE
	TN::LockGuard lock(&m_consoleMutex);
#endif

	messageType.Upcase();

	char * _res = new char[TN_MESSAGE_MAX_LENGTH];
	va_list _va;
	va_start(_va, message);
	vsnprintf(_res, TN_MESSAGE_MAX_LENGTH, message.ToCString(), _va);
	va_end(_va);

	printf("%s", Form(messageType, _res, true).ToCString());

	delete[] _res;
}

void TN::Log::PrintConsole(String messageType, String message, va_list va)
{
#if TN_THREAD_SAFE
	TN::LockGuard lock(&m_consoleMutex);
#endif

	messageType.Upcase();

	char * _res = new char[TN_MESSAGE_MAX_LENGTH];

	vsnprintf(_res, TN_MESSAGE_MAX_LENGTH, message.ToCString(), va);

	printf("%s", Form(messageType, _res, true).ToCString());

	delete[] _res;
}

void TN::Log::Write(String message, ...)
{
	va_list _va;

	va_start(_va, message);
	PrintFile("Info", message, _va);
	va_end(_va);

	va_start(_va, message);
	PrintConsole("Info", message, _va);
	va_end(_va);
}
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

#ifndef TN_CORE_FILE_HPP
#define TN_CORE_FILE_HPP

#include <Core/Config.hpp>
#include <Core/String.hpp>

/**
* @brief Get the indice of the lowest cursor position possible.
*
*/
#define TN_CURSOR_BEGINNING_POS 0

namespace TN
{
	/*! File mode */
	typedef enum __file_mode_e
	{
		FM_READ,				/*!< To read only */
		FM_WRITE,				/*!< To write and read */
		FM_OVERWRITE,			/*!< To write and read and erase existing file */
		FM_READ_BINARY,			/*!< To read in binary mode only */
		FM_WRITE_BINARY,		/*!< To write and read in binary mode only */
		FM_OVERWRITE_BINARY		/*!< To write and read in binary mode and erase existing file */
	}FileMode_e;

	/**
	* @class File
	* @brief File class.
	*
	* Manipulate file easily.
	*
	*/
	class TN_CORE File
	{
	public:

		/**
		* @brief Open/Create a file.
		*
		* @param path : the path of the file.
		* @param mode : the mode of the file.
		*
		* @see FileMode_e
		*
		*/
		File(String path, FileMode_e mode);
		~File();

		/**
		* @brief Close the file.
		*
		*/
		void Close();

		/**
		* @brief Write in the file.
		*
		* @param text : the text to write in the file.
		*
		*/
		void Write(String text, ...);

		/**
		* @brief Write in the file and specify the cursor position
		*
		* @param cursorPosition : the cursor position in the file.
		* @param text : the text to write in the file.
		*
		*/
		void Write(long cursorPosition, String text, ...);

		/**
		* @brief Read in the file.
		*
		* @param size : the size in byte of the data that will be read.
		* @param buffer : where all data will be writed.
		*
		*/
		void Read(int size, String& buffer);

		/**
		* @brief Read in the file and specify the cursor position.
		*
		* @param cursorPosition : the cursor position in the file.
		* @param buffer : where all data will be writed.
		* @param size : the size in byte of the data that will be read.
		*
		*/
		void Read(long cursorPosition, String& buffer, int size);

		/**
		* @brief Read data in the file with a specified form (like a scanf or fscanf).
		*
		* @param form : the form of the data.
		*
		*/
		void Read(String form, ...);

		/**
		* @brief Read data in the file with a specified form (like a scanf or fscanf).
		*
		* @param cursorPosition : the cursor position in the file.
		* @param form : the form of the data.
		*
		*/
		void Read(long cursorPosition, String form, ...);

		/**
		* @brief Get the cursor position.
		*
		* @return Return the position of the cursor in the file.
		*
		*/
		long GetCursorPosition();

		/**
		* @brief Set the cursor position.
		*
		* @param pos : new position of the cursor in the file.
		*
		*/
		void SetCursorPosition(long pos);

		/**
		* @brief Tell you if the file is open or not.
		*
		* @return Return if the file is open or not.
		*
		*/
		bool IsFileOpen();

		/**
		* @brief Flush the file.
		*
		*/
		void Flush();

		/**
		* @brief Skip some lines.
		*
		* @param count : number of lines to skip (default 1).
		*
		*/
		void SkipLines(size_t count = 1);

	private:
		void * m_file = NULL;
		FileMode_e m_mode;

	};
}


#endif
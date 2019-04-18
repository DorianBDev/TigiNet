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

#ifndef TN_UTILITY_MNIST_INL
#define TN_UTILITY_MNIST_INL

#include <iostream>

namespace TN
{
	/// @private
	template<typename T>
	MNIST<T>::MNIST(const char* mnistImagePath, const char* mnistLabelPath, int batchMaxSize)
	{
		TN_ASSERT(mnistImagePath != NULL && mnistLabelPath != NULL, "UTILITY", "Wrong MNIST file path");

		char buffer[4];

		//////////////////////////////////
		// Image
		std::ifstream imageFile(mnistImagePath, std::ios::in | std::ios::binary);

		// Magic number
		imageFile.read(buffer, 4);
		int magiceNumber = BufferToInt(buffer);
		TN_ASSERT(magiceNumber == 0x803, "NEURALNET", "Wrong image file");

		// Total size
		imageFile.read(buffer, 4);
		m_size = BufferToInt(buffer);
		if (batchMaxSize > 0 && batchMaxSize < m_size)
			m_size = batchMaxSize;

		// Row size
		imageFile.read(buffer, 4);
		m_rowSize = BufferToInt(buffer);

		// Col size
		imageFile.read(buffer, 4);
		m_colSize = BufferToInt(buffer);

		// 3-Tensor creation
		unsigned int* imageShape = new unsigned int[3];
		imageShape[0] = static_cast<unsigned int>(m_colSize);
		imageShape[1] = static_cast<unsigned int>(m_rowSize);
		imageShape[2] = static_cast<unsigned int>(m_size);
		m_image = new Tensor<T>(3, TensorShape(imageShape), 3);
		delete[] imageShape;

		char* imageBuffer = new char[m_rowSize * m_colSize];
		for(int i = 0; i < m_size; i++)
		{
			imageFile.read(imageBuffer, m_rowSize * m_colSize);
			for(int j = 0; j < m_rowSize; j++)
			{
				for(int k = 0; k < m_colSize; k++)
				{
					(*m_image)[i][j](k) = imageBuffer[k + j * m_colSize] / static_cast<T>(255);
				}
			}
		}
		delete[] imageBuffer;

		imageFile.close();

		//////////////////////////////////
		// Label
		std::ifstream labelFile(mnistLabelPath, std::ios::in | std::ios::binary);

		// Magic number
		labelFile.read(buffer, 4);
		magiceNumber = BufferToInt(buffer);
		TN_ASSERT(magiceNumber == 0x801, "NEURALNET", "Wrong label file");

		// Total size
		labelFile.read(buffer, 4);

		//1-tensor creation
		unsigned int* labelShape = new unsigned int[1];
		labelShape[0] = static_cast<unsigned int>(m_size);
		m_label = new Tensor<int>(1, TensorShape(labelShape), 1);
		delete[] labelShape;

		char* labelBuffer = new char[1];
		for(int i = 0; i < m_size; i++)
		{
			labelFile.read(labelBuffer, 1);
			(*m_label)(i) = labelBuffer[0];
		}
		delete[] labelBuffer;

		labelFile.close();
	}

	/// @private
	template<typename T>
	MNIST<T>::~MNIST()
	{
		if (m_image != NULL)
			delete m_image;

		if (m_label != NULL)
			delete m_label;
	}

	/// @private
	template<typename T>
	Tensor<T>& MNIST<T>::GetImage() const
	{
		return *m_image;
	}

	/// @private
	template<typename T>
	Tensor<int>& MNIST<T>::GetLabel() const
	{
		return *m_label;
	}

	/// @private
	template<typename T>
	int MNIST<T>::BufferToInt(const char* buffer)
	{
		return ((buffer[0] & 0xff) << 24) | ((buffer[1] & 0xff) << 16) | ((buffer[2] & 0xff) << 8) | ((buffer[3] & 0xff) << 0);
	}

}

#endif
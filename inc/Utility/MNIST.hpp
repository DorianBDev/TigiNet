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


#ifndef TN_UTILITY_MNIST_HPP
#define TN_UTILITY_MNIST_HPP

#include <Utility/Tensor.hpp>
#include <Core/Error.hpp>
#include <string>

namespace TN
{
	/**
	* @class MNIST
	* @brief MNIST database loader.
	*
	* Load a MNIST database in tensors (images and labels).
	*
	*/
	template<typename T>
	class MNIST
	{
	public:

		/**
		* @brief Create a MNIST loader.
		* 
		* @param mnistImagePath : the MNIST image file path.
		* @param mnistLabelPath : the MNIST label file path.
		* @param batchMaxSize : the maximal number of data to load (-1 to load all available data).
		*
		*/
		MNIST(const char* mnistImagePath, const char* mnistLabelPath, int batchMaxSize = -1);
		~MNIST();

		/**
		* @brief Get the image tensor (3-tensor).
		*
		* @return Return a reference to the image tensor.
		*
		*/
		Tensor<T>& GetImage() const;

		/**
		* @brief Get the label tensor (1-tensor).
		*
		* @return Return a reference to the label tensor.
		*
		*/
		Tensor<int>& GetLabel() const;

	protected:
		int BufferToInt(const char* buffer);

	private:
		Tensor<T>* m_image = NULL; // 3-tensor
		Tensor<int>* m_label = NULL; // 1-tensor
		int m_size;
		int m_rowSize;
		int m_colSize;

	};
}

#include <Utility/MNIST.inl>

#endif
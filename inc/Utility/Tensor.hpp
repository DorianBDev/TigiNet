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

#ifndef TN_UTILITY_TENSOR_HPP
#define TN_UTILITY_TENSOR_HPP

#include <Utility/Config.hpp>
#include <memory>

namespace TN
{

	/**
	* @class TensorShape
	* @brief Define a shape to a tensor with this class.
	*
	* A class that handle dimensions for use with a tensor 
	*
	* @see Tensor
	*
	*/
	class TN_UTILITY TensorShape
	{
	public:

		/**
		* @brief Create a tensor shape.
		*
		* @param shape : the table of dimension, one dimension per rank.
		*
		*/
		TensorShape(unsigned int shape[]);
		TensorShape() = default;
		~TensorShape();

		/**
		* @brief Get the dimension of a rank.
		*
		* @param index : the desired rank.
		*
		* @return Return the desired rank dimension.
		*
		*/
		unsigned int GetDimension(unsigned int index) const;

		/**
		* @brief Copy a TensorShape.
		*
		* @param rank : the rank of the tensor.
		*
		* @return Return a shared pointer on the new copy.
		*
		*/
		std::shared_ptr<TensorShape> Copy(unsigned int rank) const;

	private:
		unsigned int* m_shape = NULL;
		bool m_copy = false;

	};


	/**
	* @class Tensor
	* @brief A n-tensor class.
	*
	* A class that provide an entire toolkit for Tensors.
	*
	* Use : () to access data and [] to access sub-tensor.
	*
	* Example : For a 2*2 matrix (1 rank tensor)
	*
	* @code
	* unsigned int shape[] = { 2, 2 };
	* TN::Tensor<int> t(1, TN::TensorShape(shape));
	*
	* t[0](0) = 1;
	* t[0](1) = 2;
	* t[1](0) = 3;
	* t[1](1) = 4;
	* @endcode
	*
	*/
	template<typename T>
	class Tensor
	{
	public:

		/**
		* @brief Create a tensor.
		*
		* @param rank : the rank of the tensor.
		* @param shape : the shape of the tensor.
		* @param allocationRank : the rank where the datas will be allocated (useful for contiguous datas).
		* @param data : an user allocated data array, it will be deleted at the end, no bound check.
		*
		*/
		Tensor(unsigned int rank, const TensorShape & shape, unsigned int allocationRank = 0, T* data = NULL);
		Tensor() = default;
		~Tensor();

		/**
		* @brief Get the datas of this tensor.
		*
		* @return Return the datas of this tensor, can be NULL.
		*
		*/
		T* GetData();

		/**
		* @brief Access to a sub Tensor (with rank - 1).
		*
		* @param index : the desired index.
		*
		* @return Return the desired sub tensor.
		*
		*/
		Tensor& operator[] (unsigned int index);

		/**
		* @brief Access to data (read only).
		*
		* @param index : the desired index.
		*
		* @return Return the desired data.
		*
		*/
		T operator() (unsigned int index) const;

		/**
		* @brief Access to data (read write).
		*
		* @param index : the desired index.
		*
		* @return Return the desired data.
		*
		*/
		T& operator() (unsigned int index);


	protected:

		/**
		* @brief Initialize a sub tensor.
		*
		* @param rank : the rank of the sub tensor.
		* @param shape : the shape pointer of the tensor.
		* @param allocationRank : the rank where the datas will be allocated (useful for contiguous datas).
		* @param data : an tensor allocated data array, it will be deleted at the end, no bound check.
		*
		*/
		void Initialize(unsigned rank, std::shared_ptr<TensorShape> shape, unsigned int allocationRank = 0, T* data = NULL);


	private:
		std::shared_ptr<TensorShape> m_shape = NULL;
		Tensor* m_tensors = NULL;
		unsigned int m_allocationRank = 0;
		unsigned int m_rank = 0;
		T* m_data = NULL;

	};

}

#include<Utility/Tensor.inl>

#endif
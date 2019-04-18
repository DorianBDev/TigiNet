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

#ifndef TN_UTILITY_TENSOR_HPP
#define TN_UTILITY_TENSOR_HPP

#include <Utility/Config.hpp>
#include <Core/Error.hpp>

#include <memory>

namespace TN
{

	/**
	* @class TensorShape
	* @brief Define a shape to a tensor with this class.
	*
	* A class that handle dimensions for use with a tensor.
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
		* @param shape : the table of dimension, one dimension per rank and start with the tiniest.
		*
		*/
		TensorShape(unsigned int shape[]);

		/**
		* @brief Create a tensor shape with initializer list.
		*
		* @param shape : the inizialier list of dimension, one dimension per rank and start with the tiniest.
		*
		*/
		TensorShape(std::initializer_list<unsigned int> shape);
		TensorShape();
		~TensorShape();

		/**
		* @brief Get the dimension of a rank.
		*
		* @param rank : the desired rank.
		*
		* @return Return the desired rank dimension.
		*
		*/
		unsigned int GetDimension(unsigned int rank) const;

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
	* Example : For a 2*2 matrix (2 rank tensor or 2-tensor) with [row](col) usage
	*
	* @code
	* unsigned int shape[] = { 2, 2 };
	* TN::Tensor<int> t(2, TN::TensorShape(shape));
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
		Tensor(unsigned int rank, const TensorShape & shape, unsigned int allocationRank = 1, T* data = NULL);

		/**
		* @brief Create a tensor.
		*
		* @param rank : the rank of the tensor.
		* @param shape : the shape of the tensor.
		* @param allocationRank : the rank where the datas will be allocated (useful for contiguous datas).
		* @param data : an user allocated data array, it will be deleted at the end, no bound check.
		*
		*/
		Tensor(unsigned int rank, std::shared_ptr<TensorShape> shape, unsigned int allocationRank = 1, T* data = NULL);
		Tensor();
		~Tensor();

		/**
		* @brief Get the datas of this tensor.
		*
		* @return Return the datas of this tensor, can be NULL.
		*
		*/
		T* GetData();

		/**
		* @brief Get the rank of this tensor.
		*
		* @return Return the rank of this tensor.
		*
		*/
		unsigned int GetRank() const;

		/**
		* @brief Get the dimension of a rank.
		*
		* @param rank : the desired rank.
		*
		* @return Return the desired rank dimension.
		*
		*/
		unsigned int GetDimension(unsigned int rank) const;

		/**
		* @brief Get the shape of the tensor.
		*
		* @return Return the shape of the tensor.
		*
		*/
		std::shared_ptr<TensorShape> GetShape();

		/**
		* @brief Get the allocation rank of this tensor.
		*
		* @return Return the allocation rank of the tensor.
		*
		*/
		unsigned int GetAllocationRank();

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
		* @brief Access to a sub Tensor (with rank - 1).
		*
		* @param index : the desired index.
		*
		* @return Return the desired sub tensor.
		*
		*/
		Tensor operator[] (unsigned int index) const;

		/**
		* @brief Access to data (read only).
		*
		* @param index : the desired index.
		*
		* @return Return the desired data.
		*
		*/
		T operator() (unsigned int index = 0) const;

		/**
		* @brief Access to data (read write).
		*
		* @param index : the desired index.
		*
		* @return Return the desired data.
		*
		*/
		T& operator() (unsigned int index = 0);

		/**
		* @brief Initialize a sub tensor.
		*
		* @param rank : the rank of the sub tensor.
		* @param shape : the shared pointer of the tensor shape.
		* @param allocationRank : the rank where the datas will be allocated (useful for contiguous datas).
		* @param data : a tensor allocated data array, it will be deleted at the end, no bound check.
		*
		*/
		void InitializeSub(unsigned rank, std::shared_ptr<TensorShape> shape, unsigned int allocationRank = 1, T* data = NULL);

		/**
		* @brief Print the tensor datas.
		*
		*/
		void Print() const;

		/**
		* @brief Copy a tensor.
		*
		* @return Return a shared_ptr to the new tensor.
		*
		*/
		std::shared_ptr<Tensor<T>> Copy() const;


	private:
		std::shared_ptr<TensorShape> m_shape;
		Tensor* m_tensors = NULL;
		unsigned int m_allocationRank = 0;
		unsigned int m_rank = 0;
		T* m_data = NULL;

	};

	/**
	* @brief Print tensor datas.
	*
	* @param tensor : the tensor.
	*
	*/
	template<typename T>
	void PrintTensor(Tensor<T>& tensor);

	/**
	* @brief Copy all subtensors.
	*
	* @param tensor : the tensor to copy.
	* @param copy : the copy.
	*
	*/
	template<typename T>
	void CopySubTensors(Tensor<T>& tensor, Tensor<T>& copy);

}

#include<Utility/Tensor.inl>

#endif
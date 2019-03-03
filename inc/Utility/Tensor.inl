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

#include <Core/Error.hpp>

namespace TN
{
	/// @private
	template<typename T>
	TN::Tensor<T>::Tensor(unsigned int rank, TensorShape & shape, unsigned int allocationRank, T* data)
	{
		m_shape = &shape;
		m_rank = rank;
		m_allocationRank = allocationRank;

		if(rank == 0)
		{
			m_tensors = NULL;

			if (data != NULL)
				m_data = data;
			else
				m_data = new T[shape.GetDimension(rank)];
		}
		else
		{
			m_tensors = new Tensor[shape.GetDimension(rank)];
			
			unsigned int dim = 1;

			for (unsigned int j = 0; j < rank; j++)
			{
				dim *= shape.GetDimension(j);
			}

			if (data != NULL)
			{
				m_data = data;
			}
			else if (allocationRank == rank)
			{
				m_data = new T[dim * shape.GetDimension(rank)];
			}
			else
				m_data = NULL;
				
			if (m_data == NULL)
			{
				for (unsigned int i = 0; i < shape.GetDimension(rank); i++)
					m_tensors[i].Initialize(rank - 1, shape, allocationRank, NULL);
			}
			else
			{
				for (unsigned int i = 0; i < shape.GetDimension(rank); i++)
					m_tensors[i].Initialize(rank - 1, shape, allocationRank, &m_data[dim * i]);
			}
		}
	}

	/// @private
	template<typename T>
	TN::Tensor<T>::~Tensor()
	{
		if (m_data != NULL && m_allocationRank == m_rank)
			delete[] m_data;

		if(m_tensors != NULL)
			delete[] m_tensors;
	}

	/// @private
	template<typename T>
	void TN::Tensor<T>::Initialize(unsigned rank, TensorShape & shape, unsigned int allocationRank, T* data)
	{
		m_shape = &shape;
		m_rank = rank;
		m_allocationRank = allocationRank;

		if (rank == 0)
		{
			m_tensors = NULL;

			if (data != NULL)
				m_data = data;
			else
				m_data = new T[shape.GetDimension(rank)];
		}
		else
		{
			m_tensors = new Tensor[shape.GetDimension(rank)];

			unsigned int dim = 1;

			for (unsigned int j = 0; j < rank; j++)
			{
				dim *= shape.GetDimension(j);
			}

			if (data != NULL)
			{
				m_data = data;
			}
			else if (allocationRank == rank)
			{
				m_data = new T[dim * shape.GetDimension(rank)];
			}
			else
				m_data = NULL;

			if (m_data == NULL)
			{
				for (unsigned int i = 0; i < shape.GetDimension(rank); i++)
					m_tensors[i].Initialize(rank - 1, shape, allocationRank, NULL);
			}
			else
			{
				for (unsigned int i = 0; i < shape.GetDimension(rank); i++)
					m_tensors[i].Initialize(rank - 1, shape, allocationRank, &m_data[dim * i]);
			}
			
		}
	}

	/// @private
	template<typename T>
	T* TN::Tensor<T>::GetData()
	{
		return m_data;
	}

	/// @private
	template<typename T>
	TN::Tensor<T>& TN::Tensor<T>::operator[] (unsigned int index)
	{
#if TN_SAFEMODE_TENSOR
		TN_ASSERT(m_shape->GetDimension(m_rank) > index, "Wrong index while trying to access Tensor");
		TN_ASSERT(index >= 0, "Wrong index while trying to access Tensor");
		TN_ASSERT(m_rank > 0, "Wrong operator while trying to access Tensor");
#endif

		return m_tensors[index];
	}

	/// @private
	template<typename T>
	T TN::Tensor<T>::operator() (unsigned int index) const
	{
#if TN_SAFEMODE_TENSOR
		TN_ASSERT(m_rank == 0, "Wrong operator while trying to access Tensor");
		TN_ASSERT(m_data != NULL, "Wrong operator while trying to access Tensor");
#endif

		return m_data[index];
	}

	/// @private
	template<typename T>
	T& TN::Tensor<T>::operator() (unsigned int index)
	{
#if TN_SAFEMODE_TENSOR
		TN_ASSERT(m_rank == 0, "Wrong operator while trying to access Tensor");
		TN_ASSERT(m_data != NULL, "Wrong operator while trying to access Tensor");
#endif

		return m_data[index];
	}
}
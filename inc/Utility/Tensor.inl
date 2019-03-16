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

#ifndef TN_UTILITY_TENSOR_INL
#define TN_UTILITY_TENSOR_INL

namespace TN
{
	/// @private
	template<typename T>
	Tensor<T>::Tensor(unsigned int rank, const TensorShape & shape, unsigned int allocationRank, T* data)
	{
		m_rank = rank;
		m_shape = shape.Copy(rank);
		m_allocationRank = allocationRank;

		if (rank == 0)
		{
			m_tensors = NULL;

			if (data != NULL)
			{
				m_data = data;
			}
			else
			{
				m_data = new T;
				m_allocationRank = 0;
			}
		}
		else if(rank == 1)
		{
			m_tensors = NULL;

			if (data != NULL)
			{
				m_data = data;
			}
			else
			{
				m_data = new T[m_shape->GetDimension(rank)];
				m_allocationRank = 1;
			}
		}
		else
		{
			m_tensors = new Tensor[m_shape->GetDimension(rank)];
			
			unsigned int dim = 1;

			for (unsigned int j = 1; j < rank; j++)
			{
				dim *= m_shape->GetDimension(j);
			}

			if (data != NULL)
			{
				m_data = data;
			}
			else if (allocationRank >= rank)
			{
				m_data = new T[dim * m_shape->GetDimension(rank)];
				m_allocationRank = m_rank;
			}
			else
			{
				m_data = NULL;
			}
				
			if (m_data == NULL)
			{
				for (unsigned int i = 0; i < m_shape->GetDimension(rank); i++)
					m_tensors[i].InitializeSub(rank - 1, m_shape, allocationRank, NULL);
			}
			else
			{
				for (unsigned int i = 0; i < m_shape->GetDimension(rank); i++)
					m_tensors[i].InitializeSub(rank - 1, m_shape, allocationRank, &m_data[dim * i]);
			}
		}
	}

	/// @private
	template<typename T>
	Tensor<T>::Tensor()
	{
		m_tensors = NULL;
		m_allocationRank = 0;
		m_rank = 0;
		m_data = NULL;
	}

	/// @private
	template<typename T>
	Tensor<T>::~Tensor()
	{
		if (m_data != NULL)
		{
			if (m_allocationRank == 0)
				delete m_data;
			else if (m_allocationRank == m_rank)
				delete[] m_data;
		}

		if(m_tensors != NULL)
			delete[] m_tensors;
	}

	/// @private
	template<typename T>
	void Tensor<T>::InitializeSub(unsigned rank, std::shared_ptr<TensorShape> shape, unsigned int allocationRank, T* data)
	{
		m_shape = shape;
		m_rank = rank;
		m_allocationRank = allocationRank;

		if (rank == 0)
		{
			m_tensors = NULL;

			if (data != NULL)
			{
				m_data = data;
			}
			else
			{
				m_data = new T;
				m_allocationRank = 0;
			}
		}
		else if (rank == 1)
		{
			m_tensors = NULL;

			if (data != NULL)
			{
				m_data = data;
			}
			else
			{
				m_data = new T[m_shape->GetDimension(rank)];
				m_allocationRank = 1;
			}
		}
		else
		{
			m_tensors = new Tensor[m_shape->GetDimension(rank)];

			unsigned int dim = 1;

			for (unsigned int j = 1; j < rank; j++)
			{
				dim *= m_shape->GetDimension(j);
			}

			if (data != NULL)
			{
				m_data = data;
			}
			else if (allocationRank >= rank)
			{
				m_data = new T[dim * m_shape->GetDimension(rank)];
				m_allocationRank = m_rank;
			}
			else
			{
				m_data = NULL;
			}

			if (m_data == NULL)
			{
				for (unsigned int i = 0; i < m_shape->GetDimension(rank); i++)
					m_tensors[i].InitializeSub(rank - 1, m_shape, allocationRank, NULL);
			}
			else
			{
				for (unsigned int i = 0; i < m_shape->GetDimension(rank); i++)
					m_tensors[i].InitializeSub(rank - 1, m_shape, allocationRank, &m_data[dim * i]);
			}
			
		}
	}

	/// @private
	template<typename T>
	T* Tensor<T>::GetData()
	{
		return m_data;
	}

	/// @private
	template<typename T>
	unsigned int Tensor<T>::GetDimension(unsigned int rank) const
	{
		return m_shape->GetDimension(rank);
	}

	/// @private
	template<typename T>
	unsigned int Tensor<T>::GetRank() const
	{
		return m_rank;
	}

	/// @private
	template<typename T>
	Tensor<T>& Tensor<T>::operator[] (unsigned int index)
	{
#if TN_SAFEMODE_TENSOR
		TN_ASSERT(m_shape->GetDimension(m_rank) > index, "UTILITY", "Wrong index while trying to access Tensor");
		TN_ASSERT(index >= 0, "UTILITY", "Wrong index while trying to access Tensor");
		TN_ASSERT(m_rank > 0, "UTILITY", "Wrong operator while trying to access Tensor");
#endif

		return m_tensors[index];
	}

	/// @private
	template<typename T>
	Tensor<T> Tensor<T>::operator[] (unsigned int index) const
	{
#if TN_SAFEMODE_TENSOR
		TN_ASSERT(m_shape->GetDimension(m_rank) > index, "UTILITY", "Wrong index while trying to access Tensor");
		TN_ASSERT(index >= 0, "UTILITY", "Wrong index while trying to access Tensor");
		TN_ASSERT(m_rank > 0, "UTILITY", "Wrong operator while trying to access Tensor");
#endif

		return m_tensors[index];
	}

	/// @private
	template<typename T>
	T Tensor<T>::operator() (unsigned int index) const
	{
#if TN_SAFEMODE_TENSOR
		TN_ASSERT(index < m_shape->GetDimension(m_rank), "UTILITY", "Wrong operator while trying to access Tensor");
		TN_ASSERT(m_data != NULL, "UTILITY", "Wrong operator while trying to access Tensor");
#endif

		return m_data[index];
	}

	/// @private
	template<typename T>
	T& Tensor<T>::operator() (unsigned int index)
	{
#if TN_SAFEMODE_TENSOR
		TN_ASSERT(index < m_shape->GetDimension(m_rank), "UTILITY", "Wrong operator while trying to access Tensor");
		TN_ASSERT(m_data != NULL, "UTILITY", "Wrong operator while trying to access Tensor");
#endif

		return m_data[index];
	}

	/// @private
	template<typename T>
	void Tensor<T>::Print() const
	{
		TN_LOG("UTILITY") << "Tensor datas : ";
		if (GetRank() == 0)
		{
			TN_LOG("UTILITY") << m_data[0];
		}
		else if (GetRank() == 1)
		{
			TN::TigiNetLogger::GetInstance() << std::endl << TN::GetLogHeader("UTILITY", "INFO");
			for (unsigned int i = 0; i < GetDimension(1); i++)
			{
				TN::TigiNetLogger::GetInstance() << m_data[i] << " ";
			}
		}
		else if (GetRank() == 2)
		{
			for (unsigned int i = 0; i < GetDimension(2); i++)
			{
				TN::TigiNetLogger::GetInstance() << std::endl << TN::GetLogHeader("UTILITY", "INFO");
				for (unsigned int j = 0; j < GetDimension(1); j++)
				{
					TN::TigiNetLogger::GetInstance() << m_tensors[i](j) << " ";
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < GetDimension(GetRank()); i++)
			{
				TN_LOG("UTILITY") << "(" << i << ") :";
				PrintTensor<T>(m_tensors[i]);
			}
		}
	}

	/// @private
	template<typename T>
	void PrintTensor(const Tensor<T> & tensor)
	{
		TN_LOG("UTILITY");
		if (tensor.GetRank() == 0)
		{
			TN_LOG("UTILITY") << tensor();
		}
		else if (tensor.GetRank() == 1)
		{
			TN::TigiNetLogger::GetInstance() << std::endl << TN::GetLogHeader("UTILITY", "INFO");
			for (unsigned int i = 0; i < tensor.GetDimension(1); i++)
			{
				TN::TigiNetLogger::GetInstance() << tensor(i) << " ";
			}
		}
		else if (tensor.GetRank() == 2)
		{
			for (unsigned int i = 0; i < tensor.GetDimension(2); i++)
			{
				TN::TigiNetLogger::GetInstance() << std::endl << TN::GetLogHeader("UTILITY", "INFO");
				for (unsigned int j = 0; j < tensor.GetDimension(1); j++)
				{
					TN::TigiNetLogger::GetInstance() << tensor[i](j) << " ";
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < tensor.GetDimension(tensor.GetRank()); i++)
			{
				TN_LOG("UTILITY") << "(" << i << ") :";
				PrintTensor(tensor[i]);
			}
		}
	}
}

#endif
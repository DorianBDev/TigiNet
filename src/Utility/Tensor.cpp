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

#include <Utility/Tensor.hpp>
#include <Core/Error.hpp>

TN::TensorShape::TensorShape(unsigned int shape[])
{
	m_shape = shape;
	m_copy = false;
}

TN::TensorShape::TensorShape()
{
	m_shape = NULL;
	m_copy = false;
}

TN::TensorShape::~TensorShape()
{
	if (m_copy == true && m_shape != NULL)
		delete[] m_shape;
}

unsigned int TN::TensorShape::GetDimension(unsigned int rank) const
{
	if (rank == 0)
		return 1;

#if TN_SAFEMODE_TENSOR
	TN_ASSERT(m_shape != NULL, "UTILITY", "Trying to access to a non initialized TensorShape");
#endif

	return m_shape[rank - 1];
}

std::shared_ptr<TN::TensorShape> TN::TensorShape::Copy(unsigned int rank) const
{
	if (rank == 0)
		return NULL;

#if TN_SAFEMODE_TENSOR
	TN_ASSERT(m_shape != NULL, "UTILITY", "Trying to access to a non initialized TensorShape");
#endif

	std::shared_ptr<TensorShape> res = std::make_shared<TensorShape>();
	res->m_copy = true;
	res->m_shape = new unsigned int[rank];

	for (unsigned int i = 0; i < rank; i++)
		res->m_shape[i] = m_shape[i];

	return res;
}
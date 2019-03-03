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

unsigned int TN::TensorShape::GetDimension(unsigned int index) const
{
#if TN_SAFEMODE_TENSOR
	TN_ASSERT(index >= 0, "Wrong index while trying to access to a TensorShape : %d", index);
	TN_ASSERT(m_shape != NULL, "Trying to access to a non initialized TensorShape");
#endif

	return m_shape[index];
}

std::shared_ptr<TN::TensorShape> TN::TensorShape::Copy(unsigned int rank) const
{
#if TN_SAFEMODE_TENSOR
	TN_ASSERT(rank > 0, "Wrong rank while trying to copy a TensorShape");
	TN_ASSERT(m_shape != NULL, "Trying to access to a non initialized TensorShape");
#endif

	std::shared_ptr<TensorShape> res = std::make_shared<TensorShape>();
	res->m_copy = true;
	res->m_shape = new unsigned int[rank + 1];

	for (unsigned int i = 0; i <= rank; i++)
		res->m_shape[i] = m_shape[i];

	return res;
}
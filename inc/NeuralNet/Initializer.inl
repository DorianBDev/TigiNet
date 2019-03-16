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

#ifndef TN_NEURALNET_INITIALIZER_INL
#define TN_NEURALNET_INITIALIZER_INL

namespace TN
{

	/// @private
	template<typename T>
	void ZeroInitializer<T>::Initialize(Tensor<T>& tensor) const
	{
		if (tensor.GetRank() == 0)
		{
			tensor() = 0;
		}
		else if (tensor.GetRank() == 1)
		{
			for (unsigned int i = 0; i < tensor.GetDimension(1); i++)
			{
				tensor(i) = 0;
			}
		}
		else
		{
			for (unsigned int i = 0; i < tensor.GetDimension(tensor.GetRank()); i++)
			{
				Initialize(tensor[i]);
			}
		}
	}

	/// @private
	template<typename T>
	void UniformInitializer<T>::Initialize(Tensor<T>& tensor) const
	{
		double dim = 0;
		double a = 0;

		if (tensor.GetRank() == 0)
		{
			dim = 1;
			a = std::sqrt(3) / std::sqrt(dim);
			tensor() = static_cast<T>(Random<double>(-a, a));
		}
		else if (tensor.GetRank() == 1)
		{
			dim = tensor.GetDimension(1);
			a = std::sqrt(3) / std::sqrt(dim);
			for (unsigned int i = 0; i < tensor.GetDimension(1); i++)
			{
				tensor(i) = static_cast<T>(Random<double>(-a, a));
			}
		}
		else if (tensor.GetRank() == 2)
		{
			dim = tensor.GetDimension(2) * tensor.GetDimension(1);
			a = std::sqrt(3) / std::sqrt(dim);
			for (unsigned int i = 0; i < tensor.GetDimension(2); i++)
			{
				for (unsigned int j = 0; j < tensor.GetDimension(1); j++)
				{
					tensor[i](j) = static_cast<T>(Random<double>(-a, a));
				}
			}
		}
		else if (tensor.GetRank() == 3)
		{
			dim = tensor.GetDimension(3) * tensor.GetDimension(2) * tensor.GetDimension(1);
			a = std::sqrt(3) / std::sqrt(dim);
			for (unsigned int i = 0; i < tensor.GetDimension(3); i++)
			{
				for (unsigned int j = 0; j < tensor.GetDimension(2); j++)
				{
					for (unsigned int k = 0; k < tensor.GetDimension(1); k++)
					{
						tensor[i][j](k) = static_cast<T>(Random<double>(-a, a));
					}
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < tensor.GetDimension(tensor.GetRank()); i++)
			{
				Initialize(tensor[i]);
			}
		}
	}
}


#endif
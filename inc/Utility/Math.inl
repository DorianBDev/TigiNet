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

#ifndef TN_UTILITY_MATH_INL
#define TN_UTILITY_MATH_INL

namespace TN
{
	/// @private
	template<typename T>
	TN::Tensor<T>* MatrixProduct(const TN::Tensor<T> & tensor1, const TN::Tensor<T> & tensor2)
	{

#if TN_SAFEMODE_TENSOR
		TN_ASSERT(tensor1.GetRank() == 2 && tensor2.GetRank() == 2, "UTILITY", "Incompatible tensor rank");
		TN_ASSERT(tensor1.GetDimension(1) == tensor2.GetDimension(2), "UTILITY", "Incompatible tensors dimensions");
#endif

		unsigned int *shape = new unsigned int[2];
		shape[0] = tensor2.GetDimension(1); // c 2
		shape[1] = tensor1.GetDimension(2);// l 1 
		unsigned int length = tensor1.GetDimension(1); // c 1

		Tensor<T> *product = new TN::Tensor<T>(2, TN::TensorShape(shape), 2);
		unsigned int i = 0, j = 0, k = 0;
		for (i = 0; i < shape[1]; i++)
		{
			for (j = 0; j < shape[0]; j++)
			{
				(*product)[i](j) = 0;
				for (k = 0; k < length; k++)
					(*product)[i](j) += tensor1[i](k) * tensor2[k](j);
			}
		}

		delete[] shape;

		return product;
	}

	/// @private
	template<typename T, typename G>
	T Random(T min, T max)
	{
		thread_local static G gen(std::random_device{}());

		using dist_type = typename std::conditional
			<
			std::is_integral<T>::value
			, std::uniform_int_distribution<T>
			, std::uniform_real_distribution<T>
			>::type;

		thread_local static dist_type dist;

		return dist(gen, typename dist_type::param_type{ min, max });
	}
}

#endif
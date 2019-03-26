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

#ifndef TN_NEURALNET_COST_INL
#define TN_NEURALNET_COST_INL

namespace TN
{
	/// @private
	template<typename T>
	T MeanSquaredError<T>::Activation(const T& prediction, const T& result) const
	{
		return static_cast<T>(static_cast<double>(1) / static_cast<double>(2) * (prediction - result) * (prediction - result));
	}

	/// @private
	template<typename T>
	T MeanSquaredError<T>::Activation(const Tensor<T>& prediction, const Tensor<T>& result) const
	{
		TN_ASSERT(prediction.GetRank() == result.GetRank(), "NEURALNET", "Wrong tensors rank");

		if(prediction.GetRank() == 0)
			return Activation(prediction(), result());

		T res = 0;

		if (prediction.GetRank() == 1)
		{
			for (unsigned int i = 0; i < prediction.GetDimension(1); i++)
				res += Activation(prediction(i), result(i));

			return res;
		}

		for (unsigned int i = 0; i < prediction.GetDimension(prediction.GetRank()); i++)
			res += Activation(prediction[i], result[i]);

		return res;
	}

	/// @private
	template<typename T>
	T MeanSquaredError<T>::Derivation(const T& prediction, const T& result) const
	{
		return prediction - result;
	}
}

#endif
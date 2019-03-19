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

#ifndef TN_NEURALNET_OPTIMIZER_INL
#define TN_NEURALNET_OPTIMIZER_INL

namespace TN
{
	/// @private
	template<typename T>
	StochasticGradientDescent<T>::StochasticGradientDescent(double learningRate)
		: m_learningRate(learningRate)
	{

	}

	/// @private
	template<typename T>
	void StochasticGradientDescent<T>::Update(Tensor<T>& variableTensor, Tensor<T>& gradientTensor)
	{
		if (m_oldGradientTensor == NULL)
		{
			m_oldGradientTensor = new Tensor<T>(variableTensor.GetRank(), variableTensor.GetShape());
		}

		//TODO
	}
}

#endif
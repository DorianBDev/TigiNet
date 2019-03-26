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
	void Optimizer<T>::Setup(unsigned int variableCount)
	{
		m_variableCount = variableCount;
	}

	/// @private
	template<typename T>
	void Optimizer<T>::UpdateCounter()
	{
		if (m_counter + 1 >= m_variableCount)
			m_counter = 0;
		else
			m_counter++;
	}

	/// @private
	template<typename T>
	StochasticGradientDescent<T>::StochasticGradientDescent(double learningRate, double momentum)
		: m_learningRate(learningRate), m_momentum(momentum)
	{

	}

	/// @private
	template<typename T>
	StochasticGradientDescent<T>::~StochasticGradientDescent()
	{
		if(m_oldDelta != NULL)
			delete m_oldDelta;
	}

	/// @private
	template<typename T>
	void StochasticGradientDescent<T>::Setup(unsigned int variableCount)
	{
		Optimizer<T>::Setup(variableCount);

		unsigned int* shape = new unsigned int[1];
		shape[0] = variableCount;
		m_oldDelta = new Tensor<T>(1, TensorShape(shape), 1);
		delete[] shape;

		for (unsigned int i = 0; i < variableCount; i++)
			(*m_oldDelta)(i) = 0;
	}

	/// @private
	template<typename T>
	void StochasticGradientDescent<T>::Update(T& variable, T gradient, T entry)
	{
		variable = variable - m_learningRate * gradient * entry - m_momentum * (*m_oldDelta)(this->m_counter);
		(*m_oldDelta)(this->m_counter) = m_learningRate * gradient * entry + m_momentum * (*m_oldDelta)(this->m_counter);

		Optimizer<T>::UpdateCounter();
	}

	/// @private
	template<typename T>
	std::shared_ptr<Optimizer<T>> StochasticGradientDescent<T>::Copy() const
	{
		return std::make_shared<StochasticGradientDescent<T>>(m_learningRate);
	}
}

#endif
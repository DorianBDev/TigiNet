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

#ifndef TN_NEURALNET_FULLYCONNECTED_HPP
#define TN_NEURALNET_FULLYCONNECTED_HPP

#include <NeuralNet/Layer.hpp>

namespace TN
{
	template<typename T>
	class FCLayer : protected Layer<T>
	{
	public:
		FCLayer(ActivatorConfig<T> & config, unsigned int neuronsCount);
		~FCLayer();
		void Link(Layer<T> & layer);
		void Link(Tensor<T> & in);
		void Activate();
		void Update();

	private:
		Tensor<T>* m_weight = NULL;
		Tensor<T>* m_bias = NULL;
		unsigned int m_neuronsCount;

	};
}

#include <NeuralNet/Layer/FullyConnected.inl>

#endif
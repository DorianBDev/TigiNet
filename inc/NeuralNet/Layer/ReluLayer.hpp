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

#ifndef TN_NEURALNET_RELULAYER_HPP
#define TN_NEURALNET_RELULAYER_HPP

#include <NeuralNet/Layer.hpp>

namespace TN
{

	/**
	* @class ReluLayer
	* @brief RELU layer.
	*
	* Create a RELU layer.
	*
	* @see Layer
	*
	*/
	template<typename T>
	class ReluLayer : public Layer<T>
	{
	public:
		ReluLayer();
		~ReluLayer();

		/**
		* @brief Link a layer to this layer.
		*
		* @param layer : the layer to link with.
		*
		*/
		void Link(Layer<T>& layer);

		/**
		* @brief Link an input tensor to this layer.
		*
		* @param in : the input tensor to link with.
		*
		*/
		void Link(Tensor<T>& in);

		/**
		* @brief Forward propagation.
		*
		*/
		void Activate();

		/**
		* @brief Backward propagation.
		*
		*/
		void Update();

		/**
		* @brief Save the layer in a file.
		* 
		* The layer topology need to be exactly the same (pre-linked layer). The function will only save trainable data and not the topology.
		* 
		* @param file : the file to save in.
		*
		*/
		void SaveInFile(std::ofstream& file);

		/**
		* @brief Load the layer from a file.
		*
		* The layer topology need to be exactly the same (pre-linked layer). The function will only load trainable data and not the topology.
		*
		* @param file : the file to load from.
		*
		*/
		void LoadFromFile(std::ifstream& file);
	};
}

#include <NeuralNet/Layer/ReluLayer.inl>

#endif
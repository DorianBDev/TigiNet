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

#ifndef TN_UTILITY_LAYER_HPP
#define TN_UTILITY_LAYER_HPP

#include <Utility/Neurone.hpp>
#include <Utility/Link.hpp>

namespace TN
{

	/**
	* @class Layer
	* @brief A layer is simply a table of neurones.
	*
	*/
	class TN_UTILITY Layer
	{

	public:

		/**
		* @brief Create a layer.
		*
		* @param size : the number of neurones in the layer.
		* @param tabValues : the table of values of all neurones (size elements, one per neurones).
		*
		*/
		Layer(size_t size, double* tabValues = NULL);
		~Layer();

		/**
		* @brief Get the neurone value from his index.
		*
		* @param index : the index of the neurone.
		*
		* @return Return the neurone value.
		*
		*/
		double GetNeuroneValue(size_t index);

		/**
		* @brief Set the neurone value from his index.
		*
		* @param index : the index of the neurone.
		* @param value : the new value of the neurone.
		*
		*/
		void SetNeuroneValue(size_t index, double value);

		/**
		* @brief Get the size of the layer (neurones count).
		*
		* @return Return the size of the layer.
		*
		*/
		size_t GetSize();

		/**
		* @brief Get a neurone from an index.
		*
		* @param index : the index of the neurone.
		*
		* @return Return the neurone.
		*
		*/
		std::shared_ptr<Neurone> GetNeurone(unsigned int index);

		/**
		* @brief Link all neurones of this layers with all of the other layer.
		*
		* @param layer : the other layer.
		*
		*/
		void LinkAllWithAll(Layer* layer);

		/**
		* @brief Link all neurones of this layer to all neurone in [0,_to[
		*
		* @param layer : the other layer.
		* @param to : to what index link all neurones.
		*
		*/
		void LinkAllWith(Layer* layer, size_t to);

		/**
		* @brief Link all neurones in [0,_from[ of this layer to all neurone in [0,_to[
		*
		* @param layer : the other layer.
		* @param from : from what index link all neurones
		* @param to : to what index link all neurones.
		*
		*/
		void LinkWith(Layer* layer, size_t from, size_t to);

		/**
		* @brief Link all neurones of this layers with all of the other layer.
		*
		* @param layer : the other layer.
		*
		*/
		void LinkAllWithAll(std::shared_ptr<Layer> layer);

		/**
		* @brief Link all neurones of this layer to all neurone in [0,_to[
		*
		* @param layer : the other layer.
		* @param to : to what index link all neurones.
		*
		*/
		void LinkAllWith(std::shared_ptr<Layer> layer, size_t to);

		/**
		* @brief Link all neurones in [0,_from[ of this layer to all neurone in [0,_to[
		*
		* @param layer : the other layer.
		* @param from : from what index link all neurones
		* @param to : to what index link all neurones.
		*
		*/
		void LinkWith(std::shared_ptr<Layer> layer, size_t from, size_t to);

		/**
		* @brief Add a new neurone to the layer.
		*
		* @param val : the value of this new neurone.
		*
		*/
		void AddNeurone(double val = 0.5);


	private:

		void* m_neurones;

	};


	/**
	* @class Layers
	* @brief A table of layers.
	*
	*/
	class TN_UTILITY Layers
	{
	public:

		/**
		* @brief Create a table of layers.
		*
		*/
		Layers();
		~Layers();

		/**
		* @brief Get a layer from an index.
		*
		* @param index : the index of the layer.
		*
		* @return Return the layer.
		*
		*/
		std::shared_ptr<Layer> GetLayer(size_t index);


		/**
		* @brief Add a new layer, the class will destroy the pointer for you.
		*
		* @param layer : the new layer to add.
		*
		*/
		void AddLayer(Layer* layer);

		/**
		* @brief Add a new layer.
		*
		* @param layer : the new layer to add.
		*
		*/
		void AddLayer(std::shared_ptr<Layer> layer);

		/**
		* @brief Delete a layer.
		*
		* @param index : the index of the layer to delete.
		*
		*/
		void DeleteLayer(size_t index);

		/**
		* @brief Get the count of layers.
		*
		* @return Return the count of layers.
		*
		*/
		size_t GetCount();

		/**
		* @brief Clear all layers.
		*
		*/
		void Clear();


	private:

		void* m_layers;

	};

}

#endif
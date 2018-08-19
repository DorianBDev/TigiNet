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

#ifndef TN_UTILITY_LINK_HPP
#define TN_UTILITY_LINK_HPP

#include <Utility/Config.hpp>

#include <memory>

namespace TN
{

	class Neurone;

	/*! Linked neurone type */
	typedef enum __linked_neurone_type_e
	{
		AS_ORIGIN,	/*!< Linked as origin of the link */
		AS_TARGET	/*!< Linked as target of the link */
	}LinkedNeuroneType_e;


	/**
	* @class Link
	* @brief A link between two neurones.
	*
	* Use as a link between two neurones.
	*
	*/
	class TN_UTILITY Link
	{

	public:

		/**
		* @brief Create a link between two neurones with a certain weight.
		*
		* @param firstNeurone : the first neurone to link (as origin).
		* @param secondNeurone : the second neurone to link (as target).
		* @param weight : the weight of the link.
		*
		*/
		Link(Neurone* firstNeurone, Neurone* secondNeurone, double weight);

		/**
		* @brief Create a link between two neurones with a random weight.
		*
		* @param firstNeurone : the first neurone to link (as origin).
		* @param secondNeurone : the second neurone to link (as target).
		* @param max : the maximum value for the weight.
		* @param min : the minimal value for the weight.
		*
		*/
		Link(Neurone* firstNeurone, Neurone* secondNeurone, double max, double min);

		~Link();

		/**
		**@brief Get the first neurone of the link (the origin).
		*
		* @return Return the first neurone of the link (the origin).
		*
		*/
		Neurone* GetFirstNeurone();

		/**
		* @brief Get the second neurone of the link (the target).
		*
		* @return Return the second neurone of the link (the target).
		*
		*/
		Neurone* GetSecondNeurone();

		/**
		* @brief Get the weight of the link.
		*
		* @return Return the weight of the link.
		*
		*/
		double GetWeight();

		/**
		* @brief Get the previous delta of the link.
		*
		* @return Return the previous delta of the link.
		*
		*/
		double GetPreviousDelta();

		/**
		* @brief Set the weight of the link.
		*
		* @param weight : the new weight.
		*
		*/
		void SetWeight(double weight);

		/**
		* @brief Set the previous delta.
		*
		* @param previousDelta : the new previous delta.
		*
		*/
		void SetPreviousDelta(double previousDelta);

		/**
		* @brief Get the other linked neurone by passing one neurone.
		*
		* @param askerNeurone : one neurone.
		*
		* @return Return the other neurone.
		*
		*/
		Neurone* GetLinkedNeurone(Neurone* askerNeurone);

		/**
		* @brief Get the other linked neurone by passing one type.
		*
		* @param askerType : the type of one neurone.
		*
		* @return Return the other neurone.
		*
		*/
		Neurone* GetLinkedNeurone(LinkedNeuroneType_e askerType);


	private:

		Neurone* m_firstNeurone = NULL;
		Neurone* m_secondNeurone = NULL;

		double m_weight = 0.5;
		double m_previousDelta = 0;
	};


	/**
	* @class Links
	* @brief A table of links.
	*
	*/
	class TN_UTILITY Links
	{

	public:

		Links();

		~Links();

		/**
		* @brief Get a link from an index.
		*
		* @param index : the index of the link.
		*
		* @return Return the link as pointer.
		*
		*/
		std::shared_ptr<Link> GetLink(size_t index);

		/**
		* @brief Add a link.
		*
		* @param link : the new new link.
		*
		*/
		void AddLink(std::shared_ptr<Link> link);

		/**
		* @brief Add a link, the class will destroy the pointer for you.
		*
		* @param link : the new new link.
		*
		*/
		void AddLink(Link* link);

		/**
		* @brief Delete a link.
		*
		* @param index : the index of the link to delete.
		*
		*/
		void DeleteLink(size_t index);

		/**
		* @brief Get the links count.
		*
		* @return Return the links count.
		*
		*/
		size_t GetCount();

		/**
		* @brief Clear all links.
		*
		*/
		void Clear();


	private:

		void* m_links;

	};

}


#endif
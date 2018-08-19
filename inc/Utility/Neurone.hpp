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

#ifndef TN_UTILITY_NEURONE_HPP
#define TN_UTILITY_NEURONE_HPP

#include <Utility/Config.hpp>
#include <Utility/Link.hpp>

namespace TN
{

	/*
	*	(Neurone A) ------->--------[Link 1]------->-------- (Neurone B)
	*	  Origin											 Target
	*
	*	For (Neurone A) [Link 1] is an origin link because (Neurone A) is the origin of the link and for (Neurone B) [Link 1] is a target link because he is the target of the link, not the origin.
	*
	*/

	/**
	* @class Neurone
	* @brief A neurone class.
	*
	*/
	class TN_UTILITY Neurone
	{

	public:

		/**
		* @brief Create a neruone.
		*
		* @param value : the default value of the neurone.
		* @param threshold : the threshold (bias) of the neurone.
		*
		*/
		Neurone(double value = 0.5, double threshold = 1);
		~Neurone();

		/**
		* @brief Get the local gradiant of the neurone.
		*
		* @return Return the local gradiant of the neurone.
		*
		*/
		double GetLocalGradiant();

		/**
		* @brief Set the local gradiant of the neurone.
		*
		* @param value : the new local gradiant.
		*
		*/
		void SetLocalGradiant(double value);

		/**
		* @brief Get the value of the neurone.
		*
		* @return Return the value of the neurone.
		*
		*/
		double GetValue();

		/**
		* @brief Set the value of the neurone.
		*
		* @param value : the new value of the neurone.
		*
		*/
		void SetValue(double value);

		/**
		* @brief Get the threshold value of the neurone.
		*
		* @return Return the threshold value of the neurone.
		*
		*/
		double GetThresholdValue();

		/**
		* @brief Set the threshold value of the neurone.
		*
		* @param thresholdValue : the new threshold value of the neurone.
		*
		*/
		void SetThresholdValue(double thresholdValue);

		/**
		* @brief Get the threshold weight of the neurone.
		*
		* @return Return the threshold weight of the neurone.
		*
		*/
		double GetThresholdWeight();

		/**
		* @brief Set the threshold weight of the neurone.
		*
		* @param thresholdWeight : the new threshold weight of the neurone.
		*
		*/
		void SetThresholdWeight(double thresholdWeight);

		/**
		* @brief Get the threshold last delta of the neurone.
		*
		* @return Return the threshold last delta of the neurone.
		*
		*/
		double GetThresholdLastDelta();

		/**
		* @brief Set the threshold last delta of the neurone.
		*
		* @param thresholdLastDelta : the new threshold last delta of the neurone.
		*
		*/
		void SetThresholdLastDelta(double thresholdLastDelta);

		/**
		* @brief Get the origin links of the neurone.
		*
		* @return Return the origin links of the neurone.
		*
		*/
		Links* GetOriginLinks();

		/**
		* @brief Get the target links of the neurone.
		*
		* @return Return the target links of the neurone.
		*
		*/
		Links* GetTargetLinks();


	private:

		/* Value of the neurone */
		double m_value;

		/* Bias value of the neurone */
		double m_threshold;

		/* Bias weight value of the neurone */
		double m_thresholdWeight = 0.5;

		double m_localGradiant = 0;

		double m_thresholdLastDelta = 0;

		/* Links where the neurone is the origin */
		Links* m_originLinks;

		/* Links where the neurone is the target/destination */
		Links* m_targetLinks;

	};

	/**
	* @brief Link two neurones.
	*
	* @param firstNeurone : the first neurone (as origin).
	* @param secondNeurone : the second neurone (as target).
	* @param max : the maximum value for the weight of the new link.
	* @param min : the minimal value for the weight of the new link.
	*
	* @return Return the new link.
	*
	*/
	std::shared_ptr<Link> LinkNeurones(Neurone* firstNeurone, Neurone* secondNeurone, double max = 1, double min = -1);

}

#endif
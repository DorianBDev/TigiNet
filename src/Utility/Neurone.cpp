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

#include <Utility/Neurone.hpp>

TN::Neurone::Neurone(double value, double threshold)
{
	m_value = value;
	m_threshold = threshold;

	m_originLinks = new Links();
	m_targetLinks = new Links();
}

TN::Neurone::~Neurone()
{
	delete m_originLinks;
	delete m_targetLinks;
}

double TN::Neurone::GetLocalGradiant()
{
	return m_localGradiant;
}

void TN::Neurone::SetLocalGradiant(double _val)
{
	m_localGradiant = _val;
}

double TN::Neurone::GetValue()
{
	return m_value;
}

void TN::Neurone::SetValue(double value)
{ 
	m_value = value; 
}

double TN::Neurone::GetThresholdValue()
{
	return m_threshold; 
}

void TN::Neurone::SetThresholdValue(double thresholdValue)
{ 
	m_threshold = thresholdValue; 
}

double TN::Neurone::GetThresholdWeight()
{ 
	return m_thresholdWeight;
}

void TN::Neurone::SetThresholdWeight(double thresholdWeight)
{ 
	m_thresholdWeight = thresholdWeight;
}

double TN::Neurone::GetThresholdLastDelta()
{
	return m_thresholdLastDelta;
}

void TN::Neurone::SetThresholdLastDelta(double thresholdLastDelta)
{
	m_thresholdLastDelta = thresholdLastDelta;
}

TN::Links* TN::Neurone::GetOriginLinks()
{
	return m_originLinks;
}

TN::Links* TN::Neurone::GetTargetLinks()
{
	return m_targetLinks;
}

std::shared_ptr<TN::Link> TN::LinkNeurones(Neurone* firstNeurone, Neurone* secondNeurone, double max, double min)
{
	std::shared_ptr<Link> link = std::shared_ptr<Link>(new Link(firstNeurone, secondNeurone, max, min));

	firstNeurone->GetOriginLinks()->AddLink(link);
	secondNeurone->GetTargetLinks()->AddLink(link);

	return link;
}
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

#include <Utility/Link.hpp>

#include <vector>
#include <stdlib.h>

#define M_LINKS static_cast<std::vector<std::shared_ptr<Link>>*>(m_links)



/*****************************/
/**			Link			**/
/*****************************/

TN::Link::Link(Neurone* firstNeurone, Neurone* secondNeurone, double weight)
{
	m_firstNeurone = firstNeurone;
	m_secondNeurone = secondNeurone;

	m_weight = weight;
}

TN::Link::Link(Neurone* firstNeurone, Neurone* secondNeurone, double max, double min)
{
	m_firstNeurone = firstNeurone;
	m_secondNeurone = secondNeurone;

	m_weight = min + (double)rand() / RAND_MAX * (max + 1);
}

TN::Link::~Link() { }

 TN::Neurone* TN::Link::GetFirstNeurone()
{
	return m_firstNeurone;
}

 TN::Neurone* TN::Link::GetSecondNeurone()
{
	return m_secondNeurone;
}

double TN::Link::GetWeight()
{
	return m_weight;
}

double TN::Link::GetPreviousDelta()
{
	return m_previousDelta;
}

void TN::Link::SetWeight(double weight)
{
	m_weight = weight;
}

void TN::Link::SetPreviousDelta(double previousDelta)
{
	m_previousDelta = previousDelta;
}

TN::Neurone* TN::Link::GetLinkedNeurone(Neurone* askerNeurone)
{
	if (askerNeurone == m_firstNeurone)
		return m_secondNeurone;
	else
		return m_firstNeurone;
}

TN::Neurone* TN::Link::GetLinkedNeurone(LinkedNeuroneType_e askerType)
{
	if (askerType == AS_ORIGIN)
		return m_secondNeurone;
	else
		return m_firstNeurone;
}



/*****************************/
/**			Links			**/
/*****************************/

TN::Links::Links()
{
	m_links = new std::vector<std::shared_ptr<Link>>();
};

TN::Links::~Links()
{
	delete M_LINKS;
}

std::shared_ptr<TN::Link> TN::Links::GetLink(size_t index)
{
	return M_LINKS->at(index);
}

void TN::Links::AddLink(std::shared_ptr<Link> link)
{
	M_LINKS->push_back(link);
}

void TN::Links::AddLink(Link* link)
{
	M_LINKS->push_back(std::shared_ptr<Link>(link));
}

void TN::Links::DeleteLink(size_t index)
{
	M_LINKS->erase(M_LINKS->begin() + index);
	M_LINKS->shrink_to_fit();
}

size_t TN::Links::GetCount()
{
	return M_LINKS->size();
}

void TN::Links::Clear()
{
	M_LINKS->clear();
}
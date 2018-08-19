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

#include <Utility/Layer.hpp>

#include <vector>

#define M_NEURONES static_cast<std::vector<std::shared_ptr<Neurone>>*>(m_neurones)
#define M_LAYERS static_cast<std::vector<std::shared_ptr<Layer>>*>(m_layers)



/*****************************/
/**			Layer			**/
/*****************************/

TN::Layer::Layer(size_t size, double* tabValues)
{
	size_t i = 0;

	m_neurones = new std::vector<std::shared_ptr<Neurone>>();

	for (i = 0; i < size; i++)
	{
		if (tabValues != NULL)
			M_NEURONES->push_back(std::shared_ptr<Neurone>(new Neurone(tabValues[i])));
		else
			M_NEURONES->push_back(std::shared_ptr<Neurone>(new Neurone()));
	}
}

TN::Layer::~Layer()
{
	delete M_NEURONES;
}

double TN::Layer::GetNeuroneValue(size_t index)
{
	return M_NEURONES->at(index)->GetValue();
}

void TN::Layer::SetNeuroneValue(size_t index, double value)
{
	M_NEURONES->at(index)->SetValue(value);
}

size_t TN::Layer::GetSize()
{
	return M_NEURONES->size();
}

std::shared_ptr<TN::Neurone> TN::Layer::GetNeurone(unsigned int index)
{ 
	return M_NEURONES->at(index);
}

void TN::Layer::LinkAllWithAll(Layer* layer)
{
	unsigned int i, j;
	for (i = 0; i < M_NEURONES->size(); i++)
	{
		for (j = 0; j < layer->GetSize(); j++)
		{
			LinkNeurones(M_NEURONES->at(i).get(), layer->GetNeurone(j).get());
		}
	}
}

void TN::Layer::LinkAllWith(Layer* layer, size_t to)
{
	unsigned int i, j;
	for (i = 0; i < M_NEURONES->size(); i++)
	{
		for (j = 0; j < to; j++)
		{
			LinkNeurones(M_NEURONES->at(i).get(), layer->GetNeurone(j).get());
		}
	}
}

void TN::Layer::LinkWith(Layer* layer, size_t from, size_t to)
{
	unsigned int i, j;
	for (i = 0; i < from; i++)
	{
		for (j = 0; j < to; j++)
		{
			LinkNeurones(M_NEURONES->at(i).get(), layer->GetNeurone(j).get());
		}
	}
}

void TN::Layer::LinkAllWithAll(std::shared_ptr<Layer> layer)
{
	LinkAllWithAll(layer.get());
}

void TN::Layer::LinkAllWith(std::shared_ptr<Layer> layer, size_t to)
{
	LinkAllWith(layer.get(), to);
}

void TN::Layer::LinkWith(std::shared_ptr<Layer> layer, size_t from, size_t to)
{
	LinkWith(layer.get(), from, to);
}

void TN::Layer::AddNeurone(double value)
{
	M_NEURONES->push_back(std::shared_ptr<Neurone>(new Neurone(value)));
}



/*****************************/
/**			Layers			**/
/*****************************/

TN::Layers::Layers()
{
	m_layers = new std::vector<std::shared_ptr<Layer>>();
}

TN::Layers::~Layers()
{
	delete M_LAYERS;
}

std::shared_ptr<TN::Layer> TN::Layers::GetLayer(size_t index)
{
	return M_LAYERS->at(index);
}

void TN::Layers::AddLayer(Layer* layer)
{
	M_LAYERS->push_back(std::shared_ptr<Layer>(layer));
}

void TN::Layers::AddLayer(std::shared_ptr<Layer> layer)
{
	M_LAYERS->push_back(layer);
}

void TN::Layers::DeleteLayer(size_t index)
{
	M_LAYERS->erase(M_LAYERS->begin() + index);
	M_LAYERS->shrink_to_fit();
}

size_t TN::Layers::GetCount()
{
	return M_LAYERS->size();
}

void TN::Layers::Clear()
{
	M_LAYERS->clear();
}
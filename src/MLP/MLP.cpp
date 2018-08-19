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

#include <MLP/MLP.hpp>

#include <time.h>
#include <stdlib.h>
#include <math.h>


TN::MLP::MLP(double errorAcceptance, double learningLevel, double momentum, double(*activationFunction)(double), size_t layerCount, unsigned int* neuronePerLayerTable)
{
	TN_LOG("A NEURAL NETWORK IS IN CREATION...")

	srand((unsigned int)time(NULL));

	m_errorAcceptance = errorAcceptance;
	m_learningLevel = learningLevel;
	m_momentum = momentum;
	ActivationFunction = activationFunction;
	m_layerCount = layerCount;

	if (neuronePerLayerTable == NULL)
	{
		m_neuronePerLayerTable = new size_t[2];
		m_neuronePerLayerTable[0] = 1;
		m_neuronePerLayerTable[1] = 1;
	}
	else
	{
		m_neuronePerLayerTable = new size_t[layerCount];

		unsigned int i;
		for (i = 0; i < layerCount; i++)
			m_neuronePerLayerTable[i] = neuronePerLayerTable[i];
	}

	TN_LOG("Layer count : %zu", m_layerCount);

	TN_LOG("THE NETWORK IS : A MULTILAYER PERCEPTRON WITH BIAS")
			
	unsigned int i;
	for (i = 0; i < m_layerCount; i++)
	{
		m_layers.AddLayer(new Layer(m_neuronePerLayerTable[i]));
	}

	for (i = 0; i < m_layerCount - 1; i++)
	{
		m_layers.GetLayer(i)->LinkAllWithAll(m_layers.GetLayer(i + 1));
	}

	delete[] m_neuronePerLayerTable;
}

TN::MLP::~MLP()
{

}

void TN::MLP::LearnSimple(double* valIn, double* valOut)
{
	TN_LOG("Learning single sample...")

	do
	{
		Browse(valIn);
		RetroPropagation(valOut);
		CalculateError(valOut);
		TN_LOG_CONSOLE("INFO", "Learning error : %f", m_error);

	} while (sqrt(m_error) > m_errorAcceptance);

	TN_LOG("Stopping learning single sample, error : %f", m_error);
}

void TN::MLP::Learn(double** valIn, double** valOut, size_t size)
{
	TN_LOG("Learning...")

	double moy_error;

	/* Sizes */
	size_t inSize = m_layers.GetLayer(0)->GetSize();
	size_t outSize = GetLastLayerSize();

	/* Inits */
	size_t i, j;
	int rand1, rand2;
	double tempIn;
	double tempOut;

	do
	{
		moy_error = 0;

		
		/* Mix in and out tables */

		for (i = 0; i < size; i++)
		{
			rand1 = my_rand(static_cast<int>(size) - 1, 0);
			rand2 = my_rand(static_cast<int>(size) - 1, 0);

			for (j = 0; j < inSize; j++)
			{
				tempIn = valIn[rand1][j];
				valIn[rand1][j] = valIn[rand2][j];
				valIn[rand2][j] = tempIn;
			}

			for (j = 0; j < outSize; j++)
			{
				tempOut = valOut[rand1][j];
				valOut[rand1][j] = valOut[rand2][j];
				valOut[rand2][j] = tempOut;
			}
		}

		
		/* Start learning all examples */

		for (i = 0; i < size; i++)
		{
			Browse(valIn[i]);
			RetroPropagation(valOut[i]);
			CalculateError(valOut[i]);
			moy_error += m_error;
		}

		moy_error = sqrt(moy_error / size);
		//TN_LOG_CONSOLE("INFO", "Learning error : %f", moy_error);

	} while (moy_error > m_errorAcceptance);

	TN_LOG("Stopping learning, error : %f", moy_error);
}

void TN::MLP::Learn(String path)
{
	TN::File file(path, TN::FileMode_e::FM_READ);

	if (!file.IsFileOpen())
		TN_ERROR("File can't be open")

	size_t size = 0;
	size_t inSize = m_layers.GetLayer(0)->GetSize();
	size_t outSize = GetLastLayerSize();

	size_t i, j;

	file.Read("count: %zu\n", &size);

	double **in = new double*[size];
	for (i = 0; i < size; i++)
		in[i] = new double[inSize];

	double **out = new double*[size];
	for (i = 0; i < size; i++)
		out[i] = new double[outSize];

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < inSize; j++)
		{
			file.Read("%lf", &in[i][j]);
		}

		file.Read("\n");

		for (j = 0; j < outSize; j++)
		{
			file.Read("%lf", &out[i][j]);
		}
		file.Read("\n\n");
	}

	Learn(in, out, size);

	for (i = 0; i < size; i++)
		delete[] in[i];
	delete[] in;

	for (i = 0; i < size; i++)
		delete[] out[i];
	delete[] out;
}

void TN::MLP::Browse(double* valIn)
{
	unsigned int i = 0, j = 0, k = 0;

	for (i = 0; i < m_layers.GetLayer(0)->GetSize(); i++)
		m_layers.GetLayer(0)->SetNeuroneValue(i, valIn[i]);

	/* For each layer, except the first */
	for (i = 1; i < m_layers.GetCount(); i++)
	{
		/* For each neurone in this layer */
		for (j = 0; j < m_layers.GetLayer(i)->GetSize(); j++)
		{
			double sum = 0;

			/* For each link of the neurone */
			for (k = 0; k < m_layers.GetLayer(i)->GetNeurone(j)->GetTargetLinks()->GetCount(); k++)
			{
				/* SUM IN i TO link number = previous k link weight TIMES previous neurone value in the k link PLUS threshold value */
				sum += m_layers.GetLayer(i)->GetNeurone(j)->GetTargetLinks()->GetLink(k)->GetWeight() * m_layers.GetLayer(i)->GetNeurone(j)->GetTargetLinks()->GetLink(k)->GetLinkedNeurone(AS_TARGET)->GetValue();
			}

			/* Add bias */
			sum += m_layers.GetLayer(i)->GetNeurone(j)->GetThresholdValue() * m_layers.GetLayer(i)->GetNeurone(j)->GetThresholdWeight();

			/* Neurone value = activation function (sum) */
			m_layers.GetLayer(i)->GetNeurone(j)->SetValue(ActivationFunction(sum));
		}
	}
}

void TN::MLP::Browse(String path, unsigned int index)
{
	TN::File file(path, TN::FileMode_e::FM_READ);

	if (!file.IsFileOpen())
		TN_ERROR("File can't be open")

	size_t size = 0;
	size_t inSize = m_layers.GetLayer(0)->GetSize();

	size_t i, j;

	file.Read("count: %zu\n\n", &size);

	TN_ASSERT(index <= size, "Wrong index, index > size can't be possible")
	TN_ASSERT(index > 0, "Wrong index, index < 1 can't be possible")

	double *in = new double[inSize];

	for (i = 0; i < index; i++)
	{
		if (i + 1 != index)
		{
			file.SkipLines(2);
			continue;
		}

		for (j = 0; j < inSize; j++)
		{
			file.Read("%lf", &in[j]);
		}
		break;
	}

	Browse(in);

	delete[] in;
}

void TN::MLP::RetroPropagation(double* valOut)
{
	unsigned int i, j, k, l;

	double delta = 0;
	double deltas = 0;

	/* For all neurones in the last layer */
	for (j = 0; j < GetLastLayerSize(); j++)
	{
		deltas = valOut[j] - m_layers.GetLayer(GetLastLayerIndice())->GetNeuroneValue(j);

		/* Bias */
		delta = m_learningLevel * deltas * m_layers.GetLayer(GetLastLayerIndice())->GetNeuroneValue(j) * (1 - m_layers.GetLayer(GetLastLayerIndice())->GetNeuroneValue(j)) * m_layers.GetLayer(GetLastLayerIndice())->GetNeurone(j)->GetThresholdValue();
		m_layers.GetLayer(GetLastLayerIndice())->GetNeurone(j)->SetThresholdWeight(m_momentum * delta + m_layers.GetLayer(GetLastLayerIndice())->GetNeurone(j)->GetThresholdWeight() + (1 - m_momentum) * m_layers.GetLayer(GetLastLayerIndice())->GetNeurone(j)->GetThresholdLastDelta());
		m_layers.GetLayer(GetLastLayerIndice())->GetNeurone(j)->SetThresholdLastDelta(delta);

		/* Set local gradiant */
		m_layers.GetLayer(GetLastLayerIndice())->GetNeurone(j)->SetLocalGradiant(deltas * m_layers.GetLayer(GetLastLayerIndice())->GetNeuroneValue(j) * (1 - m_layers.GetLayer(GetLastLayerIndice())->GetNeuroneValue(j)));

		/* All links of the neurone */
		delta = 0;
		for (k = 0; k < m_layers.GetLayer(GetLastLayerIndice())->GetNeurone(j)->GetTargetLinks()->GetCount(); k++)
		{
			delta = m_learningLevel * m_layers.GetLayer(GetLastLayerIndice())->GetNeurone(j)->GetLocalGradiant() * m_layers.GetLayer(GetLastLayerIndice())->GetNeurone(j)->GetTargetLinks()->GetLink(k)->GetLinkedNeurone(AS_TARGET)->GetValue();
			m_layers.GetLayer(GetLastLayerIndice())->GetNeurone(j)->GetTargetLinks()->GetLink(k)->SetWeight(m_layers.GetLayer(GetLastLayerIndice())->GetNeurone(j)->GetTargetLinks()->GetLink(k)->GetWeight() + m_momentum * delta + (1 - m_momentum) * m_layers.GetLayer(GetLastLayerIndice())->GetNeurone(j)->GetTargetLinks()->GetLink(k)->GetPreviousDelta());
			m_layers.GetLayer(GetLastLayerIndice())->GetNeurone(j)->GetTargetLinks()->GetLink(k)->SetPreviousDelta(delta);
			delta = 0;
		}
	}
	/* wji : j current layer and i previous layer */


	/* Formulas for others hidden layers */
	/* From the previous layer minus one to the first layer plus one */
	for (i = static_cast<unsigned int>(m_layers.GetCount()) - 2; i > 0; i--)
	{
		for (j = 0; j < m_layers.GetLayer(i)->GetSize(); j++)
		{
			double sum = 0;

			/* For all next link */
			for (l = 0; l < m_layers.GetLayer(i)->GetNeurone(j)->GetOriginLinks()->GetCount(); l++)
				sum += m_layers.GetLayer(i)->GetNeurone(j)->GetOriginLinks()->GetLink(l)->GetLinkedNeurone(AS_ORIGIN)->GetLocalGradiant() * m_layers.GetLayer(i)->GetNeurone(j)->GetOriginLinks()->GetLink(l)->GetWeight();

			/* Set local gradiant */
			m_layers.GetLayer(i)->GetNeurone(j)->SetLocalGradiant(m_layers.GetLayer(i)->GetNeurone(j)->GetValue() * (1 - m_layers.GetLayer(i)->GetNeurone(j)->GetValue()) * sum);

			/* Bias */
			delta = m_learningLevel * m_layers.GetLayer(i)->GetNeurone(j)->GetLocalGradiant() * m_layers.GetLayer(i)->GetNeurone(j)->GetThresholdValue();
			m_layers.GetLayer(i)->GetNeurone(j)->SetThresholdWeight(m_momentum * delta + m_layers.GetLayer(i)->GetNeurone(j)->GetThresholdWeight() + (1 - m_momentum) * m_layers.GetLayer(i)->GetNeurone(j)->GetThresholdLastDelta());
			m_layers.GetLayer(i)->GetNeurone(j)->SetThresholdLastDelta(delta);

			/* All links of the neurone */
			delta = 0;
			for (k = 0; k < m_layers.GetLayer(i)->GetNeurone(j)->GetTargetLinks()->GetCount(); k++)
			{
				delta = m_learningLevel * m_layers.GetLayer(i)->GetNeurone(j)->GetLocalGradiant() * m_layers.GetLayer(i)->GetNeurone(j)->GetTargetLinks()->GetLink(k)->GetLinkedNeurone(AS_TARGET)->GetValue();
				m_layers.GetLayer(i)->GetNeurone(j)->GetTargetLinks()->GetLink(k)->SetWeight(m_layers.GetLayer(i)->GetNeurone(j)->GetTargetLinks()->GetLink(k)->GetWeight() + m_momentum * delta + (1 - m_momentum) * m_layers.GetLayer(i)->GetNeurone(j)->GetTargetLinks()->GetLink(k)->GetPreviousDelta());
				m_layers.GetLayer(i)->GetNeurone(j)->GetTargetLinks()->GetLink(k)->SetPreviousDelta(delta);
				delta = 0;
			}
		}
	}
}

void TN::MLP::CalculateError(double* valOut)
{
	unsigned int i;

	m_error = 0;

	/* Browse the last layer */
	for (i = 0; i < GetLastLayerSize(); i++)
	{
		m_error += (valOut[i] - m_layers.GetLayer(m_layers.GetCount() - 1)->GetNeuroneValue(i)) * (valOut[i] - m_layers.GetLayer(m_layers.GetCount() - 1)->GetNeuroneValue(i));
	}

	m_error = 0.5 * m_error;
}

void TN::MLP::PrintNeuronesValues()
{
	unsigned int i, j;

	TN_LOG("")
	TN_LOG("-----------------------------------------")
	TN_LOG("Printing neurones values...")
	TN_LOG("-----------------------------------------")

	for (i = 0; i < m_layers.GetCount(); i++)
	{
		String txt;

		TN_LOG("Layer %u :", static_cast<unsigned int>(i + 1));

		for (j = 0; j < m_layers.GetLayer(i)->GetSize(); j++)
		{
			txt += ToString("%lf (%lf) ", m_layers.GetLayer(i)->GetNeuroneValue(j), m_layers.GetLayer(i)->GetNeurone(j)->GetThresholdValue());
		}

		TN_LOG(txt)
	}

	TN_LOG("-----------------------------------------")
	TN_LOG("")
}

void TN::MLP::PrintLinksValues()
{
	unsigned int i, j, k;

	TN_LOG("")
	TN_LOG("-----------------------------------------")
	TN_LOG("Printing links values...")
	TN_LOG("-----------------------------------------")

	for (i = 0; i < m_layers.GetCount(); i++)
	{
		TN_LOG("Layer %u :", static_cast<unsigned int>(i + 1));

		for (j = 0; j < m_layers.GetLayer(i)->GetSize(); j++)
		{
			String txt;

			TN_LOG("Neurone %u (%lf) :", static_cast<unsigned int>(j + 1), m_layers.GetLayer(i)->GetNeurone(j)->GetThresholdWeight());


			for (k = 0; k < m_layers.GetLayer(i)->GetNeurone(j)->GetOriginLinks()->GetCount(); k++)
			{
				txt += ToString("%lf ", m_layers.GetLayer(i)->GetNeurone(j)->GetOriginLinks()->GetLink(k)->GetWeight());
			}

			TN_LOG(txt)
		}

		TN_LOG("")
	}

	TN_LOG("-----------------------------------------")
	TN_LOG("")
}

void TN::MLP::PrintLayersData()
{
	unsigned int i;

	TN_LOG("")
	TN_LOG("-----------------------------------------")
	TN_LOG("Printing layers data...");
	TN_LOG("-----------------------------------------")

	for (i = 0; i < m_layers.GetCount(); i++)
	{
		TN_LOG(ToString("Layer %u : %u neurones", i + 1, m_layers.GetLayer(i)->GetSize()))
	}

	TN_LOG("-----------------------------------------")
	TN_LOG("")
}

void TN::MLP::PrintAll()
{
	TN_LOG("")
	TN_LOG("")
	TN_LOG("=========================================")
	TN_LOG("Printing all data...")
	TN_LOG("=========================================")
	PrintLayersData();
	PrintNeuronesValues();
	PrintLinksValues();
	TN_LOG("=========================================")
	TN_LOG("")
	TN_LOG("")
}

void TN::MLP::PrintResults()
{
	unsigned int j;

	TN_LOG("")
	TN_LOG("=========================================")
	TN_LOG("Printing neurones values...")
	TN_LOG("=========================================")

	String txt;

	TN_LOG("In values :")

	txt += ToString("N%u : %lf", 0, m_layers.GetLayer(0)->GetNeuroneValue(0));
	for (j = 1; j < m_layers.GetLayer(0)->GetSize(); j++)
	{
		txt += " / ";
		txt += ToString("N%u : %lf", j, m_layers.GetLayer(0)->GetNeuroneValue(j));
	}

	TN_LOG(txt)

	txt = "";

	TN_LOG("-----------------------------------------")

	TN_LOG("Out values :");

	txt += ToString("N%u : %lf", 0, m_layers.GetLayer(GetLastLayerIndice())->GetNeuroneValue(0));
	for (j = 1; j < m_layers.GetLayer(GetLastLayerIndice())->GetSize(); j++)
	{
		txt += " / ";
		txt += ToString("N%u : %lf", j, m_layers.GetLayer(GetLastLayerIndice())->GetNeuroneValue(j));
	}

	TN_LOG(txt)

	TN_LOG("=========================================")
	TN_LOG("")
}

void TN::MLP::Ask(double* valIn)
{
	Browse(valIn);
	PrintResults();
}

void TN::MLP::Ask(String path, unsigned int index)
{
	Browse(path, index);
	PrintResults();
}

int TN::MLP::my_rand(int max, int min)
{
	return rand() % (max - min + 1) + min;
}


void TN::MLP::LoadFromFile(String path)
{
	TN::File file(path, TN::FileMode_e::FM_READ);

	if (!file.IsFileOpen())
		TN_ERROR("File can't be open")

	file.Read("lc %d\n\n", &m_layerCount);

	m_layers.Clear();

	unsigned int i, j, k;

	m_neuronePerLayerTable = new size_t[m_layerCount];

	size_t temp;

	file.Read("npl %zu", &temp);

	m_layers.AddLayer(new Layer(temp));
	m_neuronePerLayerTable[0] = temp;

	for (i = 1; i < m_layerCount; i++)
	{
		file.Read(" %zu", &temp);
		m_layers.AddLayer(new Layer(temp));
		m_neuronePerLayerTable[i] = temp;
	}

	file.Read("\n\n");

	for (i = 0; i < m_layerCount - 1; i++)
	{
		m_layers.GetLayer(i)->LinkAllWithAll(m_layers.GetLayer(i + 1));
	}

	double t1, t2;

	for (i = 0; i < m_layerCount; i++)
	{
		for (j = 0; j < m_layers.GetLayer(i)->GetSize(); j++)
		{
			file.Read("%lf (%lf)\n", &t1, &t2);
			m_layers.GetLayer(i)->SetNeuroneValue(j, t1);
			m_layers.GetLayer(i)->GetNeurone(j)->SetThresholdWeight(t2);

			for (k = 0; k < m_layers.GetLayer(i)->GetNeurone(j)->GetOriginLinks()->GetCount(); k++)
			{
				file.Read(" %lf", &t1);
				m_layers.GetLayer(i)->GetNeurone(j)->GetOriginLinks()->GetLink(k)->SetWeight(t1);
			}
			file.Read("\n\n");
		}
		file.Read("\n");
	}

	delete[] m_neuronePerLayerTable;
}

void TN::MLP::SaveInFile(String path)
{
	TN::File file(path, TN::FileMode_e::FM_OVERWRITE);

	if (!file.IsFileOpen())
		TN_ERROR("File can't be open")

	file.Write("lc %zu\n\n", m_layerCount);

	unsigned int i, j, k;

	file.Write("npl %zu", m_layers.GetLayer(0)->GetSize());

	for (i = 1; i < m_layerCount; i++)
	{
		file.Write(" %zu", m_layers.GetLayer(i)->GetSize());
	}

	file.Write("\n\n");

	for (i = 0; i < m_layerCount; i++)
	{
		for (j = 0; j < m_layers.GetLayer(i)->GetSize(); j++)
		{
			file.Write("%lf (%lf)\n", m_layers.GetLayer(i)->GetNeuroneValue(j), m_layers.GetLayer(i)->GetNeurone(j)->GetThresholdWeight());

			for (k = 0; k < m_layers.GetLayer(i)->GetNeurone(j)->GetOriginLinks()->GetCount(); k++)
			{
				file.Write(" %lf", m_layers.GetLayer(i)->GetNeurone(j)->GetOriginLinks()->GetLink(k)->GetWeight());
			}
			file.Write("\n\n");
		}
		file.Write("\n");
	}
}



double TN::MLP::GetError()
{ 
	return m_error; 
}

size_t TN::MLP::GetFirstLayerSize()
{ 
	return m_layers.GetLayer(0)->GetSize(); 
}

size_t TN::MLP::GetLastLayerSize()
{ 
	return m_layers.GetLayer(m_layers.GetCount() - 1)->GetSize();
}

size_t TN::MLP::GetLastLayerIndice()
{ 
	return m_layerCount - 1;
}

size_t TN::MLP::GetLayerCount()
{ 
	return m_layerCount; 
}

size_t TN::MLP::GetLayerSize(unsigned int index)
{ 
	return  m_layers.GetLayer(index - 1)->GetSize();
}

void TN::MLP::SetLearningLevel(double learningLevel)
{ 
	m_learningLevel = learningLevel; 
}

double TN::MLP::GetLearningLevel()
{ 
	return m_learningLevel; 
}

void TN::MLP::SetErrorAcceptance(double errorAcceptance)
{
	m_errorAcceptance = errorAcceptance;
}

double TN::MLP::GetErrorAcceptance()
{
	return m_errorAcceptance;
}
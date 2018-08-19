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

#ifndef TN_MLP_MLP_HPP
#define TN_MLP_MLP_HPP

#include <MLP/Config.hpp>
#include <Utility/Math.hpp>
#include <Utility/Layer.hpp>
#include <Utility/Link.hpp>
#include <Utility/Neurone.hpp>
#include <Core/Error.hpp>
#include <Core/Log.hpp>
#include <Core/String.hpp>

namespace TN
{

	/**
	* @class MLP
	* @brief Multi Layer Percreptron class.
	*
	* Use a simple multi layer perceptron with all included.
	*
	*/
	class TN_MLP MLP
	{

	public:

		/**
		* @brief Create a MLP network.
		*
		* @param errorAcceptance : error step of the MLP (between 0 and 1).
		* @param learningLevel : learning level of the MLP (between 0 and 1).
		* @param momentum : the momentum of the newtork, to get through local minimum (between 0 and 1).
		* @param activationFunction : the activation function (see available functions in Math class)
		* @param layerCount : the number of layers in the network.
		* @param neuronePerLayerTable : a table with all the neurones counts per layer.
		*
		*/
		MLP(double errorAcceptance = 0.1, double learningLevel = 0.01, double momentum = 0.0001, double(*activationFunction)(double) = &Sigmoide, size_t layerCount = 2, unsigned int *neuronePerLayerTable = NULL);
		~MLP();

		TN_DEPRECATED("use Learn() instead") void LearnSimple(double* valIn, double* valOut);

		/**
		* @brief Learn from matrices with size training elements.
		*
		* Each training elements for the input matrix need a size of the neurone count in the first layer. Same for output but with the last layer neurone count. e.g. valIn[size][neuroneCountInFirstLayer]
		*
		* @param valIn : the input matrix with size line and neurone count in first layer row.
		* @param valOut : the output matrix with size line and neurone count in last layer row.
		* @param size : the number of learning samples.
		*
		*/
		void Learn(double** valIn, double** valOut, size_t size);

		/**
		* @brief Learn from a file.
		*
		* @param path : the path of the file where training samples are.
		*
		* File form :
		*
		*	|	count:[TRAINING SAMPLE COUNT]
		*	|
		*	|	FIRST_NEURONE_VALUE_FIRST_LAYER SECOND_NEURONE_VALUE_FIRST_LAYER ...
		*	|	FIRST_NEURONE_VALUE_LAST_LAYER ...
		*	|
		*	|	FIRST_NEURONE_VALUE_FIRST_LAYER SECOND_NEURONE_VALUE_FIRST_LAYER ...
		*	|	FIRST_NEURONE_VALUE_LAST_LAYER ...
		*	|
		*	|	...
		*
		*/
		void Learn(String path);

		/**
		* @brief Browse from a table with all first layer neurones values.
		*
		* @param valIn : the table to browse from.
		*
		*/
		void Browse(double* valIn);

		/**
		* @brief Browse from a file.
		*
		* @param path : the path of the file where browsing from.
		* @param index : the index of the training batch in the file.
		*
		*/
		void Browse(String path, unsigned int index = 1);

		/**
		* @brief Retropropagate from a table with all last layer neurones values.
		*
		* @param valOut : the table to retropropagate from.
		*
		*/
		void RetroPropagation(double* valOut);

		/**
		* @brief Calculate the error of the actual network state with an output table.
		*
		* @param valOut : the table to refer from, with all last layer neurones values.
		*
		*/
		void CalculateError(double* valOut);

		/**
		* @brief Print neurones values.
		*
		*/
		void PrintNeuronesValues();

		/**
		* @brief Print links values.
		*
		*/
		void PrintLinksValues();

		/**
		* @brief Print layers values.
		*
		*/
		void PrintLayersData();

		/**
		* @brief Print all datas.
		*
		*/
		void PrintAll();

		/**
		* @brief Print only results (first and last layers neurones values).
		*
		*/
		void PrintResults();

		/**
		* @brief Ask the network from a table of input values with all first layer neurones values.
		*
		* It just browse and print results.
		*
		* @param valIn : the table to browse from.
		*
		*/
		void Ask(double* valIn);

		/**
		* @brief Ask the network from a file.
		*
		* It just browse and print results.
		*
		* @param path : the table of the file to browse from.
		* @param index : the index of the training bach in the file.
		*
		*/
		void Ask(String path, unsigned int index = 1);

		/**
		* @brief Load a Multilayer Preceptron from a file.
		*
		* @param path : the path of the file.
		*
		*/
		void LoadFromFile(String path);

		/**
		* @brief Save a Multilayer Preceptron in a file.
		*
		* @param path : the path of the file.
		*
		*/
		void SaveInFile(String path);

		/**
		* @brief To get the error.
		*
		* @return Return the error.
		*
		*/
		double GetError();

		/**
		* @brief TO get the first layer size.
		*
		* @return Return the first layer size.
		*
		*/
		size_t GetFirstLayerSize();

		/**
		* @brief To get the last layer size.
		*
		* @return Return the last layer size.
		*
		*/
		size_t GetLastLayerSize();

		/**
		* @brief Get the last layer indice.
		*
		* @return Return the last layer indice.
		*
		*/
		size_t GetLastLayerIndice();

		/**
		* @brief Get the layer count.
		*
		* @return Return the layer count of the network.
		*
		*/
		size_t GetLayerCount();

		/**
		* @brief Get the size of a certain layer.
		*
		* @param index : index of the layer.
		*
		* @return Return the size of the layer.
		*
		*/
		size_t GetLayerSize(unsigned int index);

		/**
		* @brief Set the learning level.
		*
		* @param learningLevel : the new learning level.
		*
		*/
		void SetLearningLevel(double learningLevel);

		/**
		* @brief Get the learning level.
		*
		* @return Return the learning level.
		*
		*/
		double GetLearningLevel();

		/**
		* @brief Set the error acceptance.
		*
		* @param errorAcceptance : the new error acceptance.
		*
		*/
		void SetErrorAcceptance(double errorAcceptance);

		/**
		* @brief Get the error acceptance.
		*
		* @return Return the error acceptance.
		*
		*/
		double GetErrorAcceptance();

		/**
		* @brief The activation function
		*
		* @param val : the value to pass to the function.
		*
		*/
		double(*ActivationFunction)(double value);

	private:

		int my_rand(int max, int min);

		Layers m_layers;

		size_t m_layerCount;
		size_t* m_neuronePerLayerTable;

		double m_learningLevel;
		double m_momentum;
		double m_errorAcceptance;

		double m_error;
	};

}

#endif
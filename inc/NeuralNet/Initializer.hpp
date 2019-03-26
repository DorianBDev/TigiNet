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

#ifndef TN_NEURALNET_INITIALIZER_HPP
#define TN_NEURALNET_INITIALIZER_HPP

#include <NeuralNet/Config.hpp>
#include <Utility/Tensor.hpp>
#include <Utility/Math.hpp>

namespace TN
{

	/**
	* @class Initializer
	* @brief Create a virtual initializer for tensors.
	*
	* A virtual class to initialize a tensor.
	*
	* @see Tensor
	*
	*/
	template<typename T>
	class Initializer
	{
	public:

		/**
		* @brief Initialize a tensor.
		*
		* @param tensor : the tensor to initialize.
		*
		*/
		virtual void Initialize(Tensor<T>& tensor) const = 0;

		/**
		* @brief Copy an initializer.
		*
		* @return Return a shared pointer of the new initializer copy.
		*
		*/
		virtual std::shared_ptr<Initializer<T>> Copy() const = 0;

	};

	/**
	* @class ZeroInitializer
	* @brief Create a zero initializer for tensors.
	*
	* Initialize a tensor datas to 0.
	*
	* @see Initializer
	*
	*/
	template<typename T>
	class ZeroInitializer : public Initializer<T>
	{
	public:

		/**
		* @brief Initialize a tensor.
		*
		* @param tensor : the tensor to initialize.
		*
		*/
		void Initialize(Tensor<T>& tensor) const;

		/**
		* @brief Copy an initializer.
		*
		* @return Return a shared pointer of the new initializer copy.
		*
		*/
		std::shared_ptr<Initializer<T>> Copy() const;
	};

	/**
	* @class UniformInitializer
	* @brief Create an uniform initializer for tensors.
	*
	* Initialize a tensor datas with random value from [-sqrt(3) / sqrt(dim);sqrt(3) / sqrt(dim)] interval.
	*
	* @see Initializer
	*
	*/
	template<typename T>
	class UniformInitializer : public Initializer<T>
	{
	public:

		/**
		* @brief Initialize a tensor.
		*
		* @param tensor : the tensor to initialize.
		*
		*/
		void Initialize(Tensor<T>& tensor) const;

		/**
		* @brief Copy an initializer.
		*
		* @return Return a shared pointer of the new initializer copy.
		*
		*/
		std::shared_ptr<Initializer<T>> Copy() const;
	};

	/**
	* @class RandomInitializer
	* @brief Create an random initializer for tensors.
	*
	* Initialize a tensor datas with random value.
	*
	* @see Initializer
	*
	*/
	template<typename T>
	class RandomInitializer : public Initializer<T>
	{
	public:

		/**
		* @brief Initialize a tensor with random value between [min;max].
		*
		* @param min : the first minimum boundary.
		* @param max : the second maximum boundary.
		*
		*/
		RandomInitializer(double min, double max);

		/**
		* @brief Initialize a tensor.
		*
		* @param tensor : the tensor to initialize.
		*
		*/
		void Initialize(Tensor<T>& tensor) const;

		/**
		* @brief Copy an initializer.
		*
		* @return Return a shared pointer of the new initializer copy.
		*
		*/
		std::shared_ptr<Initializer<T>> Copy() const;

	private:
		double m_min, m_max;
	};
}

#include <NeuralNet/Initializer.inl>

#endif
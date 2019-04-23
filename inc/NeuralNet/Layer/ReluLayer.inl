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

#ifndef TN_NEURALNET_RELULAYER_INL
#define TN_NEURALNET_RELULAYER_INL

namespace TN
{
	/// @private
	template<typename T>
	ReluLayer<T>::ReluLayer()
		: Layer<T>()
	{

	}

	/// @private
	template<typename T>
	ReluLayer<T>::~ReluLayer()
	{

	}

	/// @private
	template<typename T>
	void ReluLayer<T>::Link(Layer<T>& layer)
	{
		Layer<T>::Link(layer);
		Link(*(this->m_in));
	}

	/// @private
	template<typename T>
	void ReluLayer<T>::Link(Tensor<T>& in)
	{
		Layer<T>::Link(in);

		this->m_out = new Tensor<T>(this->m_in->GetRank(), this->m_in->GetShape(), this->m_in->GetRank());

		// The input gradient get the same shape as the input tensor
		this->m_gradIn = new Tensor<T>(this->m_in->GetRank(), this->m_in->GetShape(), this->m_in->GetRank());
	}

	/// @private
	template<typename T>
	void ReluLayer<T>::Activate()
	{
		unsigned int dim1_out = 0, dim2_out = 0, dim3_out = 0;

		switch (this->m_in->GetRank())
		{
		case 2:
			dim1_out = this->m_out->GetDimension(1);
			dim2_out = this->m_out->GetDimension(2);

			for (unsigned int x = 0; x < dim1_out; x++) // out.x
			{
				for (unsigned int y = 0; y < dim2_out; y++) // out.y
				{
					if ((*this->m_in)[y](x) < 0)
						(*this->m_out)[y](x) = 0;
					else
						(*this->m_out)[y](x) = (*this->m_in)[y](x);
				}
			}

			break;
		case 3:

			dim1_out = this->m_out->GetDimension(1);
			dim2_out = this->m_out->GetDimension(2);
			dim3_out = this->m_out->GetDimension(3);

			for (unsigned int z = 0; z < dim3_out; z++) // filter.fz == in.fz
			{
				for (unsigned int x = 0; x < dim1_out; x++) // out.x
				{
					for (unsigned int y = 0; y < dim2_out; y++) // out.y
					{
						if ((*this->m_in)[z][y](x) < 0)
							(*this->m_out)[z][y](x) = 0;
						else
							(*this->m_out)[z][y](x) = (*this->m_in)[z][y](x);
					}
				}
			}

			break;
		default:
			TN_WARNING("NEURALNET", "Wrong input size");
			break;
		}

		if (this->m_nextLayer != NULL)
			this->m_nextLayer->Activate();
	}

	/// @private
	template<typename T>
	void ReluLayer<T>::Update()
	{
		Tensor<T>* gradIn = this->m_nextLayer->GetInputGradient();
		unsigned int dim1_out = 0, dim2_out = 0, dim3_out = 0;

		switch (this->m_in->GetRank())
		{
		case 2:
			dim1_out = this->m_out->GetDimension(1);
			dim2_out = this->m_out->GetDimension(2);

			for (unsigned int x = 0; x < dim1_out; x++) // out.x
			{
				for (unsigned int y = 0; y < dim2_out; y++) // out.y
				{
					if ((*this->m_in)[y](x) < 0)
						(*this->m_gradIn)[y](x) = 0;
					else
						(*this->m_gradIn)[y](x) = (*gradIn)[y](x);
				}
			}

			break;
		case 3:

			dim1_out = this->m_out->GetDimension(1);
			dim2_out = this->m_out->GetDimension(2);
			dim3_out = this->m_out->GetDimension(3);

			for (unsigned int z = 0; z < dim3_out; z++) // filter.fz == in.fz
			{
				for (unsigned int x = 0; x < dim1_out; x++) // out.x
				{
					for (unsigned int y = 0; y < dim2_out; y++) // out.y
					{
						if ((*this->m_in)[z][y](x) < 0)
							(*this->m_gradIn)[z][y](x) = 0;
						else
							(*this->m_gradIn)[z][y](x) = (*gradIn)[z][y](x);
					}
				}
			}

			break;
		default:
			TN_WARNING("NEURALNET", "Wrong input size");
			break;
		}

		if (this->m_previousLayer != NULL)
			this->m_previousLayer->Update();
	}

	/// @private
	template<typename T>
	void ReluLayer<T>::SaveInFile(std::ofstream & file)
	{
		TN_ASSERT(file.is_open(), "NEURALNET", "Open a file before save in");

		// Do nothing because no trainable params.
	}

	/// @private
	template<typename T>
	void ReluLayer<T>::LoadFromFile(std::ifstream & file)
	{
		TN_ASSERT(file.is_open(), "NEURALNET", "Open a file before load from it");

		// Do nothing because no trainable params.
	}
}

#endif
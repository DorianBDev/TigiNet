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

#ifndef TN_NEURALNET_POOLINGLAYER_INL
#define TN_NEURALNET_POOLINGLAYER_INL

#include <algorithm>
#include <limits>

namespace TN
{
	/// @private
	template<typename T>
	PoolingLayer<T>::PoolingLayer(const PoolingMethod method, const PoolingKernel kernel, unsigned int stride, unsigned int zeroPadding)
		: Layer<T>(), m_kernel(kernel)
	{
		TN_ASSERT(stride >= 1, "NEURALNET", "Wronde stride value");

		m_stride = stride;
		m_zeroPadding = zeroPadding;
		m_method = method;
	}

	/// @private
	template<typename T>
	PoolingLayer<T>::~PoolingLayer()
	{
		
	}

	/// @private
	template<typename T>
	void PoolingLayer<T>::Link(Layer<T>& layer)
	{
		Layer<T>::Link(layer);
		Link(*(this->m_in));
	}

	/// @private
	template<typename T>
	void PoolingLayer<T>::Link(Tensor<T>& in)
	{
		Layer<T>::Link(in);

		TN_ASSERT(in.GetRank() <= 3 && in.GetRank() >= 2, "NEURALNET", "Wrong rank for the input");
		TN_ASSERT(in.GetDimension(1) >= m_kernel.m_x && in.GetDimension(2) >= m_kernel.m_y, "NEURALNET", "Wrong kernel size");
		TN_ASSERT((in.GetDimension(1) - m_kernel.m_x + 2 * m_zeroPadding) % m_stride == 0 && (in.GetDimension(2) - m_kernel.m_y + 2 * m_zeroPadding) % m_stride == 0, "NEURALNET", "Wrong padding");

		unsigned int* outShape = NULL;
		switch (in.GetRank())
		{
		case 2:

			outShape = new unsigned int[2];
			outShape[0] = (in.GetDimension(1) - m_kernel.m_x + 2 * m_zeroPadding) / m_stride + 1;
			outShape[1] = (in.GetDimension(2) - m_kernel.m_y + 2 * m_zeroPadding) / m_stride + 1;
			this->m_out = new Tensor<T>(2, TensorShape(outShape), 2);

			break;
		case 3:

			outShape = new unsigned int[3];
			outShape[0] = (in.GetDimension(1) - m_kernel.m_x + 2 * m_zeroPadding) / m_stride + 1;
			outShape[1] = (in.GetDimension(2) - m_kernel.m_y + 2 * m_zeroPadding) / m_stride + 1;
			outShape[2] = in.GetDimension(3);
			this->m_out = new Tensor<T>(3, TensorShape(outShape), 3);

			break;
		default:
			TN_WARNING("NEURALNET", "Wrong input size");
			break;
		}

		// The input gradient get the same shape as the input tensor
		this->m_gradIn = new Tensor<T>(this->m_in->GetRank(), this->m_in->GetShape(), this->m_in->GetRank());
	}

	/// @private
	template<typename T>
	void PoolingLayer<T>::Activate()
	{
		unsigned int dim1 = 0, dim2 = 0, dim3 = 0;
		unsigned int dim1_out = 0, dim2_out = 0;
		T res = 0;
		T lowest = std::numeric_limits<T>::lowest();

		switch (this->m_in->GetRank())
		{
		case 2:

			dim1 = this->m_in->GetDimension(1);
			dim2 = this->m_in->GetDimension(2);

			dim1_out = this->m_out->GetDimension(1);
			dim2_out = this->m_out->GetDimension(2);

			switch (m_method)
			{
			case PoolingMethod::PM_MAX:

				for (unsigned int x = 0; x < dim1_out; x++) // out.x
				{
					for (unsigned int y = 0; y < dim2_out; y++) // out.y
					{
						res = lowest;
						for (unsigned int fx = 0; fx < m_kernel.m_x; fx++) // filters.x
						{
							for (unsigned int fy = 0; fy < m_kernel.m_y; fy++) // filters.y
							{
								if (((x * m_stride + fx) < m_zeroPadding || (y * m_stride + fy) < m_zeroPadding) || ((x * m_stride + fx) >= dim1 + m_zeroPadding || (y * m_stride + fy) >= dim2 + m_zeroPadding))
									continue;
								else
									res = std::max<T>(res, (*this->m_in)[y * m_stride + fy - m_zeroPadding](x * m_stride + fx - m_zeroPadding));
							}
						}
						(*this->m_out)[y](x) = res;
					}
				}

				break;
			case PoolingMethod::PM_AVERAGE:
				TN_WARNING("NEURALNET", "Average pooling method isn't supported for the moment"); //TODO
				break;
			default:
				break;
			}

			break;
		case 3:

			dim1 = this->m_in->GetDimension(1);
			dim2 = this->m_in->GetDimension(2);
			dim3 = this->m_in->GetDimension(3);

			dim1_out = this->m_out->GetDimension(1);
			dim2_out = this->m_out->GetDimension(2);

			switch (m_method)
			{
			case PoolingMethod::PM_MAX:

				for (unsigned int z = 0; z < dim3; z++) // filter.fz == in.fz
				{
					for (unsigned int x = 0; x < dim1_out; x++) // out.x
					{
						for (unsigned int y = 0; y < dim2_out; y++) // out.y
						{
							res = lowest;
							for (unsigned int fx = 0; fx < m_kernel.m_x; fx++) // filters.x
							{
								for (unsigned int fy = 0; fy < m_kernel.m_y; fy++) // filters.y
								{
									if (((x * m_stride + fx) < m_zeroPadding || (y * m_stride + fy) < m_zeroPadding) || ((x * m_stride + fx) >= dim1 + m_zeroPadding || (y * m_stride + fy) >= dim2 + m_zeroPadding))
										continue;
									else
										res = std::max<T>(res, (*this->m_in)[z][y * m_stride + fy - m_zeroPadding](x * m_stride + fx - m_zeroPadding));
								}
							}
							(*this->m_out)[z][y](x) = res;
						}
					}
				}

				break;
			case PoolingMethod::PM_AVERAGE:
				TN_WARNING("NEURALNET", "Average pooling method isn't supported for the moment"); //TODO
				break;
			default:
				break;
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
	void PoolingLayer<T>::Update()
	{
		Tensor<T>* gradIn = this->m_nextLayer->GetInputGradient();
		unsigned int dim1 = 0, dim2 = 0, dim3 = 0;
		unsigned int dim1_out = 0, dim2_out = 0;
		this->m_zeroInitializer.Initialize(*this->m_gradIn);

		switch (this->m_in->GetRank())
		{
		case 2:

			dim1 = this->m_in->GetDimension(1);
			dim2 = this->m_in->GetDimension(2);

			dim1_out = this->m_out->GetDimension(1);
			dim2_out = this->m_out->GetDimension(2);

			switch (m_method)
			{
			case PoolingMethod::PM_MAX:

				for (unsigned int x = 0; x < dim1_out; x++) // filter.fz == in.fz
				{
					for (unsigned int y = 0; y < dim2_out; y++) // out.x
					{
						for (unsigned int fx = 0; fx < m_kernel.m_x; fx++) // filters.x
						{
							for (unsigned int fy = 0; fy < m_kernel.m_y; fy++) // filters.y
							{
								if (((x * m_stride + fx) < m_zeroPadding || (y * m_stride + fy) < m_zeroPadding) || ((x * m_stride + fx) >= dim1 + m_zeroPadding || (y * m_stride + fy) >= dim2 + m_zeroPadding))
									continue;
								else
								{
									if ((*this->m_out)[y](x) == (*this->m_in)[y * m_stride + fy - m_zeroPadding](x * m_stride + fx - m_zeroPadding))
										(*this->m_gradIn)[y * m_stride + fy - m_zeroPadding](x * m_stride + fx - m_zeroPadding) += (*gradIn)[y](x);
								}
							}
						}
					}
				}

				break;
			case PoolingMethod::PM_AVERAGE:
				TN_WARNING("NEURALNET", "Average pooling method isn't supported for the moment"); //TODO
				break;
			default:
				break;
			}

			break;
		case 3:

			dim1 = this->m_in->GetDimension(1);
			dim2 = this->m_in->GetDimension(2);
			dim3 = this->m_in->GetDimension(3);

			dim1_out = this->m_out->GetDimension(1);
			dim2_out = this->m_out->GetDimension(2);

			switch (m_method)
			{
			case PoolingMethod::PM_MAX:
								
				for (unsigned int x = 0; x < dim1_out; x++) // filter.fz == in.fz
				{
					for (unsigned int y = 0; y < dim2_out; y++) // out.x
					{
						for (unsigned int z = 0; z < dim3; z++) // out.y
						{
							for (unsigned int fx = 0; fx < m_kernel.m_x; fx++) // filters.x
							{
								for (unsigned int fy = 0; fy < m_kernel.m_y; fy++) // filters.y
								{
									if (((x * m_stride + fx) < m_zeroPadding || (y * m_stride + fy) < m_zeroPadding) || ((x * m_stride + fx) >= dim1 + m_zeroPadding || (y * m_stride + fy) >= dim2 + m_zeroPadding))
										continue;
									else
									{
										if ((*this->m_out)[z][y](x) == (*this->m_in)[z][y * m_stride + fy - m_zeroPadding](x * m_stride + fx - m_zeroPadding))
											(*this->m_gradIn)[z][y * m_stride + fy - m_zeroPadding](x * m_stride + fx - m_zeroPadding) += (*gradIn)[z][y](x);
									}
								}
							}
						}
					}
				}	

				break;
			case PoolingMethod::PM_AVERAGE:
				TN_WARNING("NEURALNET", "Average pooling method isn't supported for the moment"); //TODO
				break;
			default:
				break;
			}

			break;
		default:
			TN_WARNING("NEURALNET", "Wrong input size");
			break;
		}

		if (this->m_previousLayer != NULL)
			this->m_previousLayer->Update();
	}

}

#endif
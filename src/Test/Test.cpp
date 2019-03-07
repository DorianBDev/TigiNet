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

#include <Core/Log.hpp>
#include <NeuralNet/Layer.hpp>
#include <Utility/Tensor.hpp>

int main()
{
	TN::ActivatorConfig<double> config(TN::Sigmoide);
	double res = config.ActivationFunction(0);
	TN_LOG("%f", res);
	res = config.ActivationDerivative(0.5);
	TN_LOG("%f", res);

	TN_LOG("-------");


	TN::Tensor<int> s(0, TN::TensorShape(NULL), 2);

	s() = 0;

	TN_LOG("%d", s());

	TN_LOG("-------");

	unsigned int vshape[] = { 2 };
	TN::Tensor<int> v(1, TN::TensorShape(vshape), 0);

	v(0) = 0;
	v(1) = 1;

	TN_LOG("%d %d", v(0), v(1));

	TN_LOG("-------");

	unsigned int shape[] = { 2, 2, 2 };
	TN::Tensor<int> t(3, TN::TensorShape(shape), 3);

	t[0][0](0) = 1;
	t[0][0](1) = 2;
	t[0][1](0) = 3;
	t[0][1](1) = 4;
	t[1][0](0) = 5;
	t[1][0](1) = 6;
	t[1][1](0) = 7;
	t[1][1](1) = 8;

	TN_LOG("0 : %d %d", t[0][0](0), t[0][0](1));
	TN_LOG("0 : %d %d", t[0][1](0), t[0][1](1));
	TN_LOG("1 : %d %d", t[1][0](0), t[1][0](1));
	TN_LOG("1 : %d %d", t[1][1](0), t[1][1](1));

	TN_LOG("-------");

	int* data = t.GetData();
	TN_LOG("0 : %d %d", data[0], data[1]);
	TN_LOG("0 : %d %d", data[2], data[3]);
	TN_LOG("1 : %d %d", data[4], data[5]);
	TN_LOG("1 : %d %d", data[6], data[7]);

	TN_LOG("-------");

	data = t[1].GetData();
	TN_LOG("1 : %d %d", data[0], data[1]);
	TN_LOG("1 : %d %d", data[2], data[3]);

	TN_LOG("-------");

	TN_LOG("End")

	return 0;
}


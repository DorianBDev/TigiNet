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
#include <Core/Error.hpp>
#include <NeuralNet/Layer.hpp>
#include <Utility/Tensor.hpp>
#include <Utility/Gradient.hpp>
#include <NeuralNet/Layer/FullyConnected.hpp>

int main()
{
	TN::ActivatorConfig<double> config(TN::Sigmoide);
	double res = config.ActivationFunction(0);
	TN_LOG("TEST") << res;
	res = config.ActivationDerivative(0.5);
	TN_LOG("TEST") << res;

	TN::gradient_t<double> grad;
	grad.actual = 10;

	TN::ActivatorConfig<int> config2(TN::Sigmoide);
	TN::FCLayer<int> l(config2, 2);

	TN_LOG("TEST") << "-------";


	TN::Tensor<int> s(0, TN::TensorShape(NULL), 2);

	s() = 0;

	TN_LOG("TEST") << s();

	TN_LOG("TEST") << "-------";

	unsigned int vshape[] = { 2 };
	TN::Tensor<int> v(1, TN::TensorShape(vshape), 0);

	v(0) = 0;
	v(1) = 1;

	TN_LOG("TEST") << v(0) << " " << v(1);

	TN_LOG("TEST") << "-------";

	unsigned int shape[] = { 2, 2, 2 };
	TN::Tensor<int> t(3, TN::TensorShape(shape), 3);

	l.Link(t);

	t[0][0](0) = 1;
	t[0][0](1) = 2;
	t[0][1](0) = 3;
	t[0][1](1) = 4;
	t[1][0](0) = 5;
	t[1][0](1) = 6;
	t[1][1](0) = 7;
	t[1][1](1) = 8;

	TN_LOG("TEST") << "0 : " << t[0][0](0) << " " << t[0][0](1);
	TN_LOG("TEST") << "0 : " << t[0][1](0) << " " << t[0][1](1);
	TN_LOG("TEST") << "1 : " << t[1][0](0) << " " << t[1][0](1);
	TN_LOG("TEST") << "1 : " << t[1][1](0) << " " << t[1][1](1);

	TN_LOG("TEST") << "-------";

	int* data = t.GetData();
	TN_LOG("TEST") << "0 : " << data[0] << " " << data[1];
	TN_LOG("TEST") << "0 : " << data[2] << " " << data[3];
	TN_LOG("TEST") << "1 : " << data[4] << " " << data[5];
	TN_LOG("TEST") << "1 : " << data[6] << " " << data[7];

	TN_LOG("TEST") << "-------";

	data = t[1].GetData();
	TN_LOG("TEST") << "1 : " << data[0] << " " << data[1];
	TN_LOG("TEST") << "1 : " << data[2] << " " << data[3];

	TN_LOG("TEST") << "-------";

	TN_LOG("TEST") << "END";

	return 0;
}


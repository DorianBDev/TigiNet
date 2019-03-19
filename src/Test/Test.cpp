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
#include <Utility/Math.hpp>
#include <NeuralNet/Layer/FullyConnected.hpp>
#include <NeuralNet/Initializer.hpp>
#include <NeuralNet/Cost.hpp>
#include <NeuralNet/Optimizer.hpp>

int main()
{

	TN::FCLayer<double> l(TN::ActivatorConfig<double>(TN::Sigmoide), TN::UniformInitializer<double>(), 3);

	unsigned int shape[] = { 2, 2, 2 };
	TN::Tensor<double> t(3, TN::TensorShape(shape), 3);

	l.Link(t);

	t[0][0](0) = 1;
	t[0][0](1) = 2;
	t[0][1](0) = 3;
	t[0][1](1) = 4;
	t[1][0](0) = 5;
	t[1][0](1) = 6;
	t[1][1](0) = 7;
	t[1][1](1) = 8;

	t.Print();

	l.Activate();

	TN_LOG("TEST") << "-------";

	l.GetOutput().Print();

	TN_LOG("TEST") << "-------";

	TN_LOG("TEST") << "END";

	return 0;
}


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
	TN::FCLayer<double> l(TN::ActivatorConfig<double>(TN::Sigmoide, TN::SigmoideDerivative), TN::RandomInitializer<double>(-10, 10), TN::StochasticGradientDescent<double>(0.0001, 0.9), 4);
	TN::FCLayer<double> l2(TN::ActivatorConfig<double>(TN::Sigmoide, TN::SigmoideDerivative), TN::RandomInitializer<double>(-10, 10), TN::StochasticGradientDescent<double>(0.0001, 0.9), 4);
	TN::FCLayer<double> l3(TN::ActivatorConfig<double>(TN::Sigmoide, TN::SigmoideDerivative), TN::RandomInitializer<double>(-10, 10), TN::StochasticGradientDescent<double>(0.0001, 0.9), 1);

	unsigned int shape[] = { 2, 4 };
	TN::Tensor<double> batch(2, TN::TensorShape(shape));

	unsigned int shape2[] = { 2 };
	TN::Tensor<double> in(1, TN::TensorShape(shape2));
	
	unsigned int shape3[] = { 1, 4 };
	TN::Tensor<double> batchOut(2, TN::TensorShape(shape3));

	batch[0](0) = 0;
	batch[0](1) = 0;
	batchOut[0](0) = 0;
	
	batch[1](0) = 1;
	batch[1](1) = 0;
	batchOut[1](0) = 0;

	batch[2](0) = 0;
	batch[2](1) = 1;
	batchOut[2](0) = 0;

	batch[3](0) = 1;
	batch[3](1) = 1;
	batchOut[3](0) = 1;

	in(0) = batch[0](0);
	in(1) = batch[0](1);
	l.Link(in);
	l2.Link(l);
	l3.Link(l2);
	
	unsigned int index = 0;
	for (unsigned int i = 0; i < 100000; i++)
	{
		index = TN::Random<unsigned int>(0, 3);
		in(0) = batch[index](0);
		in(1) = batch[index](1);

		l.Activate();

		if(i % 10000 == 1)
			TN_LOG("TEST") << l3.GetError();

		l3.Update(batchOut[index], TN::MeanSquaredError<double>());
	}

	in(0) = batch[0](0);
	in(1) = batch[0](1);
	in.Print();
	l.Activate();
	l3.Activate();
	l3.GetOutput().Print();

	TN_LOG("TEST") << "-------";

	in(0) = batch[1](0);
	in(1) = batch[1](1);
	in.Print();
	l.Activate();
	l3.Activate();
	l3.GetOutput().Print();

	TN_LOG("TEST") << "-------";

	in(0) = batch[2](0);
	in(1) = batch[2](1);
	in.Print();
	l.Activate();
	l3.Activate();
	l3.GetOutput().Print();

	TN_LOG("TEST") << "-------";

	in(0) = batch[3](0);
	in(1) = batch[3](1);
	in.Print();
	l.Activate();
	l3.Activate();
	l3.GetOutput().Print();

	TN_LOG("TEST") << "-------";

	TN_LOG("TEST") << "END";

	return 0;
}


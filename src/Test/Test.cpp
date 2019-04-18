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
#include <NeuralNet/Layer/FCLayer.hpp>
#include <NeuralNet/Layer/ConvLayer.hpp>
#include <NeuralNet/Initializer.hpp>
#include <NeuralNet/Cost.hpp>
#include <NeuralNet/Optimizer.hpp>
#include "NeuralNet/Layer/PoolingLayer.hpp"

int main()
{
	TN::KernelHolder<double> k;
	TN::Tensor<double> f1(2, TN::TensorShape({ 3, 3 }));
	f1[0](0) = 1;
	f1[0](1) = 0;
	f1[0](2) = 0;
	f1[1](0) = 0;
	f1[1](1) = 1;
	f1[1](2) = 0;
	f1[2](0) = 0;
	f1[2](1) = 0;
	f1[2](2) = 1;

	TN::Tensor<double> f2(2, TN::TensorShape({ 3, 3 }));
	f2[0](0) = 0;
	f2[0](1) = 0;
	f2[0](2) = 1;
	f2[1](0) = 0;
	f2[1](1) = 1;
	f2[1](2) = 0;
	f2[2](0) = 1;
	f2[2](1) = 0;
	f2[2](2) = 0;

	k.Add(TN::Kernel2D<double>(f1));
	k.Add(TN::Kernel2D<double>(f2));

	TN::ConvLayer<double> c(TN::RandomInitializer<double>(-10, 10), TN::StochasticGradientDescent<double>(0.0001, 0.9), k, 1, 1);
	TN::PoolingLayer<double> p(TN::PoolingMethod::PM_MAX, TN::PoolingKernel(3, 3), 3, 0);
	TN::FCLayer<double> co2(TN::ActivatorConfig<double>(TN::Sigmoide, TN::SigmoideDerivative), TN::RandomInitializer<double>(-10, 10), TN::StochasticGradientDescent<double>(0.0001, 0.9), 2);

	TN::Tensor<double> im1(2, TN::TensorShape({ 3, 3 }));
	TN::Tensor<double> cout(2, TN::TensorShape({ 2, 2 }));
	TN::ZeroInitializer<double> init;
	init.Initialize(im1);

	// 1
	cout[0](0) = 1;
	cout[0](1) = 0;

	// 2
	cout[1](0) = 0;
	cout[1](1) = 1;

	c.Link(im1);
	p.Link(c);
	co2.Link(p);

	unsigned int index = 0;
	for (unsigned int i = 0; i < 10000; i++)
	{
		index = TN::Random<unsigned int>(1, 2);

		if (index % 2 == 0)
		{
			// 1
			im1[0](0) = 1;
			im1[0](1) = 0;
			im1[0](2) = 0;

			im1[1](0) = 0;
			im1[1](1) = 1;
			im1[1](2) = 0;

			im1[2](0) = 0;
			im1[2](1) = 0;
			im1[2](2) = 1;
		}
		else
		{
			// 2
			im1[0](0) = 0;
			im1[0](1) = 0;
			im1[0](2) = 1;

			im1[1](0) = 0;
			im1[1](1) = 1;
			im1[1](2) = 0;

			im1[2](0) = 1;
			im1[2](1) = 0;
			im1[2](2) = 0;
		}

		c.Activate();

		co2.Update(cout[index % 2], TN::MeanSquaredError<double>());

		if (i % 1000 == 0)
		{
			TN_LOG("TEST") << co2.GetError();
		}
	}
	TN_LOG("TEST") << "-------------";

	c.GetKernelHolder().Get(0)->GetKernel()->Print();
	c.GetKernelHolder().Get(1)->GetKernel()->Print();

	TN_LOG("TEST") << "-------------";

	// 1
	im1[0](0) = 1;
	im1[0](1) = 0;
	im1[0](2) = 0;

	im1[1](0) = 0;
	im1[1](1) = 1;
	im1[1](2) = 0;

	im1[2](0) = 0;
	im1[2](1) = 0;
	im1[2](2) = 1;

	im1.Print();
	c.Activate();
	co2.GetOutput().Print();

	TN_LOG("TEST") << "-------";

	// 2
	im1[0](0) = 0;
	im1[0](1) = 0;
	im1[0](2) = 1;

	im1[1](0) = 0;
	im1[1](1) = 1;
	im1[1](2) = 0;

	im1[2](0) = 1;
	im1[2](1) = 0;
	im1[2](2) = 0;

	im1.Print();
	c.Activate();
	co2.GetOutput().Print();


	/*im1.Print();
	TN_LOG("TEST") << "-------";
	c.Activate();
	c.GetOutput().Print();
	co1.Update(cout, TN::MeanSquaredError<double>());
	TN_LOG("TEST") << "-------";
	*/

	

	TN_LOG("TEST") << "END";

	return 0;
}


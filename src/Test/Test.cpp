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
#include <NeuralNet/Layer/PoolingLayer.hpp>
#include <Utility/MNIST.hpp>

int main()
{
	TN::Tensor<double> t1(2, TN::TensorShape({ 3, 3 }));
	t1[0](0) = 10;
	t1[0](1) = 20;
	t1[0](2) = 30;
	t1[1](0) = 40;
	t1[1](1) = 50;
	t1[1](2) = 60;
	t1[2](0) = 70;
	t1[2](1) = 80;
	t1[2](2) = 90;

	t1.Print();
	t1.SaveInFile("tensor.tn");

	TN::Tensor<double> t2("tensor.tn");
	t2.Print();

	
	TN::MNIST<double> mnist("img.mnist", "label.mnist", 200);

	TN::KernelHolder<double> k;
	TN::Tensor<double> t(2, TN::TensorShape({ 3, 3 }));
	TN::RandomInitializer<double> rand(-10, 10);
	rand.Initialize(t);
	k.Add(TN::Kernel2D<double>(t));
	rand.Initialize(t);
	k.Add(TN::Kernel2D<double>(t));
	rand.Initialize(t);
	k.Add(TN::Kernel2D<double>(t));
	rand.Initialize(t);
	k.Add(TN::Kernel2D<double>(t));

	TN::ConvLayer<double> c1(TN::UniformInitializer<double>(), TN::StochasticGradientDescent<double>(0.0001, 0.9), k, 1, 1);
	TN::PoolingLayer<double> p1(TN::PoolingMethod::PM_MAX, TN::PoolingKernel(2, 2), 2, 0);
	TN::ConvLayer<double> c2(TN::UniformInitializer<double>(), TN::StochasticGradientDescent<double>(0.0001, 0.9), k, 1, 1);
	TN::PoolingLayer<double> p2(TN::PoolingMethod::PM_MAX, TN::PoolingKernel(2, 2), 2, 1);
	TN::FCLayer<double> f2(TN::ActivatorConfig<double>(TN::Sigmoide, TN::SigmoideDerivative), TN::UniformInitializer<double>(), TN::StochasticGradientDescent<double>(0.0001, 0.9), 10);

	c1.Link(mnist.GetImage()[0]);
	p1.Link(c1);
	c2.Link(p1);
	p2.Link(c2);
	f2.Link(p2);

	TN::Tensor<double> res(1, TN::TensorShape({ 10 }), 1);
	TN::ZeroInitializer<double> zero;
	zero.Initialize(res);

	unsigned int index = 0;
	int labelRes = 0;
	unsigned int max = mnist.GetImage().GetDimension(3) - 1;
	for (unsigned int i = 0; i < 10000; i++)
	{
		index = TN::Random<unsigned int>(0, max);
		labelRes = mnist.GetLabel()(index);
		
		c1.ResetInput(mnist.GetImage()[index]);
		c1.Activate();

		res(labelRes) = 1;
		f2.Update(res, TN::MeanSquaredError<double>());
		res(labelRes) = 0;

		if (i % 1000 == 0)
		{
			TN_LOG("TEST") << f2.GetError();
		}
	}

	TN_LOG("TEST") << "-------- 0 --------";
	index = TN::Random<unsigned int>(0, max);
	c1.ResetInput(mnist.GetImage()[index]);
	c1.Activate();
	f2.GetOutput().Print();
	TN_LOG("TEST") << mnist.GetLabel()(index);

	TN_LOG("TEST") << "-------- 1 --------";
	index = TN::Random<unsigned int>(0, max);
	c1.ResetInput(mnist.GetImage()[index]);
	c1.Activate();
	f2.GetOutput().Print();
	TN_LOG("TEST") << mnist.GetLabel()(index);

	TN_LOG("TEST") << "-------- 2 --------";
	index = TN::Random<unsigned int>(0, max);
	c1.ResetInput(mnist.GetImage()[index]);
	c1.Activate();
	f2.GetOutput().Print();
	TN_LOG("TEST") << mnist.GetLabel()(index);


	TN_LOG("TEST") << "END";

	return 0;
}


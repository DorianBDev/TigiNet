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
#include <NeuralNet/Layer/ReluLayer.hpp>

int main()
{
	TN::MNIST<double> mnist("img.mnist", "label.mnist", 1000);

	TN::KernelHolder<double> k;
	TN::Tensor<double> t(2, TN::TensorShape({ 5, 5 }));
	//TN::RandomInitializer<double> rand(-10, 10);
	TN::UniformInitializer<double> rand;
	rand.Initialize(t);
	k.Add(TN::Kernel2D<double>(t));
	rand.Initialize(t);
	k.Add(TN::Kernel2D<double>(t));
	rand.Initialize(t);
	k.Add(TN::Kernel2D<double>(t));
	rand.Initialize(t);
	k.Add(TN::Kernel2D<double>(t));
	rand.Initialize(t);
	k.Add(TN::Kernel2D<double>(t));
	rand.Initialize(t);
	k.Add(TN::Kernel2D<double>(t));
	rand.Initialize(t);
	k.Add(TN::Kernel2D<double>(t));
	rand.Initialize(t);
	k.Add(TN::Kernel2D<double>(t));
	rand.Initialize(t);
	k.Add(TN::Kernel2D<double>(t));
	rand.Initialize(t);
	k.Add(TN::Kernel2D<double>(t));

	TN::ConvLayer<double> c1(TN::UniformInitializer<double>(), TN::StochasticGradientDescent<double>(0.0001, 0.9), k, 1, 0);
	TN::PoolingLayer<double> p1(TN::PoolingMethod::PM_MAX, TN::PoolingKernel(2, 2), 2, 0);
	TN::FCLayer<double> f2(TN::ActivatorConfig<double>(TN::Sigmoide, TN::SigmoideDerivative), TN::UniformInitializer<double>(), TN::StochasticGradientDescent<double>(0.0001, 0.9), 10);

	TN::ReluLayer<double> r1;

	c1.Link(mnist.GetImage()[0]);
	r1.Link(c1);
	p1.Link(r1);
	f2.Link(p1);

	///*
	std::ifstream fileIn("net.tn");
	c1.LoadFromFile(fileIn);
	p1.LoadFromFile(fileIn);
	f2.LoadFromFile(fileIn);
	fileIn.close();
	//*/

	///*
	std::ifstream fileData("data.ppm");
	TN::Tensor<double> data(2, TN::TensorShape({ 28, 28 }));
	char pixelBuffer[3];

	fileData.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip magic number
	fileData.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip #
	fileData.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip size
	fileData.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip ppp
	for(unsigned int i = 0; i < 28; i++)
	{
		for(unsigned int j = 0; j < 28; j++)
		{
			fileData >> pixelBuffer[0];
			fileData >> pixelBuffer[1];
			fileData >> pixelBuffer[2];
			data[i](j) = (static_cast<double>(pixelBuffer[0] + pixelBuffer[1] + pixelBuffer[2])) / (3.0 * 255.0);
		}
	}
	data.Print();
	mnist.GetImage()[0].Print();

	TN_LOG("TEST") << "-------- Prediction --------";
	c1.ResetInput(data);
	c1.Activate();
	f2.GetOutput().Print();//*/

	/*
	TN::Tensor<double> res(1, TN::TensorShape({ 10 }), 1);
	TN::ZeroInitializer<double> zero;
	zero.Initialize(res);

	unsigned int index = 0;
	int labelRes = 0;
	unsigned int max = mnist.GetImage().GetDimension(3) - 1;
	TN::MeanSquaredError<double> err;
	double error = 0;
	for (unsigned int i = 0; i < 100000; i++)
	{
		index = TN::Random<unsigned int>(0, max);
		labelRes = mnist.GetLabel()(index);
		
		c1.ResetInput(mnist.GetImage()[index]);
		c1.Activate();

		res(labelRes) = 1;
		f2.Update(res, err);
		res(labelRes) = 0;
		error += f2.GetError();
		if (i % 10000 == 0)
		{
			TN_LOG("TEST") << "Error : " << (error / 10000.0) * 100 << "%";
			error = 0;
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

	std::ofstream fileOut("net.tn");
	c1.SaveInFile(fileOut);
	p1.SaveInFile(fileOut);
	f2.SaveInFile(fileOut);
	fileOut.close();

	*/

	TN_LOG("TEST") << "END";

	return 0;
}


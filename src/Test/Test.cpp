/**
*
*   TIGINET
*   Copyright (C) 2018  BACHELOT Dorian
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

#include <Core/Error.hpp>
#include <Core/Log.hpp>
#include <MLP/MLP.hpp>
#include <Utility/Math.hpp>

int main()
{
	unsigned int neuronePerLayer[3] = { 2, 2, 1 };

	TN::MLP* net = new TN::MLP(0.1, 0.01, 0.00001, &TN::Sigmoide, 3, neuronePerLayer);

	net->PrintAll();

	int i;

	double **in = new double*[4];
	for (i = 0; i < 4; i++)
		in[i] = new double[2];

	TN::String Script1 =
		#include <Test/test.vs>
	;

	TN::String Script2 =
		TN_SCRIPT(
			test;
			test line 2;
			"quoted";
		)
	;

	TN::String Script3 =	//TODO: See if it possible to encapsulate that in a macro
		R"delimiter(
			test;
			test line 2;
			"quoted";
		)delimiter"
	;

	TN_LOG(Script1);
	TN_LOG(Script2);
	TN_LOG(Script3);

	in[0][0] = 1;
	in[0][1] = 0;

	in[1][0] = 0;
	in[1][1] = 1;

	in[2][0] = 1;
	in[2][1] = 1;

	in[3][0] = 0;
	in[3][1] = 0;

	double **out = new double*[4];
	for (i = 0; i < 4; i++)
		out[i] = new double[1];

	out[0][0] = 1;

	out[1][0] = 1;

	out[2][0] = 0;

	out[3][0] = 0;

	net->Learn(in, out, 4);
	net->PrintAll();

	net->Browse(in[0]);
	net->PrintResults();

	net->Browse(in[1]);
	net->PrintResults();

	net->Browse(in[2]);
	net->PrintResults();

	net->Browse(in[3]);
	net->PrintResults();

	net->SaveInFile("save1.txt");

	TN_LOG("========================Save OK=========================")

	net->Learn("learn1.txt");

	TN_LOG("========================LEARN OK=========================")

	net->Ask(in[0]);

	net->Ask(in[1]);

	net->Ask(in[2]);

	net->Ask(in[3]);

	net->SaveInFile("save2.txt");

	TN_LOG("========================SAVE OK=========================")

	net->LoadFromFile("save1.txt");

	TN_LOG("========================LOAD OK=========================")

	net->Ask("learn1.txt", 1);

	net->Ask("learn1.txt", 2);

	net->Ask("learn1.txt", 3);

	net->Ask("learn1.txt", 4);


	for (i = 0; i < 4; i++)
		delete[] in[i];
	delete[] in;

	for (i = 0; i < 4; i++)
		delete[] out[i];
	delete[] out;

	delete net;

	TN_LOG("End")

	system("pause");

	return 0;
}


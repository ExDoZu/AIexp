#include"mymatrix.h"
#include "Network.h"
#include<iostream>

using namespace std;
using namespace aizuev;

int main()
{
	

	string PATH = "weights.zai";
	int dwidth, dheight, awidth, aheight;

	int numoflay = 2;
	int numofneu[] = { 1, 1 };

	double* ans;
	/// <summary>
	/// The number of neurons in the first layer must be equal to the number of input arguments.
	/// (dwidth == numofneu[0])
	/// There is not check of this, so be careful.
	/// </summary>
	double** data = matrix_from_file("data.txt", dwidth, dheight);
	double** answer = matrix_from_file("answers.txt", awidth, aheight);
	

	Network ob(numoflay, numofneu, activation_functions::identity, activation_functions::identityDeriv, PATH);
	//Network ob( activation_functions::identity, activation_functions::identityDeriv, PATH);
	ob.backpropagation(data, answer, dheight, 1000000, 0.000001);
	ob.saveNetwork(PATH);
	ob.answersOnTests(data, dheight);

	return 0;

}


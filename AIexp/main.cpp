#include"mymatrix.h"
#include "Network.h"
#include<iostream>

using namespace std;
using namespace aizuev;

int main()
{
	string PATH = "weights.zai";
	int dwidth, dheight, awidth, aheight;

	int numoflay = 4;
	int* numofneu = new int[numoflay];
	numofneu[0] = 3;
	numofneu[1] = 3;
	numofneu[2] = 3;
	numofneu[3] = 1;

	double* ans;

	double** data = matrix_from_file("data.txt", dwidth, dheight);
	double** answer = matrix_from_file("answers.txt", awidth, aheight);
	//Network ob(numoflay, numofneu,  activation_functions::sigmoid,PATH);
	Network ob(PATH, activation_functions::sigmoid);
	ob.backpropagation(data, answer, dheight, 100000, 0.01);
	ob.saveNetwork(PATH);
	ob.answersOnTests(data, dheight);

	return 0;

}


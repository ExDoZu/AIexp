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
	int numofneu[] = { 3, 6, 6, 1 };

	double* ans;

	double** data = matrix_from_file("data.txt", dwidth, dheight);
	double** answer = matrix_from_file("answers.txt", awidth, aheight);
	Network ob(numoflay, numofneu,  activation_functions::sigmoid, activation_functions::sigmoid_prime,PATH);
	//Network ob( activation_functions::sigmoid, activation_functions::sigmoid_prime, PATH);
	ob.backpropagation(data, answer, dheight, 1000000, 0.001);
	ob.saveNetwork(PATH);
	ob.answersOnTests(data, dheight);

	return 0;

}


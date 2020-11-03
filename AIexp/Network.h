#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include<ctime>
#include <cassert>
#include<random>
#include<Windows.h>
#include<cmath>
#include"mymatrix.h"
class Network
{
private:
	double*** weights;
	double** biases;
	int numberOfLayers;
	int* numberOfNeurons;
	double (*activationFunction)(double);



public:
	Network(std::string path, double(*activationFunc)(double));
	Network(int numberOfLayers, int* numberOfNeurons,  double(*activationFunc)(double), std::string newFileName = "");
	~Network();

	void saveNetwork(std::string newFilePath = "");
	double* getAnswer(double* data);
	void backpropagation(double** data, double** answers, int numberOfTests, int epochs, int batchSize, double learningRate);


};

namespace activation_functions
{
	double sigmoid(double x);
	double sigmoid_prime(double x);
}
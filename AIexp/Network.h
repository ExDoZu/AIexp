#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include<ctime>
#include <cassert>
#include<random>
#include<Windows.h>
#include<iostream>
#include<fstream>
#include <iomanip>

class Network
{
private:
	double*** weights;
	double** biases;
	int numberOfLayers;
	int* numberOfNeurons;
	double (*activationFunction)(double);
	double (*activationFunctionDeriv)(double);


public:
	Network(double(*activationFunc)(double), double(*activationFuncDeriv)(double), std::string path);
	Network(int numberOfLayers, int* numberOfNeurons, double(*activationFunc)(double), double(*activationFuncDeriv)(double), std::string newFilePath = "");
	~Network();

	void saveNetwork(std::string newFilePath = "");
	double* getAnswer(double* data);
	void backpropagation(double** data, double** answers, int numberOfTests, int epochs, double learningRate);
	void answersOnTests(double** data, int numberOfTests);

};

namespace activation_functions
{
	double sigmoid(double x);
	double sigmoid_derivative(double x);
	
	double identity(double x);
	double identityDeriv(double x);
}
#include "Network.h"

Network::Network(double(*activationFunc)(double), double(*activationFuncPrime)(double), std::string path)
{
	activationFunction = activationFunc;
	activationFunctionPrime = activationFuncPrime;
	if (path.size() > 4)
	{
		assert(path.substr(path.size() - 4, 4) == ".zai");
	}
	std::fstream fs;
	fs.open(path, std::fstream::in);

	fs >> numberOfLayers;

	numberOfNeurons = new int[numberOfLayers];
	weights = new double** [numberOfLayers - 1];
	biases = new double* [numberOfLayers - 1];

	for (int i = 0; i < numberOfLayers; i++)
		fs >> numberOfNeurons[i];


	for (int i = 0; i < numberOfLayers - 1; i++)
	{
		weights[i] = new double* [numberOfNeurons[i + 1]];
		for (int j = 0; j < numberOfNeurons[i + 1]; j++)
		{
			weights[i][j] = new double[numberOfNeurons[i]];
			for (int k = 0; k < numberOfNeurons[i]; k++)
				fs >> weights[i][j][k];
		}
	}
	for (int i = 0; i < numberOfLayers - 1; i++)
	{
		biases[i] = new double[numberOfNeurons[i + 1]];
		for (int j = 0; j < numberOfNeurons[i + 1]; j++)
			fs >> biases[i][j];
	}
	fs.close();


}

Network::Network(int numberOfLayers, int* numberOfNeurons, double(*activationFunc)(double), double(*activationFuncPrime)(double), std::string newFilePath)
{
	this->numberOfLayers = numberOfLayers;
	this->numberOfNeurons = new int[numberOfLayers];
	memcpy(this->numberOfNeurons, numberOfNeurons, numberOfLayers * sizeof(int));

	activationFunction = activationFunc;
	activationFunctionPrime = activationFuncPrime;

	weights = new double** [numberOfLayers - 1];
	biases = new double* [numberOfLayers - 1];

	srand(time(0));

	for (int i = 0; i < numberOfLayers - 1; i++)
	{
		weights[i] = new double* [numberOfNeurons[i + 1]];
		for (int j = 0; j < numberOfNeurons[i + 1]; j++)
		{
			weights[i][j] = new double[numberOfNeurons[i]];
			for (int k = 0; k < numberOfNeurons[i]; k++)
				weights[i][j][k] = (rand() % 200) / 100.0 - 1.0;
		}
	}
	for (int i = 0; i < numberOfLayers - 1; i++)
	{
		biases[i] = new double[numberOfNeurons[i + 1]];
		for (int j = 0; j < numberOfNeurons[i + 1]; j++)
			biases[i][j] = (rand() % 200) / 100.0 - 1.0;
	}
	saveNetwork(newFilePath);
}

Network::~Network()
{
	for (int i = 0; i < numberOfLayers - 1; i++)
	{
		for (int j = 0; j < numberOfNeurons[i + 1]; j++)
		{
			delete[] weights[i][j];
		}
		delete[]weights[i];
	}
	delete[]weights;
	for (int i = 0; i < numberOfLayers - 1; i++)
	{
		delete[]biases[i];
	}
	delete[]biases;
	delete[]numberOfNeurons;
}

void Network::saveNetwork(std::string newFilePath)
{
	std::fstream fs;
	if (newFilePath == "")
	{
		time_t now = time(0);
		tm* ldt = localtime(&now);
		CreateDirectory(L"unnamed", NULL);
		newFilePath = "unnamed/" + std::to_string(1 + ldt->tm_mday) + '.' + std::to_string(1 + ldt->tm_mon) + '.' + std::to_string(1900 + ldt->tm_year)
			+ '_' + std::to_string(ldt->tm_hour) + '.' + std::to_string(ldt->tm_min) + '.' + std::to_string(ldt->tm_sec) + ".zai";

	}
	else if (newFilePath.size() > 4)
	{
		if (newFilePath.substr(newFilePath.size() - 4, 4) != ".zai")newFilePath += ".zai";
	}
	else
	{
		newFilePath += ".zai";
	}

	fs.open(newFilePath, std::fstream::out);
	fs << numberOfLayers << '\n';
	for (int i = 0; i < numberOfLayers; i++)
		fs << numberOfNeurons[i] << ' ';
	fs << '\n';


	for (int i = 0; i < numberOfLayers - 1; i++)
	{
		for (int j = 0; j < numberOfNeurons[i + 1]; j++)
		{
			for (int k = 0; k < numberOfNeurons[i]; k++)
				fs << weights[i][j][k] << ' ';
			fs << '\n';
		}
	}
	for (int i = 0; i < numberOfLayers - 1; i++)
	{
		for (int j = 0; j < numberOfNeurons[i + 1]; j++)
			fs << biases[i][j] << ' ';
		fs << '\n';
	}

	fs.close();

}

double* Network::getAnswer(double* data)
{
	double* deldata = new double[numberOfNeurons[0]];
	double* nextdeldata;

	memcpy(deldata, data, numberOfNeurons[0] * sizeof(double));

	for (int i = 0; i < numberOfLayers - 1; i++)
	{
		nextdeldata = new double[numberOfNeurons[i + 1]];
		for (int j = 0; j < numberOfNeurons[i + 1]; j++)
		{
			nextdeldata[j] = 0;
			for (int k = 0; k < numberOfNeurons[i]; k++)
			{
				nextdeldata[j] += deldata[k] * weights[i][j][k];
			}
			nextdeldata[j] += biases[i][j];
			nextdeldata[j] = activationFunction(nextdeldata[j]);
		}
		delete[]deldata;
		deldata = new double[numberOfNeurons[i + 1]];
		memcpy(deldata, nextdeldata, numberOfNeurons[i + 1] * sizeof(double));
		delete[]nextdeldata;
	}
	return deldata;
}

void Network::backpropagation(double** data, double** answers, int numberOfTests, int epochs, double learningRate)
{
	double** delresults = new double* [numberOfLayers];
	double** delerrors = new double* [numberOfLayers - 1];

	for (int i = 0; i < numberOfLayers; i++)
		delresults[i] = new double[numberOfNeurons[i]];
	for (int i = 0; i < numberOfLayers - 1; i++)
		delerrors[i] = new double[numberOfNeurons[i + 1]];

	for (int epoch = 0; epoch < epochs; epoch++)
	{
		for (int t = 0; t < numberOfTests; t++)
		{
			memcpy(delresults[0], data[t], numberOfNeurons[0] * sizeof(double));
			for (int j = 0; j < numberOfNeurons[1]; j++)
			{
				delresults[1][j] = 0;
				for (int k = 0; k < numberOfNeurons[0]; k++)
				{
					delresults[1][j] += delresults[0][k] * weights[0][j][k];
				}
				delresults[1][j] += biases[0][j];
			}
			for (int i = 1; i < numberOfLayers - 1; i++)
			{
				for (int j = 0; j < numberOfNeurons[i + 1]; j++)
				{
					delresults[i + 1][j] = 0;
					for (int k = 0; k < numberOfNeurons[i]; k++)
					{
						delresults[i + 1][j] += activationFunction(delresults[i][k]) * weights[i][j][k];
					}
					delresults[i + 1][j] += biases[i][j];
				}
			}

			for (int i = 0; i < numberOfNeurons[numberOfLayers - 1]; i++)
				delerrors[numberOfLayers - 2][i] = activationFunction(delresults[numberOfLayers - 1][i]) - answers[t][i];

			for (int i = numberOfLayers - 3; i >= 0; i--)
			{
				for (int j = 0; j < numberOfNeurons[i + 1]; j++)
				{
					delerrors[i][j] = 0.0;
					for (int k = 0; k < numberOfNeurons[i + 2]; k++)
					{
						delerrors[i][j] += delerrors[i + 1][k] * weights[i + 1][k][j];
					}
				}
			}

			for (int i = 0; i < numberOfLayers - 1; i++)
			{
				for (int j = 0; j < numberOfNeurons[i + 1]; j++)
				{
					for (int k = 0; k < numberOfNeurons[i]; k++)
					{
						weights[i][j][k] -= learningRate * delerrors[i][j] * activationFunction(delresults[i][k]) * activationFunctionPrime(delresults[i + 1][j]);
					}
				}
				for (int j = 0; j < numberOfNeurons[i + 1]; j++)
				{
					biases[i][j] -= learningRate * delerrors[i][j] * activationFunctionPrime(delresults[i + 1][j]);
				}
			}

		}
	}

	for (int i = 0; i < numberOfLayers; i++)delete[]delresults[i];
	delete[]delresults;

	for (int i = 0; i < numberOfLayers - 1; i++)delete[]delerrors[i];
	delete[]delerrors;
}

void Network::answersOnTests(double** data, int numberOfTests)
{
	double* answer;
	for (int k = 0; k < numberOfTests; k++)
	{
		answer = getAnswer(data[k]);
		std::cout << "Test " << k + 1 << std::endl;
		for (int i = 0; i < numberOfNeurons[numberOfLayers - 1]; i++)
		{
			std::cout << answer[i] << ' ';
		}
		std::cout << std::endl;
		delete[]answer;
	}
}

double activation_functions::sigmoid(double x)
{
	return 1.0 / (1.0 + exp(-x));
}

double activation_functions::sigmoid_prime(double x)
{
	return sigmoid(x) * (1.0 - sigmoid(x));
}

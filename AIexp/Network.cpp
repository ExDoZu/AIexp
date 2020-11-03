#include "Network.h"

Network::Network(std::string path, double(*activationFunc)(double))
{
	activationFunction = activationFunc;
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

Network::Network(int numberOfLayers, int* numberOfNeurons,double(*activationFunc)(double),std::string newFilePath)
{
	this->numberOfLayers = numberOfLayers;
	this->numberOfNeurons = numberOfNeurons;
	activationFunction = activationFunc;

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
				weights[i][j][k] = (rand() % 200)/100.0 - 1.0;
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
	//for (int i = 0; i < numberOfNeurons[0]; i++) deldata[i] = data[i];
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

void Network::backpropagation(double** data, double** answers, int numberOfTests, int epochs, int batchSize, double learningRate)
{

}

double activation_functions::sigmoid(double x)
{
	return 1.0 / (1.0 + exp(-x));
}

double activation_functions::sigmoid_prime(double x)
{
	return sigmoid(x) * (1 - sigmoid(x));
}

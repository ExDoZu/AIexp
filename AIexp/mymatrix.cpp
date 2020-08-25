#include"mymatrix.h"


double** aizuev::transpose(double** old_matrix, int old_width, int old_height)
{
	double** new_matrix = new  double* [old_width];
	for (int i = 0; i < old_width; i++)
	{
		new_matrix[i] = new double[old_height];
		for (int j = 0; j < old_height; j++)
		{
			new_matrix[i][j] = old_matrix[j][i];
		}
	}

	for (int i = 0; i < old_height; i++)
	{
		delete[]old_matrix[i];
	}
	delete[]old_matrix;
	return new_matrix;
}

void aizuev::print_matrix(double** matrix, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout << matrix[i][j] << '\t';
		}
		std::cout << std::endl;
	}
}

double** aizuev::create_matrix(int width, int height)
{
	double** new_matrix = new  double* [height];
	for (int i = 0; i < height; i++)
	{
		new_matrix[i] = new double[width];
	}
	return new_matrix;
}

double** aizuev::create_matrix(int width, int height, double default_value)
{
	double** new_matrix = new  double* [height];
	for (int i = 0; i < height; i++)
	{
		new_matrix[i] = new double[width];
		for (int j = 0; j < width; j++)
		{
			new_matrix[i][j] = default_value;
		}
	}
	return new_matrix;
}

void aizuev::delete_matrix(double** matrix, int height)
{
	for (int i = 0; i < height; i++)
	{
		delete[]matrix[i];
	}
	delete[]matrix;
}

double** aizuev::matrix_from_file(std::string path, int& get_width, int& get_height)
{

	std::fstream fs;
	fs.open(path, std::fstream::in);
	fs >> get_width >> get_height;
	double** matrix = create_matrix(get_width, get_height);
	for (int i = 0; i < get_height; i++)
	{
		for (int j = 0; j < get_width; j++)
		{
			fs >> matrix[i][j];
		}
	}

	fs.close();
	return matrix;
}

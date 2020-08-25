#pragma once
#include<iostream>
#include<fstream>

namespace aizuev
{
	double** transpose(double** matrix, int width, int height);
	void print_matrix(double** matrix, int width, int height);
	double** create_matrix(int width, int height);
	double** create_matrix(int width, int height, double default_value);
	void delete_matrix(double** matrix, int height);
	double** matrix_from_file(std::string path, int& get_width, int& get_height);

}
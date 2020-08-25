#pragma once
namespace aizuev
{
	double** graph_second_group(double r, double** graph_matrix, int size);
	double** graph_first_group(int k, double** graph_matrix, int size);
	double** kruskal_algorithm(double** graph_matrix, int size);
	double** prim_algorithm(double** graph_matrix, int size);

}
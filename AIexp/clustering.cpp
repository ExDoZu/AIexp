#include "clustering.h"

double** clustering::graph_second_group(double r, double** graph_matrix, int size)
{
	double** clustered_graph = new  double* [size];
	for (int i = 0; i < size; i++) {
		clustered_graph[i] = new double[size];
		for (int j = 0; j < size; j++)
		{
			if (graph_matrix[i][j] > r)
			{
				clustered_graph[i][j] = -1.0;
			}
			else
			{
				clustered_graph[i][j] = graph_matrix[i][j];
			}
		}
	}

	return clustered_graph;
}

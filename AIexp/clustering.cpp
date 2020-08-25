#include "clustering.h"

double** aizuev::graph_second_group(double r, double** graph_matrix, int size)
{
	double** clustered_graph = new  double* [size];
	for (int i = 0; i < size; i++)
	{
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

double** aizuev::graph_first_group(int k, double** graph_matrix, int size)
{
	int max_ind[2];
	double** clustered_matrix = graph_matrix;//prim_algorithm(graph_matrix, size);
	for (int i = 0; i < k - 1; i++)
	{
		max_ind[0] = 0;
		max_ind[1] = 0;
		for (int j = 0; j < size; j++)
		{
			for (int y = 0; y <= j; y++)
			{
				if (clustered_matrix[y][j] > clustered_matrix[max_ind[0]][max_ind[1]])
				{
					max_ind[0] = y;
					max_ind[1] = j;
				}
			}
		}
		clustered_matrix[max_ind[0]][max_ind[1]] = -1.0;
		clustered_matrix[max_ind[1]][max_ind[0]] = -1.0;
	}
	return clustered_matrix;
}

double** aizuev::kruskal_algorithm(double** graph_matrix, int size)
{
	throw "Not realized";
	return nullptr;
}

double** aizuev::prim_algorithm(double** graph_matrix, int size)
{
	bool false_exists = true;
	int min_ind[2] = { 0,0 };
	bool* un = new bool[size];
	un[0] = true;
	for (int i = 1; i < size; i++)
	{
		un[i] = false;
	}

	double** matrix = new double* [size];
	for (int i = 0; i < size; i++)
	{
		matrix[i] = new double[size];
		for (int j = 0; j < size; j++)
		{
			if (j == i)
			{
				matrix[i][j] = 0.0;
			}
			else
			{
				matrix[i][j] = -1.0;
			}

		}
	}
	while (false_exists)
	{
		min_ind[0] = -1;
		for (int i = 0; i < size; i++)
		{
			if (un[i])
			{
				for (int j = 0; j < size; j++)
				{
					if (!un[j])
					{
						if (min_ind[0] == -1)
						{
							min_ind[0] = j;
							min_ind[1] = i;
						}
						else if (graph_matrix[j][i] < graph_matrix[min_ind[0]][min_ind[1]])
						{
							min_ind[0] = j;
							min_ind[1] = i;
						}
					}
				}
			}
		}
		matrix[min_ind[0]][min_ind[1]] = graph_matrix[min_ind[0]][min_ind[1]];
		matrix[min_ind[1]][min_ind[0]] = graph_matrix[min_ind[1]][min_ind[0]];

		un[min_ind[0]] = true;
		false_exists = false;
		for (int i = 0; i < size; i++)
		{
			if (!un[i])
			{
				false_exists = true;
				break;
			}
		}
	}


	delete[]un;
	return matrix;
}

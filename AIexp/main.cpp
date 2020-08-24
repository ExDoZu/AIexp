#include"clustering.h"
#include"mymatrix.h"

int main()
{
	std::string PATH = "input_matrix.txt";
	int w, h;
	double** matrix = mymatrix::matrix_from_file(PATH, w, h);
	double** matrix2 = clustering::graph_second_group(2.5, matrix, 5);
	mymatrix::print_matrix(matrix2, w, h);
	
}
	

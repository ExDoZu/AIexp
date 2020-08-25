#include"mymatrix.h"
#include"clustering.h"
#include"aiutils.h"

using namespace std;
using namespace aizuev;

int main()
{
	string PATH = "input_matrix.txt";
	int w, h;
	double** matrix = matrix_from_file(PATH, w, h);
	double** matrix2 =new double*[1];
	matrix2[0] = mass_center(matrix, w, h);
	print_matrix(matrix2, w, 1);
	
	return 0;

}


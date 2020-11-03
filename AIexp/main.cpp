
#include"mymatrix.h"
#include"clustering.h"
#include"aiutils.h"
#include "Network.h"
#include<iostream>

using namespace std;
using namespace aizuev;

int main()
{
	string PATH = "weights.zai";
	
	int* arr = new int[3];
	arr[0] = 2;
	arr[1] = 2;
	arr[2] = 2;

	double* ans;
	double data[] = { 1,3 };
	Network ob(PATH, activation_functions::sigmoid);
	ans = ob.getAnswer(data);

	for (int i = 0; i < 2; i++)
	{
		cout << ans [i] << ' ';
	}
	
	return 0;

}


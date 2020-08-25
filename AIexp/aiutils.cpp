#include"aiutils.h"
#include<cmath>

double aizuev::distance(double* v1, double* v2, int length, metrics metric)
{
	double val = 0.0, maxv = -1.0;
	switch (metric)
	{
	case metrics::EUCLIDEAN:
		
		double v;
		for (int i = 0; i < length; i++)
		{
			v = v1[i] - v2[i];
			val += v * v;
		}
		return sqrt(val);
		break;
	case metrics::MANHATTAN:
		for (int i = 0; i < length; i++)
		{
			val += fabs(v1[i] - v2[i]);
		}
		return val;
		break;
	case metrics::MAX:

		
		double absv;
		for (int i = 0; i < length; i++)
		{
			absv = fabs(v1[i] - v2[i]);
			if (absv > maxv)
			{
				maxv = absv;
			}
		}
		return maxv;
		break;
	default:
		throw "Metric?";
		break;
	}
}

double* aizuev::mass_center(double** matrix, int width, int height)
{
	double* mc = new double[width];
	for (int i = 0; i < width; i++)
	{
		mc[i] = 0;
	}
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			mc[i] += matrix[j][i];
		}
	}
	for (int i = 0; i < width; i++)
	{
		mc[i] /= height;
	}
	return mc;
}

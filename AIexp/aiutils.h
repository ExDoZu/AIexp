#pragma once
namespace aizuev
{
	enum class metrics
	{
		EUCLIDEAN,
		MANHATTAN,
		MAX
	};

	double distance(double* v1, double* v2, int length, metrics metric);
	double* mass_center(double** matrix, int width, int height);

}

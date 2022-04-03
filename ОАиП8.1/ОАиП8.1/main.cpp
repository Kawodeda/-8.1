
#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>
#include <vector>

struct CartesianPoint
{
	const std::string NAME_PLACEHOLDER = "untitled";
	int dimension;
	std::vector<float> x;
	std::string name;

	CartesianPoint(int dim, std::vector<float> coordinates, const std::string& pointName)
	{
		dimension = dim;
		x = coordinates;
		name = pointName;
	}

	CartesianPoint(std::vector<float> coordinates)
		: CartesianPoint(coordinates.size(), coordinates, NAME_PLACEHOLDER) {}

	CartesianPoint(std::vector<float> coordinates, const std::string& pointName)
		: CartesianPoint(coordinates.size(), coordinates, pointName) {}

	CartesianPoint(int dim, std::vector<float> coordinates)
		: CartesianPoint(dim, coordinates, NAME_PLACEHOLDER) {}
};

struct PolarPoint
{
	const std::string NAME_PLACEHOLDER = "untitled";
	int dimension;
	float r;
	std::vector<float> phi;
	std::string name;

	PolarPoint(int dim, float distance, std::vector<float> angles, const std::string& pointName)
	{
		dimension = dim;
		r = distance;
		phi = angles;
		name = pointName;
	}

	PolarPoint(float distance, std::vector<float> angles, const std::string& pointName)
		: PolarPoint(angles.size() + 1, distance, angles, pointName) {}

	PolarPoint(float distance, std::vector<float> angles)
		: PolarPoint(angles.size() + 1, distance, angles, NAME_PLACEHOLDER) {}

	PolarPoint(int dim, float distance, std::vector<float> angles)
		: PolarPoint(dim, distance, angles, NAME_PLACEHOLDER) {}
};

void PrintPoint(const CartesianPoint& point)
{
	const int FLOAT_PRECISION = 4;

	std::cout << std::endl << point.name << " (" << point.dimension << "-dim):" << std::endl;
	for (int i = 0; i < point.x.size(); ++i)
	{
		std::cout << "  x" << i << " = "
			<< std::setprecision(FLOAT_PRECISION)
			<< point.x[i] << std::endl;
	}
}

void PrintPoint(const PolarPoint& point)
{
	const int FLOAT_PRECISION = 4;

	std::cout << std::endl << point.name << " (" << point.dimension << "-dim):" << std::endl;
	std::cout << "  r = " << std::setprecision(FLOAT_PRECISION) << point.r << std::endl;

	for (int i = 0; i < point.phi.size(); ++i)
	{
		std::cout << "  phi" << i << " = "
			<< std::setprecision(FLOAT_PRECISION)
			<< point.phi[i] << std::endl;
	}
}

CartesianPoint ScanCartesianPoint()
{
	std::cout << std::endl << "Enter point's name: ";
	std::string name;
	std::cin >> name;

	std::cout << "Enter point's dimension (whole number): ";
	int n = 0;
	std::cin >> n;

	std::cout << "Enter point's coordinates:" << std::endl;
	std::vector<float> x(n);
	for (int i = 0; i < n; ++i)
	{
		std::cout << "  x" << i << " = ";
		std::cin >> x[i];
	}

	CartesianPoint point(n, x, name);
	return point;
}

int Sign(float number)
{
	if (number > 0)
	{
		return 1;
	}
	else if (number == 0)
	{
		return 0;
	}
	else if (number < 0)
	{
		return -1;
	}
}

float GetAngle(int sign, float cos)
{
	float arccos = acos(cos);

	return sign >= 0 ? arccos : (M_PI * 2 - arccos);
}

PolarPoint CartesianToPolar(const CartesianPoint& point)
{
	float r = 0.f;
	int n = point.dimension - 1;
	std::vector<float> phi(n);

	for (int i = 0; i <= n; ++i)
	{
		r += pow(point.x[i], 2);
	}
	r = sqrt(r);

	if (n > 0)
	{
		for (int i = 0; i < n - 1; ++i)
		{
			float sumOfSquares = 0.f;

			for (int j = i; j < n; ++j)
			{
				sumOfSquares += pow(point.x[j], 2);
			}

			phi[i] = acos(point.x[i] / sqrt(sumOfSquares));
		}

		float cos = point.x[n - 1] / sqrt(pow(point.x[n], 2) + pow(point.x[n - 1], 2));
		phi[n - 1] = GetAngle(Sign(point.x[n]), cos);
	}

	PolarPoint result(r, phi, point.name);
	return result;
}

int main()
{
	std::cout << "Enter the number of points: ";
	int numberOfPoints = 0;
	std::cin >> numberOfPoints;

	CartesianPoint* points = new CartesianPoint[numberOfPoints];

	for (int i = 0; i < numberOfPoints; ++i)
	{
		points[i] = ScanCartesianPoint();
	}

	std::cout << std::endl << "Polar points:" << std::endl;
	for (int i = 0; i < numberOfPoints; ++i)
	{
		PrintPoint(CartesianToPolar(points[i]));
	}

	return 0;
}

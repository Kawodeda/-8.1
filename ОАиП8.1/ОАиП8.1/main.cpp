
#include "Points.h"
#include <iostream>
#include <stdexcept>

int main()
{
	std::cout << "Enter the number of points: ";
	size_t numberOfPoints = 0;
	std::cin >> numberOfPoints;

	CartesianPoint* points = new CartesianPoint[numberOfPoints];

	for (size_t i = 0; i < numberOfPoints; ++i)
	{
		points[i] = CartesianPoint::Scan();
	}

	std::cout << std::endl << "Polar points:" << std::endl;
	for (size_t i = 0; i < numberOfPoints; ++i)
	{
		points[i].ToPolarPoint().Print();
	}

	return 0;
}

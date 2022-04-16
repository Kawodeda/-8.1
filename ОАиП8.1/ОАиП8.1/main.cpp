
#include "Points.h"
#include <iostream>
#include <stdexcept>

int main()
{
	std::cout << "Enter the number of points: ";
	size_t numberOfPoints = 0;
	std::cin >> numberOfPoints;

	CartesianPoint* points = new (std::nothrow) CartesianPoint[numberOfPoints];
	if (points == nullptr)
	{
		std::cout << std::endl << "Failed memory allocation" << std::endl;
		return -1;
	}

	try
	{
		for (size_t i = 0; i < numberOfPoints; ++i)
		{
			points[i] = CartesianPoint::Scan();
		}

		std::cout << std::endl << "Polar points:" << std::endl;
		for (size_t i = 0; i < numberOfPoints; ++i)
		{
			points[i].ToPolarPoint().Print();
		}
	}
	catch(std::exception& e)
	{
		std::cout << std::endl << e.what() << std::endl;
		return -1;
	}

	delete[] points;

	return 0;
}


#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <limits>
#include <stdexcept>

class Cartesian
{
private:
	static const size_t MIN_DIMENSION = 1;
	static const size_t MAX_DIMENSION = 1024;
	inline static const std::string NAME_PLACEHOLDER = "untitled";
	inline static const std::string DIMENSION_OUT_OF_RANGE_MESSAGE = "dimension was out of range";
	inline static const std::string DIMENSION_MISMATCH_MESSAGE = "dimension and number of components must be the same";
	inline static const std::string INDEX_OUT_OF_RANGE_MESSAGE = "the index was out of range";

	size_t m_dimension;
	std::vector<float> m_x;
	std::string m_name;

public:
	Cartesian(size_t dimension, const std::vector<float>& x, const std::string& name)
	{
		if (dimension < MIN_DIMENSION || dimension > MAX_DIMENSION)
		{
			throw std::out_of_range(DIMENSION_OUT_OF_RANGE_MESSAGE);
		}
		if (dimension != x.size())
		{
			throw std::logic_error(DIMENSION_MISMATCH_MESSAGE);
		}

		m_dimension = dimension;
		m_x = x;
		m_name = name;
	}

	Cartesian(const std::vector<float>& x, const std::string& name) : Cartesian(x.size(), x, name) {}

	Cartesian(const std::vector<float>& x) : Cartesian(x.size(), x, NAME_PLACEHOLDER) {}

	const std::string& GetNamePlaceholder()
	{
		return NAME_PLACEHOLDER;
	}

	const std::string& GetName()
	{
		return m_name;
	}

	size_t GetDimension()
	{
		return m_dimension;
	}

	float GetXAt(size_t index)
	{
		if (index >= m_x.size() || index < 0)
		{
			throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
		}

		return m_x[index];
	}

	void SetXAt(size_t index, float value)
	{
		if (index >= m_x.size() || index < 0)
		{
			throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
		}

		m_x[index] = value;
	}
};

struct CartesianPoint
{
	const std::string NAME_PLACEHOLDER = "untitled";
	size_t dimension;
	std::vector<float> x;
	std::string name;

	CartesianPoint() : CartesianPoint(1, {0.f}, NAME_PLACEHOLDER) {}

	CartesianPoint(size_t dim, std::vector<float> coordinates, const std::string& pointName)
	{
		dimension = dim;
		x = coordinates;
		name = pointName;
	}

	CartesianPoint(std::vector<float> coordinates)
		: CartesianPoint(coordinates.size(), coordinates, NAME_PLACEHOLDER) {}

	CartesianPoint(std::vector<float> coordinates, const std::string& pointName)
		: CartesianPoint(coordinates.size(), coordinates, pointName) {}

	CartesianPoint(size_t dim, std::vector<float> coordinates)
		: CartesianPoint(dim, coordinates, NAME_PLACEHOLDER) {}

	void operator=(const CartesianPoint& other)
	{
		dimension = other.dimension;
		x = other.x;
		name = other.name;
	}
};

struct PolarPoint
{
	const std::string NAME_PLACEHOLDER = "untitled";
	size_t dimension;
	float r;
	std::vector<float> phi;
	std::string name;

	PolarPoint(size_t dim, float distance, std::vector<float> angles, const std::string& pointName)
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

	PolarPoint(size_t dim, float distance, std::vector<float> angles)
		: PolarPoint(dim, distance, angles, NAME_PLACEHOLDER) {}
};

void PrintPoint(const CartesianPoint& point)
{
	const int FLOAT_PRECISION = 4;

	std::cout << std::endl << point.name << " (" << point.dimension << "-dim):" << std::endl;
	for (size_t i = 0; i < point.x.size(); ++i)
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

	for (size_t i = 0; i < point.phi.size(); ++i)
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
	size_t n = 0;
	std::cin >> n;

	std::cout << "Enter point's coordinates:" << std::endl;
	std::vector<float> x(n);
	for (size_t i = 0; i < n; ++i)
	{
		std::cout << "  x" << i << " = ";
		std::cin >> x[i];
	}

	CartesianPoint point(n, x, name);
	return point;
}

int Sign(float number)
{
	if (std::isnan(number))
	{
		throw std::invalid_argument("recieved NaN value");
	}

	const float eps = 0.00000001f;
	float diff = fabs(number);

	if (diff <= eps)
	{
		return 0;
	}
	else if (number > 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

float GetAngle(int sign, float cos)
{
	float arccos = acos(cos);

	return (sign >= 0 ? arccos : static_cast<float>(M_PI * 2 - arccos));
}

PolarPoint CartesianToPolar(const CartesianPoint& point)
{
	float r = 0.f;
	auto n = point.dimension - 1;
	std::vector<float> phi(n);

	for (int i = 0; i <= n; ++i)
	{
		r += static_cast<float>(pow(point.x[i], 2));
	}
	r = sqrt(r);

	if (n > 0)
	{
		for (int i = 0; i < n - 1; ++i)
		{
			float sumOfSquares = 0.f;

			for (int j = i; j < n; ++j)
			{
				sumOfSquares += static_cast<float>(pow(point.x[j], 2));
			}

			phi[i] = acos(point.x[i] / sqrt(sumOfSquares));
		}

		float cos = static_cast<float>(point.x[n - 1] / sqrt(pow(point.x[n], 2) + pow(point.x[n - 1], 2)));
		phi[n - 1] = GetAngle(Sign(point.x[n]), cos);
	}

	PolarPoint result(r, phi, point.name);
	return result;
}

int main()
{
	std::cout << "Enter the number of points: ";
	size_t numberOfPoints = 0;
	std::cin >> numberOfPoints;

	CartesianPoint* points = new CartesianPoint[numberOfPoints];

	for (size_t i = 0; i < numberOfPoints; ++i)
	{
		points[i] = ScanCartesianPoint();
	}

	std::cout << std::endl << "Polar points:" << std::endl;
	for (size_t i = 0; i < numberOfPoints; ++i)
	{
		PrintPoint(CartesianToPolar(points[i]));
	}

	return 0;
}

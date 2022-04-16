
#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <limits>
#include <stdexcept>

class CartesianPoint
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
	CartesianPoint(size_t dimension, const std::vector<float>& x, const std::string& name)
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

	CartesianPoint(const std::vector<float>& x, const std::string& name) : CartesianPoint(x.size(), x, name) {}

	CartesianPoint(const std::vector<float>& x) : CartesianPoint(x.size(), x, NAME_PLACEHOLDER) {}

	CartesianPoint() : CartesianPoint(1, {0.f}, NAME_PLACEHOLDER) {}

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

	void Print()
	{
		const int FLOAT_PRECISION = 4;

		std::cout << std::endl << m_name << " (" << m_dimension << "-dim):" << std::endl;
		for (size_t i = 0; i < m_x.size(); ++i)
		{
			std::cout << "  x" << i << " = "
				<< std::setprecision(FLOAT_PRECISION)
				<< m_x[i] << std::endl;
		}
	}

	static CartesianPoint Scan()
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

	PolarPoint ToPolarPoint()
	{
		float r = 0.f;
		auto n = m_dimension - 1;
		std::vector<float> phi(n);

		for (int i = 0; i <= n; ++i)
		{
			r += static_cast<float>(pow(m_x[i], 2));
		}
		r = sqrt(r);

		if (n > 0)
		{
			for (int i = 0; i < n - 1; ++i)
			{
				float sumOfSquares = 0.f;

				for (int j = i; j < n; ++j)
				{
					sumOfSquares += static_cast<float>(pow(m_x[j], 2));
				}

				phi[i] = acos(m_x[i] / sqrt(sumOfSquares));
			}

			float cos = static_cast<float>(m_x[n - 1] / sqrt(pow(m_x[n], 2) + pow(m_x[n - 1], 2)));
			phi[n - 1] = GetAngle(Sign(m_x[n]), cos);
		}

		PolarPoint result(r, phi, m_name);
		return result;
	}
};

class PolarPoint
{
private:
	static const size_t MIN_DIMENSION = 1;
	static const size_t MAX_DIMENSION = 1024;
	inline static const std::string NAME_PLACEHOLDER = "untitled";
	inline static const std::string DIMENSION_OUT_OF_RANGE_MESSAGE = "dimension was out of range";
	inline static const std::string DIMENSION_MISMATCH_MESSAGE = "number of angles must be one less then dimension";
	inline static const std::string INDEX_OUT_OF_RANGE_MESSAGE = "the index was out of range";

	size_t m_dimension;
	float m_r;
	std::vector<float> m_phi;
	std::string m_name;

public:
	PolarPoint(size_t dimension, float r, const std::vector<float>& phi, const std::string& name)
	{
		if (dimension < MIN_DIMENSION || dimension > MAX_DIMENSION)
		{
			throw std::out_of_range(DIMENSION_OUT_OF_RANGE_MESSAGE);
		}
		if (dimension - 1 != phi.size())
		{
			throw std::logic_error(DIMENSION_MISMATCH_MESSAGE);
		}

		m_dimension = dimension;
		m_r = r;
		m_phi = phi;
		m_name = name;
	}

	PolarPoint(float r, const std::vector<float>& phi, const std::string& name) : PolarPoint(phi.size() + 1, r, phi, name) {}

	PolarPoint(float r, const std::vector<float>& phi) : PolarPoint(phi.size() + 1, r, phi, NAME_PLACEHOLDER) {}

	void Print()
	{
		const int FLOAT_PRECISION = 4;

		std::cout << std::endl << m_name << " (" << m_dimension << "-dim):" << std::endl;
		std::cout << "  r = " << std::setprecision(FLOAT_PRECISION) << m_r << std::endl;

		for (size_t i = 0; i < m_phi.size(); ++i)
		{
			std::cout << "  phi" << i << " = "
				<< std::setprecision(FLOAT_PRECISION)
				<< m_phi[i] << std::endl;
		}
	}
};

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
		
	}

	return 0;
}

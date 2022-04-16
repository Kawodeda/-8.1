
#include "Points.h"
#include "MathUtil.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

const size_t CartesianPoint::MIN_DIMENSION = 1;
const size_t CartesianPoint::MAX_DIMENSION = 1024;
const std::string CartesianPoint::NAME_PLACEHOLDER = "untitled";
const std::string CartesianPoint::DIMENSION_OUT_OF_RANGE_MESSAGE = "dimension was out of range";
const std::string CartesianPoint::DIMENSION_MISMATCH_MESSAGE = "dimension and number of components must be the same";
const std::string CartesianPoint::INDEX_OUT_OF_RANGE_MESSAGE = "the index was out of range";

CartesianPoint::CartesianPoint(size_t dimension, const std::vector<float>& x, const std::string& name)
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

CartesianPoint::CartesianPoint(const std::vector<float>& x, const std::string& name) : CartesianPoint(x.size(), x, name) {}

CartesianPoint::CartesianPoint(const std::vector<float>& x) : CartesianPoint(x.size(), x, NAME_PLACEHOLDER) {}

CartesianPoint::CartesianPoint() : CartesianPoint(1, { 0.f }, NAME_PLACEHOLDER) {}

const std::string& CartesianPoint::GetNamePlaceholder()
{
	return NAME_PLACEHOLDER;
}

const std::string& CartesianPoint::GetName()
{
	return m_name;
}

size_t CartesianPoint::GetDimension()
{
	return m_dimension;
}

float CartesianPoint::GetXAt(size_t index)
{
	if (index >= m_x.size() || index < 0)
	{
		throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
	}

	return m_x[index];
}

void CartesianPoint::SetXAt(size_t index, float value)
{
	if (index >= m_x.size() || index < 0)
	{
		throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
	}

	m_x[index] = value;
}

void CartesianPoint::Print()
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

CartesianPoint CartesianPoint::Scan()
{
	std::cout << std::endl << "Enter point's name: ";
	std::string name;
	std::cin >> name;

	std::cout << "Enter point's dimension (whole number): ";
	size_t n = 0;
	std::cin >> n;
	if (n < MIN_DIMENSION || n > MAX_DIMENSION)
	{
		throw std::out_of_range(DIMENSION_OUT_OF_RANGE_MESSAGE);
	}

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

PolarPoint CartesianPoint::ToPolarPoint()
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


const size_t PolarPoint::MIN_DIMENSION = 1;
const size_t PolarPoint::MAX_DIMENSION = 1024;
const std::string PolarPoint::NAME_PLACEHOLDER = "untitled";
const std::string PolarPoint::DIMENSION_OUT_OF_RANGE_MESSAGE = "dimension was out of range";
const std::string PolarPoint::DIMENSION_MISMATCH_MESSAGE = "number of angles must be one less then dimension";
const std::string PolarPoint::INDEX_OUT_OF_RANGE_MESSAGE = "the index was out of range";

PolarPoint::PolarPoint(size_t dimension, float r, const std::vector<float>& phi, const std::string& name)
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

PolarPoint::PolarPoint(float r, const std::vector<float>& phi, const std::string& name) : PolarPoint(phi.size() + 1, r, phi, name) {}

PolarPoint::PolarPoint(float r, const std::vector<float>& phi) : PolarPoint(phi.size() + 1, r, phi, NAME_PLACEHOLDER) {}

void PolarPoint::Print()
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

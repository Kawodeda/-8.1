
#pragma once
#include <string>
#include <vector>

class PolarPoint
{
private:
	static const size_t MIN_DIMENSION;
	static const size_t MAX_DIMENSION;
	static const std::string NAME_PLACEHOLDER;
	static const std::string DIMENSION_OUT_OF_RANGE_MESSAGE;
	static const std::string DIMENSION_MISMATCH_MESSAGE;
	static const std::string INDEX_OUT_OF_RANGE_MESSAGE;

	size_t m_dimension;
	float m_r;
	std::vector<float> m_phi;
	std::string m_name;

public:
	PolarPoint(size_t dimension, float r, const std::vector<float>& phi, const std::string& name);

	PolarPoint(float r, const std::vector<float>& phi, const std::string& name);

	PolarPoint(float r, const std::vector<float>& phi);

	void Print();
};

class CartesianPoint
{
private:
	static const size_t MIN_DIMENSION;
	static const size_t MAX_DIMENSION;
	static const std::string NAME_PLACEHOLDER;
	static const std::string DIMENSION_OUT_OF_RANGE_MESSAGE;
	static const std::string DIMENSION_MISMATCH_MESSAGE;
	static const std::string INDEX_OUT_OF_RANGE_MESSAGE;

	size_t m_dimension;
	std::vector<float> m_x;
	std::string m_name;

public:
	CartesianPoint(size_t dimension, const std::vector<float>& x, const std::string& name);

	CartesianPoint(const std::vector<float>& x, const std::string& name);

	CartesianPoint(const std::vector<float>& x);

	CartesianPoint();

	const std::string& GetNamePlaceholder();

	const std::string& GetName();

	size_t GetDimension();

	float GetXAt(size_t index);

	void SetXAt(size_t index, float value);

	void Print();

	static CartesianPoint Scan();

	PolarPoint ToPolarPoint();
};

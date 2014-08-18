#include "Matrix4f.h"

Matrix4f::Matrix4f() : m(16, 0)
{
}

Matrix4f::~Matrix4f()
{
}

const Matrix4f& Matrix4f::initIdentity()
{
	m[0] = 1;	m[1] = 0;	 m[2] = 0;	m[3] = 0;
	m[4] = 0;	m[5] = 1;	 m[6] = 0;	m[7] = 0;
	m[8] = 0;	m[9] = 0;	 m[10] = 1;	m[11] = 0;
	m[12] = 0;	m[13] = 0;	 m[14] = 0;	m[15] = 1;

	return *this;
}

const Matrix4f& Matrix4f::initTranslation(float x, float y, float z)
{
	m[0] = 1;	m[1] = 0;	 m[2] = 0;	m[3] = x;
	m[4] = 0;	m[5] = 1;	 m[6] = 0;	m[7] = y;
	m[8] = 0;	m[9] = 0;	 m[10] = 1;	m[11] = z;
	m[12] = 0;	m[13] = 0;	 m[14] = 0;	m[15] = 1;

	return *this;
}

Matrix4f operator* (const Matrix4f& a, const Matrix4f& b)
{
	Matrix4f res;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			res.m[i * 4 + j] =	a.m[i * 4 + 0] * b.m[0 * 4 + j] +
								a.m[i * 4 + 1] * b.m[1 * 4 + j] +
								a.m[i * 4 + 2] * b.m[2 * 4 + j] +
								a.m[i * 4 + 3] * b.m[3 * 4 + j];
		}
	}

	return res;
}

float Matrix4f::operator()(unsigned int col, unsigned int row) const
{
	return m[col * 4 + row];
}

float& Matrix4f::operator()(unsigned int col, unsigned int row)
{
	return m[col * 4 + row];
}

const std::vector<float>& Matrix4f::getM() const
{
	return m;
}

void Matrix4f::setM(const std::vector<float>& m)
{
	this->m.assign(m.begin(), m.end());
}
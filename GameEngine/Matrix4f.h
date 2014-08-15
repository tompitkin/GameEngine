#pragma once

#include <vector>

//Column-major order
class Matrix4f
{
public:
	Matrix4f();
	~Matrix4f();
	void initIdentity();
	friend Matrix4f operator* (const Matrix4f& a, const Matrix4f& b);
	float operator()(unsigned int col, unsigned int row) const;
	float& operator()(unsigned int col, unsigned int row);
	std::vector<float> getM() const;
	void setM(const std::vector<float>& m);

private:
	std::vector<float> m;
};


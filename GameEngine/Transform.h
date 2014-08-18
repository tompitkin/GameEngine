#pragma once

class Vector3f;
class Matrix4f;

class Transform
{
public:
	Transform();
	~Transform();
	Matrix4f getTransformation() const;
	const Vector3f& getTranslation() const;
	void setTranslation(const Vector3f& translation);
	void setTranslation(float x, float y, float z);

private:
	Vector3f *translation;
};


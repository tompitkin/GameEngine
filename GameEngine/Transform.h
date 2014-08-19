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
	const Vector3f& getRotation() const;
	void setRotation(const Vector3f& rotation);
	void setRotation(float x, float y, float z);
	const Vector3f& getScale() const;
	void setScale(const Vector3f& scale);
	void setScale(float x, float y, float z);

private:
	Vector3f *translation;
	Vector3f *rotation;
	Vector3f *scale;
};


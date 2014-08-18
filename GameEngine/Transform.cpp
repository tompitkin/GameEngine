#include "Transform.h"

#include "Vector3f.h"
#include "Matrix4f.h"

Transform::Transform()
{
	translation = new Vector3f(0, 0, 0);
}

Transform::~Transform()
{
	delete translation;
}

Matrix4f Transform::getTransformation() const
{
	Matrix4f transM;
	return transM.initTranslation(translation->getX(), translation->getY(), translation->getZ());
}

const Vector3f& Transform::getTranslation() const
{
	return *translation;
}

void Transform::setTranslation(const Vector3f& translation)
{
	*this->translation = translation;
}

void Transform::setTranslation(float x, float y, float z)
{
	delete translation;
	translation = new Vector3f(x, y, z);
}
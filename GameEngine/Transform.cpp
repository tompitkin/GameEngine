#include "Transform.h"

#include "Vector3f.h"
#include "Matrix4f.h"

Transform::Transform()
{
	translation = new Vector3f(0, 0, 0);
	rotation = new Vector3f(0, 0, 0);
}

Transform::~Transform()
{
	delete translation;
	delete rotation;
}

Matrix4f Transform::getTransformation() const
{
	Matrix4f transM;
	Matrix4f rotM;
	transM.initTranslation(translation->getX(), translation->getY(), translation->getZ());
	rotM.initRotation(rotation->getX(), rotation->getY(), rotation->getZ());

	return rotM * transM;
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

const Vector3f& Transform::getRotation() const
{
	return *rotation;
}

void Transform::setRotation(const Vector3f& rotation)
{
	*this->rotation = rotation;
}

void Transform::setRotation(float x, float y, float z)
{
	delete rotation;
	rotation = new Vector3f(x, y, z);
}
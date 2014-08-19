#include "Transform.h"

#include "Vector3f.h"
#include "Matrix4f.h"

Transform::Transform()
{
	translation = new Vector3f(0, 0, 0);
	rotation = new Vector3f(0, 0, 0);
	scale = new Vector3f(1, 1, 1);
}

Transform::~Transform()
{
	delete translation;
	delete rotation;
	delete scale;
}

Matrix4f Transform::getTransformation() const
{
	Matrix4f transM;
	Matrix4f rotM;
	Matrix4f scaleM;
	transM.initTranslation(translation->getX(), translation->getY(), translation->getZ());
	rotM.initRotation(rotation->getX(), rotation->getY(), rotation->getZ());
	scaleM.initScale(scale->getX(), scale->getY(), scale->getZ());

	return transM * rotM * scaleM;
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

const Vector3f& Transform::getScale() const
{
	return *scale;
}

void Transform::setScale(const Vector3f& scale)
{
	*this->scale = scale;
}

void Transform::setScale(float x, float y, float z)
{
	delete scale;
	scale = new Vector3f(x, y, z);
}
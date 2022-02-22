#include"GPShape.hpp"
using namespace GamePhysics;

void GPShape::UpdateTransform()
{
	Rotation = normalize(Rotation);
	Transform = translate(toMat4(Rotation), Center);
	InversedTransform = inverse(Transform);
}

GPShape::GPShape() : Center(), Rotation()
{
	UpdateTransform();
}

quat GPShape::GetRotation() const
{
	return Rotation;
}

void GPShape::SetRotation(const quat &q)
{
	this->Rotation = q;
	UpdateTransform();
}

vec3 GPShape::GetPosition() const
{
	return Center;
}

void GPShape::SetPosition(const vec3 &Center)
{
	this->Center = Center;
	UpdateTransform();
}

void GPShape::SetPositionRotation(const vec3 &Center, const quat &q)
{
	this->Center = Center;
	this->Rotation = q;
	UpdateTransform();
}

mat4 GPShape::GetTransform() const
{
	return Transform;
}

mat4 GPShape::GetInversedTransform() const
{
	return InversedTransform;
}

GPShape::~GPShape()
{
}

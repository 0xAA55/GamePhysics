#include "GPPlane.hpp"

using namespace GamePhysics;

GPPlane::GPPlane(const vec3 &point, const vec3 &normal) :
	GPPlane(vec4(normal, -dot(point, normal)))
{
}

GPPlane::GPPlane(const vec3 &p1, const vec3 &p2, const vec3& p3) :
	GPPlane(p1, cross(p2 - p1, p3 - p2))
{
}

GPPlane::GPPlane(const vec4 &abcd) :
	GPShape()
{
	SetABCD(abcd);
}

float GPPlane::SDF(const vec3 &p) const
{
	return abs(dot(abcd, vec4(p, 1.0f)));
}

vec3 GPPlane::GetNormal() const
{
	return vec3(abcd.x, abcd.y, abcd.z);
}

vec4 GPPlane::GetABCD() const
{
	return abcd;
}

void GPPlane::SetABCD(const vec4 &abcd)
{
	// Make sure ABC is the normal vector that points to a direction that is away from the origin, and it's normalized.
	// Thus further calculations can be simplified.
	float l = length(vec3(abcd.x, abcd.y, abcd.z));
	this->abcd = abcd / l;
	if (this->abcd.w > 0) this->abcd = -this->abcd;
}

GPShape* GPPlane::Clone() const
{
	return new GPPlane(*this);
}

void GPPlane::Clone(GPShape& CloneTo, const GPShape& CloneFrom) const
{
	CloneTo = CloneFrom;
}

vec3 GPPlane::GetNearestPoint(const vec3 &p) const
{
	return p + GetNormal() * SDF(p);
}

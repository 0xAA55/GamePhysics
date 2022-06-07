#include "GPSphere.hpp"

using namespace GamePhysics;

GPSphere::GPSphere(const float Radius) : GPShape(), Radius(Radius)
{
}

float GPSphere::SDF(const vec3 &p) const
{
	return length(p) - Radius;
}

GPShape* GPSphere::Clone() const
{
	GPShape* ret = new GPSphere(*this);
}

void GPSphere::Clone(GPShape& CloneTo, const GPShape& CloneFrom) const
{
	CloneTo = CloneFrom;
}

vec3 GPSphere::GetNearestPoint(const vec3 &p) const
{
	float l = length(p);
	if (l <= Radius)
		return p;
	else
		return normalize(p) * Radius;
}

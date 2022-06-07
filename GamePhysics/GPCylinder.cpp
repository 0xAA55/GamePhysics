#include "GPCylinder.hpp"
using namespace GamePhysics;

GPCylinder::GPCylinder(float Height, float Radius)
	: GPShape(), Height(Height), Radius(Radius)
{
}

float GPCylinder::SDF(const vec3 &p) const
{
	vec2 xz = vec2(p.x, p.z);
	vec2 d = abs(vec2(length(xz), p.y)) - vec2(Height, Radius);
	return min(max(d.x, d.y), 0.0f) + length(max(d, 0.0f));
}

GPShape* GPCylinder::Clone() const
{
	GPShape* ret = new GPCylinder(*this);
}

void GPCylinder::Clone(GPShape& CloneTo, const GPShape& CloneFrom) const
{
	CloneTo = CloneFrom;
}

vec3 GPCylinder::GetNearestPoint(const vec3 &p) const
{
	const float HalfHeight = Height * 0.5f;
	vec3 x0z = vec3(p.x, 0, p.z);
	float l = length(x0z);
	float yd = abs(p.y) - HalfHeight;
	if (yd <= 0)
	{
		if (l <= Radius)
			return p;
		else
			return x0z * Radius / l + vec3(0, p.y, 0);
	}
	else
	{
		vec3 yv = vec3(0, sign(p.y) * HalfHeight, 0);
		if (l <= Radius)
			return x0z + yv;
		else
			return x0z * Radius / l + yv;
	}
}

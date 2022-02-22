#include "GPCapsule.hpp"
using namespace GamePhysics;

GPCapsule::GPCapsule(float Height, float Radius) :
	GPShape(), Height(Height), Radius(Radius)
{
}

float GPCapsule::SDF(const vec3 &p) const
{
	const float HalfHeight = Height * 0.5f;
	vec3 v = p;
	v.y = max(abs(v.y) - HalfHeight, 0.0f);
	return length(v) - Radius;
}

vec3 GPCapsule::GetNearestPoint(const vec3 &p) const
{
	const float HalfHeight = Height * 0.5f;
	if (abs(p.y) <= HalfHeight)
	{
		vec3 x0z = vec3(p.x, 0, p.z);
		float l = length(x0z);
		if (l <= Radius) return p;
		return x0z * Radius / l + vec3(0, p.y, 0);
	}
	else
	{
		vec3 ref = p - vec3(0, sign(p.y) * HalfHeight, 0);
		float l = length(ref);
		if (l <= Radius) return p;
		return ref * Radius / l;
	}
}

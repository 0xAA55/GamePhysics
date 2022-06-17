#include "GPBox.hpp"
using namespace GamePhysics;

GPBox::GPBox(const vec3 &Dimension) : GPShape(), Dimension(Dimension)
{
}

float GPBox::SDF(const vec3 &p) const
{
	vec3 q = abs(p) - Dimension;
	return length(max(q, 0.0f)) + min(max(q.x, max(q.y, q.z)), 0.0f);
}

GPShape* GPBox::Clone() const
{
	return new GPBox(*this);
}

void GPBox::Clone(GPShape& CloneTo, const GPShape& CloneFrom) const
{
	CloneTo = CloneFrom;
}

vec3 GPBox::GetNearestPoint(const vec3 &p) const
{
	return min(abs(p), Dimension) * sign(p);
}

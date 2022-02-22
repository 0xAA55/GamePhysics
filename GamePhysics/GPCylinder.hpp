#pragma once
#include<GPShape.hpp>
namespace GamePhysics
{
	class GPCylinder : public GPShape
	{
	public:
		float Height;
		float Radius;

		GPCylinder(float Height, float Radius);
		float SDF(const vec3 &p)const override;
		vec3 GetNearestPoint(const vec3 &p)const override;
	};
}

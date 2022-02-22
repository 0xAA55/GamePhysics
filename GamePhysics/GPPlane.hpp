#pragma once

#include<GPShape.hpp>
namespace GamePhysics
{
	class GPPlane : public GPShape
	{
	protected:
		vec4 abcd;
	public:

		GPPlane(const vec3 &point, const vec3 &normal);
		GPPlane(const vec3 &p1, const vec3 &p2, const vec3 &p3);
		GPPlane(const vec4 &abcd);

		vec3 GetNormal() const;
		vec4 GetABCD() const;
		void SetABCD(const vec4 &abcd);

		float SDF(const vec3 &p) const override;
		vec3 GetNearestPoint(const vec3 &p) const override;
	};
}

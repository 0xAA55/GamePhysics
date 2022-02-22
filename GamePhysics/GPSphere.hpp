#pragma once
#include<GPShape.hpp>
namespace GamePhysics
{
    class GPSphere : public GPShape
    {
    public:
        float Radius;

        GPSphere(const float Radius);
        float SDF(const vec3 &p) const override;
        vec3 GetNearestPoint(const vec3 &p) const override;
    };
}

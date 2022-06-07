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
        GPShape* Clone() const override;
        void Clone(GPShape& CloneTo, const GPShape& CloneFrom) const override;
        vec3 GetNearestPoint(const vec3 &p) const override;
    };
}

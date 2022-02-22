#pragma once
#include<GPShape.hpp>

namespace GamePhysics
{
    class GPCapsule : public GPShape
    {
    public:
        float Height;
        float Radius;
        
        GPCapsule(float Height, float Radius);
        float SDF(const vec3 &p) const override;
        vec3 GetNearestPoint(const vec3 &p) const override;
    };
}

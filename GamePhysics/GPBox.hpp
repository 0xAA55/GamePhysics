#pragma once
#include<GPShape.hpp>
namespace GamePhysics
{
    class GPBox : public GPShape
    {
    public:
        vec3 Dimension;

        GPBox(const vec3 &Dimension);
        float SDF(const vec3 &p) const override;
        GPShape* Clone() const override;
        void Clone(GPShape& CloneTo, const GPShape& CloneFrom) const override;
        vec3 GetNearestPoint(const vec3 &p) const override;
    };
}

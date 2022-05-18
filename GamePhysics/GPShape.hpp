#pragma once
#include<GPMath.hpp>

namespace GamePhysics
{
	class GPShape
	{
	protected:
		// For gets only
		vec3 Center;
		quat Rotation;

		// Question: why don't just expose the transform matrix into the public scope to allow it to be accessed and modified directly?
		// Answer: A transform matrix is able to contain more transform information than just translation and rotation.
		mat4 Transform;
		mat4 InversedTransform;
		void UpdateTransform();

	public:

		// What is SDF?
		// see: https://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm
		virtual float SDF(const vec3 & p) const = 0;
		virtual vec3 GetNearestPoint(const vec3 &p) const = 0;
		virtual ~GPShape();

		GPShape();
		quat GetRotation() const;
		void SetRotation(const quat &q);
		vec3 GetPosition() const;
		void SetPosition(const vec3 &Center);
		void SetPositionRotation(const vec3 &Center, const quat &q);
		mat4 GetTransform() const;
		mat4 GetInversedTransform() const;
	};
}

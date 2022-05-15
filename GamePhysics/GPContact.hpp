#pragma once

#include<GPMath.hpp>
#include<GPRigidBody.hpp>

namespace GamePhysics
{
	class GPContact
	{
	protected:
		GPRigidBody* RigidBodies[2];
		vec3 ContactPoint;
		vec3 ContactNormal;

	public:
		inline vec3 GetContactPoint() const { return ContactPoint; }
		inline vec3 GetContactNormal() const { return ContactNormal; }

		GPContact() = delete;
		GPContact(GPRigidBody* B1, GPRigidBody* B2, vec3 ContactPoint, vec3 ContactNormal);
		~GPContact();


	};
}

#pragma once

#include<GPMath.hpp>
#include<GPRigidBody.hpp>
#include<GPContact.hpp>

namespace GamePhysics
{


	class GPContactSolver
	{
	protected:
		using RigidBodyArray = std::vector<GPRigidBody*>;
		using ContactArray = std::vector<GPContact>;

		RigidBodyArray& RigidBodies;
		RigidBodyArray RigidBodySnapshot;
		ContactArray Contacts;

		float SDF(const GPRigidBody* b, const vec3 Point);
		void CreateRigidBodySnapshot();
		void ClearRigidBodySnapshot();
		void CheckContact(const GPRigidBody* a, const GPRigidBody* b); // Argument must come from `RigidBodySnapshot`

	public:
		GPContactSolver(RigidBodyArray& RigidBodiesOfWorld);
		~GPContactSolver();

		void DetectContacts();
		void ResolveContacts();
	};
}



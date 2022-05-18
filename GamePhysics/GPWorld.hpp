#pragma once

#include<vector>
#include<GPMath.hpp>
#include<GPShape.hpp>
#include<GPRigidBody.hpp>
#include<GPContact.hpp>

namespace GamePhysics
{
	class GPWorld
	{
	protected:
		std::vector<GPRigidBody*> RigidBodies;
		std::vector<GPContact*> Contacts;
		
		double SimulationDeltaTime;
		double TickSkipThreshold;
		double CumulativeTime;

		void UpdateMovement(float IntegrationTime);
		void CheckContact(const GPRigidBody* a, const GPRigidBody*b);
		void DetectContacts();
		void ResolveContacts();

	public:
		vec3 Gravity;
		
		GPWorld();
		~GPWorld();
		void AddRigidBody(const GPRigidBody& r);
		void AddRigidBody(const GPRigidBodyCreation &r);
		void RemoveRigidBody(GPRigidBody *&b);
		void Tick(double Duration);
	};
}

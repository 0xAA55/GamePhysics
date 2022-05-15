#pragma once

#include<vector>
#include<GPMath.hpp>
#include<GPShape.hpp>
#include<GPRigidBody.hpp>

namespace GamePhysics
{
	class GPWorld
	{
	protected:
		std::vector<GPRigidBody*> RigidBodies;
		
		double SimulationDeltaTime;
		double TickSkipThreshold;
		double CumulativeTime;

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

#pragma once

#include<memory>
#include<GPMath.hpp>
#include<GPShape.hpp>
#include<GPRigidBody.hpp>

namespace GamePhysics
{
	class GPWorld
	{
	protected:
		std::vector<std::shared_ptr<GPRigidBody>> RigidBodies;
		
		double SimulationDeltaTime;
		double TickSkipThreshold;
		double CumulativeTime;

	public:
		vec3 Gravity;
		
		GPWorld();
		void AddRigidBody(std::shared_ptr<GPRigidBody> r);
		void AddRigidBody(const GPRigidBodyCreation &r);
		void RemoveRigidBody(GPRigidBody *p);
		void Tick(double Duration);
	};
}

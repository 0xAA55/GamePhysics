#include"GPWorld.hpp"
using namespace GamePhysics;

GPWorld::GPWorld() :
	RigidBodies(),
	SimulationDeltaTime(1.0/100.0),
	TickSkipThreshold(1.0),
	CumulativeTime(0),
	Gravity(0.0f, -9.8f, 0.0f)
{
}

void GPWorld::AddRigidBody(std::shared_ptr<GPRigidBody> r)
{
	RigidBodies.push_back(r);
}

void GPWorld::AddRigidBody(const GPRigidBodyCreation &r)
{
	RigidBodies.push_back(std::shared_ptr<GPRigidBody>(new GPRigidBody(r)));
}

void GPWorld::RemoveRigidBody(GPRigidBody *b)
{
	RigidBodies.erase(
		std::remove_if(RigidBodies.begin(),
			RigidBodies.end(),
			[b](const auto &r)
			{
				return b == r.get();
			}),
		RigidBodies.end()
	);
}

void GPWorld::Tick(double Duration)
{
	int i;
	const double TargetTime = CumulativeTime + Duration;
#pragma omp parallel for
	for (i = 0; (size_t)i < RigidBodies.size(); i++)
	{
		std::shared_ptr<GPRigidBody> r = RigidBodies[i];
		double CurTime = CumulativeTime;
		if (CurTime + TickSkipThreshold <= TargetTime)
		{
			r->Integrate(Duration);
			CurTime += Duration;
		}
		else if (CurTime + SimulationDeltaTime <= TargetTime)
		{
			r->Integrate(SimulationDeltaTime);
			CurTime += SimulationDeltaTime;
		}
	}
}


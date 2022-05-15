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

GPWorld::~GPWorld()
{
	for (auto p : RigidBodies)
	{
		delete p;
	}
	RigidBodies.clear();
}

void GPWorld::AddRigidBody(const GPRigidBody& r)
{
	RigidBodies.push_back(new GPRigidBody(r));
}

void GPWorld::AddRigidBody(const GPRigidBodyCreation &r)
{
	RigidBodies.push_back(new GPRigidBody(r));
}

void GPWorld::RemoveRigidBody(GPRigidBody *&b)
{
	RigidBodies.erase(
		std::remove_if(RigidBodies.begin(),
			RigidBodies.end(),
			[b](const auto &r)
			{
				return b == r;
			}),
		RigidBodies.end()
	);
	delete b;
	b = nullptr;
}

void GPWorld::Tick(double Duration)
{
	int i;
	const double TargetTime = CumulativeTime + Duration;
	float IntegrationTime = SimulationDeltaTime;
	if (CumulativeTime + TickSkipThreshold <= TargetTime)
	{
		IntegrationTime = (float)Duration;
	}
	else if (CumulativeTime + SimulationDeltaTime > TargetTime)
	{
		return;
	}
	CumulativeTime += IntegrationTime;
#pragma omp parallel for
	for (i = 0; (size_t)i < RigidBodies.size(); i++)
	{
		GPRigidBody* r = RigidBodies[i];
		r->Integrate(IntegrationTime);
	}
}


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

void GPWorld::CheckContact(const GPRigidBody* a, const GPRigidBody* b)
{

}

void GPWorld::DetectContacts()
{
	Contacts.clear();

	ptrdiff_t NumBodies = (ptrdiff_t)RigidBodies.size();
	if (!NumBodies) return;

#pragma omp parallel
	{
		for (ptrdiff_t i = 0; i < NumBodies - 1; i++)
		{
#pragma omp for nowait
			for (ptrdiff_t j = i + 1; j < NumBodies; j++)
			{
				CheckContact(RigidBodies[i], RigidBodies[j]);
			}
		}
	}
}

void GPWorld::ResolveContacts()
{

}

void GPWorld::UpdateMovement(float IntegrationTime)
{
	ptrdiff_t NumBodies = (ptrdiff_t)RigidBodies.size();

#pragma omp parallel for
	for (ptrdiff_t i = 0; i < NumBodies; i++)
	{
		GPRigidBody* r = RigidBodies[i];
		r->Integrate(IntegrationTime);
	}
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

	UpdateMovement(IntegrationTime);
	DetectContacts();
	ResolveContacts();

	CumulativeTime += IntegrationTime;
}

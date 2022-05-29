#include"GPContactSolver.hpp"
using namespace GamePhysics;

GPContactSolver::GPContactSolver(RigidBodyArray& RigidBodiesOfWorld) :
	RigidBodies(RigidBodiesOfWorld)
{
}

void GPContactSolver::CreateRigidBodySnapshot()
{

}

void GPContactSolver::ClearRigidBodySnapshot()
{

}

float GPContactSolver::SDF(const GPRigidBody* b, const vec3 Point)
{

}

void GPContactSolver::CheckContact(const GPRigidBody* a, const GPRigidBody* b)
{

}

void GPContactSolver::DetectContacts()
{
	Contacts.clear();
	CreateRigidBodySnapshot();

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

void GPContactSolver::ResolveContacts()
{

}

GPContactSolver::~GPContactSolver()
{
	ClearRigidBodySnapshot();
}






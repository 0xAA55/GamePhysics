#include"GPContactSolver.hpp"
using namespace GamePhysics;

GPContactSolver::GPContactSolver(RigidBodyArray& RigidBodiesOfWorld) :
	Contacts(), RigidBodies(RigidBodiesOfWorld), RigidBodySnapshot()
{
}

void GPContactSolver::CreateRigidBodySnapshot()
{
	ptrdiff_t i, j, size_src, size_dst;
	size_src = RigidBodies.size();
	size_dst = RigidBodySnapshot.size();

	// Do minimum efforts to match the memory size of the rigid bodies
	if (size_src > size_dst)
	{
		RigidBodySnapshot.resize(size_src);
		for (i = size_dst; i < size_src; i++)
		{
			RigidBodySnapshot[i] = new GPRigidBody(*RigidBodies[i]);
		}
	}
	else if (size_src < size_dst)
	{
		for (i = size_src; i < size_dst; i++) delete RigidBodySnapshot[i];
		RigidBodySnapshot.resize(size_src);
	}
#pragma omp parallel for
	for (i = 0; i < size_src; i++)
	{
		GPRigidBody& Target = *RigidBodySnapshot[i];
		Target = *RigidBodies[i];
		for (auto Shape : Target.Shapes)
		{
			// Transform all the shapes to be relative to 
			Shape->SetPositionRotation(Target.Orient * Shape->GetPosition() + Target.Position, Target.Orient * Shape->GetRotation());
		}
	}
}

void GPContactSolver::ClearRigidBodySnapshot()
{
	for (auto it : RigidBodySnapshot) delete it;
	RigidBodySnapshot.clear();
}

float GPContactSolver::SDF(const GPRigidBody* b, const vec3 Point)
{
	float MinDist = FLT_MAX;
	for (auto Shape : b->Shapes)
	{
		vec3 RelPoint = Shape->GetInversedTransform() * vec4(Point.x, Point.y, Point.z, 1);
		MinDist = min(MinDist, Shape->SDF(RelPoint));
	}
	return MinDist;
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






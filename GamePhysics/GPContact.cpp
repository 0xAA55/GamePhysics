#include"GPContact.hpp"
using namespace GamePhysics;

GPContact::GPContact(GPRigidBody* B1, GPRigidBody* B2, vec3 ContactPoint, vec3 ContactNormal, float Restitution, float Friction, float Penetration) :
	RigidBodies(), ContactPoint(ContactPoint), ContactNormal(ContactNormal),
	Restitution(Restitution), Friction(Friction), Penetration(Penetration)
{
	RigidBodies[0] = B1;
	RigidBodies[1] = B2;
}

GPContact::~GPContact()
{
}

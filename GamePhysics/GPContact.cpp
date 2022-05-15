#include"GPContact.hpp"
using namespace GamePhysics;

GPContact::GPContact(GPRigidBody* B1, GPRigidBody* B2, vec3 ContactPoint, vec3 ContactNormal) :
	RigidBodies(), ContactPoint(ContactPoint), ContactNormal(ContactNormal)
{
	RigidBodies[0] = B1;
	RigidBodies[1] = B2;
}

GPContact::~GPContact()
{
}

#include "GPRigidBody.hpp"
using namespace GamePhysics;

GPRigidBody::GPRigidBody(const GPRigidBodyCreation &c) :
    Shapes(c.Shapes),
    Movable(c.Movable),
    Sleepable(c.Sleepable),
    Acceleration(c.Acceleration),
    Friction(c.Friction),
    Restitution(c.Restitution),
    LinearDamp(c.LinearDamp),
    AngularDamp(c.AngularDamp),
    Position(c.Position),
    Orient(c.Orient),
    Velocity(c.InitialVelocity),
    Rotation(c.InitialRotation),
    IsAwake(true),
    ForceAccum(),
    TorqueAccum(),
    LastFrameLinearAccel()
{
    SetMass(c.Mass);
    SetInertiaTensor(c.InertiaTensor);
    UpdateTransform();
}

GPRigidBody::GPRigidBody(const GPRigidBody& f)
{
    size_t NumShapes = f.Shapes.size();
    *this = f;
    for (size_t i = 0; i < NumShapes; i++)
    {
        // Re-allocate pointers
        Shapes[i] = f.Shapes[i]->Clone();
    }
}

GPRigidBody::~GPRigidBody()
{
    for (auto it : Shapes) delete it;
}

mat4 GPRigidBody::GetTransform()
{
    return Transform;
}

float GPRigidBody::GetMass()
{
    return Mass;
}

mat3 GPRigidBody::GetInertiaTensor()
{
    return InertiaTensor;
}

void GPRigidBody::UpdateTransform()
{
    Transform = translate(toMat4(Orient), Position);
}

void GPRigidBody::SetMass(float Mass)
{
    this->Mass = Mass;
    this->InversedMass = 1.0f / Mass;
}

void GPRigidBody::SetInertiaTensor(mat3 InertiaTensor)
{
    this->InertiaTensor = InertiaTensor;
    this->InversedInertiaTensor = inverse(InertiaTensor);
}

void GPRigidBody::Integrate(float DeltaTime)
{
    UpdateTransform();
}

#pragma once
#include<GPMath.hpp>
#include<GPShape.hpp>
#include<vector>
#include<memory>

namespace GamePhysics
{
    class GPRigidBodyCreation
    {
    public:
        // The pointers of the shapes shouldn't be deleted.
        // The created `GPRigidBody` owns the shapes.
        std::vector<GPShape*> Shapes;

        float Mass;
        mat3 InertiaTensor;

        bool Movable;
        bool Sleepable;

        vec3 Acceleration;

        float Friction;
        float Restitution;

        float LinearDamp;
        float AngularDamp;

        vec3 Position;
        quat Orient;

        vec3 InitialVelocity;
        vec3 InitialRotation;
    };

	class GPRigidBody
	{
    protected:
        float Mass;
        mat3 InertiaTensor;

        float InversedMass;
        mat3 InversedInertiaTensor;

        mat4 Transform;

        vec3 ForceAccum;
        vec3 TorqueAccum;

        vec3 Acceleration;

        vec3 LastFrameLinearAccel;

	public:
        GPRigidBody() = default;
        GPRigidBody(const GPRigidBody& f);
        GPRigidBody(const GPRigidBodyCreation& c);
        ~GPRigidBody();

        // Attributes
        std::vector<GPShape*> Shapes;

        bool Movable;
        bool Sleepable;

        float Friction;
        float Restitution;

        float LinearDamp;
        float AngularDamp;

        // Volatile Attributes
        vec3 Position;
        quat Orient;

        vec3 Velocity;
        vec3 Rotation;

        bool IsAwake;

        mat4 GetTransform();
        float GetMass();
        mat3 GetInertiaTensor();

        void UpdateTransform();
        void SetMass(float Mass);
        void SetInertiaTensor(mat3 InertiaTensor);

        void Integrate(float DeltaTime);
	};
}

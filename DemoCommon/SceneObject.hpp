#pragma once
#include<GLStaticMesh.hpp>
#include<GLTexture.hpp>
#include<memory>
namespace GLRenderer
{
	class SceneObject
	{
	public:
		vec3 Position;
		vec3 YawPitchRoll;
		vec3 Scale;

		mat4 MakeTransform();



	protected:

	};
}

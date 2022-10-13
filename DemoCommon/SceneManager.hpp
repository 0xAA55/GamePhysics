#pragma once
#include<GamePhysics.hpp>
#include<SceneObject.hpp>
#include<map>
#include<memory>
#include<string>
#include<vector>
namespace GLRenderer
{
	using SceneObjectRef = std::shared_ptr<SceneObject>;

	class SceneManager
	{
	public:
		vec3 CameraPos;
		vec3 CameraYawPitchRoll;
		vec3 CameraDir;

		std::vector<SceneObjectRef> Objects;

		void Update(double Time);
		void Render(double Time);

	protected:
		double LastUpdateTime;
	};

}

#pragma once
#include<GLRendererBase.hpp>
namespace GLRenderer
{
	class SceneManager;
	class GLRenderer
	{
	public:
		inline GLRenderer(SceneManager& Scene) :
			Scene(Scene)
		{}

		virtual bool CheckRequirements() = 0;
		virtual void LoadResources() = 0;
		virtual void UnloadResources() = 0;
		virtual void Update(double Time) = 0;
		virtual void Render(double Time) = 0;

		inline ~GLRenderer()
		{
			UnloadResources();
		}

	protected:
		SceneManager& Scene;


	};
}

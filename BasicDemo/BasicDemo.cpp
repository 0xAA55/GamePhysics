#include<AppFrame.hpp>
#include<GLRenderer.hpp>
#include<GamePhysics.hpp>
#include<iostream>

#ifdef _WIN32
#include<Windows.h>
#include<stdlib.h>
int main(int argc, char **argv);
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nShow)
{
	return main(__argc, __argv);
}
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int nShow)
{
	return main(__argc, __argv);
}
#endif

using namespace GLFWApp;
using namespace GamePhysics;
using namespace GLRenderer;

struct Vertex3D
{
	vec3 Position;
	vec3 Normal;
	Vertex3D(const vec3& Position, const vec3 &Normal) :
		Position(Position), Normal(Normal)
	{
	}
};

class BasicDemo : public AppFrame
{
public:
	GPWorld World;
	double LastUpdateTime;
	GLShaderProgram BoxShader;
	GLMesh<Vertex3D, mat4, MeshElementType::UnsignedByte> BoxMesh;
	vec3 CameraPos;
	vec3 CamYawPitchRoll;

	BasicDemo() :
		World(),
		LastUpdateTime(0),
		BoxShader
		(
"#version 130\n"
"uniform mat4 ProjectionView;"
"in vec3 Position;"
"in vec3 Normal;"
"in mat4 Transform;"
"out vec3 WorldNormal;"
"void main()"
"{"
"    WorldNormal = mat3(Transform) * Normal;"
"    gl_Position = ProjectionView * Transform * vec4(Position, 1.0);"
"}"
"",
			nullptr,
"#version 130\n"
"in vec3 WorldNormal;"
"out vec4 Color;"
"void main()"
"{"
"    Color = vec4(WorldNormal * 0.5 + 0.5, 1.0);"
"}"
""
		),
		BoxMesh(MeshPrimitiveType::Triangles),
		CameraPos(0, 0, -5),
		CamYawPitchRoll(0, 0, 0)
	{
		BoxMesh.VertexBufferFormat.push_back(AttribDesc("Position", AttribTypeEnum::Vec3));
		BoxMesh.VertexBufferFormat.push_back(AttribDesc("Normal", AttribTypeEnum::Vec3));
		BoxMesh.InstanceBufferFormat.push_back(AttribDesc("Transform", AttribTypeEnum::Mat4));

		std::cout
			<< "================" << std::endl
			<< "Active Attribs:" << std::endl
			<< "================" << std::endl;
		auto Attribs = BoxShader.GetActiveAttribs();
		for (auto &it : Attribs)
		{
			std::cout << AttribTypeToString(it.Type) << " " << it.Name << "; // " << it.Size << std::endl;
		}

		std::cout
			<< "================" << std::endl
			<< "Active Uniforms:" << std::endl
			<< "================" << std::endl;
		auto Uniforms = BoxShader.GetActiveUniforms();
		for (auto &it : Uniforms)
		{
			std::cout << UniformTypeToString(it.Type) << " " << it.Name << "; // " << it.Size << std::endl;
		}
	}

	void OnLoadResources() noexcept(false) override
	{
		const GLfloat P = 0.5f, N = -0.5f;
		const vec3
			V0 = vec3(N, P, N),
			V1 = vec3(P, P, N),
			V2 = vec3(N, N, N),
			V3 = vec3(P, N, N),
			V4 = vec3(N, P, P),
			V5 = vec3(P, P, P),
			V6 = vec3(N, N, P),
			V7 = vec3(P, N, P);
		Vertex3D Vertices[] =
		{
			Vertex3D(V0, vec3(0, 0, -1)),
			Vertex3D(V1, vec3(0, 0, -1)),
			Vertex3D(V2, vec3(0, 0, -1)),
			Vertex3D(V3, vec3(0, 0, -1)),

			Vertex3D(V4, vec3(-1, 0, 0)),
			Vertex3D(V0, vec3(-1, 0, 0)),
			Vertex3D(V6, vec3(-1, 0, 0)),
			Vertex3D(V2, vec3(-1, 0, 0)),
			
			Vertex3D(V5, vec3(0, 0, 1)),
			Vertex3D(V4, vec3(0, 0, 1)),
			Vertex3D(V7, vec3(0, 0, 1)),
			Vertex3D(V6, vec3(0, 0, 1)),
			
			Vertex3D(V1, vec3(1, 0, 0)),
			Vertex3D(V5, vec3(1, 0, 0)),
			Vertex3D(V3, vec3(1, 0, 0)),
			Vertex3D(V7, vec3(1, 0, 0)),
			
			Vertex3D(V4, vec3(0, 1, 0)),
			Vertex3D(V5, vec3(0, 1, 0)),
			Vertex3D(V0, vec3(0, 1, 0)),
			Vertex3D(V1, vec3(0, 1, 0)),
			
			Vertex3D(V7, vec3(0, -1, 0)),
			Vertex3D(V6, vec3(0, -1, 0)),
			Vertex3D(V3, vec3(0, -1, 0)),
			Vertex3D(V2, vec3(0, -1, 0))
		};
		BoxMesh.VertexBuffer.PushBack(Vertices, countof(Vertices));
		
#define FACE(B) 0 + B, 1 + B, 2 + B, 1 + B, 3 + B, 2 + B
		GLubyte Indices[] =
		{
			FACE(0), FACE(4), FACE(8),
			FACE(12), FACE(16), FACE(20)
		};
#undef FACE
		BoxMesh.IndexBuffer.PushBack(Indices, countof(Indices));

		BoxMesh.InstanceBuffer.PushBack(mat4(
			vec4(1, 0, 0, 0),
			vec4(0, 1, 0, 0),
			vec4(0, 0, 1, 0),
			vec4(0, 0, 0, 1)));
	}
	
	void OnUnLoadResources() noexcept(false)override
	{
		BoxMesh.VertexBuffer.Clear();
		BoxMesh.IndexBuffer.Clear();
		BoxMesh.InstanceBuffer.Clear();
	}

	void OnRender(double Time, int ClientWidth, int ClientHeight) override
	{
		Renderer::SetViewport(0, 0, ClientWidth, ClientHeight);
		Renderer::ClearScreen(0, 0, 0, 0);
		Renderer::SetDepthMode(true);

		CameraPos = vec3(0, 1, 5);
		CamYawPitchRoll = vec3(0, 0, 0);

		GLfloat PZ = 0.1f;
		GLfloat PX = PZ * ClientWidth * 2.0f / (ClientWidth + ClientHeight);
		GLfloat PY = PZ * ClientHeight * 2.0f / (ClientWidth + ClientHeight);

		mat4 MatView = Renderer::GetViewMatrix(CamYawPitchRoll, CameraPos);
		mat4 MatProjection = Renderer::Perspective(-PX, PX, -PY, PY, PZ, 10000.0f);
		mat4 MatProjectionView = MatProjection * MatView;
		mat4 MatItem = Renderer::Mat4RotEuler((float)Time, 0.0f, 0.0f);

		BoxMesh.InstanceBuffer[0] = MatItem;

		BoxShader.Use();
		BoxShader.SetUniform("View", MatView);
		BoxShader.SetUniform("Projection", MatProjection);
		BoxShader.SetUniform("ProjectionView", MatProjectionView);

		BoxMesh.Draw(BoxShader);
		SwapBuffers();
	}

	void OnUpdate(double Time) override
	{
		double DeltaTime = Time - LastUpdateTime;
		World.Tick(DeltaTime);
		LastUpdateTime += DeltaTime;
	}
};

int main(int argc, char **argv)
{
	try
	{
		BasicDemo App;
		App.RunLoop();
	}
	catch (ShaderCompilationException &e)
	{
		fprintf(stderr, "ShaderCompilationException: %s\n", e.what());
	}
}

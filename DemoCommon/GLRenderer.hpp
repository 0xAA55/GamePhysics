#pragma once
#include<GLShader.hpp>
#include<GLMesh.hpp>
namespace GLRenderer
{
	enum class FaceType
	{
		CW = 0x0900,
		CCW = 0x0901
	};

	enum class CullMode
	{
		FrontFace = 0x0404,
		BackFace = 0x0405,
		BothFace = 0x0408
	};

	enum class CompareFunc
	{
		Never = 0x0200,
		Less = 0x0201,
		Equal = 0x0202,
		LessEqual = 0x0203,
		Greater = 0x0204,
		NotEqual = 0x0205,
		GreaterEqual = 0x0206,
		Always = 0x0207
	};

	class Renderer
	{
	public:
		static void ClearScreen(GLclampf Red, GLclampf Green, GLclampf Blue, GLclampf Alpha, bool ClearZ = true, bool ClearStencil = true);
		static void SetViewport(GLint x, GLint y, GLsizei w, GLsizei h);
		static void DefineFrontFace(FaceType ft = FaceType::CCW);
		static void SetCullFace(bool Enabled = true, CullMode cm = CullMode::BackFace);
		static void SetDepthMode(bool Enabled = false, CompareFunc CompareToZBuf = CompareFunc::Less, GLdouble NearVal = 0, GLdouble FarVal = 1);

		static mat3 Mat3RotEuler(GLfloat Yaw, GLfloat Pitch, GLfloat Roll);
		static mat4 Mat4RotEuler(GLfloat Yaw, GLfloat Pitch, GLfloat Roll);
		static mat4 GetViewMatrix(GLfloat Yaw, GLfloat Pitch, GLfloat Roll, vec3 Position);
		static mat3 Mat3RotEuler(vec3 YawPitchRoll);
		static mat4 Mat4RotEuler(vec3 YawPitchRoll);
		static mat4 GetViewMatrix(vec3 YawPitchRoll, vec3 Position);
		static mat4 Perspective(GLfloat Left = -1, GLfloat Right = 1, GLfloat Bottom = -1, GLfloat Top = 1, GLfloat Near = 1, GLfloat Far = 1000);
	};
}

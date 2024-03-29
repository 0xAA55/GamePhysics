#include "GLRenderUtility.hpp"
#include <GL/glew.h>
namespace GLRenderer
{
	void RenderUtility::ClearScreen(GLclampf Red, GLclampf Green, GLclampf Blue, GLclampf Alpha, bool ClearZ, bool ClearStencil)
	{
		glClearColor(Red, Green, Blue, Alpha);
		glClear(GL_COLOR_BUFFER_BIT |
			(ClearZ ? GL_DEPTH_BUFFER_BIT : 0) |
			(ClearStencil ? GL_STENCIL_BUFFER_BIT : 0));
	}

	void RenderUtility::SetViewport(GLint x, GLint y, GLsizei w, GLsizei h)
	{
		glViewport(x, y, w, h);
	}

	void RenderUtility::DefineFrontFace(FaceType ft)
	{
		glFrontFace(static_cast<GLenum>(ft));
	}

	void RenderUtility::SetCullFace(bool Enabled, CullMode cm)
	{
		if (Enabled)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(static_cast<GLenum>(cm));
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}
	}

	void RenderUtility::SetDepthMode(bool Enabled, CompareFunc CompareToZBuf, GLdouble NearVal, GLdouble FarVal)
	{
		if (Enabled)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(static_cast<GLenum>(CompareToZBuf));
			glDepthRange(NearVal, FarVal);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
	}

	mat3 RenderUtility::Mat3RotEuler(GLfloat Yaw, GLfloat Pitch, GLfloat Roll)
	{
		GLfloat
			sr = sin(Roll),
			cr = cos(Roll),
			sp = sin(Pitch),
			cp = cos(Pitch),
			sy = sin(Yaw),
			cy = cos(Yaw);

		GLfloat
			srcp = sr * cp,
			srsp = sr * sp,
			crcp = cr * cp,
			crsp = cr * sp;

		return mat3
		(
			vec3(cr * cy + srsp * sy, srcp, -sy * cr + srsp * cy),
			vec3(-sr * cy + crsp * sy, crcp, sy * sr + crsp * cy),
			vec3(sy * cp, -sp, cp * cy)
		);
	}

	mat4 RenderUtility::Mat4RotEuler(GLfloat Yaw, GLfloat Pitch, GLfloat Roll)
	{
		GLfloat
			sr = sin(Roll),
			cr = cos(Roll),
			sp = sin(Pitch),
			cp = cos(Pitch),
			sy = sin(Yaw),
			cy = cos(Yaw);

		GLfloat
			srcp = sr * cp,
			srsp = sr * sp,
			crcp = cr * cp,
			crsp = cr * sp;

		return mat4
		(
			vec4(cr * cy + srsp * sy, srcp, -sy * cr + srsp * cy, 0),
			vec4(-sr * cy + crsp * sy, crcp, sy * sr + crsp * cy, 0),
			vec4(sy * cp, -sp, cp * cy, 0),
			vec4(0, 0, 0, 1)
		);
	}

	mat4 RenderUtility::GetViewMatrix(GLfloat Yaw, GLfloat Pitch, GLfloat Roll, vec3 Position)
	{
		mat4 TransposedEuler = transpose(Mat4RotEuler(Yaw, Pitch, Roll));
		TransposedEuler[3] = vec4(mat3(TransposedEuler) * -Position, 1.0f);
		return TransposedEuler;
	}

	mat3 RenderUtility::Mat3RotEuler(vec3 YawPitchRoll)
	{
		return Mat3RotEuler(YawPitchRoll.x, YawPitchRoll.y, YawPitchRoll.z);
	}

	mat4 RenderUtility::Mat4RotEuler(vec3 YawPitchRoll)
	{
		return Mat4RotEuler(YawPitchRoll.x, YawPitchRoll.y, YawPitchRoll.z);
	}

	mat4 RenderUtility::Mat4Translate(vec3 Position)
	{
		return mat4(
			vec4(1, 0, 0, 0),
			vec4(0, 1, 0, 0),
			vec4(0, 0, 1, 0),
			vec4(Position.x, Position.y, Position.z, 1)
		);
	}

	mat4 RenderUtility::Mat4Scale(const float s)
	{
		return mat4(
			vec4(s, 0, 0, 0),
			vec4(0, s, 0, 0),
			vec4(0, 0, s, 0),
			vec4(0, 0, 0, 1)
		);
	}

	mat4 RenderUtility::GetViewMatrix(vec3 YawPitchRoll, vec3 Position)
	{
		return GetViewMatrix(YawPitchRoll.x, YawPitchRoll.y, YawPitchRoll.z, Position);
	}

	mat4 RenderUtility::Perspective(GLfloat Left, GLfloat Right, GLfloat Bottom, GLfloat Top, GLfloat Near, GLfloat Far)
	{
		GLfloat
			Width = Right - Left,
			Height = Top - Bottom,
			Depth = Far - Near;

		return mat4(
			vec4(2 * Near / Width, 0, 0, 0),
			vec4(0, 2 * Near / Height, 0, 0),
			vec4(0, 0, -Far / Depth, -1),
			vec4(0, 0, -2 * Near * Far / Depth, 0)
		);
	}
}

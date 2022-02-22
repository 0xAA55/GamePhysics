#pragma once
#include<string>
#include<stdexcept>
#include<type_traits>
#include<GLRendererBase.hpp>
namespace GLRenderer
{
	class ShaderCompilationException : public std::runtime_error
	{
	public:
		ShaderCompilationException(std::string InfoLog) noexcept;
	};

	class GLShaderObject
	{
	protected:
		std::string InfoLog;

	public:
		GLuint Obj;

		GLShaderObject(GLenum ShaderType);
		~GLShaderObject();

		operator GLuint() const;
		void Compile(const char *ShaderSource) noexcept(false);
		std::string GetInfoLog() const;
	};

	class GLUniformLocation
	{
	protected:
		GLint Location;
		static GLuint UsingProgram;
		friend class GLShaderProgram;

	public:
		GLUniformLocation(GLint Location);
		GLUniformLocation(const GLchar *UniformName);
		operator GLint() const;
	};

	class GLVertexAttribLocation
	{
	protected:
		GLint Location;
		static GLuint UsingProgram;
		friend class GLShaderProgram;

	public:
		GLVertexAttribLocation(GLint Location);
		GLVertexAttribLocation(const GLchar *VertexAttribName);
		operator GLint() const;
	};

	class GLShaderProgram
	{
	protected:
		GLuint Program;
		std::string InfoLogVS;
		std::string InfoLogGS;
		std::string InfoLogFS;
		std::string InfoLogLinkage;

	public:
		GLShaderProgram(const char *VertexShaderCode, const char *GeometryShaderCode, const char *FragmentShaderCode) noexcept(false);
		~GLShaderProgram();

		std::string GetInfoLogVS() const;
		std::string GetInfoLogGS() const;
		std::string GetInfoLogFS() const;
		std::string GetInfoLogLinkage() const;
		operator GLuint() const;

		void Use() const;

		static void SetUniform(GLUniformLocation location, GLfloat x);
		static void SetUniform(GLUniformLocation location, GLfloat x, GLfloat y);
		static void SetUniform(GLUniformLocation location, GLfloat x, GLfloat y, GLfloat z);
		static void SetUniform(GLUniformLocation location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		static void SetUniform(GLUniformLocation location, int dimension, const GLfloat *value, int count);
		static void SetUniform(GLUniformLocation location, GLint x);
		static void SetUniform(GLUniformLocation location, GLint x, GLint y);
		static void SetUniform(GLUniformLocation location, GLint x, GLint y, GLint z);
		static void SetUniform(GLUniformLocation location, GLint x, GLint y, GLint z, GLint w);
		static void SetUniform(GLUniformLocation location, int dimension, const GLint *value, int count);
		static void SetUniform(GLUniformLocation location, GLuint x);
		static void SetUniform(GLUniformLocation location, GLuint x, GLuint y);
		static void SetUniform(GLUniformLocation location, GLuint x, GLuint y, GLuint z);
		static void SetUniform(GLUniformLocation location, GLuint x, GLuint y, GLuint z, GLuint w);
		static void SetUniform(GLUniformLocation location, int dimension, const GLuint *value, int count);
		static void SetUniform(GLUniformLocation location, GLdouble x);
		static void SetUniform(GLUniformLocation location, GLdouble x, GLdouble y);
		static void SetUniform(GLUniformLocation location, GLdouble x, GLdouble y, GLdouble z);
		static void SetUniform(GLUniformLocation location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
		static void SetUniform(GLUniformLocation location, int dimension, const GLdouble *value, int count);
		static void SetUniform(GLUniformLocation location, GLint64 x);
		static void SetUniform(GLUniformLocation location, GLint64 x, GLint64 y);
		static void SetUniform(GLUniformLocation location, GLint64 x, GLint64 y, GLint64 z);
		static void SetUniform(GLUniformLocation location, GLint64 x, GLint64 y, GLint64 z, GLint64 w);
		static void SetUniform(GLUniformLocation location, int dimension, const GLint64 *value, int count);
		static void SetUniform(GLUniformLocation location, GLuint64 x);
		static void SetUniform(GLUniformLocation location, GLuint64 x, GLuint64 y);
		static void SetUniform(GLUniformLocation location, GLuint64 x, GLuint64 y, GLuint64 z);
		static void SetUniform(GLUniformLocation location, GLuint64 x, GLuint64 y, GLuint64 z, GLuint64 w);
		static void SetUniform(GLUniformLocation location, int dimension, const GLuint64 *value, int count);

		static void SetUniform(GLUniformLocation location, vec1 v);
		static void SetUniform(GLUniformLocation location, vec2 v);
		static void SetUniform(GLUniformLocation location, vec3 v);
		static void SetUniform(GLUniformLocation location, vec4 v);
		static void SetUniform(GLUniformLocation location, ivec1 v);
		static void SetUniform(GLUniformLocation location, ivec2 v);
		static void SetUniform(GLUniformLocation location, ivec3 v);
		static void SetUniform(GLUniformLocation location, ivec4 v);
		static void SetUniform(GLUniformLocation location, uvec1 v);
		static void SetUniform(GLUniformLocation location, uvec2 v);
		static void SetUniform(GLUniformLocation location, uvec3 v);
		static void SetUniform(GLUniformLocation location, uvec4 v);
		static void SetUniform(GLUniformLocation location, dvec1 v);
		static void SetUniform(GLUniformLocation location, dvec2 v);
		static void SetUniform(GLUniformLocation location, dvec3 v);
		static void SetUniform(GLUniformLocation location, dvec4 v);
		static void SetUniform(GLUniformLocation location, i64vec1 v);
		static void SetUniform(GLUniformLocation location, i64vec2 v);
		static void SetUniform(GLUniformLocation location, i64vec3 v);
		static void SetUniform(GLUniformLocation location, i64vec4 v);
		static void SetUniform(GLUniformLocation location, u64vec1 v);
		static void SetUniform(GLUniformLocation location, u64vec2 v);
		static void SetUniform(GLUniformLocation location, u64vec3 v);
		static void SetUniform(GLUniformLocation location, u64vec4 v);

		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLfloat x);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLfloat x, GLfloat y);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLfloat x, GLfloat y, GLfloat z);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLshort x);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLshort x, GLshort y);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLshort x, GLshort y, GLshort z);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLshort x, GLshort y, GLshort z, GLshort w);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLdouble x);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLdouble x, GLdouble y);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLdouble x, GLdouble y, GLdouble z);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);

		static void SetVertexAttribInt(GLVertexAttribLocation location, GLint x);
		static void SetVertexAttribInt(GLVertexAttribLocation location, GLint x, GLint y);
		static void SetVertexAttribInt(GLVertexAttribLocation location, GLint x, GLint y, GLint z);
		static void SetVertexAttribInt(GLVertexAttribLocation location, GLint x, GLint y, GLint z, GLint w);
		static void SetVertexAttribInt(GLVertexAttribLocation location, GLuint x);
		static void SetVertexAttribInt(GLVertexAttribLocation location, GLuint x, GLuint y);
		static void SetVertexAttribInt(GLVertexAttribLocation location, GLuint x, GLuint y, GLuint z);
		static void SetVertexAttribInt(GLVertexAttribLocation location, GLuint x, GLuint y, GLuint z, GLuint w);

		static void SetVertexAttribDouble(GLVertexAttribLocation location, GLdouble x);
		static void SetVertexAttribDouble(GLVertexAttribLocation location, GLdouble x, GLdouble y);
		static void SetVertexAttribDouble(GLVertexAttribLocation location, GLdouble x, GLdouble y, GLdouble z);
		static void SetVertexAttribDouble(GLVertexAttribLocation location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	};
}

#pragma once
#include<string>
#include<stdexcept>
#include<functional>
#include<type_traits>
#include<unordered_map>
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
		constexpr GLUniformLocation(GLint Location);
		GLUniformLocation(const GLchar *UniformName);
		GLUniformLocation(std::string UniformName);
		constexpr operator GLint() const;
	};

	class GLVertexAttribLocation
	{
	protected:
		GLint Location;
		static GLuint UsingProgram;
		friend class GLShaderProgram;

	public:
		constexpr GLVertexAttribLocation(GLint Location);
		GLVertexAttribLocation(const GLchar *VertexAttribName);
		GLVertexAttribLocation(std::string VertexAttribName);
		constexpr operator GLint() const;
	};

	struct ActiveUniform
	{
		std::string Name;
		GLsizei Size;
	};

	class GLShaderProgram
	{
	protected:
		GLuint Program;
		std::string InfoLogVS;
		std::string InfoLogGS;
		std::string InfoLogFS;
		std::string InfoLogLinkage;
		size_t Hash;
		
	public:
		GLShaderProgram(const GLchar *VertexShaderCode, const GLchar *GeometryShaderCode, const GLchar *FragmentShaderCode) noexcept(false);
		~GLShaderProgram();

		std::string GetInfoLogVS() const;
		std::string GetInfoLogGS() const;
		std::string GetInfoLogFS() const;
		std::string GetInfoLogLinkage() const;

		size_t GetHash() const;
		bool operator==(const GLShaderProgram &Another) const;

		operator GLuint() const;
		void Use() const;
		void Unuse() const;

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

		static inline void SetUniform(GLUniformLocation location, const vec1 &v) { SetUniform(location, v.x); }
		static inline void SetUniform(GLUniformLocation location, const vec2 &v) { SetUniform(location, v.x, v.y); }
		static inline void SetUniform(GLUniformLocation location, const vec3 &v) { SetUniform(location, v.x, v.y, v.z); }
		static inline void SetUniform(GLUniformLocation location, const vec4 &v) { SetUniform(location, v.x, v.y, v.z, v.w); }
		static inline void SetUniform(GLUniformLocation location, const ivec1 &v) { SetUniform(location, v.x); }
		static inline void SetUniform(GLUniformLocation location, const ivec2 &v) { SetUniform(location, v.x, v.y); }
		static inline void SetUniform(GLUniformLocation location, const ivec3 &v) { SetUniform(location, v.x, v.y, v.z); }
		static inline void SetUniform(GLUniformLocation location, const ivec4 &v) { SetUniform(location, v.x, v.y, v.z, v.w); }
		static inline void SetUniform(GLUniformLocation location, const uvec1 &v) { SetUniform(location, v.x); }
		static inline void SetUniform(GLUniformLocation location, const uvec2 &v) { SetUniform(location, v.x, v.y); }
		static inline void SetUniform(GLUniformLocation location, const uvec3 &v) { SetUniform(location, v.x, v.y, v.z); }
		static inline void SetUniform(GLUniformLocation location, const uvec4 &v) { SetUniform(location, v.x, v.y, v.z, v.w); }
		static inline void SetUniform(GLUniformLocation location, const dvec1 &v) { SetUniform(location, v.x); }
		static inline void SetUniform(GLUniformLocation location, const dvec2 &v) { SetUniform(location, v.x, v.y); }
		static inline void SetUniform(GLUniformLocation location, const dvec3 &v) { SetUniform(location, v.x, v.y, v.z); }
		static inline void SetUniform(GLUniformLocation location, const dvec4 &v) { SetUniform(location, v.x, v.y, v.z, v.w); }
		static inline void SetUniform(GLUniformLocation location, const i64vec1 &v) { SetUniform(location, v.x); }
		static inline void SetUniform(GLUniformLocation location, const i64vec2 &v) { SetUniform(location, v.x, v.y); }
		static inline void SetUniform(GLUniformLocation location, const i64vec3 &v) { SetUniform(location, v.x, v.y, v.z); }
		static inline void SetUniform(GLUniformLocation location, const i64vec4 &v) { SetUniform(location, v.x, v.y, v.z, v.w); }
		static inline void SetUniform(GLUniformLocation location, const u64vec1 &v) { SetUniform(location, v.x); }
		static inline void SetUniform(GLUniformLocation location, const u64vec2 &v) { SetUniform(location, v.x, v.y); }
		static inline void SetUniform(GLUniformLocation location, const u64vec3 &v) { SetUniform(location, v.x, v.y, v.z); }
		static inline void SetUniform(GLUniformLocation location, const u64vec4 &v) { SetUniform(location, v.x, v.y, v.z, v.w); }

		static inline void SetUniform(GLUniformLocation location, const vec1 v[], int count) { SetUniform(location, 1, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const vec2 v[], int count) { SetUniform(location, 2, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const vec3 v[], int count) { SetUniform(location, 3, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const vec4 v[], int count) { SetUniform(location, 4, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const ivec1 v[], int count) { SetUniform(location, 1, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const ivec2 v[], int count) { SetUniform(location, 2, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const ivec3 v[], int count) { SetUniform(location, 3, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const ivec4 v[], int count) { SetUniform(location, 4, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const uvec1 v[], int count) { SetUniform(location, 1, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const uvec2 v[], int count) { SetUniform(location, 2, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const uvec3 v[], int count) { SetUniform(location, 3, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const uvec4 v[], int count) { SetUniform(location, 4, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const dvec1 v[], int count) { SetUniform(location, 1, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const dvec2 v[], int count) { SetUniform(location, 2, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const dvec3 v[], int count) { SetUniform(location, 3, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const dvec4 v[], int count) { SetUniform(location, 4, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const i64vec1 v[], int count) { SetUniform(location, 1, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const i64vec2 v[], int count) { SetUniform(location, 2, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const i64vec3 v[], int count) { SetUniform(location, 3, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const i64vec4 v[], int count) { SetUniform(location, 4, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const u64vec1 v[], int count) { SetUniform(location, 1, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const u64vec2 v[], int count) { SetUniform(location, 2, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const u64vec3 v[], int count) { SetUniform(location, 3, &v[0].x, count); }
		static inline void SetUniform(GLUniformLocation location, const u64vec4 v[], int count) { SetUniform(location, 4, &v[0].x, count); }

		static void SetUniform(GLUniformLocation location, const mat2 v[], int count, bool transpose = false);
		static void SetUniform(GLUniformLocation location, const mat3 v[], int count, bool transpose = false);
		static void SetUniform(GLUniformLocation location, const mat4 v[], int count, bool transpose = false);
		static void SetUniform(GLUniformLocation location, const mat2x3 v[], int count, bool transpose = false);
		static void SetUniform(GLUniformLocation location, const mat2x4 v[], int count, bool transpose = false);
		static void SetUniform(GLUniformLocation location, const mat3x2 v[], int count, bool transpose = false);
		static void SetUniform(GLUniformLocation location, const mat3x4 v[], int count, bool transpose = false);
		static void SetUniform(GLUniformLocation location, const mat4x2 v[], int count, bool transpose = false);
		static void SetUniform(GLUniformLocation location, const mat4x3 v[], int count, bool transpose = false);
		static void SetUniform(GLUniformLocation location, const dmat2 v[], int count, bool transpose = false);
		static void SetUniform(GLUniformLocation location, const dmat3 v[], int count, bool transpose = false);
		static void SetUniform(GLUniformLocation location, const dmat4 v[], int count, bool transpose = false);
		static void SetUniform(GLUniformLocation location, const dmat2x3 v[], int count, bool transpose = false);
		static void SetUniform(GLUniformLocation location, const dmat2x4 v[], int count, bool transpose = false);
		static void SetUniform(GLUniformLocation location, const dmat3x2 v[], int count, bool transpose = false);
		static void SetUniform(GLUniformLocation location, const dmat3x4 v[], int count, bool transpose = false);
		static void SetUniform(GLUniformLocation location, const dmat4x2 v[], int count, bool transpose = false);
		static void SetUniform(GLUniformLocation location, const dmat4x3 v[], int count, bool transpose = false);

		static inline void SetUniform(GLUniformLocation location, const mat2 &v, bool transpose = false) { SetUniform(location, &v, 1, transpose); }
		static inline void SetUniform(GLUniformLocation location, const mat3 &v, bool transpose = false) { SetUniform(location, &v, 1, transpose); }
		static inline void SetUniform(GLUniformLocation location, const mat4 &v, bool transpose = false) { SetUniform(location, &v, 1, transpose); }
		static inline void SetUniform(GLUniformLocation location, const mat2x3 &v, bool transpose = false) { SetUniform(location, &v, 1, transpose); }
		static inline void SetUniform(GLUniformLocation location, const mat2x4 &v, bool transpose = false) { SetUniform(location, &v, 1, transpose); }
		static inline void SetUniform(GLUniformLocation location, const mat3x2 &v, bool transpose = false) { SetUniform(location, &v, 1, transpose); }
		static inline void SetUniform(GLUniformLocation location, const mat3x4 &v, bool transpose = false) { SetUniform(location, &v, 1, transpose); }
		static inline void SetUniform(GLUniformLocation location, const mat4x2 &v, bool transpose = false) { SetUniform(location, &v, 1, transpose); }
		static inline void SetUniform(GLUniformLocation location, const mat4x3 &v, bool transpose = false) { SetUniform(location, &v, 1, transpose); }
		static inline void SetUniform(GLUniformLocation location, const dmat2 &v, bool transpose = false) { SetUniform(location, &v, 1, transpose); }
		static inline void SetUniform(GLUniformLocation location, const dmat3 &v, bool transpose = false) { SetUniform(location, &v, 1, transpose); }
		static inline void SetUniform(GLUniformLocation location, const dmat4 &v, bool transpose = false) { SetUniform(location, &v, 1, transpose); }
		static inline void SetUniform(GLUniformLocation location, const dmat2x3 &v, bool transpose = false) { SetUniform(location, &v, 1, transpose); }
		static inline void SetUniform(GLUniformLocation location, const dmat2x4 &v, bool transpose = false) { SetUniform(location, &v, 1, transpose); }
		static inline void SetUniform(GLUniformLocation location, const dmat3x2 &v, bool transpose = false) { SetUniform(location, &v, 1, transpose); }
		static inline void SetUniform(GLUniformLocation location, const dmat3x4 &v, bool transpose = false) { SetUniform(location, &v, 1, transpose); }
		static inline void SetUniform(GLUniformLocation location, const dmat4x2 &v, bool transpose = false) { SetUniform(location, &v, 1, transpose); }
		static inline void SetUniform(GLUniformLocation location, const dmat4x3 &v, bool transpose = false) { SetUniform(location, &v, 1, transpose); }

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

		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLbyte *xyzw, bool Normalized);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLubyte *xyzw, bool Normalized);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLint *xyzw, bool Normalized);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLuint *xyzw, bool Normalized);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLshort *xyzw, bool Normalized);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLushort *xyzw, bool Normalized);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLbyte x, GLbyte y, GLbyte z, GLbyte w, bool Normalized);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLubyte x, GLubyte y, GLubyte z, GLubyte w, bool Normalized);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLint x, GLint y, GLint z, GLint w, bool Normalized);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLuint x, GLuint y, GLuint z, GLuint w, bool Normalized);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLshort x, GLshort y, GLshort z, GLshort w, bool Normalized);
		static void SetVertexAttribFloat(GLVertexAttribLocation location, GLushort x, GLushort y, GLushort z, GLushort w, bool Normalized);

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

	struct GLShaderProgramHasher
	{
		std::size_t operator()(const GLShaderProgram &K) const
		{
			return K.GetHash();
		}
	};

}

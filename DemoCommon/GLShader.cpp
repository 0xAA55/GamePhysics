#include <GL/glew.h>
#include "GLShader.hpp"
#include <cstring>
using namespace GLRenderer;

ShaderCompilationException::ShaderCompilationException(std::string InfoLog) noexcept :
	std::runtime_error(InfoLog)
{
}

GLShaderObject::GLShaderObject(GLenum ShaderType) :
	Obj(glCreateShader(ShaderType))
{
	if (!Obj) throw std::runtime_error("glCreateShader() failed.");
}

GLShaderObject::~GLShaderObject()
{
	glDeleteShader(Obj);
}

GLShaderObject::operator GLuint() const
{
	return Obj;
}

void GLShaderObject::Compile(const char *ShaderSource)
{
	GLint Status = GL_FALSE;
	GLsizei InfoLogLength = 0;

	const char *CodeArray[1] = {ShaderSource};
	const GLint LengthArray[1] = {(GLint)strlen(ShaderSource)};

	glShaderSource(Obj, 1, CodeArray, LengthArray);
	glCompileShader(Obj);
	glGetShaderiv(Obj, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength)
	{
		InfoLog.resize(InfoLogLength, '\0');
		glGetShaderInfoLog(Obj, InfoLogLength, &InfoLogLength, &InfoLog[0]);
	}
	glGetShaderiv(Obj, GL_COMPILE_STATUS, &Status);
	if (!Status) throw ShaderCompilationException(InfoLog);
}

std::string GLShaderObject::GetInfoLog() const
{
	return InfoLog;
}

GLUniformLocation::GLUniformLocation(GLint Location) :
	Location(Location)
{
}

GLUniformLocation::GLUniformLocation(const GLchar *UniformName) :
	Location(glGetUniformLocation(UsingProgram, UniformName))
{
}

GLUniformLocation::operator GLint() const
{
	return Location;
}

GLVertexAttribLocation::GLVertexAttribLocation(GLint Location) :
	Location(Location)
{
}

GLVertexAttribLocation::GLVertexAttribLocation(const GLchar *VertexAttribName) :
	Location(glGetAttribLocation(UsingProgram, VertexAttribName))
{
}

GLVertexAttribLocation::operator GLint() const
{
	return Location;
}

GLShaderProgram::GLShaderProgram(const char *VertexShaderCode, const char *GeometryShaderCode, const char *FragmentShaderCode) :
	Program(glCreateProgram())
{
	if (VertexShaderCode)
	{
		GLShaderObject s(GL_VERTEX_SHADER);
		s.Compile(VertexShaderCode);
		InfoLogVS = s.GetInfoLog();
		glAttachShader(Program, s);
	}
	if (GeometryShaderCode)
	{
		GLShaderObject s(GL_GEOMETRY_SHADER);
		s.Compile(GeometryShaderCode);
		InfoLogGS = s.GetInfoLog();
		glAttachShader(Program, s);
	}
	if (FragmentShaderCode)
	{
		GLShaderObject s(GL_FRAGMENT_SHADER);
		s.Compile(FragmentShaderCode);
		InfoLogFS = s.GetInfoLog();
		glAttachShader(Program, s);
	}
	glLinkProgram(Program);

	GLint Status = GL_FALSE;
	GLsizei InfoLogLength = 0;
	glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength)
	{
		InfoLogLinkage.resize(InfoLogLength, '\0');
		glGetShaderInfoLog(Program, InfoLogLength, &InfoLogLength, &InfoLogLinkage[0]);
	}
	glGetProgramiv(Program, GL_COMPILE_STATUS, &Status);
	if (!Status) throw ShaderCompilationException(InfoLogLinkage);
}

GLShaderProgram::~GLShaderProgram()
{
	glDeleteProgram(Program);
}

std::string GLShaderProgram::GetInfoLogVS() const
{
	return InfoLogVS;
}
std::string GLShaderProgram::GetInfoLogGS() const
{
	return InfoLogGS;
}
std::string GLShaderProgram::GetInfoLogFS() const
{
	return InfoLogFS;
}
std::string GLShaderProgram::GetInfoLogLinkage() const
{
	return InfoLogLinkage;
}

GLShaderProgram::operator GLuint() const
{
	return Program;
}

void GLShaderProgram::Use() const
{
	glUseProgram(Program);
	GLUniformLocation::UsingProgram = Program;
	GLVertexAttribLocation::UsingProgram = Program;
}

void GLShaderProgram::SetUniform(GLUniformLocation location, GLfloat x) { glUniform1f(location, x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLfloat x, GLfloat y) { glUniform2f(location, x, y); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLfloat x, GLfloat y, GLfloat z) { glUniform3f(location, x, y, z); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { glUniform4f(location, x, y, z, w); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLint x) { glUniform1i(location, x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLint x, GLint y) { glUniform2i(location, x, y); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLint x, GLint y, GLint z) { glUniform3i(location, x, y, z); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLint x, GLint y, GLint z, GLint w) { glUniform4i(location, x, y, z, w); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLuint x) { glUniform1ui(location, x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLuint x, GLuint y) { glUniform2ui(location, x, y); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLuint x, GLuint y, GLuint z) { glUniform3ui(location, x, y, z); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLuint x, GLuint y, GLuint z, GLuint w) { glUniform4ui(location, x, y, z, w); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLdouble x) { glUniform1d(location, x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLdouble x, GLdouble y) { glUniform2d(location, x, y); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLdouble x, GLdouble y, GLdouble z) { glUniform3d(location, x, y, z); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { glUniform4d(location, x, y, z, w); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLint64 x) { glUniform1i64ARB(location, x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLint64 x, GLint64 y) { glUniform2i64ARB(location, x, y); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLint64 x, GLint64 y, GLint64 z) { glUniform3i64ARB(location, x, y, z); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLint64 x, GLint64 y, GLint64 z, GLint64 w) { glUniform4i64ARB(location, x, y, z, w); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLuint64 x) { glUniform1ui64ARB(location, x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLuint64 x, GLuint64 y) { glUniform2ui64ARB(location, x, y); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLuint64 x, GLuint64 y, GLuint64 z) { glUniform3ui64ARB(location, x, y, z); }
void GLShaderProgram::SetUniform(GLUniformLocation location, GLuint64 x, GLuint64 y, GLuint64 z, GLuint64 w) { glUniform4ui64ARB(location, x, y, z, w); }
void GLShaderProgram::SetUniform(GLUniformLocation location, int dimension, const GLfloat *value, int count)
{
	switch (dimension)
	{
	case 1: glUniform1fv(location, count, value); break;
	case 2: glUniform2fv(location, count, value); break;
	case 3: glUniform3fv(location, count, value); break;
	case 4: glUniform4fv(location, count, value); break;
	default: throw std::invalid_argument("`dimension` must be 1 or 2 or 3 or 4.");
	}
}
void GLShaderProgram::SetUniform(GLUniformLocation location, int dimension, const GLint *value, int count)
{
	switch (dimension)
	{
	case 1: glUniform1iv(location, count, value); break;
	case 2: glUniform2iv(location, count, value); break;
	case 3: glUniform3iv(location, count, value); break;
	case 4: glUniform4iv(location, count, value); break;
	default: throw std::invalid_argument("`dimension` must be 1 or 2 or 3 or 4.");
	}
}
void GLShaderProgram::SetUniform(GLUniformLocation location, int dimension, const GLuint *value, int count)
{
	switch (dimension)
	{
	case 1: glUniform1uiv(location, count, value); break;
	case 2: glUniform2uiv(location, count, value); break;
	case 3: glUniform3uiv(location, count, value); break;
	case 4: glUniform4uiv(location, count, value); break;
	default: throw std::invalid_argument("`dimension` must be 1 or 2 or 3 or 4.");
	}
}
void GLShaderProgram::SetUniform(GLUniformLocation location, int dimension, const GLdouble *value, int count)
{
	switch (dimension)
	{
	case 1: glUniform1dv(location, count, value); break;
	case 2: glUniform2dv(location, count, value); break;
	case 3: glUniform3dv(location, count, value); break;
	case 4: glUniform4dv(location, count, value); break;
	default: throw std::invalid_argument("`dimension` must be 1 or 2 or 3 or 4.");
	}
}
void GLShaderProgram::SetUniform(GLUniformLocation location, int dimension, const GLint64 *value, int count)
{
	switch (dimension)
	{
	case 1: glUniform1i64vARB(location, count, value); break;
	case 2: glUniform2i64vARB(location, count, value); break;
	case 3: glUniform3i64vARB(location, count, value); break;
	case 4: glUniform4i64vARB(location, count, value); break;
	default: throw std::invalid_argument("`dimension` must be 1 or 2 or 3 or 4.");
	}
}
void GLShaderProgram::SetUniform(GLUniformLocation location, int dimension, const GLuint64 *value, int count)
{
	switch (dimension)
	{
	case 1: glUniform1ui64vARB(location, count, value); break;
	case 2: glUniform2ui64vARB(location, count, value); break;
	case 3: glUniform3ui64vARB(location, count, value); break;
	case 4: glUniform4ui64vARB(location, count, value); break;
	default: throw std::invalid_argument("`dimension` must be 1 or 2 or 3 or 4.");
	}
}

void GLShaderProgram::SetUniform(GLUniformLocation location, vec1 v) { SetUniform(location, v.x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, vec2 v) { SetUniform(location, v.x, v.y); }
void GLShaderProgram::SetUniform(GLUniformLocation location, vec3 v) { SetUniform(location, v.x, v.y, v.z); }
void GLShaderProgram::SetUniform(GLUniformLocation location, vec4 v) { SetUniform(location, v.x, v.y, v.z, v.w); }
void GLShaderProgram::SetUniform(GLUniformLocation location, ivec1 v) { SetUniform(location, v.x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, ivec2 v) { SetUniform(location, v.x, v.y); }
void GLShaderProgram::SetUniform(GLUniformLocation location, ivec3 v) { SetUniform(location, v.x, v.y, v.z); }
void GLShaderProgram::SetUniform(GLUniformLocation location, ivec4 v) { SetUniform(location, v.x, v.y, v.z, v.w); }
void GLShaderProgram::SetUniform(GLUniformLocation location, uvec1 v) { SetUniform(location, v.x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, uvec2 v) { SetUniform(location, v.x, v.y); }
void GLShaderProgram::SetUniform(GLUniformLocation location, uvec3 v) { SetUniform(location, v.x, v.y, v.z); }
void GLShaderProgram::SetUniform(GLUniformLocation location, uvec4 v) { SetUniform(location, v.x, v.y, v.z, v.w); }
void GLShaderProgram::SetUniform(GLUniformLocation location, dvec1 v) { SetUniform(location, v.x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, dvec2 v) { SetUniform(location, v.x, v.y); }
void GLShaderProgram::SetUniform(GLUniformLocation location, dvec3 v) { SetUniform(location, v.x, v.y, v.z); }
void GLShaderProgram::SetUniform(GLUniformLocation location, dvec4 v) { SetUniform(location, v.x, v.y, v.z, v.w); }
void GLShaderProgram::SetUniform(GLUniformLocation location, i64vec1 v) { SetUniform(location, v.x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, i64vec2 v) { SetUniform(location, v.x, v.y); }
void GLShaderProgram::SetUniform(GLUniformLocation location, i64vec3 v) { SetUniform(location, v.x, v.y, v.z); }
void GLShaderProgram::SetUniform(GLUniformLocation location, i64vec4 v) { SetUniform(location, v.x, v.y, v.z, v.w); }
void GLShaderProgram::SetUniform(GLUniformLocation location, u64vec1 v) { SetUniform(location, v.x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, u64vec2 v) { SetUniform(location, v.x, v.y); }
void GLShaderProgram::SetUniform(GLUniformLocation location, u64vec3 v) { SetUniform(location, v.x, v.y, v.z); }
void GLShaderProgram::SetUniform(GLUniformLocation location, u64vec4 v) { SetUniform(location, v.x, v.y, v.z, v.w); }

void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLfloat x) { glVertexAttrib1f(location, x); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLfloat x, GLfloat y) { glVertexAttrib2f(location, x, y); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLfloat x, GLfloat y, GLfloat z) { glVertexAttrib3f(location, x, y, z); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { glVertexAttrib4f(location, x, y, z, w); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLshort x) { glVertexAttrib1s(location, x); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLshort x, GLshort y) { glVertexAttrib2s(location, x, y); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLshort x, GLshort y, GLshort z) { glVertexAttrib3s(location, x, y, z); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLshort x, GLshort y, GLshort z, GLshort w) { glVertexAttrib4s(location, x, y, z, w); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLdouble x) { glVertexAttrib1d(location, x); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLdouble x, GLdouble y) { glVertexAttrib2d(location, x, y); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLdouble x, GLdouble y, GLdouble z) { glVertexAttrib3d(location, x, y, z); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { glVertexAttrib4d(location, x, y, z, w); }

void GLShaderProgram::SetVertexAttribInt(GLVertexAttribLocation location, GLint x) { glVertexAttribI1i(location, x); }
void GLShaderProgram::SetVertexAttribInt(GLVertexAttribLocation location, GLint x, GLint y) { glVertexAttribI2i(location, x, y); }
void GLShaderProgram::SetVertexAttribInt(GLVertexAttribLocation location, GLint x, GLint y, GLint z) { glVertexAttribI3i(location, x, y, z); }
void GLShaderProgram::SetVertexAttribInt(GLVertexAttribLocation location, GLint x, GLint y, GLint z, GLint w) { glVertexAttribI4i(location, x, y, z, w); }
void GLShaderProgram::SetVertexAttribInt(GLVertexAttribLocation location, GLuint x) { glVertexAttribI1ui(location, x); }
void GLShaderProgram::SetVertexAttribInt(GLVertexAttribLocation location, GLuint x, GLuint y) { glVertexAttribI2ui(location, x, y); }
void GLShaderProgram::SetVertexAttribInt(GLVertexAttribLocation location, GLuint x, GLuint y, GLuint z) { glVertexAttribI3ui(location, x, y, z); }
void GLShaderProgram::SetVertexAttribInt(GLVertexAttribLocation location, GLuint x, GLuint y, GLuint z, GLuint w) { glVertexAttribI4ui(location, x, y, z, w); }

void GLShaderProgram::SetVertexAttribDouble(GLVertexAttribLocation location, GLdouble x) { glVertexAttribL1d(location, x); }
void GLShaderProgram::SetVertexAttribDouble(GLVertexAttribLocation location, GLdouble x, GLdouble y) { glVertexAttribL2d(location, x, y); }
void GLShaderProgram::SetVertexAttribDouble(GLVertexAttribLocation location, GLdouble x, GLdouble y, GLdouble z) { glVertexAttribL3d(location, x, y, z); }
void GLShaderProgram::SetVertexAttribDouble(GLVertexAttribLocation location, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { glVertexAttribL4d(location, x, y, z, w); }


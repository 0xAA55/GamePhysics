#include <GL/glew.h>
#include "GLShader.hpp"
#include <cstring>
#include<GLMesh.hpp>
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

GLuint GLUniformLocation::UsingProgram = 0;
GLuint GLVertexAttribLocation::UsingProgram = 0;

GLUniformLocation::GLUniformLocation(const GLchar *UniformName)
{
#if _DEBUG
	if (!UsingProgram) throw std::logic_error("Must call GLShaderProgram::Use() first.");
#endif
	Location = glGetUniformLocation(UsingProgram, UniformName);
}

GLVertexAttribLocation::GLVertexAttribLocation(const GLchar *VertexAttribName)
{
#if _DEBUG
	if (!UsingProgram) throw std::logic_error("Must call GLShaderProgram::Use() first.");
#endif
	Location = glGetAttribLocation(UsingProgram, VertexAttribName);
}

ActiveUniform::ActiveUniform(const std::string &Name, UniformTypeEnum Type, GLsizei Size) :
	Name(Name), Type(Type), Size(Size)
{
}

ActiveAttrib::ActiveAttrib(const std::string &Name, AttribTypeEnum Type, GLsizei Size) :
	Name(Name), Type(Type), Size(Size)
{
}

GLShaderProgram::GLShaderProgram(const GLchar *VertexShaderCode, const GLchar *GeometryShaderCode, const GLchar *FragmentShaderCode) :
	Program(glCreateProgram()), ComputeNumWorkGroups(nullptr), Hash(0)
{
	if (VertexShaderCode)
	{
		GLShaderObject s(GL_VERTEX_SHADER);
		s.Compile(VertexShaderCode);
		InfoLogVS = s.GetInfoLog();
		glAttachShader(Program, s);
		GLHashCombine(Hash, std::string(VertexShaderCode));
		GLHashCombine(Hash, InfoLogVS);
	}
	if (GeometryShaderCode)
	{
		GLShaderObject s(GL_GEOMETRY_SHADER);
		s.Compile(GeometryShaderCode);
		InfoLogGS = s.GetInfoLog();
		glAttachShader(Program, s);
		GLHashCombine(Hash, std::string(GeometryShaderCode));
		GLHashCombine(Hash, InfoLogGS);
	}
	if (FragmentShaderCode)
	{
		GLShaderObject s(GL_FRAGMENT_SHADER);
		s.Compile(FragmentShaderCode);
		InfoLogFS = s.GetInfoLog();
		glAttachShader(Program, s);
		GLHashCombine(Hash, std::string(FragmentShaderCode));
		GLHashCombine(Hash, InfoLogFS);
	}
	glLinkProgram(Program);

	GLint Status = GL_FALSE;
	GLsizei InfoLogLength = 0;
	glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength)
	{
		InfoLogLinkage.resize(InfoLogLength, '\0');
		glGetShaderInfoLog(Program, InfoLogLength, &InfoLogLength, &InfoLogLinkage[0]);
		GLHashCombine(Hash, InfoLogLength);
	}
	glGetProgramiv(Program, GL_LINK_STATUS, &Status);
	if (!Status) throw ShaderCompilationException(InfoLogLinkage);
}

GLShaderProgram::GLShaderProgram(const GLchar *ComputeShaderCode) :
	Program(glCreateProgram()), ComputeNumWorkGroups(new GLBufferObject(BufferType::DispatchIndirectBuffer, sizeof(uvec3), BufferUsage::StreamDraw)), Hash(0)
{
	GLShaderObject s(GL_COMPUTE_SHADER);
	s.Compile(ComputeShaderCode);
	InfoLogFS = s.GetInfoLog();
	glAttachShader(Program, s);
	GLHashCombine(Hash, std::string(ComputeShaderCode));
	GLHashCombine(Hash, InfoLogCS);
	glLinkProgram(Program);

	GLint Status = GL_FALSE;
	GLsizei InfoLogLength = 0;
	glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength)
	{
		InfoLogLinkage.resize(InfoLogLength, '\0');
		glGetShaderInfoLog(Program, InfoLogLength, &InfoLogLength, &InfoLogLinkage[0]);
		GLHashCombine(Hash, InfoLogLength);
	}
	glGetProgramiv(Program, GL_LINK_STATUS, &Status);
	if (!Status) throw ShaderCompilationException(InfoLogLinkage);
}


GLShaderProgram::GLShaderProgram(const GLchar *ComputeShaderCode, const uvec3 &NumWorkGroups) :
	GLShaderProgram(ComputeShaderCode)
{
	SetComputeNumWorkGroups(NumWorkGroups);
}

GLShaderProgram::~GLShaderProgram()
{
	delete ComputeNumWorkGroups;
	glDeleteProgram(Program);
}

void GLShaderProgram::Use() const
{
	glUseProgram(Program);
	GLUniformLocation::UsingProgram = Program;
	GLVertexAttribLocation::UsingProgram = Program;
}

void GLShaderProgram::Unuse() const
{
	glUseProgram(0);
	GLUniformLocation::UsingProgram = 0;
	GLVertexAttribLocation::UsingProgram = 0;
}

#if _DEBUG
#define CHECKSHADERTYPE 1
#define CHECKDIMENSIONS 1
#else
#define CHECKSHADERTYPE 0
#define CHECKDIMENSIONS 0
#endif

#if CHECKSHADERTYPE
#define CheckIsCompute() assert(ComputeNumWorkGroups.get() != nullptr)
#define CheckIsNotCompute() assert(ComputeNumWorkGroups.get() == nullptr)
#else
#define CheckIsCompute()
#define CheckIsNotCompute()
#endif

void GLShaderProgram::SetComputeNumWorkGroups(const uvec3 &NumWorkGroups)
{
	CheckIsCompute();
	ComputeNumWorkGroups->Bind();
	ComputeNumWorkGroups->SetData(&NumWorkGroups);
	ComputeNumWorkGroups->Unbind();
}

uvec3 GLShaderProgram::GetComputeNumWorkGroups() const
{
	CheckIsCompute();
	uvec3 ret;
	ComputeNumWorkGroups->Bind();
	ComputeNumWorkGroups->GetData(&ret);
	ComputeNumWorkGroups->Unbind();
	return ret;
}

void GLShaderProgram::RunComputeShader() const
{
	CheckIsCompute();
	Use();
	ComputeNumWorkGroups->Bind();
	glDispatchComputeIndirect(ComputeNumWorkGroups->GetObject());
	ComputeNumWorkGroups->Unbind();
}

void GLShaderProgram::RunComputeShader(const uvec3 &NumWorkGroups) const
{
	CheckIsCompute();
	Use();
	glDispatchCompute(NumWorkGroups.x, NumWorkGroups.y, NumWorkGroups.z);
}

void GLShaderProgram::WaitForCompute() const
{
	CheckIsCompute();
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

std::vector<ActiveUniform> GLShaderProgram::GetActiveUniforms() const
{
	GLint Count, i;
	std::vector<ActiveUniform> Ret;

	glGetProgramiv(Program, GL_ACTIVE_UNIFORMS, &Count);
	Ret.reserve(static_cast<size_t>(Count));
	for (i = 0; i < Count; i++)
	{
		char Buf[512];
		GLsizei Length;
		GLint Size;
		GLenum Type;
		glGetActiveUniform(Program, static_cast<GLuint>(i), sizeof Buf, &Length, &Size, &Type, Buf);
		Ret.push_back(ActiveUniform(Buf, static_cast<UniformTypeEnum>(Type), Size));
	}
	Ret.shrink_to_fit();
	return Ret;
}

std::vector<ActiveAttrib> GLShaderProgram::GetActiveAttribs() const
{
	GLint Count, i;
	std::vector<ActiveAttrib> Ret;

	glGetProgramiv(Program, GL_ACTIVE_ATTRIBUTES, &Count);
	Ret.reserve(static_cast<size_t>(Count));
	for (i = 0; i < Count; i++)
	{
		char Buf[512];
		GLsizei Length;
		GLint Size;
		GLenum Type;
		glGetActiveAttrib(Program, static_cast<GLuint>(i), sizeof Buf, &Length, &Size, &Type, Buf);
		Ret.push_back(ActiveAttrib(Buf, static_cast<AttribTypeEnum>(Type), Size));
	}
	Ret.shrink_to_fit();
	return Ret;
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
#if CHECKDIMENSIONS
	default: throw std::invalid_argument("`dimension` must be 1 or 2 or 3 or 4.");
#endif
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
#if CHECKDIMENSIONS
	default: throw std::invalid_argument("`dimension` must be 1 or 2 or 3 or 4.");
#endif
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
#if CHECKDIMENSIONS
	default: throw std::invalid_argument("`dimension` must be 1 or 2 or 3 or 4.");
#endif
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
#if CHECKDIMENSIONS
	default: throw std::invalid_argument("`dimension` must be 1 or 2 or 3 or 4.");
#endif
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
#if CHECKDIMENSIONS
	default: throw std::invalid_argument("`dimension` must be 1 or 2 or 3 or 4.");
#endif
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
#if CHECKDIMENSIONS
	default: throw std::invalid_argument("`dimension` must be 1 or 2 or 3 or 4.");
#endif
	}
}

void GLShaderProgram::SetUniform(GLUniformLocation location, const mat2 v[], int count, bool transpose) { glUniformMatrix2fv(location, count, transpose, &v[0][0].x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, const mat3 v[], int count, bool transpose) { glUniformMatrix3fv(location, count, transpose, &v[0][0].x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, const mat4 v[], int count, bool transpose) { glUniformMatrix4fv(location, count, transpose, &v[0][0].x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, const mat2x3 v[], int count, bool transpose) { glUniformMatrix2x3fv(location, count, transpose, &v[0][0].x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, const mat2x4 v[], int count, bool transpose) { glUniformMatrix2x4fv(location, count, transpose, &v[0][0].x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, const mat3x2 v[], int count, bool transpose) { glUniformMatrix3x2fv(location, count, transpose, &v[0][0].x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, const mat3x4 v[], int count, bool transpose) { glUniformMatrix3x4fv(location, count, transpose, &v[0][0].x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, const mat4x2 v[], int count, bool transpose) { glUniformMatrix4x2fv(location, count, transpose, &v[0][0].x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, const mat4x3 v[], int count, bool transpose) { glUniformMatrix4x3fv(location, count, transpose, &v[0][0].x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, const dmat2 v[], int count, bool transpose) { glUniformMatrix2dv(location, count, transpose, &v[0][0].x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, const dmat3 v[], int count, bool transpose) { glUniformMatrix3dv(location, count, transpose, &v[0][0].x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, const dmat4 v[], int count, bool transpose) { glUniformMatrix4dv(location, count, transpose, &v[0][0].x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, const dmat2x3 v[], int count, bool transpose) { glUniformMatrix2x3dv(location, count, transpose, &v[0][0].x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, const dmat2x4 v[], int count, bool transpose) { glUniformMatrix2x4dv(location, count, transpose, &v[0][0].x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, const dmat3x2 v[], int count, bool transpose) { glUniformMatrix3x2dv(location, count, transpose, &v[0][0].x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, const dmat3x4 v[], int count, bool transpose) { glUniformMatrix3x4dv(location, count, transpose, &v[0][0].x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, const dmat4x2 v[], int count, bool transpose) { glUniformMatrix4x2dv(location, count, transpose, &v[0][0].x); }
void GLShaderProgram::SetUniform(GLUniformLocation location, const dmat4x3 v[], int count, bool transpose) { glUniformMatrix4x3dv(location, count, transpose, &v[0][0].x); }

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

void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLbyte *xyzw, bool Normalized) { if (Normalized) glVertexAttrib4Nbv(location, xyzw); else  glVertexAttrib4bv(location, xyzw); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLubyte *xyzw, bool Normalized) { if (Normalized) glVertexAttrib4Nubv(location, xyzw); else  glVertexAttrib4ubv(location, xyzw); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLint *xyzw, bool Normalized) { if (Normalized) glVertexAttrib4Niv(location, xyzw); else  glVertexAttrib4iv(location, xyzw); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLuint *xyzw, bool Normalized) { if (Normalized) glVertexAttrib4Nuiv(location, xyzw); else  glVertexAttrib4uiv(location, xyzw); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLshort *xyzw, bool Normalized) { if (Normalized) glVertexAttrib4Nsv(location, xyzw); else  glVertexAttrib4sv(location, xyzw); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLushort *xyzw, bool Normalized) { if (Normalized) glVertexAttrib4Nusv(location, xyzw); else  glVertexAttrib4usv(location, xyzw); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLbyte x, GLbyte y, GLbyte z, GLbyte w, bool Normalized) { GLbyte xyzw[4] = {x, y, z, w}; SetVertexAttribFloat(location, xyzw, Normalized); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLubyte x, GLubyte y, GLubyte z, GLubyte w, bool Normalized) { if (Normalized) glVertexAttrib4Nub(location, x, y, z, w); else { GLubyte xyzw[] = {x, y, z, w}; glVertexAttrib4ubv(location, xyzw); } }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLint x, GLint y, GLint z, GLint w, bool Normalized) { GLint xyzw[4] = {x, y, z, w}; SetVertexAttribFloat(location, xyzw, Normalized); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLuint x, GLuint y, GLuint z, GLuint w, bool Normalized) { GLuint xyzw[4] = {x, y, z, w}; SetVertexAttribFloat(location, xyzw, Normalized); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLshort x, GLshort y, GLshort z, GLshort w, bool Normalized) { GLshort xyzw[4] = {x, y, z, w}; SetVertexAttribFloat(location, xyzw, Normalized); }
void GLShaderProgram::SetVertexAttribFloat(GLVertexAttribLocation location, GLushort x, GLushort y, GLushort z, GLushort w, bool Normalized) { GLushort xyzw[4] = {x, y, z, w}; SetVertexAttribFloat(location, xyzw, Normalized); }

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


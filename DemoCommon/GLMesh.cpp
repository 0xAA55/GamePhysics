#include "GLMesh.hpp"
#include<GL/glew.h>
using namespace GLRenderer;

GLVAO::GLVAO() : VAO(0), Described(false)
{
	glGenVertexArrays(1, &VAO);
}

GLVAO::~GLVAO()
{
	glDeleteVertexArrays(1, &VAO);
}

GLVAO::operator GLuint() const
{
	return VAO;
}

void GLVAO::Bind() const
{
	glBindVertexArray(VAO);
}

bool GLVAO::IsDescribed() const
{
	return Described;
}

void GLVAO::SetDescribed()
{
	Described = true;
}

void GLVAO::Draw(MeshPrimitiveType PrimitiveType, GLsizei CommandCount) const
{
	GLenum PT = static_cast<GLenum>(PrimitiveType);
	glMultiDrawArraysIndirect(PT, nullptr, CommandCount, 0);
}

void GLVAO::Draw(MeshPrimitiveType PrimitiveType, GLsizei VertexCount, GLsizei InstanceCount) const
{
	GLenum PT = static_cast<GLenum>(PrimitiveType);
	if (InstanceCount <= 1) glDrawArrays(PT, 0, VertexCount);
	else glDrawArraysInstanced(PT, 0, InstanceCount, VertexCount);
}

void GLVAO::DrawByElements(MeshPrimitiveType PrimitiveType, MeshElementType ElementType, GLsizei CommandCount) const
{
	GLenum PT = static_cast<GLenum>(PrimitiveType);
	GLenum ET = static_cast<GLenum>(ElementType);
	glMultiDrawElementsIndirect(PT, ET, nullptr, CommandCount, 0);
}

void GLVAO::DrawByElements(MeshPrimitiveType PrimitiveType, MeshElementType ElementType, GLsizei ElementCount, GLsizei InstanceCount) const
{
	GLenum PT = static_cast<GLenum>(PrimitiveType);
	GLenum ET = static_cast<GLenum>(ElementType);
	if (InstanceCount == 0) glDrawElements(PT, ElementCount, ET, nullptr);
	else glDrawElementsInstanced(PT, ElementCount, ET, nullptr, InstanceCount);
}

AttribDesc::AttribDesc(std::string Name, AttribType Type, GLsizei Offset, bool AsFloat, bool Normalize) :
	Name(Name),
	Type(Type),
	UnitType(GLGetUnitType(Type)),
	Offset(Offset),
	ColCount(GLGetNumCols(Type)),
	RowCount(GLGetNumRows(Type)),
	AsFloat(AsFloat),
	Normalize(Normalize)
{
	Length = GLGetUnitLength(Type) * ColCount * RowCount;
	if (!AsFloat)
	{
		AsFloat = (!GLIsInteger(Type) && !GLIsDouble(Type));
	}
}

AttribDesc::AttribDesc(std::string Name, std::string Type, GLsizei Offset, bool AsFloat, bool Normalize) :
	AttribDesc(Name, GLStringToAttribType(Type), Offset, AsFloat, Normalize)
{
}

void AttribDesc::Describe(const GLShaderProgram &Shader, GLsizei Stride, GLuint AVD) const
{
	GLint Location = GLVertexAttribLocation(Name);
	if (Location < 0) return;
	GLsizei CurOffset = Offset;
	GLsizei RowSize = GLGetUnitLength(UnitType) * ColCount;
	for (GLint i = 0; i < RowCount; i++)
	{
		const void *PtrParam = reinterpret_cast<const void *>(static_cast<size_t>(CurOffset));
		GLenum GLType = static_cast<GLenum>(UnitType);
		glEnableVertexAttribArray(Location);
		if (AsFloat) glVertexAttribPointer(Location, ColCount, GLType, Normalize, Stride, PtrParam);
		else if (GLIsInteger(Type)) glVertexAttribIPointer(Location, ColCount, GLType, Stride, PtrParam);
		else if (GLIsDouble(Type)) glVertexAttribLPointer(Location, ColCount, GLType, Stride, PtrParam);
		else throw std::invalid_argument("AttribDesc::Describe(): Don't know how to describe vertex structure.");
		glVertexAttribDivisor(Location, AVD);
		Location++;
		CurOffset += RowSize;
	}
}




#include "GLMesh.hpp"
#include <GL/glew.h>
using namespace GLRenderer;

GLVAO::GLVAO() : VAO(0), Described(false)
{
	glGenVertexArrays(1, &VAO);
}

GLVAO::~GLVAO()
{
	glDeleteVertexArrays(1, &VAO);
}

void GLVAO::Bind() const
{
	glBindVertexArray(VAO);
}

void GLVAO::Draw(MeshPrimitiveType PrimitiveType, GLsizei CommandCount) const
{
	GLenum PT = static_cast<GLenum>(PrimitiveType);
	glMultiDrawArraysIndirect(PT, nullptr, CommandCount, 0);
}

void GLVAO::Draw(MeshPrimitiveType PrimitiveType, GLsizei VertexCount, GLsizei InstanceCount) const
{
	GLenum PT = static_cast<GLenum>(PrimitiveType);
	if (!InstanceCount) glDrawArrays(PT, 0, VertexCount);
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
	if (!InstanceCount) glDrawElements(PT, ElementCount, ET, nullptr);
	else glDrawElementsInstanced(PT, ElementCount, ET, nullptr, InstanceCount);
}

AttribDesc::AttribDesc(std::string Name, AttribTypeEnum Type, GLsizei Offset, GLsizei Stride, bool AsFloat, bool Normalize) :
	Name(Name),
	Type(Type),
	VarType(GetVarType(Type)),
	Offset(Offset),
	Stride(Stride),
	ColCount(GetNumCols(Type)),
	RowCount(GetNumRows(Type)),
	AsFloat(AsFloat),
	Normalize(Normalize)
{
	Length = GetUnitLength(Type) * ColCount * RowCount;
	if (!AsFloat) { AsFloat = (!IsInteger(Type) && !IsDouble(Type)); }
}

AttribDesc::AttribDesc(std::string Name, std::string Type, GLsizei Offset, GLsizei Stride, bool AsFloat, bool Normalize) :
	AttribDesc(Name, StringToAttribType(Type), Offset, Stride, AsFloat, Normalize)
{
}

void AttribDesc::Describe(const GLShaderProgram& Shader, GLuint AVD) const
{
	GLint Location = GLVertexAttribLocation(Name);
	if (Location < 0) return;
	GLsizei CurOffset = Offset;
	GLsizei RowSize = GetUnitLength(VarType) * ColCount;
	for (GLint i = 0; i < RowCount; i++)
	{
		const void* PtrParam = reinterpret_cast<const void*>(static_cast<size_t>(CurOffset));
		GLenum GLType = static_cast<GLenum>(VarType);
		glEnableVertexAttribArray(Location);
		if (AsFloat) glVertexAttribPointer(Location, ColCount, GLType, Normalize, Stride, PtrParam);
		else if (IsInteger(Type)) glVertexAttribIPointer(Location, ColCount, GLType, Stride, PtrParam);
		else if (IsDouble(Type)) glVertexAttribLPointer(Location, ColCount, GLType, Stride, PtrParam);
		else throw std::invalid_argument("AttribDesc::Describe(): Don't know how to describe vertex structure.");
		glVertexAttribDivisor(Location, AVD);
		Location++;
		CurOffset += RowSize;
	}
}

GLMesh::GLMesh(MeshPrimitiveType PrimitiveType):
	PrimitiveType(PrimitiveType),
	IndexBufferElementType(MeshElementType::UnsignedInt)
{
}

GLMesh::GLMesh(const GLMesh& Mesh) :
	PrimitiveType(Mesh.PrimitiveType),
	IndexBufferElementType(Mesh.IndexBufferElementType),
	VertexBuffer(Mesh.VertexBuffer),
	IndexBuffer(Mesh.IndexBuffer),
	InstanceBuffer(Mesh.InstanceBuffer),
	CommandBuffer(Mesh.CommandBuffer),
	VertexBufferFormat(Mesh.VertexBufferFormat),
	InstanceBufferFormat(Mesh.InstanceBufferFormat)
{
}

GLVAO& GLMesh::Describe(const GLShaderProgram& Shader)
{
	bool ShouldDescribe = VertexBuffer.BufferChanged() || InstanceBuffer.BufferChanged();
	GLVAO& VAO = VAOsForEachShader[Shader];
	if (!VAO.IsDescribed()) ShouldDescribe = true;
	VAO.Bind();
	if (ShouldDescribe)
	{
		VerifyBufferFormat();
		if (VertexBuffer.Size())
		{
			VertexBuffer.BindForDraw();
			for (auto& it : VertexBufferFormat) it.Describe(Shader, 0);
			VertexBuffer.Unbind();
		}
		if (InstanceBuffer.Size())
		{
			InstanceBuffer.BindForDraw();
			for (auto& it : InstanceBufferFormat) it.Describe(Shader, 1);
			InstanceBuffer.Unbind();
		}
		VAO.SetDescribed();
	}
	return VAO;
}

void GLMesh::Draw(const GLShaderProgram& Shader)
{
	Shader.Use();
	auto& VAO = Describe(Shader);
	if (IndexBuffer.Size())
	{
		IndexBuffer.BindForDraw();
		if (CommandBuffer.Size())
		{
			CommandBuffer.BindForDraw();
			VAO.DrawByElements(PrimitiveType, IndexBufferElementType, static_cast<GLsizei>(CommandBuffer.Size()));
			CommandBuffer.Unbind();
		}
		else VAO.DrawByElements(PrimitiveType, IndexBufferElementType, static_cast<GLsizei>(IndexBuffer.Size()), static_cast<GLsizei>(InstanceBuffer.Size()));
		IndexBuffer.Unbind();
	}
	else
	{
		if (CommandBuffer.Size())
		{
			CommandBuffer.BindForDraw();
			VAO.Draw(PrimitiveType, static_cast<GLsizei>(CommandBuffer.Size()));
			CommandBuffer.Unbind();
		}
		else VAO.Draw(PrimitiveType, static_cast<GLsizei>(VertexBuffer.Size()), static_cast<GLsizei>(InstanceBuffer.Size()));
	}
	Shader.Unuse();
}

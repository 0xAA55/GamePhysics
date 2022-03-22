#include "GLTexture.hpp"
#include <GL/glew.h>
#include <cstdlib>
namespace GLRenderer
{
	const GLSampler &GLSampler::DefaultSampler = GLSampler();

	void GLSampler::SetSamplerParamsForTexture(TextureTypeEnum TextureType) const
	{
		GLenum Target = static_cast<GLenum>(TextureType);
		glTexParameteri(Target, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(MinFilter));
		glTexParameteri(Target, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(MagFilter));
		glTexParameteri(Target, GL_TEXTURE_WRAP_S, static_cast<GLint>(WrapS));
		glTexParameteri(Target, GL_TEXTURE_WRAP_T, static_cast<GLint>(WrapT));
		glTexParameteri(Target, GL_TEXTURE_WRAP_R, static_cast<GLint>(WrapR));
		glTexParameterfv(Target, GL_TEXTURE_BORDER_COLOR, &BorderColor.x);
	}

	GLTexture::GLTexture(TextureTypeEnum TextureType, GLsizei Width, GLsizei Height, GLsizei Depth, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr) :
		Object(), Width(Width), Height(Height), Depth(Depth), InternalFormat(InternalFormat), TextureFormat(GLGetTextureFormat(InternalFormat)), Sampler(Sampler), ArtifactType(ArtifactType),
		PBO(BufferType::PixelUnpackBuffer, Depth * Height *CalcBitmapPitch(Width, GLGetTexelSize(GLGetTextureFormat(InternalFormat), ArtifactType) * 8), BufferUsage::StreamRead)
	{
		GLenum Target = static_cast<GLenum>(TextureType);

		glGenTextures(1, &Object);
		glBindTexture(Target, Object);
		Sampler.SetSamplerParamsForTexture(TextureType);

		PBO.Bind();
		switch (TextureType)
		{
		case TextureTypeEnum::Texture1D:
		case TextureTypeEnum::Texture2D:
		case TextureTypeEnum::Texture3D:
		}
		PBO.Unbind();
	}

	GLTexture::GLTexture(TextureTypeEnum TextureType, GLsizei Width, GLsizei Height, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr) :
		GLTexture(TextureType, Width, Height, 1, InternalFormat, Sampler, ArtifactType, TextureData)
	{
	}

	GLTexture::GLTexture(TextureTypeEnum TextureType, GLsizei Width, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr) :
		GLTexture(TextureType, Width, 1, 1, InternalFormat, Sampler, ArtifactType, TextureData)
	{
	}
};

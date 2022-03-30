#include "GLTexture.hpp"
#include <GL/glew.h>
#include <cstdlib>
#include <cassert>
namespace GLRenderer
{
    TextureInternalFormatEnum GetBaseInternalFormat(TextureInternalFormatEnum Format)
    {
        switch (Format)
        {
        case TextureInternalFormatEnum::R:
        case TextureInternalFormatEnum::R8:
        case TextureInternalFormatEnum::R8_SN:
        case TextureInternalFormatEnum::R16:
        case TextureInternalFormatEnum::R16_SN:
        case TextureInternalFormatEnum::R16F:
        case TextureInternalFormatEnum::R32F:
        case TextureInternalFormatEnum::R8I:
        case TextureInternalFormatEnum::R8UI:
        case TextureInternalFormatEnum::R16I:
        case TextureInternalFormatEnum::R16UI:
        case TextureInternalFormatEnum::R32I:
        case TextureInternalFormatEnum::R32UI: return TextureInternalFormatEnum::R;
        case TextureInternalFormatEnum::RG:
        case TextureInternalFormatEnum::RG8:
        case TextureInternalFormatEnum::RG8_SN:
        case TextureInternalFormatEnum::RG16:
        case TextureInternalFormatEnum::RG16_SN:
        case TextureInternalFormatEnum::RG16F:
        case TextureInternalFormatEnum::RG32F:
        case TextureInternalFormatEnum::RG8I:
        case TextureInternalFormatEnum::RG8UI:
        case TextureInternalFormatEnum::RG16I:
        case TextureInternalFormatEnum::RG16UI:
        case TextureInternalFormatEnum::RG32I:
        case TextureInternalFormatEnum::RG32UI: return TextureInternalFormatEnum::RG;
        case TextureInternalFormatEnum::RGB:
        case TextureInternalFormatEnum::R3_G3_B2:
        case TextureInternalFormatEnum::RGB4:
        case TextureInternalFormatEnum::RGB5:
        case TextureInternalFormatEnum::RGB8:
        case TextureInternalFormatEnum::RGB8_SN:
        case TextureInternalFormatEnum::RGB10:
        case TextureInternalFormatEnum::RGB12:
        case TextureInternalFormatEnum::RGB16_SN:
        case TextureInternalFormatEnum::SRGB8:
        case TextureInternalFormatEnum::RGB9_E5:
        case TextureInternalFormatEnum::RGB16F:
        case TextureInternalFormatEnum::RGB32F:
        case TextureInternalFormatEnum::R11F_G11F_B10F:
        case TextureInternalFormatEnum::RGB8I:
        case TextureInternalFormatEnum::RGB8UI:
        case TextureInternalFormatEnum::RGB16I:
        case TextureInternalFormatEnum::RGB16UI:
        case TextureInternalFormatEnum::RGB32I:
        case TextureInternalFormatEnum::RGB32UI: return TextureInternalFormatEnum::RGB;
        case TextureInternalFormatEnum::RGBA:
        case TextureInternalFormatEnum::RGBA2:
        case TextureInternalFormatEnum::RGBA4:
        case TextureInternalFormatEnum::RGB5_A1:
        case TextureInternalFormatEnum::RGBA8:
        case TextureInternalFormatEnum::RGBA8_SN:
        case TextureInternalFormatEnum::RGB10_A2:
        case TextureInternalFormatEnum::RGB10_A2UI:
        case TextureInternalFormatEnum::RGBA12:
        case TextureInternalFormatEnum::RGBA16:
        case TextureInternalFormatEnum::SRGB8_ALPHA8:
        case TextureInternalFormatEnum::RGBA16F:
        case TextureInternalFormatEnum::RGBA32F:
        case TextureInternalFormatEnum::RGBA8I:
        case TextureInternalFormatEnum::RGBA8UI:
        case TextureInternalFormatEnum::RGBA16I:
        case TextureInternalFormatEnum::RGBA16UI:
        case TextureInternalFormatEnum::RGBA32I:
        case TextureInternalFormatEnum::RGBA32UI: return TextureInternalFormatEnum::RGBA;
        case TextureInternalFormatEnum::Depth: return TextureInternalFormatEnum::Depth;
        case TextureInternalFormatEnum::DepthStencil: return TextureInternalFormatEnum::DepthStencil;
        default: throw std::invalid_argument(std::string("Invalid `Format`"));
        }
    }

    TextureFormatEnum GetTextureFormat(TextureInternalFormatEnum Format, bool BGR)
    {
        switch (Format)
        {
        case TextureInternalFormatEnum::R:
        case TextureInternalFormatEnum::R8:
        case TextureInternalFormatEnum::R8_SN:
        case TextureInternalFormatEnum::R16:
        case TextureInternalFormatEnum::R16_SN:
        case TextureInternalFormatEnum::R16F:
        case TextureInternalFormatEnum::R32F: return TextureFormatEnum::R;
        case TextureInternalFormatEnum::R8I:
        case TextureInternalFormatEnum::R8UI:
        case TextureInternalFormatEnum::R16I:
        case TextureInternalFormatEnum::R16UI:
        case TextureInternalFormatEnum::R32I:
        case TextureInternalFormatEnum::R32UI: return TextureFormatEnum::RI;
        case TextureInternalFormatEnum::RG:
        case TextureInternalFormatEnum::RG8:
        case TextureInternalFormatEnum::RG8_SN:
        case TextureInternalFormatEnum::RG16:
        case TextureInternalFormatEnum::RG16_SN:
        case TextureInternalFormatEnum::RG16F:
        case TextureInternalFormatEnum::RG32F: return TextureFormatEnum::RG;
        case TextureInternalFormatEnum::RG8I:
        case TextureInternalFormatEnum::RG8UI:
        case TextureInternalFormatEnum::RG16I:
        case TextureInternalFormatEnum::RG16UI:
        case TextureInternalFormatEnum::RG32I:
        case TextureInternalFormatEnum::RG32UI: return TextureFormatEnum::RGI;
        case TextureInternalFormatEnum::RGB:
        case TextureInternalFormatEnum::R3_G3_B2:
        case TextureInternalFormatEnum::RGB4:
        case TextureInternalFormatEnum::RGB5:
        case TextureInternalFormatEnum::RGB8:
        case TextureInternalFormatEnum::RGB8_SN:
        case TextureInternalFormatEnum::RGB10:
        case TextureInternalFormatEnum::RGB12:
        case TextureInternalFormatEnum::RGB16_SN:
        case TextureInternalFormatEnum::SRGB8:
        case TextureInternalFormatEnum::RGB9_E5:
        case TextureInternalFormatEnum::RGB16F:
        case TextureInternalFormatEnum::RGB32F:
        case TextureInternalFormatEnum::R11F_G11F_B10F: return BGR ? TextureFormatEnum::BGR : TextureFormatEnum::RGB;
        case TextureInternalFormatEnum::RGB8I:
        case TextureInternalFormatEnum::RGB8UI:
        case TextureInternalFormatEnum::RGB16I:
        case TextureInternalFormatEnum::RGB16UI:
        case TextureInternalFormatEnum::RGB32I:
        case TextureInternalFormatEnum::RGB32UI: return BGR ? TextureFormatEnum::BGRI : TextureFormatEnum::RGBI;
        case TextureInternalFormatEnum::RGBA:
        case TextureInternalFormatEnum::RGBA2:
        case TextureInternalFormatEnum::RGBA4:
        case TextureInternalFormatEnum::RGB5_A1:
        case TextureInternalFormatEnum::RGBA8:
        case TextureInternalFormatEnum::RGBA8_SN:
        case TextureInternalFormatEnum::RGB10_A2:
        case TextureInternalFormatEnum::RGB10_A2UI:
        case TextureInternalFormatEnum::RGBA12:
        case TextureInternalFormatEnum::RGBA16:
        case TextureInternalFormatEnum::SRGB8_ALPHA8:
        case TextureInternalFormatEnum::RGBA16F:
        case TextureInternalFormatEnum::RGBA32F: return BGR ? TextureFormatEnum::BGRA : TextureFormatEnum::RGBA;
        case TextureInternalFormatEnum::RGBA8I:
        case TextureInternalFormatEnum::RGBA8UI:
        case TextureInternalFormatEnum::RGBA16I:
        case TextureInternalFormatEnum::RGBA16UI:
        case TextureInternalFormatEnum::RGBA32I:
        case TextureInternalFormatEnum::RGBA32UI: return BGR ? TextureFormatEnum::BGRAI : TextureFormatEnum::RGBAI;
        case TextureInternalFormatEnum::Depth: return TextureFormatEnum::Depth;
        case TextureInternalFormatEnum::DepthStencil: return TextureFormatEnum::DepthStencil;
        default: throw std::invalid_argument(std::string("Invalid `Format`"));
        }
    }

    GLsizei GetChannelCount(TextureFormatEnum Format)
    {
        switch (Format)
        {
        case TextureFormatEnum::R: return 1;
        case TextureFormatEnum::RG: return 2;
        case TextureFormatEnum::RGB:
        case TextureFormatEnum::BGR: return 3;
        case TextureFormatEnum::RGBA:
        case TextureFormatEnum::BGRA: return 4;
        case TextureFormatEnum::RI: return 1;
        case TextureFormatEnum::RGI: return 2;
        case TextureFormatEnum::RGBI:
        case TextureFormatEnum::BGRI: return 3;
        case TextureFormatEnum::RGBAI:
        case TextureFormatEnum::BGRAI: return 4;
        case TextureFormatEnum::StencilIndex:
        case TextureFormatEnum::Depth: return 1;
        case TextureFormatEnum::DepthStencil: return 2;
        default: throw std::invalid_argument(std::string("Invalid `Format`"));
        }
    }

    GLsizei GetTexelSize(TextureFormatEnum Format, TextureDataTypeEnum DataType)
    {
        switch (DataType)
        {
        case TextureDataTypeEnum::Byte:
        case TextureDataTypeEnum::UnsignedByte: return 1 * GetChannelCount(Format);
        case TextureDataTypeEnum::Short:
        case TextureDataTypeEnum::UnsignedShort: return 2 * GetChannelCount(Format);
        case TextureDataTypeEnum::Int:
        case TextureDataTypeEnum::UnsignedInt: return 4 * GetChannelCount(Format);
        case TextureDataTypeEnum::HalfFloat: return 2 * GetChannelCount(Format);
        case TextureDataTypeEnum::Float: return 4 * GetChannelCount(Format);
        case TextureDataTypeEnum::UnsignedByte_3_3_2: return 1;
        case TextureDataTypeEnum::UnsignedShort_5_6_5: return 2;
        case TextureDataTypeEnum::UnsignedShort_4_4_4_4: return 2;
        case TextureDataTypeEnum::UnsignedShort_5_5_5_1: return 2;
        case TextureDataTypeEnum::UnsignedInt_8_8_8_8: return 4;
        case TextureDataTypeEnum::UnsignedInt_10_10_10_2: return 4;
        case TextureDataTypeEnum::UnsignedByte_2_3_3_Rev: return 1;
        case TextureDataTypeEnum::UnsignedShort_5_6_5_Rev: return 2;
        case TextureDataTypeEnum::UnsignedShort_4_4_4_4_Rev: return 2;
        case TextureDataTypeEnum::UnsignedShort_1_5_5_5_Rev: return 2;
        case TextureDataTypeEnum::UnsignedInt_8_8_8_8_Rev: return 4;
        case TextureDataTypeEnum::UnsignedInt_2_10_10_10_Rev: return 4;
        default: throw std::invalid_argument(std::string("Invalid `DataType`"));
        }
    }

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

	GLTexture::GLTexture(TextureTypeEnum TextureType, GLsizei Width, GLsizei Height, GLsizei Depth, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler, const TextureDataTypeEnum ArtifactType, const void *TextureData) :
		Object(), Width(Width), Height(Height), Depth(Depth), InternalFormat(InternalFormat), TextureFormat(GetTextureFormat(InternalFormat)), Sampler(Sampler), ArtifactType(ArtifactType),
		PBO(BufferType::PixelUnpackBuffer, Depth * Height * CalcBitmapPitch(Width, GetTexelSize(GetTextureFormat(InternalFormat), ArtifactType) * 8), BufferUsage::StreamRead)
	{
		GLenum Target = static_cast<GLenum>(TextureType);
		GLint TexIF = static_cast<GLint>(InternalFormat);
		GLenum TexF = static_cast<GLenum>(TextureFormat);
		GLenum TexT = static_cast<GLenum>(ArtifactType);

		glGenTextures(1, &Object);
		glBindTexture(Target, Object);
		Sampler.SetSamplerParamsForTexture(TextureType);

		PBO.Bind();
		if (TextureData) std::memcpy(PBO.MapWO(), TextureData, PBO.GetLength());
		else std::memset(PBO.MapWO(), 0, PBO.GetLength());
		PBO.Unmap();
		switch (TextureType)
		{
		case TextureTypeEnum::Texture1D:
			glTexImage1D(Target, 0, TexIF, Width, 0, TexF, TexT, nullptr);
			break;
		case TextureTypeEnum::Texture2D:
			glTexImage2D(Target, 0, TexIF, Width, Height, 0, TexF, TexT, nullptr);
			break;
		case TextureTypeEnum::Texture3D:
			glTexImage3D(Target, 0, TexIF, Width, Height, Depth, 0, TexF, TexT, nullptr);
			break;
		case TextureTypeEnum::TextureRect:
			glTexImage2D(Target, 0, TexIF, Width, Height, 0, TexF, TexT, nullptr);
			break;
		case TextureTypeEnum::TextureBuffer:
			glTexImage1D(Target, 0, TexIF, Width, 0, TexF, TexT, nullptr);
			break;
		case TextureTypeEnum::TextureCubeMap:

		case TextureTypeEnum::Texture1DArray:

		case TextureTypeEnum::Texture2DArray:

		case TextureTypeEnum::TextureCubeMapArray:

		case TextureTypeEnum::Texture2DMultisample:

		case TextureTypeEnum::Texture2DMultisampleArray:

		}
		PBO.Unbind();
	}

	GLTexture::GLTexture(GLsizei Width, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr) :
		GLTexture(TextureTypeEnum::Texture1D, Width, 1, 1, InternalFormat, Sampler, ArtifactType, TextureData)
	{
	}

	GLTexture::GLTexture(GLsizei Width, GLsizei Height, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr) :
		GLTexture(TextureTypeEnum::Texture2D, Width, Height, 1, InternalFormat, Sampler, ArtifactType, TextureData)
	{
	}

	GLTexture::GLTexture(GLsizei Width, GLsizei Height, GLsizei Depth, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr) :
		GLTexture(TextureTypeEnum::Texture3D, Width, Height, Depth, InternalFormat, Sampler, ArtifactType, TextureData)
	{
	}
};

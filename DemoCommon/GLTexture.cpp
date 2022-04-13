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

    bool IsCube(TextureTypeEnum TextureType)
    {
        return TextureType == TextureTypeEnum::TextureCubeMap || TextureType == TextureTypeEnum::TextureCubeMapArray;
    }

    GLTexture::GLTexture(TextureTypeEnum TextureType, GLsizei Width, GLsizei Height, GLsizei Depth, GLsizei LayerCount, GLsizei BufferSize, GLsizei SampleCount, GLboolean FixedSampleLocations, const TextureFormatEnum TextureFormat, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler, const TextureDataTypeEnum ArtifactType, const void *TextureData) :
        TextureType(TextureType), Object(), Width(Width), Height(Height), Depth(Depth), LayerCount(LayerCount), BufferSize(BufferSize), SampleCount(SampleCount), FixedSampleLocations(FixedSampleLocations), InternalFormat(InternalFormat), TextureFormat(TextureFormat), Sampler(Sampler), ArtifactType(ArtifactType)
    {

        PBO = std::shared_ptr<GLBufferObject>(new GLBufferObject(BufferType::PixelUnpackBuffer, BufferSize, BufferUsage::StreamRead));
        PBO->Bind();
        if (TextureData) std::memcpy(PBO->MapWO(), TextureData, PBO->GetLength());
        else std::memset(PBO->MapWO(), 0, PBO->GetLength());
        PBO->Unmap();
    }

    GLTexture GLTexture::Create1D(GLsizei Size, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler, const TextureDataTypeEnum ArtifactType, const void *TextureData)
    {
        auto TextureFormat = GetTextureFormat(InternalFormat);
        GLsizei LineSize = CalcBitmapPitch(Size, GetTexelSize(TextureFormat, ArtifactType) * 8);
        GLTexture Ret = GLTexture(TextureTypeEnum::Texture1D, Size, 1, 1, 1, LineSize, 1, 0, TextureFormat, InternalFormat, Sampler, ArtifactType, TextureData);

        glBindTexture(static_cast<GLenum>(Ret.TextureType), Ret.Object);
        Sampler.SetSamplerParamsForTexture(Ret.TextureType);
        glTexImage1D(static_cast<GLenum>(Ret.TextureType), 0, static_cast<GLint>(InternalFormat), Size, 0, static_cast<GLenum>(TextureFormat), static_cast<GLenum>(ArtifactType), nullptr);
        Ret.PBO->Unbind();
        return Ret;
    }

    GLTexture GLTexture::Create2D(GLsizei Width, GLsizei Height, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler, const TextureDataTypeEnum ArtifactType, const void *TextureData)
    {
        auto TextureFormat = GetTextureFormat(InternalFormat);
        GLsizei LineSize = CalcBitmapPitch(Width, GetTexelSize(TextureFormat, ArtifactType) * 8);
        GLsizei PlaneSize = LineSize * Height;
        GLTexture Ret = GLTexture(TextureTypeEnum::Texture2D, Width, Height, 1, 1, PlaneSize, 1, 0, TextureFormat, InternalFormat, Sampler, ArtifactType, TextureData);

        glBindTexture(static_cast<GLenum>(Ret.TextureType), Ret.Object);
        Sampler.SetSamplerParamsForTexture(Ret.TextureType);
        glTexImage2D(static_cast<GLenum>(Ret.TextureType), 0, static_cast<GLint>(InternalFormat), Width, Height, 0, static_cast<GLenum>(TextureFormat), static_cast<GLenum>(ArtifactType), nullptr);
        Ret.PBO->Unbind();
        return Ret;
    }

    GLTexture GLTexture::Create3D(GLsizei Width, GLsizei Height, GLsizei Depth, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler, const TextureDataTypeEnum ArtifactType, const void *TextureData)
    {
        auto TextureFormat = GetTextureFormat(InternalFormat);
        GLsizei LineSize = CalcBitmapPitch(Width, GetTexelSize(TextureFormat, ArtifactType) * 8);
        GLsizei PlaneSize = LineSize * Height;
        GLsizei VolumeSize = PlaneSize * Depth;
        GLTexture Ret = GLTexture(TextureTypeEnum::Texture3D, Width, Height, Depth, 1, PlaneSize, 1, 0, TextureFormat, InternalFormat, Sampler, ArtifactType, TextureData);

        glBindTexture(static_cast<GLenum>(Ret.TextureType), Ret.Object);
        Sampler.SetSamplerParamsForTexture(Ret.TextureType);
        glTexImage3D(static_cast<GLenum>(Ret.TextureType), 0, static_cast<GLint>(InternalFormat), Width, Height, Depth, 0, static_cast<GLenum>(TextureFormat), static_cast<GLenum>(ArtifactType), nullptr);
        Ret.PBO->Unbind();
        return Ret;
    }

    GLTexture GLTexture::CreateBuffer(GLsizei Size, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler, const TextureDataTypeEnum ArtifactType, const void *TextureData)
    {
        auto TextureFormat = GetTextureFormat(InternalFormat);
        GLsizei LineSize = CalcBitmapPitch(Size, GetTexelSize(TextureFormat, ArtifactType) * 8);
        GLTexture Ret = GLTexture(TextureTypeEnum::TextureBuffer, Size, 1, 1, 1, LineSize, 1, 0, TextureFormat, InternalFormat, Sampler, ArtifactType, TextureData);

        glBindTexture(static_cast<GLenum>(Ret.TextureType), Ret.Object);
        Sampler.SetSamplerParamsForTexture(Ret.TextureType);
        glTexImage1D(static_cast<GLenum>(Ret.TextureType), 0, static_cast<GLint>(InternalFormat), Size, 0, static_cast<GLenum>(TextureFormat), static_cast<GLenum>(ArtifactType), nullptr);
        Ret.PBO->Unbind();
        return Ret;
    }

    GLTexture GLTexture::CreateRect(GLsizei Width, GLsizei Height, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler, const TextureDataTypeEnum ArtifactType, const void *TextureData)
    {
        auto TextureFormat = GetTextureFormat(InternalFormat);
        GLsizei LineSize = CalcBitmapPitch(Width, GetTexelSize(TextureFormat, ArtifactType) * 8);
        GLsizei PlaneSize = LineSize * Height;
        GLTexture Ret = GLTexture(TextureTypeEnum::TextureRect, Width, Height, 1, 1, PlaneSize, 1, 0, TextureFormat, InternalFormat, Sampler, ArtifactType, TextureData);

        glBindTexture(static_cast<GLenum>(Ret.TextureType), Ret.Object);
        Sampler.SetSamplerParamsForTexture(Ret.TextureType);
        glTexImage2D(static_cast<GLenum>(Ret.TextureType), 0, static_cast<GLint>(InternalFormat), Width, Height, 0, static_cast<GLenum>(TextureFormat), static_cast<GLenum>(ArtifactType), nullptr);
        Ret.PBO->Unbind();
        return Ret;
    }

    GLTexture GLTexture::CreateCubeMap(GLsizei Size, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler, const TextureDataTypeEnum ArtifactType, const void *TextureData)
    {
        auto TextureFormat = GetTextureFormat(InternalFormat);
        GLsizei LineSize = CalcBitmapPitch(Size, GetTexelSize(TextureFormat, ArtifactType) * 8);
        GLsizei PlaneSize = LineSize * Size;
        GLTexture Ret = GLTexture(TextureTypeEnum::TextureCubeMap, Size, Size, 1, 1, PlaneSize * 6, 1, 0, TextureFormat, InternalFormat, Sampler, ArtifactType, TextureData);

        glBindTexture(static_cast<GLenum>(Ret.TextureType), Ret.Object);
        Sampler.SetSamplerParamsForTexture(Ret.TextureType);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, static_cast<GLint>(InternalFormat), Size, Size, 0, static_cast<GLenum>(TextureFormat), static_cast<GLenum>(ArtifactType), reinterpret_cast<const void *>(static_cast<size_t>(PlaneSize) * 0));
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, static_cast<GLint>(InternalFormat), Size, Size, 0, static_cast<GLenum>(TextureFormat), static_cast<GLenum>(ArtifactType), reinterpret_cast<const void *>(static_cast<size_t>(PlaneSize) * 1));
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, static_cast<GLint>(InternalFormat), Size, Size, 0, static_cast<GLenum>(TextureFormat), static_cast<GLenum>(ArtifactType), reinterpret_cast<const void *>(static_cast<size_t>(PlaneSize) * 2));
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, static_cast<GLint>(InternalFormat), Size, Size, 0, static_cast<GLenum>(TextureFormat), static_cast<GLenum>(ArtifactType), reinterpret_cast<const void *>(static_cast<size_t>(PlaneSize) * 3));
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, static_cast<GLint>(InternalFormat), Size, Size, 0, static_cast<GLenum>(TextureFormat), static_cast<GLenum>(ArtifactType), reinterpret_cast<const void *>(static_cast<size_t>(PlaneSize) * 4));
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, static_cast<GLint>(InternalFormat), Size, Size, 0, static_cast<GLenum>(TextureFormat), static_cast<GLenum>(ArtifactType), reinterpret_cast<const void *>(static_cast<size_t>(PlaneSize) * 5));
        Ret.PBO->Unbind();
        return Ret;
    }

    GLTexture GLTexture::Create1DArray(GLsizei Size, GLsizei LayerCount, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler, const TextureDataTypeEnum ArtifactType, const void *TextureData)
    {
        auto TextureFormat = GetTextureFormat(InternalFormat);
        GLsizei LineSize = CalcBitmapPitch(Size, GetTexelSize(TextureFormat, ArtifactType) * 8);
        GLTexture Ret = GLTexture(TextureTypeEnum::Texture1DArray, Size, 1, 1, LayerCount, LineSize * LayerCount, 1, 0, TextureFormat, InternalFormat, Sampler, ArtifactType, TextureData);

        glBindTexture(static_cast<GLenum>(Ret.TextureType), Ret.Object);
        glTexStorage2D(static_cast<GLenum>(Ret.TextureType), 0, static_cast<GLint>(InternalFormat), Size, LayerCount);
        Sampler.SetSamplerParamsForTexture(Ret.TextureType);
        glTexImage2D(static_cast<GLenum>(Ret.TextureType), 0, static_cast<GLint>(InternalFormat), Size, LayerCount, 0, static_cast<GLenum>(TextureFormat), static_cast<GLenum>(ArtifactType), nullptr);
        Ret.PBO->Unbind();
        return Ret;
    }

    GLTexture GLTexture::Create2DArray(GLsizei Width, GLsizei Height, GLsizei LayerCount, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler, const TextureDataTypeEnum ArtifactType, const void *TextureData)
    {
        auto TextureFormat = GetTextureFormat(InternalFormat);
        GLsizei LineSize = CalcBitmapPitch(Width, GetTexelSize(TextureFormat, ArtifactType) * 8);
        GLsizei PlaneSize = LineSize * Height;
        GLTexture Ret = GLTexture(TextureTypeEnum::Texture2DArray, Width, Height, 1, LayerCount, LineSize * LayerCount, 1, 0, TextureFormat, InternalFormat, Sampler, ArtifactType, TextureData);

        glBindTexture(static_cast<GLenum>(Ret.TextureType), Ret.Object);
        glTexStorage3D(static_cast<GLenum>(Ret.TextureType), 0, static_cast<GLint>(InternalFormat), Width, Height, LayerCount);
        Sampler.SetSamplerParamsForTexture(Ret.TextureType);
        glTexImage3D(static_cast<GLenum>(Ret.TextureType), 0, static_cast<GLint>(InternalFormat), Width, Height, LayerCount, 0, static_cast<GLenum>(TextureFormat), static_cast<GLenum>(ArtifactType), nullptr);
        Ret.PBO->Unbind();
        return Ret;
    }

    GLTexture GLTexture::Create2DMS(GLsizei Width, GLsizei Height, GLsizei SampleCount, GLboolean FixedSampleLocations, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler, const TextureDataTypeEnum ArtifactType, const void *TextureData)
    {
        auto TextureFormat = GetTextureFormat(InternalFormat);
        GLsizei LineSize = CalcBitmapPitch(Width, GetTexelSize(TextureFormat, ArtifactType) * 8);
        GLsizei PlaneSize = LineSize * Height;
        GLTexture Ret = GLTexture(TextureTypeEnum::Texture2DMultisample, Width, Height, 1, 1, PlaneSize, SampleCount, FixedSampleLocations, TextureFormat, InternalFormat, Sampler, ArtifactType, TextureData);

        glBindTexture(static_cast<GLenum>(Ret.TextureType), Ret.Object);
        glTexStorage2DMultisample(static_cast<GLenum>(Ret.TextureType), SampleCount, static_cast<GLint>(InternalFormat), Width, Height, FixedSampleLocations);
        Sampler.SetSamplerParamsForTexture(Ret.TextureType);
        glTexImage2D(static_cast<GLenum>(Ret.TextureType), 0, static_cast<GLint>(InternalFormat), Width, Height, 0, static_cast<GLenum>(TextureFormat), static_cast<GLenum>(ArtifactType), nullptr);
        Ret.PBO->Unbind();
        return Ret;
    }

    GLTexture GLTexture::Create2DMSArray(GLsizei Width, GLsizei Height, GLsizei SampleCount, GLboolean FixedSampleLocations, GLsizei LayerCount, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler, const TextureDataTypeEnum ArtifactType, const void *TextureData)
    {
        auto TextureFormat = GetTextureFormat(InternalFormat);
        GLsizei LineSize = CalcBitmapPitch(Width, GetTexelSize(TextureFormat, ArtifactType) * 8);
        GLsizei PlaneSize = LineSize * Height;
        GLTexture Ret = GLTexture(TextureTypeEnum::Texture2DMultisampleArray, Width, Height, 1, LayerCount, LineSize * LayerCount, SampleCount, FixedSampleLocations, TextureFormat, InternalFormat, Sampler, ArtifactType, TextureData);

        glBindTexture(static_cast<GLenum>(Ret.TextureType), Ret.Object);
        glTexStorage3DMultisample(static_cast<GLenum>(Ret.TextureType), SampleCount, static_cast<GLint>(InternalFormat), Width, Height, LayerCount, FixedSampleLocations);
        Sampler.SetSamplerParamsForTexture(Ret.TextureType);
        glTexImage3D(static_cast<GLenum>(Ret.TextureType), 0, static_cast<GLint>(InternalFormat), Width, Height, LayerCount, 0, static_cast<GLenum>(TextureFormat), static_cast<GLenum>(ArtifactType), nullptr);
        Ret.PBO->Unbind();
        return Ret;
    }
};

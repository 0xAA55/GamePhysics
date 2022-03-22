#pragma once
#include<GLRendererBase.hpp>
#include<GLBuffer.hpp>
namespace GLRenderer
{
	enum class MinFilterEnum
	{
		Nearest = 0x2600,
		Linear = 0x2601,
		NearestMipmapNearest = 0x2700, // Find nearest mipmap
		LinearMipmapNearest = 0x2701, // Interpolate between mipmaps
		NearestMipmapLinear = 0x2702, // Find nearest mipmap
		LinearMipmapLinear = 0x2703 // Interpolate between mipmaps
	};

	enum class MagFilterEnum
	{
		Nearest = 0x2600,
		Linear = 0x2601
	};

	enum class WrapMethodEnum
	{
		ClampToEdge = 0x812F,
		ClampToBorder = 0x812D,
		MirroredRepeat = 0x8370,
		Repeat = 0x2901,
		MirrorClampToEdge = 0x8743
	};

	enum class TextureTypeEnum
	{
		Texture1D = 0x0DE0,
		Texture2D = 0x0DE1,
		Texture3D = 0x806F,
		TextureRect = 0x84F5,
		TextureBuffer = 0x8C2A,
		TextureCubeMap = 0x8513,
		TextureRect1DArray = 0x8C18,
		TextureRect2DArray = 0x8C1A,
		TextureCubeMapArray = 0x9009,
		Texture2DMultisample = 0x9100,
		Texture2DMultisampleArray = 0x9102
	};

	class GLSampler
	{
	public:
		MinFilterEnum MinFilter;
		MagFilterEnum MagFilter;
		WrapMethodEnum WrapS;
		WrapMethodEnum WrapT;
		WrapMethodEnum WrapR;
		vec4 BorderColor;
		
		constexpr inline GLSampler(MagFilterEnum MagFilter = MagFilterEnum::Linear,
			MinFilterEnum MinFilter = MinFilterEnum::LinearMipmapLinear,
			WrapMethodEnum WrapS = WrapMethodEnum::Repeat,
			WrapMethodEnum WrapT = WrapMethodEnum::Repeat,
			WrapMethodEnum WrapR = WrapMethodEnum::Repeat,
			vec4 BorderColor = vec4(0, 0, 0, 0)) :
			MagFilter(MagFilter), MinFilter(MinFilter), WrapS(WrapS), WrapT(WrapT), WrapR(WrapR), BorderColor(BorderColor)
		{
		}

		static const GLSampler &DefaultSampler;

		void SetSamplerParamsForTexture(TextureTypeEnum TextureType) const;
	};

	class GLTexture
	{
	protected:
		GLenum Object;
		GLsizei Width;
		GLsizei Height;
		GLsizei Depth;
		TextureFormatEnum TextureFormat;
		TextureInternalFormatEnum InternalFormat;
		GLSampler Sampler;
		TextureDataTypeEnum ArtifactType;
		GLBufferObject PBO;

	public:
		GLTexture() = delete;
		GLTexture(TextureTypeEnum TextureType, GLsizei Width, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr);
		GLTexture(TextureTypeEnum TextureType, GLsizei Width, GLsizei Height, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr);
		GLTexture(TextureTypeEnum TextureType, GLsizei Width, GLsizei Height, GLsizei Depth, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr);

		inline operator GLuint() const { return Object; }
		inline GLsizei GetWidth() const { return Width; }
		inline GLsizei GetHeight() const { return Height; }
		inline GLsizei GetDepth() const { return Depth; }
		inline TextureInternalFormatEnum GetInternalFormat() const { return InternalFormat; }
		inline GLSampler GetSampler() const { return Sampler; }
		inline GLBufferObject &GetPBO() { return PBO; }
	};
}

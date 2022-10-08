#pragma once
#include<GLRendererBase.hpp>
#include<GLBufferObject.hpp>
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
		Texture1DArray = 0x8C18,
		Texture2DArray = 0x8C1A,
		TextureCubeMapArray = 0x9009,
		Texture2DMultisample = 0x9100,
		Texture2DMultisampleArray = 0x9102
	};

	enum class TextureFormatEnum
	{
		R = 0x1903,
		RG = 0x8227,
		RGB = 0x1907,
		BGR = 0x80E0,
		RGBA = 0x1908,
		BGRA = 0x80E1,
		RI = 0x8D94,
		RGI = 0x8228,
		RGBI = 0x8D98,
		BGRI = 0x8D9A,
		RGBAI = 0x8D99,
		BGRAI = 0x8D9B,
		StencilIndex = 0x1901,
		Depth = 0x1902,
		DepthStencil = 0x84F9
	};

	enum class TextureDataTypeEnum
	{
		Byte = 0x1400,
		UnsignedByte = 0x1401,
		Short = 0x1402,
		UnsignedShort = 0x1403,
		Int = 0x1404,
		UnsignedInt = 0x1405,
		HalfFloat = 0x140B,
		Float = 0x1406,
		UnsignedByte_3_3_2 = 0x8032,
		UnsignedShort_5_6_5 = 0x8363,
		UnsignedShort_4_4_4_4 = 0x8033,
		UnsignedShort_5_5_5_1 = 0x8034,
		UnsignedInt_8_8_8_8 = 0x8035,
		UnsignedInt_10_10_10_2 = 0x8036,
		UnsignedByte_2_3_3_Rev = 0x8362,
		UnsignedShort_5_6_5_Rev = 0x8364,
		UnsignedShort_4_4_4_4_Rev = 0x8365,
		UnsignedShort_1_5_5_5_Rev = 0x8366,
		UnsignedInt_8_8_8_8_Rev = 0x8367,
		UnsignedInt_2_10_10_10_Rev = 0x8368
	};

	enum class TextureInternalFormatEnum
	{
		R = 0x1903,
		RG = 0x8227,
		RGB = 0x1907,
		RGBA = 0x1908,
		Depth = 0x1902,
		DepthStencil = 0x84F9,
		R8 = 0x8229,
		R8_SN = 0x8F94,
		R16 = 0x822A,
		R16_SN = 0x8F98,
		RG8 = 0x822B,
		RG8_SN = 0x8F95,
		RG16 = 0x822C,
		RG16_SN = 0x8F99,
		R3_G3_B2 = 0x2A10,
		RGB4 = 0x804F,
		RGB5 = 0x8050,
		RGB8 = 0x8051,
		RGB8_SN = 0x8F96,
		RGB10 = 0x8052,
		RGB12 = 0x8053,
		RGB16_SN = 0x8F9A,
		RGBA2 = 0x8055,
		RGBA4 = 0x8056,
		RGB5_A1 = 0x8057,
		RGBA8 = 0x8058,
		RGBA8_SN = 0x8F97,
		RGB10_A2 = 0x8059,
		RGB10_A2UI = 0x906F,
		RGBA12 = 0x805A,
		RGBA16 = 0x805B,
		SRGB8 = 0x8C41,
		SRGB8_ALPHA8 = 0x8C43,
		R16F = 0x822D,
		RG16F = 0x822F,
		RGB16F = 0x881B,
		RGBA16F = 0x881A,
		R32F = 0x822E,
		RG32F = 0x8230,
		RGB32F = 0x8815,
		RGBA32F = 0x8814,
		R11F_G11F_B10F = 0x8C3A,
		RGB9_E5 = 0x8C3D,
		R8I = 0x8231,
		R8UI = 0x8232,
		R16I = 0x8233,
		R16UI = 0x8234,
		R32I = 0x8235,
		R32UI = 0x8236,
		RG8I = 0x8237,
		RG8UI = 0x8238,
		RG16I = 0x8239,
		RG16UI = 0x823A,
		RG32I = 0x823B,
		RG32UI = 0x823C,
		RGB8I = 0x8D8F,
		RGB8UI = 0x8D7D,
		RGB16I = 0x8D89,
		RGB16UI = 0x8D77,
		RGB32I = 0x8D83,
		RGB32UI = 0x8D71,
		RGBA8I = 0x8D8E,
		RGBA8UI = 0x8D7C,
		RGBA16I = 0x8D88,
		RGBA16UI = 0x8D76,
		RGBA32I = 0x8D82,
		RGBA32UI = 0x8D70,
		Depth16 = 0x81A5,
		Depth24 = 0x81A6,
		Depth32 = 0x81A7
	};

	TextureInternalFormatEnum GetBaseInternalFormat(TextureInternalFormatEnum Format);
	TextureFormatEnum GetTextureFormat(TextureInternalFormatEnum Format, bool BGR = false);
	GLsizei GetChannelCount(TextureFormatEnum Format);
	GLsizei GetTexelSize(TextureFormatEnum Format, TextureDataTypeEnum DataType);

	enum class TextureCubeMapFace
	{
		PositiveX = 0x8515,
		NegativeX = 0x8516,
		PositiveY = 0x8517,
		NegativeY = 0x8518,
		PositiveZ = 0x8519,
		NegativeZ = 0x851A
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
		TextureTypeEnum TextureType;
		GLsizei Width;
		GLsizei Height;
		GLsizei Depth;
		GLsizei LayerCount;
		TextureFormatEnum TextureFormat;
		TextureInternalFormatEnum InternalFormat;
		GLSampler Sampler;
		TextureDataTypeEnum ArtifactType;
		GLsizei BufferSize;
		GLsizei SampleCount;
		GLboolean FixedSampleLocations;
		GLBufferObject* PBO;

		GLTexture(TextureTypeEnum TextureType, GLsizei Width, GLsizei Height, GLsizei Depth, GLsizei LayerCount, GLsizei BufferSize, GLsizei SampleCount, GLboolean FixedSampleLocations, const TextureFormatEnum TextureFormat, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr);

	public:
		GLTexture() = delete;
		~GLTexture();

		static GLTexture Create1D(GLsizei Size, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr);
		static GLTexture Create2D(GLsizei Width, GLsizei Height, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr);
		static GLTexture Create3D(GLsizei Width, GLsizei Height, GLsizei Depth, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr);

		static GLTexture CreateBuffer(GLsizei Size, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr);
		static GLTexture CreateRect(GLsizei Width, GLsizei Height, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr);
		static GLTexture CreateCubeMap(GLsizei Size, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr);

		static GLTexture Create1DArray(GLsizei Size, GLsizei LayerCount, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr);
		static GLTexture Create2DArray(GLsizei Width, GLsizei Height, GLsizei LayerCount, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr);

		static GLTexture Create2DMS(GLsizei Width, GLsizei Height, GLsizei SampleCount, GLboolean FixedSampleLocations, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr);
		static GLTexture Create2DMSArray(GLsizei Width, GLsizei Height, GLsizei SampleCount, GLboolean FixedSampleLocations, GLsizei LayerCount, const TextureInternalFormatEnum InternalFormat, const GLSampler &Sampler = GLSampler::DefaultSampler, const TextureDataTypeEnum ArtifactType = TextureDataTypeEnum::UnsignedByte, const void *TextureData = nullptr);

		inline operator GLuint() const { return Object; }
		inline GLsizei GetWidth() const { return Width; }
		inline GLsizei GetHeight() const { return Height; }
		inline GLsizei GetDepth() const { return Depth; }
		inline TextureInternalFormatEnum GetInternalFormat() const { return InternalFormat; }
		inline GLSampler GetSampler() const { return Sampler; }
		inline GLBufferObject &GetPBO() { return *PBO; }
	};
}

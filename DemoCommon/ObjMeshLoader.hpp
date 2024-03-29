#pragma once
#include<GLRendererBase.hpp>
#include<map>
#include<vector>
namespace GLRenderer
{
	struct ObjVectorData
	{
		float* ptr;
		int len;
		inline ObjVectorData(float *pointer, int length) :
			ptr(pointer),
			len(length)
		{}
		vec2 ToVec2();
		vec3 ToVec3();
		vec4 ToVec4();
	};

	struct ObjVertData
	{
		int Pos;
		int Tex;
		int Normal;
		inline ObjVertData(int v, int vt, int vn) :
			Pos(v),
			Tex(vt),
			Normal(vn)
		{}
	};

	struct ObjFaceData
	{
		ObjVertData* ptr;
		int len;
		inline ObjFaceData(ObjVertData* pointer, int length) :
			ptr(pointer),
			len(length)
		{}
	};

	struct ObjLineData
	{
		uint32_t* ptr;
		int len;
		inline ObjLineData(uint32_t* pointer, int length) :
			ptr(pointer),
			len(length)
		{}
	};

	struct ObjMaterialData
	{
		vec3 Ambient; // Ka
		vec3 Diffuse; // Kd
		vec3 Specular; // Ks
		float SpecularExp; // Ns
		float Alpha; // d, Tr, for transparency
		vec3 TransmissionFilter; // Tf
		float RefractionIndex; // Ni
		std::string AmbientTexture; // map_Ka
		std::string DiffuseTexture; // map_Kd
		std::string SpecularTexture; // map_Ks
		std::string SpecularExpTexture; // map_Ns
		std::string AlphaTexture; // map_d
		std::string TransmissionTexture; // map_Tr
		std::string BumpTexture; // bump, map_bump
		std::string DisplacementTexture; // disp
		std::string DecalTexture; // decal
		std::map<std::string, std::string> RawData;

		ObjMaterialData();
	};

	using ObjFloatDataArray = std::vector<float>;
	using ObjUIntDataArray = std::vector<uint32_t>;
	using ObjFaceDataArray = std::vector<ObjFaceData>;
	using ObjLineDataArray = std::vector<ObjLineData>;
	using ObjVectorDataArray = std::vector<ObjVectorData>;
	using ObjVertDataArray = std::vector<ObjVertData>;

	struct GeneralObjVertexType
	{
		vec3 Position;
		vec3 Normal;
		vec2 TexCoord;
		inline GeneralObjVertexType() :
			Position(vec3(0, 0, 0)),
			Normal(vec3(0, 0, 0)),
			TexCoord(vec2(0, 0))
		{}
		inline GeneralObjVertexType(vec3 P, vec3 N, vec2 T) :
			Position(P),
			Normal(N),
			TexCoord(T)
		{}
	};

	using GeneralObjVertexArrayType = std::vector<GeneralObjVertexType>;

	class ObjMeshSubset
	{
	public:
		std::string GroupName;
		ObjMaterialData Material;
		ObjVectorDataArray VertPos;
		ObjVectorDataArray VertTex;
		ObjVectorDataArray VertNormal;
		ObjFaceDataArray Faces;
		ObjLineDataArray Lines;

		void ConvertToGeneralObjVertices(GeneralObjVertexArrayType& VertOut, ObjUIntDataArray& IndexOut);
	};

	class GeneralObjVertices
	{
	public:
		GeneralObjVertexArrayType Vertices;
		ObjUIntDataArray Indices;

		static void OnMeshSubset(void* cb_userdata, ObjMeshSubset& subset);
	};

	typedef void(*OnMeshSubset)(void* cb_userdata, ObjMeshSubset& subset);
	bool LoadObjFile(const char* path, OnMeshSubset CB, void* cb_userdata);
}

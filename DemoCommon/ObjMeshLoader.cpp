#include "ObjMeshLoader.hpp"
#include<map>
#include<string>
#include<cstdio>
#include<cctype>
#include<cstdlib>

using namespace std;
using namespace GLRenderer;

struct ObjVectorDataIndex
{
	int idx;
	int len;
	ObjVectorDataIndex(int idx, int len) : idx(idx), len(len)
	{}
};

using ObjVectorDataIndexArray = vector<ObjVectorDataIndex>;

vec2 ObjVectorData::ToVec2()
{
	float ret[2] = { 0, 0 };
	for (int i = 0; i < 2 && i < len; i++) ret[i] = ptr[i];
	return vec2(ret[0], ret[1]);
}

vec3 ObjVectorData::ToVec3()
{
	float ret[3] = { 0, 0, 0 };
	for (int i = 0; i < 3 && i < len; i++) ret[i] = ptr[i];
	return vec3(ret[0], ret[1], ret[2]);
}

vec4 ObjVectorData::ToVec4()
{
	float ret[4] = { 0, 0, 0, 0 };
	for (int i = 0; i < 4 && i < len; i++) ret[i] = ptr[i];
	return vec4(ret[0], ret[1], ret[2], ret[3]);
}


ObjMaterialData::ObjMaterialData() :
	Ambient(vec3(0, 0, 0)),
	Diffuse(vec3(0, 0, 0)),
	Specular(vec3(0, 0, 0)),
	SpecularExp(0),
	Alpha(0),
	TransmissionFilter(vec3(0, 0, 0)),
	RefractionIndex(0)
{}

class ObjFileLoader
{
public:
	ObjFloatDataArray VertPosComponents;
	ObjFloatDataArray VertTexComponents;
	ObjFloatDataArray VertNormalComponents;
	map<string, ObjMaterialData> Materials;
	ObjVectorDataIndexArray VertPosIndices;
	ObjVectorDataIndexArray VertTexIndices;
	ObjVectorDataIndexArray VertNormalIndices;

	bool ParsingSubset;
	string SubsetName;
	ObjVertDataArray SubsetFaceVerts;
	ObjUIntDataArray SubsetLineVerts;
	ObjVectorDataIndexArray SubsetFaceIndices;
	ObjVectorDataIndexArray SubsetLineIndices;
	string UsingMaterialName;
	string ParsingMaterialName;
	ObjMaterialData ParsingMaterial;

	void* CBUserData;
	OnMeshSubset OnSubsetCB;
	using StringValueMap = map<string, string*>;
	StringValueMap MaterialStringValueMap;
	StringValueMap MakeMaterialStringValueMap(ObjMaterialData& m)
	{
		StringValueMap r;
		r["map_Ka"] = &m.AmbientTexture;
		r["map_Kd"] = &m.DiffuseTexture;
		r["map_Ks"] = &m.SpecularTexture;
		r["map_Ns"] = &m.SpecularExpTexture;
		r["map_d"] = &m.AlphaTexture;
		r["map_Tr"] = &m.TransmissionTexture;
		r["bump"] = &m.BumpTexture;
		r["map_bump"] = &m.BumpTexture;
		r["disp"] = &m.DisplacementTexture;
		r["decal"] = &m.DecalTexture;
		return r;
	}

	ObjFileLoader() :
		ParsingSubset(false),
		CBUserData(nullptr),
		OnSubsetCB(nullptr)
	{
		MaterialStringValueMap = MakeMaterialStringValueMap(ParsingMaterial);
	}

	template<typename PointerDataType, typename FlatDataType>
	static vector<PointerDataType> MakePointerDataArray(vector<FlatDataType>& DataSource, ObjVectorDataIndexArray& IndexData)
	{
		vector<PointerDataType> ret;
		ret.reserve(IndexData.size());
		for (auto& it : IndexData)
		{
			ret.push_back(PointerDataType(&DataSource[it.idx], it.len));
		}
		return ret;
	}

	static ObjVectorDataArray MakeVectorDataArray(ObjFloatDataArray& DataSource, ObjVectorDataIndexArray& IndexData)
	{
		return MakePointerDataArray<ObjVectorData>(DataSource, IndexData);
	}

	static ObjFaceDataArray MakeFaceDataArray(ObjVertDataArray& DataSource, ObjVectorDataIndexArray& IndexData)
	{
		return MakePointerDataArray<ObjFaceData>(DataSource, IndexData);
	}

	static ObjLineDataArray MakeLineDataArray(ObjUIntDataArray& DataSource, ObjVectorDataIndexArray& IndexData)
	{
		return MakePointerDataArray<ObjLineData>(DataSource, IndexData);
	}

	ObjMeshSubset MakeObjMeshSubset()
	{
		ObjMeshSubset ret;
		ret.GroupName = SubsetName;
		ret.Material = Materials[UsingMaterialName];
		ret.VertPos = MakeVectorDataArray(VertPosComponents, VertPosIndices);
		ret.VertTex = MakeVectorDataArray(VertTexComponents, VertTexIndices);
		ret.VertNormal = MakeVectorDataArray(VertNormalComponents, VertNormalIndices);
		ret.Faces = MakeFaceDataArray(SubsetFaceVerts, SubsetFaceIndices);
		ret.Lines = MakeLineDataArray(SubsetLineVerts, SubsetLineIndices);
		return ret;
	}

	void FinishSubset(const char* NewSubsetName)
	{
		if (!ParsingSubset)
		{
			ParsingSubset = true;
		}
		else
		{
			ObjMeshSubset* SubsetData = new ObjMeshSubset(MakeObjMeshSubset());
			OnSubsetCB(CBUserData, *SubsetData);
			delete SubsetData;
		}
		SubsetName = NewSubsetName;
		SubsetFaceVerts.clear();
		SubsetFaceIndices.clear();
		SubsetLineVerts.clear();
		SubsetLineIndices.clear();
	}

	void FinishMaterial(const char* NewMaterialName)
	{
		Materials[ParsingMaterialName] = ParsingMaterial;
		ParsingMaterialName = NewMaterialName;
		ParsingMaterial = ObjMaterialData();
	}
};


static bool startswith(const char* str1, const char* str2)
{
	return !memcmp(str1, str2, strlen(str2));
}

inline bool is_space(char ch)
{
	return isspace(static_cast<int>(static_cast<uint8_t>(ch)));
}

inline bool is_number(char ch)
{
	return ch >= '0' && ch <= '9';
}

static char* skip_spaces(char*& ch)
{
	while (is_space(*ch)) ch++;
	return ch;
}

static char* kill_spaces(char*& ch)
{
	while (is_space(*ch))
	{
		*ch++ = '\0';
	}
	return ch;
}

static char* skip_number(char*& ch)
{
	while (is_number(*ch)) ch++;
	return ch;
}

static void rstrip(char* ch)
{
	size_t i = strlen(ch);
	while (i--)
	{
		if (!isspace(static_cast<int>(static_cast<uint8_t>(ch[i]))))
		{
			ch[i + 1] = '\0';
			break;
		}
	}
}

static bool check_begin(char*& ch, const char* check)
{
	size_t bl = strlen(check);
	if (!memcmp(ch, check, bl))
	{
		ch += bl;
		skip_spaces(ch);
		return true;
	}
	return false;
}

static bool match_k_v(char*& key, char *&value)
{
	char* key_end = key;
	while (*key_end && !is_space(*key_end)) key_end++;
	if (!is_space(*key_end)) return false;

	char* value_start = key_end;
	while (is_space(*value_start)) value_start++;

	*key_end = '\0';
	value = value_start;
	return true;
}

class ParseError : public runtime_error
{
public:
	ParseError(string What) noexcept :
		runtime_error(What)
	{}
};

static ObjFloatDataArray ParseFloats(char*& ch)
{
	double d;
	ObjFloatDataArray ret;
	while (sscanf(ch, "%lf", &d) == 1)
	{
		ret.push_back(static_cast<float>(d));
		ch = strchr(ch, ' ');
		if (!ch) break;
		skip_spaces(ch);
	}
	return ret;
}

static ObjUIntDataArray ParseUInts(char*& ch)
{
	uint32_t u;
	ObjUIntDataArray ret;
	while (sscanf(ch, "%d", &u) == 1)
	{
		ret.push_back(u);
		ch = strchr(ch, ' ');
		if (!ch) break;
		skip_spaces(ch);
	}
	return ret;
}

static ObjVertDataArray ParseVerts(char*& ch)
{
	int v, vt, vn;
	v = vt = vn = 0;
	ObjVertDataArray ret;
	for(;*ch != '\0';)
	{
		if (is_number(*ch))
		{
			v = atoi(ch);
			skip_number(ch);
		}
		else break;
		if (*ch == '/')
		{
			ch++;
			if (is_number(*ch))
			{
				vt = atoi(ch);
				skip_number(ch);
			}
		}
		if (*ch == '/')
		{
			ch++;
			if (is_number(*ch))
			{
				vn = atoi(ch);
				skip_number(ch);
			}
		}
		if (v || vt || vn)
		{
			ret.push_back(ObjVertData(v, vt, vn));
		}
		if (*ch == ' ')
		{
			skip_spaces(ch);
		}
	}
	return ret;
}

static vec2 ParseVec2(char*& ch)
{
	auto data = ParseFloats(ch);
	if (data.size() != 2) throw ParseError("Could not parse vec2: " + string(ch));
	return vec2(data[0], data[1]);
}

static vec3 ParseVec3(char*& ch)
{
	auto data = ParseFloats(ch);
	if (data.size() != 3) throw ParseError("Could not parse vec3: " + string(ch));
	return vec3(data[0], data[1], data[2]);
}

static vec4 ParseVec4(char*& ch)
{
	auto data = ParseFloats(ch);
	if (data.size() != 4) throw ParseError("Could not parse vec4: " + string(ch));
	return vec4(data[0], data[1], data[2], data[3]);
}

template <typename FlatDataArrayType, typename ParseFuncType>
static int ParseAndStoreVectors(char*& ch, ParseFuncType ParseFunc, FlatDataArrayType& FlatDataArray, ObjVectorDataIndexArray& IndexArray)
{
	auto data = ParseFunc(ch);
	int idx = static_cast<int>(FlatDataArray.size());
	int len = static_cast<int>(data.size());
	if (len)
	{
		FlatDataArray.insert(FlatDataArray.end(), data.begin(), data.end());
		IndexArray.push_back(ObjVectorDataIndex(idx, len));
	}
	return len;
}

static int ParseVectors(char*& ch, ObjFloatDataArray& FlatDataArray, ObjVectorDataIndexArray& IndexArray)
{
	return ParseAndStoreVectors(ch, ParseFloats, FlatDataArray, IndexArray);
}

static int ParseFaceVerts(char*& ch, ObjVertDataArray& FlatDataArray, ObjVectorDataIndexArray& IndexArray)
{
	return ParseAndStoreVectors(ch, ParseVerts, FlatDataArray, IndexArray);
}

static int ParseLineVerts(char*& ch, ObjUIntDataArray& FlatDataArray, ObjVectorDataIndexArray& IndexArray)
{
	return ParseAndStoreVectors(ch, ParseUInts, FlatDataArray, IndexArray);
}

static bool ReadTextFile(const char* path, void* userdata, void(*on_line)(void* userdata, char* ch), int buf_len = 1024)
{
	char* buf = new char[buf_len];
	FILE* fp = fopen(path, "r");
	if (!fp) goto FailExit;

	while (fgets(buf, buf_len, fp))
	{
		char* ch = strchr(buf, '#');
		if (ch) *ch = '\0';
		ch = strchr(buf, '\n');
		if (ch) *ch = '\0';
		ch = buf;
		skip_spaces(ch);
		if (*ch == '\0') continue;
		rstrip(ch);
		on_line(userdata, ch);
	}

	fclose(fp);
	delete[] buf;
	return true;
FailExit:
	if(fp) fclose(fp);
	delete[] buf;
	return false;
}

static void OnMtlLine(void* userdata, char* ch)
{
	ObjFileLoader& objf = *static_cast<ObjFileLoader*>(userdata);
	char* key = ch;
	char* value;

	if (!match_k_v(key, value)) return;
	if (!strcmp(key, "newmtl"))
	{
		objf.FinishMaterial(value);
		return;
	}
	objf.ParsingMaterial.RawData[key] = value;
	try
	{
		if (!strcmp(key, "Ka"))
		{
			objf.ParsingMaterial.Ambient = ParseVec3(value);
		}
		else if (!strcmp(key, "Kd"))
		{
			objf.ParsingMaterial.Diffuse = ParseVec3(value);
		}
		else if (!strcmp(key, "Ks"))
		{
			objf.ParsingMaterial.Specular = ParseVec3(value);
		}
		else if (!strcmp(key, "Ns"))
		{
			objf.ParsingMaterial.SpecularExp = (float)atof(value);
		}
		else if (!strcmp(key, "d"))
		{
			objf.ParsingMaterial.Alpha = (float)atof(value);
		}
		else if (!strcmp(key, "Tr"))
		{
			objf.ParsingMaterial.Alpha = 1.0f - (float)atof(value);
		}
		else if (!strcmp(key, "Tf"))
		{
			objf.ParsingMaterial.TransmissionFilter = ParseVec3(value);
		}
		else if (!strcmp(key, "Ni"))
		{
			objf.ParsingMaterial.RefractionIndex = (float)atof(value);
		}
		else
		{
			string* sv = objf.MaterialStringValueMap[key];
			if (sv) *sv = value;
		}
	}
	catch (const ParseError& pe)
	{
		fprintf(stderr, "%s\n", pe.what());
		return;
	}
}

static void OnObjLine(void* userdata, char* ch)
{
	ObjFileLoader& objf = *static_cast<ObjFileLoader*>(userdata);
	if (check_begin(ch, "v "))
	{
		ParseVectors(ch, objf.VertPosComponents, objf.VertPosIndices);
	}
	else if (check_begin(ch, "vt "))
	{
		ParseVectors(ch, objf.VertTexComponents, objf.VertTexIndices);
	}
	else if (check_begin(ch, "vn "))
	{
		ParseVectors(ch, objf.VertNormalComponents, objf.VertNormalIndices);
	}
	else if (check_begin(ch, "f "))
	{
		ParseFaceVerts(ch, objf.SubsetFaceVerts, objf.SubsetFaceIndices);
	}
	else if (check_begin(ch, "l "))
	{
		ParseLineVerts(ch, objf.SubsetLineVerts, objf.SubsetLineIndices);
	}
	else if (check_begin(ch, "g "))
	{
		objf.FinishSubset(ch);
	}
	else if (check_begin(ch, "usemtl "))
	{
		objf.UsingMaterialName = ch;
	}
	else if (check_begin(ch, "mtllib "))
	{
		ReadTextFile(ch, userdata, OnMtlLine);
		objf.FinishMaterial("");
	}
	else
	{
		fprintf(stderr, "Unknown OBJ line: %s\n", ch);
	}
}

static bool operator < (const ObjVertData& v1, const ObjVertData& v2)
{
	return v1.Pos < v2.Pos || v1.Tex < v2.Tex || v1.Normal < v2.Normal;
}

void ObjMeshSubset::ConvertToGeneralObjVertices(GeneralObjVertexArrayType& VertOut, ObjUIntDataArray& IndexOut)
{
	//map<ObjVertData, uint32_t> VertMap;
	for (auto& f : Faces)
	{
		uint32_t P0 = 0, P1 = 0;
		for (int i = 0; i < f.len; i++)
		{
			auto& VPTNi = f.ptr[i];
			uint32_t VertIndex = 0;// VertMap[VPTNi];
			if (!VertIndex)
			{
				GeneralObjVertexType NewVert;
				if (VPTNi.Pos) NewVert.Position =  VertPos[static_cast<size_t>(VPTNi.Pos) - 1].ToVec3();
				if (VPTNi.Tex) NewVert.TexCoord =  VertTex[static_cast<size_t>(VPTNi.Tex) - 1].ToVec2();
				if (VPTNi.Normal) NewVert.Normal = VertTex[static_cast<size_t>(VPTNi.Normal) - 1].ToVec3();
				VertOut.push_back(NewVert);
				VertIndex = static_cast<uint32_t>(VertOut.size());
				// VertMap[VPTNi] = VertIndex;
			}
			VertIndex -= 1;
			if (i > 2)
			{
				IndexOut.push_back(P0);
				IndexOut.push_back(P1);
				IndexOut.push_back(VertIndex);
			}
			else
			{
				IndexOut.push_back(VertIndex);
			}
			P0 = P1;
			P1 = VertIndex;
		}
	}
}

void GeneralObjVertices::OnMeshSubset(void* cb_userdata, ObjMeshSubset& subset)
{
	auto &self = *static_cast<GeneralObjVertices*>(cb_userdata);
	subset.ConvertToGeneralObjVertices(self.Vertices, self.Indices);
}

bool GLRenderer::LoadObjFile(const char* path, OnMeshSubset CB, void* cb_userdata)
{
	ObjFileLoader *ObjLoader = new ObjFileLoader();

	ObjLoader->CBUserData = cb_userdata;
	ObjLoader->OnSubsetCB = CB;
	if (!ReadTextFile(path, ObjLoader, OnObjLine)) goto FailExit;
	ObjLoader->FinishSubset("");

	delete ObjLoader;
	return true;
FailExit:
	delete ObjLoader;
	return false;
}


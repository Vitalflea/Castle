#pragma once

typedef unsigned short MaterialHandle_t;

class KeyValues;

class IMaterialSystem : public IAppSystem
{
public:
	//virtual void				BeginFrame(float frameTime) = 0;
	IMaterial* BeginFrame(float frameTime)
	{
		typedef IMaterial* (__thiscall* oCreateMaterial)(void*, float);
		return getvfunc<oCreateMaterial>(this, 42)(this, frameTime);
	}

	IMaterial* CreateMaterial(const char* pMaterialName, KeyValues* pVMTKeyValues)
	{
		typedef IMaterial* (__thiscall* oCreateMaterial)(void*, const char*, KeyValues*);
		return getvfunc<oCreateMaterial>(this, 83)(this, pMaterialName, pVMTKeyValues);
	}

	IMaterial* FindMaterial(char const* pMaterialName, const char* pTextureGroupName, bool complain = true, const char* pComplainPrefix = NULL)
	{
		typedef IMaterial* (__thiscall* oFindMaterial)(void*, char const*, const char*, bool, const char*);
		return getvfunc<oFindMaterial>(this, 84)(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
	}
	IMaterial* FindMaterial2(const char* pMaterialName, const char* pTextureGroupName = "Model textures", bool complain = true, const char* pComplainPrefix = NULL)
	{
		typedef IMaterial* (__thiscall* FindMaterialFn)(void*, const char*, const char*, bool, const char*);
		return getvfunc<FindMaterialFn>(this, 84)(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
	}
	MaterialHandle_t FirstMaterial()
	{
		typedef MaterialHandle_t(__thiscall* oFirstMaterial)(void*);
		return getvfunc<oFirstMaterial>(this, 86)(this);
	}

	MaterialHandle_t NextMaterial(MaterialHandle_t h)
	{
		typedef MaterialHandle_t(__thiscall* oNextMaterial)(void*, MaterialHandle_t);
		return getvfunc<oNextMaterial>(this, 87)(this, h);
	}

	MaterialHandle_t InvalidMaterial()
	{
		typedef MaterialHandle_t(__thiscall* oInvalidMaterial)(void*);
		return getvfunc<oInvalidMaterial>(this, 88)(this);
	}

	IMaterial* GetMaterial(MaterialHandle_t h)
	{
		typedef IMaterial* (__thiscall* oGetMaterial)(void*, MaterialHandle_t);
		return getvfunc<oGetMaterial>(this, 89)(this, h);
	}
};
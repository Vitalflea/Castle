#pragma once
 
struct surfacephysicsparams_t
{
	float friction;
	float elasticity;
	float density;
	float thickness;
	float dampening;
};
 
struct surfaceaudioparams_t
{
	float audioReflectivity;
	float audioHardnessFactor;
	float audioRoughnessFactor;
	float scrapeRoughThreshold;
	float impactHardThreshold;
	float audioHardMinVelocity;
	float highPitchOcclusion;
	float midPitchOcclusion;
	float lowPitchOcclusion;
};
 
struct surfacesoundnames_t
{
	short walkLeft;
	short walkRight;
	short runLeft;
	short runRight;
	short impactsoft;
	short impacthard;
	short scrapesmooth;
	short scraperough;
	short bulletimpact;
	short rolling;
	short breakSound; // named "break" in vphysics.dll but since break is also a type rename it to breakSound
	short strain;
};
 
struct surfacegameprops_t
{
	float maxspeedfactor;
	float jumpfactor;
	float penetrationmodifier;
	float damagemodifier;
	uint16_t material;
	uint8_t climbable;
};
 
struct surfacedata_t
{
	surfacephysicsparams_t physics;
	surfaceaudioparams_t audio;
	surfacesoundnames_t sounds;
	surfacegameprops_t game;
	char pad[48];
}; // size = 0x94
 
class IPhysicsSurfaceProps
{
public:
	virtual ~IPhysicsSurfaceProps(void) {}
 
	// parses a text file containing surface prop keys
	virtual int ParseSurfaceData(const char *pFilename, const char *pTextfile) = 0;
 
	// current number of entries in the database
	virtual int SurfacePropCount(void) const = 0;
 
	virtual int GetSurfaceIndex(const char *pSurfacePropName) const = 0;
 
	virtual void GetPhysicsProperties(int surfaceDataIndex, float *density, float *thickness, float *friction, float *elasticity) const = 0;
 
	virtual surfacedata_t *GetSurfaceData(int surfaceDataIndex) = 0;
 
	virtual const char *GetString(unsigned short stringTableIndex) const = 0;
 
	virtual const char *GetPropName(int surfaceDataIndex) const = 0;
 
	// sets the global index table for world materials
	// UNDONE: Make this per-CPhysCollide
	virtual void SetWorldMaterialIndexTable(int *pMapArray, int mapSize) = 0;
 
	// NOTE: Same as GetPhysicsProperties, but maybe more convenient
	virtual void GetPhysicsParameters(int surfaceDataIndex, surfacephysicsparams_t *pParamsOut) const = 0;
};

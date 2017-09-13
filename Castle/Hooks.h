#pragma once
#include <Windows.h>
#include "SDK/SDK.h"
#include "Interfaces.h"
#include "Features.h"
#include "Renderer.h"
#include "ImGui\imgui.h"
#include "Menu.h"
#include "DDI.h"
#include "Draw.h"

typedef long(__stdcall* EndSceneFn)(IDirect3DDevice9* device);
typedef long(__stdcall* ResetFn)(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pp);
typedef long(__stdcall* PresentFn)(IDirect3DDevice9* device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion);
typedef bool(__thiscall* CreateMoveFn)(IClientMode*, float, CUserCmd*);
typedef void(__thiscall* RunCommand_t)(IPrediction*, IClientEntity*, CUserCmd*, void*);
typedef void(__thiscall* PaintTraverseFn)(void*, unsigned int, bool, bool);
typedef void(__thiscall* DrawModelExecuteFn)(void*, void*, const DrawModelState_t&, const ModelRenderInfo_t&, matrix3x4*);
typedef void(__thiscall* FrameStageNotifyFn)(void*, ClientFrameStage_t);
typedef bool(__thiscall* FireEventClientSideFn)(void*, IGameEvent*);
typedef void(__thiscall *BeginFrameFn) (void*, float);
typedef void(__thiscall *EmitSound1Fn) (void*, IRecipientFilter&, int, int, const char*, unsigned int, const char*, float, int, float, int, int, const Vector*, const Vector*, void*, bool, float, int);
typedef void(__thiscall *EmitSound2Fn) (void*, IRecipientFilter&, int, int, const char*, unsigned int, const char*, float, int, soundlevel_t, int, int, const Vector*, const Vector*, void*, bool, float, int);
typedef void(__thiscall* PlaySoundFn)(ISurface*, const char*);
typedef void(__thiscall* RenderViewFn)(void*, CViewSetup&, CViewSetup&, int, int);
typedef void(__thiscall* OverreideViewFn)(void*, ViewSetup*);
typedef float(__thiscall *GetViewModelFOVFn)();

namespace Hooks
{
	HRESULT WINAPI hPresent(IDirect3DDevice9* pDevice, RECT* pSourceRect, RECT* pDestRect, HWND hDestWindowOverride, RGNDATA* pDirtyRegion);
	HRESULT WINAPI hReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
	bool __stdcall hCreateMove(float frametime, CUserCmd* cmd);
	void __stdcall Hooked_RunCommand(IClientEntity* pEntity, CUserCmd* pCmd, void* pMoveHelper);
	void __stdcall hPaintTraverse(unsigned int VGUIPanel, bool forcerepaint, bool allowforce);
	void __stdcall hDrawModelExecute(IMatRenderContext* matctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld);
	void __fastcall hFrameStageNotify(void* ecx, void* edx, ClientFrameStage_t Stage);
	bool __fastcall hFireEventClientSide(void* ecx, void* edx, IGameEvent* pEvent);
	HRESULT __stdcall hkEndScene(IDirect3DDevice9* device);
	void __stdcall hBeginFrame(float frameTime);
	void __fastcall hEmitSound1(IEngineSound* thisptr, int edx, IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample, float flVolume, float iSoundlevel, int nSeed, int iFlags = 0, int iPitch = PITCH_NORM, const Vector *pOrigin = NULL, const Vector *pDirection = NULL, CUtlVector< Vector >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1);
	void __fastcall hEmitSound2(IEngineSound* thisptr, int edx, IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample, float flVolume, soundlevel_t flAttenuation, int nSeed, int iFlags = 0, int iPitch = PITCH_NORM, const Vector *pOrigin = NULL, const Vector *pDirection = NULL, CUtlVector< Vector >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1);
	void __stdcall hPlaySounds(const char* fileName);
	void __fastcall hRenderView(void* ecx, void* edx, CViewSetup &setup, CViewSetup &hudViewSetup, int nClearFlags, int whatToDraw);
	void __fastcall hOverrideView(void* _this, void* _edx, ViewSetup* setup);
	float __stdcall hGetViewModelFOV();
}
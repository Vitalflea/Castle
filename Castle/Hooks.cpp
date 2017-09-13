#include "Hooks.h"

namespace Hooks
{ 
	HRESULT WINAPI hPresent(IDirect3DDevice9* pDevice, RECT* pSourceRect, RECT* pDestRect, HWND hDestWindowOverride, RGNDATA* pDirtyRegion) {

		if (GetAsyncKeyState(VK_SNAPSHOT) || pEngine->IsTakingScreenshot()) {
			return Present(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
		}

		DWORD dwOld_D3DRS_COLORWRITEENABLE;
		pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &dwOld_D3DRS_COLORWRITEENABLE);
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);

		//Menu();

		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, dwOld_D3DRS_COLORWRITEENABLE);

		return Present(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	}
	HRESULT WINAPI hReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters) 
	{
		static Reset_t oReset = D3D9Hook->GetOriginalFunction<Reset_t>(16);

		if (!renderer.IsReady() || !pDevice)
			return oReset(pDevice, pPresentationParameters);

		ImGui_ImplDX9_InvalidateDeviceObjects();

		HRESULT result = oReset(pDevice, pPresentationParameters);

		ImGui_ImplDX9_CreateDeviceObjects();

		return result;
	}
	void __stdcall hPaintTraverse(unsigned int VGUIPanel, bool forcerepaint, bool allowforce)
	{
		PanelHook->GetOriginalFunction<PaintTraverseFn>(41)(pPanel, VGUIPanel, forcerepaint, allowforce);
		static unsigned int drawPanel;

		if (!drawPanel)
			if (strstr(pPanel->GetName(VGUIPanel), "MatSystemTopPanel"))
				drawPanel = VGUIPanel;

		if (VGUIPanel != drawPanel)
			return;

		Info();
		Dlights::Paint();
		ESP::Paint();
		GrenadeHelper::Paint();
		Recoilcrosshair::Paint();
		Hitmarkers::Paint();
		//NadePrediction();
	}
	bool __stdcall hCreateMove(float frametime, CUserCmd* cmd)
	{
		ClientModeHook->GetOriginalFunction<CreateMoveFn>(24)(pClientMode, frametime, cmd);
		if (cmd && cmd->command_number)
		{
			PDWORD pEBP;
			__asm mov pEBP, ebp;
			bool& bSendPacket = *(bool*)(*pEBP - 0x1C);

			bSendPacket = SendPacket;
			bSendPackett = bSendPacket;
			SendPacket = true;

			BHop::CreateMove(cmd);
			AutoStrafe::CreateMove(cmd);
			ShowRanks::CreateMove(cmd);
			AutoDefuse::CreateMove(cmd);
			JumpThrow::CreateMove(cmd);
			GrenadeHelper::CreateMove(cmd);
			EdgeJump::PrePredictionCreateMove(cmd);

			Prediction::Start(cmd);
			Autoblock::CreateMove(cmd);
			Aimbot::CreateMove(cmd);
			Triggerbot::CreateMove(cmd);
			AntiAim::CreateMove(cmd);
			Airstuck::CreateMove(cmd);
			Teleport::CreateMove(cmd);
			FakeLag::CreateMove(cmd);
			ESP::CreateMove(cmd);
			Walkbot::CreateMove(cmd);
			Prediction::End();
			FakeWalk(cmd, bSendPacket);
			TracerEffect::CreateMove(cmd);
			EdgeJump::PostPredictionCreateMove(cmd);

			if (Settings::ThirdPerson::Fake && !SendPacket)
				lastTickViewAngles = cmd->viewangles;
		
			if (Settings::ThirdPerson::Real && SendPacket)
				lastTickViewAngles = cmd->viewangles;

		}
		else 
			return ClientModeHook->GetOriginalFunction<CreateMoveFn>(24)(pClientMode, frametime, cmd);

		return false;
	}
	void __stdcall hDrawModelExecute(IMatRenderContext* matctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld)
	{
		//ModelRenderHook->UnhookFunction(21);
		Chams::DrawModelExecute(matctx, state, pInfo, pCustomBoneToWorld);
		

		ModelRenderHook->GetOriginalFunction<DrawModelExecuteFn>(21)(pModelRender, matctx, state, pInfo, pCustomBoneToWorld);
		pModelRender->ForcedMaterialOverride(nullptr);
		//ModelRenderHook->HookFunction(hDrawModelExecute, 21);-
	}
	void __fastcall hFrameStageNotify(void* ecx, void* edx, ClientFrameStage_t stage)
	{
		// PVS Fix
		if (stage == ClientFrameStage_t::FRAME_RENDER_START)
		{
			for (int i = 1; i <= pGlobalVars->maxClients; i++)
			{
				if (i == pEngine->GetLocalPlayer()) continue;

				IClientEntity* pCurEntity = pEntityList->GetClientEntity(i);
				if (!pCurEntity) continue;

				*(int*)((uintptr_t)pCurEntity + 0xA30) = pGlobalVars->framecount; //we'll skip occlusion checks now
				*(int*)((uintptr_t)pCurEntity + 0xA28) = 0;//clear occlusion flags
			}
		}
		static bool Rekt = false;
		if (!Rekt)
		{
			ConVar* sv_cheats = pCvar->FindVar("sv_cheats");
			SpoofedConvar* sv_cheats_spoofed = new SpoofedConvar(sv_cheats);
			sv_cheats_spoofed->SetInt(1);

			ConVar* ST = pCvar->FindVar("r_DrawSpecificStaticProp");
		//	SpoofedConvar* sST = new SpoofedConvar(sv_cheats);
			//ST->
			ST->SetValue(0);

			Rekt = true;
		}
		//CustomGlow::FrameStageNotify(stage);
		//SkinChanger::FrameStageNotifyModels(stage);
		SkinChanger::FrameStageNotifySkins(stage);

		Noflash::FrameStageNotify(stage);
		View::FrameStageNotify(stage);
		Resolver::FrameStageNotify(stage);
		NoSky::FrameStageNotify(stage);
		ASUSWalls::FrameStageNotify(stage);
		NoSmoke::FrameStageNotify(stage);
		ThirdPerson::FrameStageNotify(stage);

		//if (SkinChanger::forceFullUpdate)
		//{
		//	pClientState->m_nDeltaTick = -1;
		//	SkinChanger::forceFullUpdate = false;
		//}

		ClientHook->GetOriginalFunction<FrameStageNotifyFn>(36)(ecx, stage);
		ESP::DrawModelExecute(stage);
		Resolver::PostFrameStageNotify(stage);
		View::PostFrameStageNotify(stage);
	}
	HRESULT WINAPI hkEndScene(IDirect3DDevice9* device)
	{
		static EndScene_t oEndScene = D3D9Hook->GetOriginalFunction<EndScene_t>(42);

		DWORD dwOld_D3DRS_COLORWRITEENABLE;
		device->GetRenderState(D3DRS_COLORWRITEENABLE, &dwOld_D3DRS_COLORWRITEENABLE);
		device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);

		Menu();

		device->SetRenderState(D3DRS_COLORWRITEENABLE, dwOld_D3DRS_COLORWRITEENABLE);

		return oEndScene(device);
	}
	bool __fastcall hFireEventClientSide(void* ecx, void* edx, IGameEvent* pEvent)
	{
		SkinChanger::FireEventClientSide(pEvent);

		Aimbot::FireGameEvent(pEvent);
		Hitmarkers::FireGameEvent(pEvent);
		NameStealer::FireGameEvent(pEvent);
		Resolver::FireGameEvent(pEvent);
		Spammer::FireGameEvent(pEvent);
		//ValveDSCheck::FireGameEvent(pEvent);
		SkinChanger::FireGameEvent(pEvent);
		//if (pEvent)
		//{
		//	FireGameEvent(pEvent);
		//}
		return FireEventHook->GetOriginalFunction<FireEventClientSideFn>(9)(ecx, pEvent);
	}
	void __stdcall hBeginFrame(float frameTime)
	{
		ClanTagChanger::BeginFrame(frameTime);
		NameChanger::BeginFrame(frameTime);
		NameStealer::BeginFrame(frameTime);
		Spammer::BeginFrame(frameTime);
		//Radar::BeginFrame();
		//SniperCrosshair::BeginFrame();
		//ThirdPerson::BeginFrame();
		//DisablePostProcessing::BeginFrame();

		//if (!pEngine->IsInGame())
		//{
			//SendPacket = true;
			//*bSendPacket = CreateMove::sendPacket;
		//}

		//Skins::Localize();

		return MaterialHook->GetOriginalFunction<BeginFrameFn>(42)(pMaterial,frameTime);
	}
	void __fastcall hEmitSound1(IEngineSound* thisptr, int edx, IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample, float flVolume, float iSoundlevel, int nSeed, int iFlags , int iPitch , const Vector *pOrigin , const Vector *pDirection , CUtlVector< Vector >* pUtlVecOrigins , bool bUpdatePositions , float soundtime , int speakerentity)
	{
		return SoundHook->GetOriginalFunction<EmitSound1Fn>(5)(thisptr, filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample, flVolume, nSeed, iSoundlevel, iFlags, iPitch, pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity);
	}
	void __fastcall hEmitSound2(IEngineSound* thisptr, int edx, IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample, float flVolume, soundlevel_t flAttenuation, int nSeed, int iFlags , int iPitch , const Vector *pOrigin , const Vector *pDirection , CUtlVector< Vector >* pUtlVecOrigins , bool bUpdatePositions , float soundtime, int speakerentity )
	{
		//ESP::EmitSound(iEntIndex, pSample);
		return SoundHook->GetOriginalFunction<EmitSound2Fn>(6)(thisptr, filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample, flVolume, nSeed, flAttenuation, iFlags, iPitch, pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity);
	}
	void __stdcall hPlaySounds(const char* fileName)
	{
		SurfaceHook->GetOriginalFunction<PlaySoundFn>(82)(pSurface, fileName);

		AutoAccept::PlaySound(fileName);
	}
	void __fastcall hRenderView(void* ecx, void* edx, CViewSetup &setup, CViewSetup &hudViewSetup, int nClearFlags, int whatToDraw)
	{
		//C_BasePlayer* Local = (C_BasePlayer*)pEntityList->GetClientEntity(pEngine->GetLocalPlayer());

		//mirror = setup; mirror.x = 300; mirror.y = 200;
		//mirror.origin = Local->GetEyePosition();
		//pEngine->GetViewAngles(mirror.angles);
		//mirror.angles.y += 180.0f;
		//pViewRender->RenderView(mirror, hudViewSetup, 0, 0);
		//RenderViewHook->GetOriginalFunction<RenderViewFn>(6)(ecx, mirror, hudViewSetup, 0, 0);

		RenderViewHook->GetOriginalFunction<RenderViewFn>(6)(ecx, setup, hudViewSetup, nClearFlags, whatToDraw);
	}
	void __fastcall hOverrideView(void* _this, void* _edx, ViewSetup* setup)
	{
		FOVChanger::OverrideView(setup);
		OverrideView::currentFOV = setup->fov;

		ClientModeHook->GetOriginalFunction<OverreideViewFn>(18)(_this, setup);
	}
	float __stdcall hGetViewModelFOV()
	{
		float fov = ClientModeHook->GetOriginalFunction<GetViewModelFOVFn>(35)();

		
		FOVChanger::GetViewModelFOV(fov);

		return fov;
	}
}
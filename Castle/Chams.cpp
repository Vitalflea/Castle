#include "Features.h"
#include "Util_SDK.h"
#include "Hooks.h"

bool Settings::ESP::Chams::enabled = false;
bool Settings::ESP::Chams::Arms::enabled = false;
bool Settings::ESP::Chams::Weapon::enabled = false;
int Settings::ESP::Chams::Arms::type = (int)ArmsType::DEFAULT;
HealthColorVar Settings::ESP::Chams::allyColor = ImColor(7, 98, 168, 255);
HealthColorVar Settings::ESP::Chams::allyVisibleColor = ImColor(40, 52, 138, 255);
HealthColorVar Settings::ESP::Chams::enemyColor = ImColor(243, 24, 28, 255);
HealthColorVar Settings::ESP::Chams::enemyVisibleColor = ImColor(243, 159, 20, 255);
HealthColorVar Settings::ESP::Chams::localplayerColor = ImColor(117, 43, 73, 255);
ColorVar Settings::ESP::Chams::Arms::color = ImColor(117, 43, 73, 255);
ColorVar Settings::ESP::Chams::Weapon::color = ImColor(255, 255, 255, 255);
int Settings::ESP::Chams::type = (int)ChamsType::CHAMS;

IMaterial* materialChams;
IMaterial* materialChamsIgnorez;
IMaterial* materialChamsFlat;
IMaterial* materialChamsFlatIgnorez;
IMaterial* materialChamsArms;
IMaterial* materialChamsWeapons;

void DrawPlayer(IMatRenderContext* matctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld)
{
	if (!Settings::ESP::Chams::enabled)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)pEntityList->GetClientEntity(pEngine->GetLocalPlayer());
	if (!localplayer)
		return;

	C_BasePlayer* entity = (C_BasePlayer*)pEntityList->GetClientEntity(pInfo.entity_index);
	if (!entity
		|| entity->GetDormant()
		|| !entity->GetAlive())
		return;

	if (entity == localplayer && !Settings::ESP::Filters::localplayer)
		return;

	if (entity->GetTeam() != localplayer->GetTeam() && !Settings::ESP::Filters::enemies)
		return;

	if (entity != localplayer && entity->GetTeam() == localplayer->GetTeam() && !Settings::ESP::Filters::allies)
		return;

	IMaterial* visible_material;
	IMaterial* hidden_material;

	if (Settings::ESP::Chams::type == (int)ChamsType::CHAMS || Settings::ESP::Chams::type == (int)ChamsType::CHAMS_XQZ)
	{
		visible_material = materialChams;
		hidden_material = materialChamsIgnorez;
	}
	if (Settings::ESP::Chams::type == (int)ChamsType::CHAMS_FLAT || Settings::ESP::Chams::type == (int)ChamsType::CHAMS_FLAT_XQZ)
	{
		visible_material = materialChamsFlat;
		hidden_material = materialChamsFlatIgnorez;
	}

	visible_material->AlphaModulate(1.0f);
	hidden_material->AlphaModulate(1.0f);

	if (entity == localplayer)
	{
		Color visColor = Color::FromImColor(Settings::ESP::Chams::localplayerColor.Color(entity));
		Color color = visColor;
		color *= 0.45f;

		visible_material->ColorModulate(visColor.r / 255.f, visColor.g / 255.f, visColor.b / 255.f);
		hidden_material->ColorModulate(color.r / 255.f, color.g / 255.f, color.b / 255.f);
	}
	else if (entity->GetTeam() == localplayer->GetTeam())
	{
		Color visColor = Color::FromImColor(Settings::ESP::Chams::allyVisibleColor.Color(entity));
		Color color = Color::FromImColor(Settings::ESP::Chams::allyColor.Color(entity));

		visible_material->ColorModulate(visColor.r / 255.f, visColor.g / 255.f, visColor.b / 255.f);
		hidden_material->ColorModulate(color.r / 255.f, color.g / 255.f, color.b / 255.f);
	}
	else if (entity->GetTeam() != localplayer->GetTeam())
	{
		Color visColor = Color::FromImColor(Settings::ESP::Chams::enemyVisibleColor.Color(entity));
		Color color = Color::FromImColor(Settings::ESP::Chams::enemyColor.Color(entity));

		visible_material->ColorModulate(visColor.r / 255.f, visColor.g / 255.f, visColor.b / 255.f);
		hidden_material->ColorModulate(color.r / 255.f, color.g / 255.f, color.b / 255.f);
	}
	else
	{
		return;
	}

	if (entity->GetImmune())
	{
		visible_material->AlphaModulate(0.5f);
		hidden_material->AlphaModulate(0.5f);
	}

	if (!Settings::ESP::Filters::legit && (Settings::ESP::Chams::type == (int)ChamsType::CHAMS_XQZ || Settings::ESP::Chams::type == (int)ChamsType::CHAMS_FLAT_XQZ))
	{
		pModelRender->ForcedMaterialOverride(hidden_material);
		ModelRenderHook->GetOriginalFunction<DrawModelExecuteFn>(21)(pModelRender, matctx, state, pInfo, pCustomBoneToWorld);
	}

	pModelRender->ForcedMaterialOverride(visible_material);
	ModelRenderHook->GetOriginalFunction<DrawModelExecuteFn>(21)(pModelRender, matctx, state, pInfo, pCustomBoneToWorld);
}

void DrawWeapon(const ModelRenderInfo_t& pInfo)
{
	if (!Settings::ESP::Chams::Weapon::enabled)
		return;

	std::string modelName = pModelInfo->GetModelName(pInfo.pModel);
	IMaterial* mat = materialChamsWeapons;

	if (!Settings::ESP::Chams::Weapon::enabled)
		mat = pMaterial->FindMaterial(modelName.c_str(), TEXTURE_GROUP_MODEL);

	mat->AlphaModulate(1.0f);
	mat->ColorModulate(Settings::ESP::Chams::Weapon::color.Color().Value.x, Settings::ESP::Chams::Weapon::color.Color().Value.y, Settings::ESP::Chams::Weapon::color.Color().Value.z);

	pModelRender->ForcedMaterialOverride(mat);
}

void DrawArms(const ModelRenderInfo_t& pInfo)
{
	if (!Settings::ESP::Chams::Arms::enabled)
		return;

	std::string modelName = pModelInfo->GetModelName(pInfo.pModel);
	IMaterial* mat = materialChamsArms;

	if (!Settings::ESP::Chams::Arms::enabled)
		mat = pMaterial->FindMaterial(modelName.c_str(), TEXTURE_GROUP_MODEL);

	switch (Settings::ESP::Chams::Arms::type)
	{
	default:
		break;
	case (int)ArmsType::DEFAULT:
		mat->AlphaModulate(1.0f);
		mat->ColorModulate(Settings::ESP::Chams::Arms::color.Color().Value.x, Settings::ESP::Chams::Arms::color.Color().Value.y, Settings::ESP::Chams::Arms::color.Color().Value.z);
		break;
	}

	mat->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, Settings::ESP::Chams::Arms::type == (int)ArmsType::WIREFRAME);
	mat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, Settings::ESP::Chams::Arms::type == (int)ArmsType::NONE);
	pModelRender->ForcedMaterialOverride(mat);
}

void Chams::DrawModelExecute(IMatRenderContext* matctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld)
{
	if (Settings::ScreenshotCleaner::enabled && pEngine->IsTakingScreenshot())
		return;

	if (!pEngine->IsInGame())
		return;

	if (!Settings::ESP::enabled)
		return;

	if (!pInfo.pModel)
		return;

	static bool materialsCreated = false;
	if (!materialsCreated)
	{
		materialChams = Util::CreateMaterial("VertexLitGeneric", "VGUI/white_additive", false, true, true, true, true);
		materialChamsIgnorez = Util::CreateMaterial("VertexLitGeneric", "VGUI/white_additive", true, true, true, true, true);
		materialChamsFlat = Util::CreateMaterial("UnlitGeneric", "VGUI/white_additive", false, true, true, true, true);
		materialChamsFlatIgnorez = Util::CreateMaterial("UnlitGeneric", "VGUI/white_additive", true, true, true, true, true);
		materialChamsArms = Util::CreateMaterial("VertexLitGeneric", "VGUI/white_additive", false, true, true, true, true);
		materialChamsWeapons = Util::CreateMaterial("VertexLitGeneric", "VGUI/white_additive", false, true, true, true, true);
		materialsCreated = true;
	}

	std::string modelName = pModelInfo->GetModelName(pInfo.pModel);

	if (modelName.find("models/player") != std::string::npos)
		DrawPlayer(matctx, state, pInfo, pCustomBoneToWorld);
	else if (modelName.find("arms") != std::string::npos)
		DrawArms(pInfo);
	else if (modelName.find("weapon") != std::string::npos)
		DrawWeapon(pInfo);
}
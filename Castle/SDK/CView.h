#pragma once
struct CViewSetup
{
	char _0x0000[16];
	__int32 x;
	__int32 x_old;
	__int32 y;
	__int32 y_old;
	__int32 width;
	__int32    width_old;
	__int32 height;
	__int32    height_old;
	char _0x0030[128];
	float fov;
	float fovViewmodel;
	Vector origin;
	Vector angles;
	float zNear;
	float zFar;
	float zNearViewmodel;
	float zFarViewmodel;
	float m_flAspectRatio;
	float m_flNearBlurDepth;
	float m_flNearFocusDepth;
	float m_flFarFocusDepth;
	float m_flFarBlurDepth;
	float m_flNearBlurRadius;
	float m_flFarBlurRadius;
	float m_nDoFQuality;
	__int32 m_nMotionBlurMode;
	char _0x0104[68];
	__int32 m_EdgeBlur;
};

class CViewRender
{
public:
	void RenderView(CViewSetup &view, CViewSetup &hud, int nClearFlags, int whatToDraw)
	{
		typedef void(__thiscall*oGetAllClasses)(void*, CViewSetup&, CViewSetup&, int, int);
		return getvfunc<oGetAllClasses>(this, 6)(this, view, hud, nClearFlags, whatToDraw);
	}
};

class ViewSetup {
public:
	int x;
	int unscaled_x;
	int y;
	int unscaled_y;
	int width;
	int unscaled_width;
	int height;
	int unscaled_height;
	int stereo_eye;
	char _pad0x24[0x78];
	bool ortho;
	float ortho_left;
	float ortho_top;
	float ortho_right;
	float ortho_bottom;
	float fov;
	float fov_viewmodel;
	Vector origin;
	Vector angles;
	float z_near;
	float z_far;
	float z_near_viewmodel;
	float z_far_viewmodel;
	bool render_to_subrect_of_larger_screen;
	float aspect_ratio;
	bool off_center;
	float off_center_top;
	float off_center_bottom;
	float off_center_left;
	float off_center_right;
	bool do_bloom_and_tone_mapping;
	bool cache_full_scene_state;
	bool view_to_projection_override;
	//Matrix view_to_projection;
};



/**************************************************************************/
/*  register_types.cpp                                                    */
/**************************************************************************/

#include "register_types.h"

#include "balmung_hd2d_profile.h"
#include "core/config/project_settings.h"

void initialize_balmung_hd2d_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_CLASS(BalmungHD2DProfile);
	GDREGISTER_CLASS(BalmungHD2DRig);

	GLOBAL_DEF_BASIC(PropertyInfo(Variant::INT, "balmung/hd2d/default_projection_mode", PROPERTY_HINT_ENUM, "Orthographic,Narrow Perspective"), int(BalmungHD2DProfile::PROJECTION_NARROW_PERSPECTIVE));
	GLOBAL_DEF_BASIC(PropertyInfo(Variant::FLOAT, "balmung/hd2d/default_orthographic_size", PROPERTY_HINT_RANGE, "1,256,0.1"), 18.0);
	GLOBAL_DEF_BASIC(PropertyInfo(Variant::FLOAT, "balmung/hd2d/default_perspective_fov", PROPERTY_HINT_RANGE, "1,120,0.1"), 22.0);
	GLOBAL_DEF_BASIC(PropertyInfo(Variant::FLOAT, "balmung/hd2d/default_camera_pitch_degrees", PROPERTY_HINT_RANGE, "-89,89,0.1"), -32.0);
	GLOBAL_DEF_BASIC(PropertyInfo(Variant::FLOAT, "balmung/hd2d/default_camera_yaw_degrees", PROPERTY_HINT_RANGE, "-180,180,0.1"), 45.0);
	GLOBAL_DEF_BASIC(PropertyInfo(Variant::FLOAT, "balmung/hd2d/default_camera_distance", PROPERTY_HINT_RANGE, "0.1,512,0.1"), 24.0);
	GLOBAL_DEF_BASIC(PropertyInfo(Variant::FLOAT, "balmung/hd2d/default_focus_height", PROPERTY_HINT_RANGE, "-64,64,0.01"), 2.5);
	GLOBAL_DEF_BASIC(PropertyInfo(Variant::FLOAT, "balmung/hd2d/default_pixels_per_unit", PROPERTY_HINT_RANGE, "1,512,1"), 32.0);
	GLOBAL_DEF_BASIC(PropertyInfo(Variant::FLOAT, "balmung/hd2d/default_layer_depth_step", PROPERTY_HINT_RANGE, "0.001,8,0.001"), 0.25);
}

void uninitialize_balmung_hd2d_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

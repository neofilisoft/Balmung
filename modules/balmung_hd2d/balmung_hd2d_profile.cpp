/**************************************************************************/
/*  balmung_hd2d_profile.cpp                                              */
/**************************************************************************/

#include "balmung_hd2d_profile.h"

#include "core/config/engine.h"
#include "core/config/project_settings.h"
#include "core/math/math_funcs.h"
#include "scene/3d/camera_3d.h"
#include "scene/3d/light_3d.h"
#include "scene/3d/world_environment.h"
#include "scene/resources/camera_attributes.h"
#include "scene/resources/environment.h"

namespace {
template <class T>
T *_resolve_typed_node(const Node *p_owner, const NodePath &p_path) {
	if (!p_owner || p_path.is_empty()) {
		return nullptr;
	}
	return Object::cast_to<T>(p_owner->get_node_or_null(p_path));
}

static void _apply_environment_profile(const Ref<BalmungHD2DProfile> &p_profile, const Ref<Environment> &p_environment) {
	ERR_FAIL_COND(p_profile.is_null());
	ERR_FAIL_COND(p_environment.is_null());

	p_environment->set_background(Environment::BG_COLOR);
	p_environment->set_bg_color(p_profile->get_background_color());
	p_environment->set_ambient_source(Environment::AMBIENT_SOURCE_COLOR);
	p_environment->set_ambient_light_color(p_profile->get_ambient_color());
	p_environment->set_ambient_light_energy(p_profile->get_ambient_energy());
	p_environment->set_ambient_light_sky_contribution(0.0f);
	p_environment->set_tonemapper(Environment::TONE_MAPPER_ACES);

	p_environment->set_glow_enabled(p_profile->is_glow_enabled());
	p_environment->set_glow_strength(p_profile->get_glow_strength());
	p_environment->set_glow_mix(p_profile->get_glow_mix());
	p_environment->set_glow_bloom(0.05f);

	p_environment->set_fog_enabled(p_profile->is_fog_enabled());
	p_environment->set_fog_mode(Environment::FOG_MODE_DEPTH);
	p_environment->set_fog_density(p_profile->get_fog_density());
	p_environment->set_fog_depth_begin(p_profile->get_fog_depth_begin());
	p_environment->set_fog_depth_end(p_profile->get_fog_depth_end());
	p_environment->set_fog_sky_affect(0.25f);

	p_environment->set_adjustment_enabled(p_profile->is_adjustments_enabled());
	p_environment->set_adjustment_contrast(p_profile->get_adjustment_contrast());
	p_environment->set_adjustment_saturation(p_profile->get_adjustment_saturation());
}
} // namespace

void BalmungHD2DProfile::_bind_methods() {
	ClassDB::bind_method(D_METHOD("load_project_defaults"), &BalmungHD2DProfile::load_project_defaults);
	ClassDB::bind_method(D_METHOD("set_projection_mode", "mode"), &BalmungHD2DProfile::set_projection_mode);
	ClassDB::bind_method(D_METHOD("get_projection_mode"), &BalmungHD2DProfile::get_projection_mode);
	ClassDB::bind_method(D_METHOD("set_orthographic_size", "size"), &BalmungHD2DProfile::set_orthographic_size);
	ClassDB::bind_method(D_METHOD("get_orthographic_size"), &BalmungHD2DProfile::get_orthographic_size);
	ClassDB::bind_method(D_METHOD("set_perspective_fov", "fov"), &BalmungHD2DProfile::set_perspective_fov);
	ClassDB::bind_method(D_METHOD("get_perspective_fov"), &BalmungHD2DProfile::get_perspective_fov);
	ClassDB::bind_method(D_METHOD("set_near_clip", "near_clip"), &BalmungHD2DProfile::set_near_clip);
	ClassDB::bind_method(D_METHOD("get_near_clip"), &BalmungHD2DProfile::get_near_clip);
	ClassDB::bind_method(D_METHOD("set_far_clip", "far_clip"), &BalmungHD2DProfile::set_far_clip);
	ClassDB::bind_method(D_METHOD("get_far_clip"), &BalmungHD2DProfile::get_far_clip);
	ClassDB::bind_method(D_METHOD("set_camera_pitch_degrees", "pitch"), &BalmungHD2DProfile::set_camera_pitch_degrees);
	ClassDB::bind_method(D_METHOD("get_camera_pitch_degrees"), &BalmungHD2DProfile::get_camera_pitch_degrees);
	ClassDB::bind_method(D_METHOD("set_camera_yaw_degrees", "yaw"), &BalmungHD2DProfile::set_camera_yaw_degrees);
	ClassDB::bind_method(D_METHOD("get_camera_yaw_degrees"), &BalmungHD2DProfile::get_camera_yaw_degrees);
	ClassDB::bind_method(D_METHOD("set_camera_distance", "distance"), &BalmungHD2DProfile::set_camera_distance);
	ClassDB::bind_method(D_METHOD("get_camera_distance"), &BalmungHD2DProfile::get_camera_distance);
	ClassDB::bind_method(D_METHOD("set_focus_height", "height"), &BalmungHD2DProfile::set_focus_height);
	ClassDB::bind_method(D_METHOD("get_focus_height"), &BalmungHD2DProfile::get_focus_height);
	ClassDB::bind_method(D_METHOD("set_pixels_per_unit", "pixels_per_unit"), &BalmungHD2DProfile::set_pixels_per_unit);
	ClassDB::bind_method(D_METHOD("get_pixels_per_unit"), &BalmungHD2DProfile::get_pixels_per_unit);
	ClassDB::bind_method(D_METHOD("set_layer_depth_step", "step"), &BalmungHD2DProfile::set_layer_depth_step);
	ClassDB::bind_method(D_METHOD("get_layer_depth_step"), &BalmungHD2DProfile::get_layer_depth_step);
	ClassDB::bind_method(D_METHOD("set_background_color", "color"), &BalmungHD2DProfile::set_background_color);
	ClassDB::bind_method(D_METHOD("get_background_color"), &BalmungHD2DProfile::get_background_color);
	ClassDB::bind_method(D_METHOD("set_ambient_color", "color"), &BalmungHD2DProfile::set_ambient_color);
	ClassDB::bind_method(D_METHOD("get_ambient_color"), &BalmungHD2DProfile::get_ambient_color);
	ClassDB::bind_method(D_METHOD("set_ambient_energy", "energy"), &BalmungHD2DProfile::set_ambient_energy);
	ClassDB::bind_method(D_METHOD("get_ambient_energy"), &BalmungHD2DProfile::get_ambient_energy);
	ClassDB::bind_method(D_METHOD("set_glow_enabled", "enabled"), &BalmungHD2DProfile::set_glow_enabled);
	ClassDB::bind_method(D_METHOD("is_glow_enabled"), &BalmungHD2DProfile::is_glow_enabled);
	ClassDB::bind_method(D_METHOD("set_glow_strength", "strength"), &BalmungHD2DProfile::set_glow_strength);
	ClassDB::bind_method(D_METHOD("get_glow_strength"), &BalmungHD2DProfile::get_glow_strength);
	ClassDB::bind_method(D_METHOD("set_glow_mix", "mix"), &BalmungHD2DProfile::set_glow_mix);
	ClassDB::bind_method(D_METHOD("get_glow_mix"), &BalmungHD2DProfile::get_glow_mix);
	ClassDB::bind_method(D_METHOD("set_fog_enabled", "enabled"), &BalmungHD2DProfile::set_fog_enabled);
	ClassDB::bind_method(D_METHOD("is_fog_enabled"), &BalmungHD2DProfile::is_fog_enabled);
	ClassDB::bind_method(D_METHOD("set_fog_density", "density"), &BalmungHD2DProfile::set_fog_density);
	ClassDB::bind_method(D_METHOD("get_fog_density"), &BalmungHD2DProfile::get_fog_density);
	ClassDB::bind_method(D_METHOD("set_fog_depth_begin", "begin"), &BalmungHD2DProfile::set_fog_depth_begin);
	ClassDB::bind_method(D_METHOD("get_fog_depth_begin"), &BalmungHD2DProfile::get_fog_depth_begin);
	ClassDB::bind_method(D_METHOD("set_fog_depth_end", "end"), &BalmungHD2DProfile::set_fog_depth_end);
	ClassDB::bind_method(D_METHOD("get_fog_depth_end"), &BalmungHD2DProfile::get_fog_depth_end);
	ClassDB::bind_method(D_METHOD("set_adjustments_enabled", "enabled"), &BalmungHD2DProfile::set_adjustments_enabled);
	ClassDB::bind_method(D_METHOD("is_adjustments_enabled"), &BalmungHD2DProfile::is_adjustments_enabled);
	ClassDB::bind_method(D_METHOD("set_adjustment_saturation", "saturation"), &BalmungHD2DProfile::set_adjustment_saturation);
	ClassDB::bind_method(D_METHOD("get_adjustment_saturation"), &BalmungHD2DProfile::get_adjustment_saturation);
	ClassDB::bind_method(D_METHOD("set_adjustment_contrast", "contrast"), &BalmungHD2DProfile::set_adjustment_contrast);
	ClassDB::bind_method(D_METHOD("get_adjustment_contrast"), &BalmungHD2DProfile::get_adjustment_contrast);
	ClassDB::bind_method(D_METHOD("set_directional_shadow_mode", "mode"), &BalmungHD2DProfile::set_directional_shadow_mode);
	ClassDB::bind_method(D_METHOD("get_directional_shadow_mode"), &BalmungHD2DProfile::get_directional_shadow_mode);
	ClassDB::bind_method(D_METHOD("set_shadow_max_distance", "distance"), &BalmungHD2DProfile::set_shadow_max_distance);
	ClassDB::bind_method(D_METHOD("get_shadow_max_distance"), &BalmungHD2DProfile::get_shadow_max_distance);
	ClassDB::bind_method(D_METHOD("set_shadow_blur", "blur"), &BalmungHD2DProfile::set_shadow_blur);
	ClassDB::bind_method(D_METHOD("get_shadow_blur"), &BalmungHD2DProfile::get_shadow_blur);
	ClassDB::bind_method(D_METHOD("set_light_pitch_degrees", "pitch"), &BalmungHD2DProfile::set_light_pitch_degrees);
	ClassDB::bind_method(D_METHOD("get_light_pitch_degrees"), &BalmungHD2DProfile::get_light_pitch_degrees);
	ClassDB::bind_method(D_METHOD("set_light_yaw_degrees", "yaw"), &BalmungHD2DProfile::set_light_yaw_degrees);
	ClassDB::bind_method(D_METHOD("get_light_yaw_degrees"), &BalmungHD2DProfile::get_light_yaw_degrees);
	ClassDB::bind_method(D_METHOD("get_layer_depth", "layer_index"), &BalmungHD2DProfile::get_layer_depth);
	ClassDB::bind_method(D_METHOD("snap_world_position", "position"), &BalmungHD2DProfile::snap_world_position);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "projection_mode", PROPERTY_HINT_ENUM, "Orthographic,Narrow Perspective"), "set_projection_mode", "get_projection_mode");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "orthographic_size", PROPERTY_HINT_RANGE, "1,256,0.1"), "set_orthographic_size", "get_orthographic_size");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "perspective_fov", PROPERTY_HINT_RANGE, "1,120,0.1"), "set_perspective_fov", "get_perspective_fov");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "near_clip", PROPERTY_HINT_RANGE, "0.001,32,0.001"), "set_near_clip", "get_near_clip");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "far_clip", PROPERTY_HINT_RANGE, "1,4096,0.1"), "set_far_clip", "get_far_clip");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "camera_pitch_degrees", PROPERTY_HINT_RANGE, "-89,89,0.1"), "set_camera_pitch_degrees", "get_camera_pitch_degrees");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "camera_yaw_degrees", PROPERTY_HINT_RANGE, "-180,180,0.1"), "set_camera_yaw_degrees", "get_camera_yaw_degrees");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "camera_distance", PROPERTY_HINT_RANGE, "0.1,512,0.1"), "set_camera_distance", "get_camera_distance");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "focus_height", PROPERTY_HINT_RANGE, "-64,64,0.01"), "set_focus_height", "get_focus_height");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "pixels_per_unit", PROPERTY_HINT_RANGE, "1,512,1"), "set_pixels_per_unit", "get_pixels_per_unit");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "layer_depth_step", PROPERTY_HINT_RANGE, "0.001,8,0.001"), "set_layer_depth_step", "get_layer_depth_step");
	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "background_color"), "set_background_color", "get_background_color");
	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "ambient_color"), "set_ambient_color", "get_ambient_color");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "ambient_energy", PROPERTY_HINT_RANGE, "0,8,0.01"), "set_ambient_energy", "get_ambient_energy");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "glow_enabled"), "set_glow_enabled", "is_glow_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "glow_strength", PROPERTY_HINT_RANGE, "0,4,0.01"), "set_glow_strength", "get_glow_strength");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "glow_mix", PROPERTY_HINT_RANGE, "0,1,0.01"), "set_glow_mix", "get_glow_mix");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "fog_enabled"), "set_fog_enabled", "is_fog_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "fog_density", PROPERTY_HINT_RANGE, "0,1,0.0001"), "set_fog_density", "get_fog_density");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "fog_depth_begin", PROPERTY_HINT_RANGE, "0,1024,0.1"), "set_fog_depth_begin", "get_fog_depth_begin");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "fog_depth_end", PROPERTY_HINT_RANGE, "0,4096,0.1"), "set_fog_depth_end", "get_fog_depth_end");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "adjustments_enabled"), "set_adjustments_enabled", "is_adjustments_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "adjustment_saturation", PROPERTY_HINT_RANGE, "0,4,0.01"), "set_adjustment_saturation", "get_adjustment_saturation");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "adjustment_contrast", PROPERTY_HINT_RANGE, "0,4,0.01"), "set_adjustment_contrast", "get_adjustment_contrast");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "directional_shadow_mode", PROPERTY_HINT_ENUM, "Disabled,Orthogonal,Parallel 2 Splits,Parallel 4 Splits"), "set_directional_shadow_mode", "get_directional_shadow_mode");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "shadow_max_distance", PROPERTY_HINT_RANGE, "1,4096,0.1"), "set_shadow_max_distance", "get_shadow_max_distance");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "shadow_blur", PROPERTY_HINT_RANGE, "0,8,0.01"), "set_shadow_blur", "get_shadow_blur");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "light_pitch_degrees", PROPERTY_HINT_RANGE, "-89,89,0.1"), "set_light_pitch_degrees", "get_light_pitch_degrees");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "light_yaw_degrees", PROPERTY_HINT_RANGE, "-180,180,0.1"), "set_light_yaw_degrees", "get_light_yaw_degrees");
}

void BalmungHD2DProfile::load_project_defaults() {
	if (!ProjectSettings::get_singleton()) {
		return;
	}

	projection_mode = ProjectionMode(int(GLOBAL_GET("balmung/hd2d/default_projection_mode")));
	orthographic_size = GLOBAL_GET("balmung/hd2d/default_orthographic_size");
	perspective_fov = GLOBAL_GET("balmung/hd2d/default_perspective_fov");
	camera_pitch_degrees = GLOBAL_GET("balmung/hd2d/default_camera_pitch_degrees");
	camera_yaw_degrees = GLOBAL_GET("balmung/hd2d/default_camera_yaw_degrees");
	camera_distance = GLOBAL_GET("balmung/hd2d/default_camera_distance");
	focus_height = GLOBAL_GET("balmung/hd2d/default_focus_height");
	pixels_per_unit = MAX(1.0f, float(GLOBAL_GET("balmung/hd2d/default_pixels_per_unit")));
	layer_depth_step = MAX(0.001f, float(GLOBAL_GET("balmung/hd2d/default_layer_depth_step")));
}

void BalmungHD2DProfile::set_projection_mode(ProjectionMode p_mode) { projection_mode = p_mode; }
BalmungHD2DProfile::ProjectionMode BalmungHD2DProfile::get_projection_mode() const { return projection_mode; }
void BalmungHD2DProfile::set_orthographic_size(float p_size) { orthographic_size = MAX(0.01f, p_size); }
float BalmungHD2DProfile::get_orthographic_size() const { return orthographic_size; }
void BalmungHD2DProfile::set_perspective_fov(float p_fov) { perspective_fov = CLAMP(p_fov, 1.0f, 179.0f); }
float BalmungHD2DProfile::get_perspective_fov() const { return perspective_fov; }
void BalmungHD2DProfile::set_near_clip(float p_near) { near_clip = MAX(0.001f, p_near); }
float BalmungHD2DProfile::get_near_clip() const { return near_clip; }
void BalmungHD2DProfile::set_far_clip(float p_far) { far_clip = MAX(near_clip + 0.01f, p_far); }
float BalmungHD2DProfile::get_far_clip() const { return far_clip; }
void BalmungHD2DProfile::set_camera_pitch_degrees(float p_pitch) { camera_pitch_degrees = CLAMP(p_pitch, -89.0f, 89.0f); }
float BalmungHD2DProfile::get_camera_pitch_degrees() const { return camera_pitch_degrees; }
void BalmungHD2DProfile::set_camera_yaw_degrees(float p_yaw) { camera_yaw_degrees = p_yaw; }
float BalmungHD2DProfile::get_camera_yaw_degrees() const { return camera_yaw_degrees; }
void BalmungHD2DProfile::set_camera_distance(float p_distance) { camera_distance = MAX(0.01f, p_distance); }
float BalmungHD2DProfile::get_camera_distance() const { return camera_distance; }
void BalmungHD2DProfile::set_focus_height(float p_height) { focus_height = p_height; }
float BalmungHD2DProfile::get_focus_height() const { return focus_height; }
void BalmungHD2DProfile::set_pixels_per_unit(float p_pixels_per_unit) { pixels_per_unit = MAX(1.0f, p_pixels_per_unit); }
float BalmungHD2DProfile::get_pixels_per_unit() const { return pixels_per_unit; }
void BalmungHD2DProfile::set_layer_depth_step(float p_step) { layer_depth_step = MAX(0.001f, p_step); }
float BalmungHD2DProfile::get_layer_depth_step() const { return layer_depth_step; }
void BalmungHD2DProfile::set_background_color(const Color &p_color) { background_color = p_color; }
Color BalmungHD2DProfile::get_background_color() const { return background_color; }
void BalmungHD2DProfile::set_ambient_color(const Color &p_color) { ambient_color = p_color; }
Color BalmungHD2DProfile::get_ambient_color() const { return ambient_color; }
void BalmungHD2DProfile::set_ambient_energy(float p_energy) { ambient_energy = MAX(0.0f, p_energy); }
float BalmungHD2DProfile::get_ambient_energy() const { return ambient_energy; }
void BalmungHD2DProfile::set_glow_enabled(bool p_enabled) { glow_enabled = p_enabled; }
bool BalmungHD2DProfile::is_glow_enabled() const { return glow_enabled; }
void BalmungHD2DProfile::set_glow_strength(float p_strength) { glow_strength = MAX(0.0f, p_strength); }
float BalmungHD2DProfile::get_glow_strength() const { return glow_strength; }
void BalmungHD2DProfile::set_glow_mix(float p_mix) { glow_mix = CLAMP(p_mix, 0.0f, 1.0f); }
float BalmungHD2DProfile::get_glow_mix() const { return glow_mix; }
void BalmungHD2DProfile::set_fog_enabled(bool p_enabled) { fog_enabled = p_enabled; }
bool BalmungHD2DProfile::is_fog_enabled() const { return fog_enabled; }
void BalmungHD2DProfile::set_fog_density(float p_density) { fog_density = MAX(0.0f, p_density); }
float BalmungHD2DProfile::get_fog_density() const { return fog_density; }
void BalmungHD2DProfile::set_fog_depth_begin(float p_begin) { fog_depth_begin = MAX(0.0f, p_begin); }
float BalmungHD2DProfile::get_fog_depth_begin() const { return fog_depth_begin; }
void BalmungHD2DProfile::set_fog_depth_end(float p_end) { fog_depth_end = MAX(fog_depth_begin + 0.01f, p_end); }
float BalmungHD2DProfile::get_fog_depth_end() const { return fog_depth_end; }
void BalmungHD2DProfile::set_adjustments_enabled(bool p_enabled) { adjustments_enabled = p_enabled; }
bool BalmungHD2DProfile::is_adjustments_enabled() const { return adjustments_enabled; }
void BalmungHD2DProfile::set_adjustment_saturation(float p_saturation) { adjustment_saturation = MAX(0.0f, p_saturation); }
float BalmungHD2DProfile::get_adjustment_saturation() const { return adjustment_saturation; }
void BalmungHD2DProfile::set_adjustment_contrast(float p_contrast) { adjustment_contrast = MAX(0.0f, p_contrast); }
float BalmungHD2DProfile::get_adjustment_contrast() const { return adjustment_contrast; }
void BalmungHD2DProfile::set_directional_shadow_mode(DirectionalShadowMode p_mode) { directional_shadow_mode = p_mode; }
BalmungHD2DProfile::DirectionalShadowMode BalmungHD2DProfile::get_directional_shadow_mode() const { return directional_shadow_mode; }
void BalmungHD2DProfile::set_shadow_max_distance(float p_distance) { shadow_max_distance = MAX(0.0f, p_distance); }
float BalmungHD2DProfile::get_shadow_max_distance() const { return shadow_max_distance; }
void BalmungHD2DProfile::set_shadow_blur(float p_blur) { shadow_blur = MAX(0.0f, p_blur); }
float BalmungHD2DProfile::get_shadow_blur() const { return shadow_blur; }
void BalmungHD2DProfile::set_light_pitch_degrees(float p_pitch) { light_pitch_degrees = CLAMP(p_pitch, -89.0f, 89.0f); }
float BalmungHD2DProfile::get_light_pitch_degrees() const { return light_pitch_degrees; }
void BalmungHD2DProfile::set_light_yaw_degrees(float p_yaw) { light_yaw_degrees = p_yaw; }
float BalmungHD2DProfile::get_light_yaw_degrees() const { return light_yaw_degrees; }

float BalmungHD2DProfile::get_layer_depth(int p_layer_index) const {
	return layer_depth_step * p_layer_index;
}

Vector3 BalmungHD2DProfile::snap_world_position(const Vector3 &p_position) const {
	const float world_step = 1.0f / MAX(1.0f, pixels_per_unit);
	Vector3 snapped = p_position;
	snapped.x = Math::snapped(snapped.x, world_step);
	snapped.y = Math::snapped(snapped.y, world_step);
	snapped.z = Math::snapped(snapped.z, layer_depth_step);
	return snapped;
}

BalmungHD2DProfile::BalmungHD2DProfile() {
	load_project_defaults();
}

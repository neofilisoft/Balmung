/**************************************************************************/
/*  balmung_hd2d_profile.h                                                */
/**************************************************************************/

#pragma once

#include "core/io/resource.h"
#include "scene/3d/node_3d.h"

class Camera3D;
class DirectionalLight3D;
class WorldEnvironment;

class BalmungHD2DProfile : public Resource {
	GDCLASS(BalmungHD2DProfile, Resource);

public:
	enum ProjectionMode {
		PROJECTION_ORTHOGRAPHIC = 0,
		PROJECTION_NARROW_PERSPECTIVE = 1,
	};

	enum DirectionalShadowMode {
		SHADOW_DISABLED = -1,
		SHADOW_ORTHOGONAL = 0,
		SHADOW_PARALLEL_2_SPLITS = 1,
		SHADOW_PARALLEL_4_SPLITS = 2,
	};

private:
	ProjectionMode projection_mode = PROJECTION_NARROW_PERSPECTIVE;
	float orthographic_size = 18.0f;
	float perspective_fov = 22.0f;
	float near_clip = 0.1f;
	float far_clip = 400.0f;
	float camera_pitch_degrees = -32.0f;
	float camera_yaw_degrees = 45.0f;
	float camera_distance = 24.0f;
	float focus_height = 2.5f;
	float pixels_per_unit = 32.0f;
	float layer_depth_step = 0.25f;
	Color background_color = Color(0.035, 0.04, 0.06);
	Color ambient_color = Color(0.68, 0.72, 0.82);
	float ambient_energy = 0.65f;
	bool glow_enabled = true;
	float glow_strength = 0.75f;
	float glow_mix = 0.12f;
	bool fog_enabled = true;
	float fog_density = 0.008f;
	float fog_depth_begin = 12.0f;
	float fog_depth_end = 96.0f;
	bool adjustments_enabled = true;
	float adjustment_saturation = 1.05f;
	float adjustment_contrast = 1.08f;
	DirectionalShadowMode directional_shadow_mode = SHADOW_PARALLEL_4_SPLITS;
	float shadow_max_distance = 160.0f;
	float shadow_blur = 0.6f;
	float light_pitch_degrees = -48.0f;
	float light_yaw_degrees = -32.0f;

protected:
	static void _bind_methods();

public:
	void load_project_defaults();

	void set_projection_mode(ProjectionMode p_mode);
	ProjectionMode get_projection_mode() const;

	void set_orthographic_size(float p_size);
	float get_orthographic_size() const;

	void set_perspective_fov(float p_fov);
	float get_perspective_fov() const;

	void set_near_clip(float p_near);
	float get_near_clip() const;

	void set_far_clip(float p_far);
	float get_far_clip() const;

	void set_camera_pitch_degrees(float p_pitch);
	float get_camera_pitch_degrees() const;

	void set_camera_yaw_degrees(float p_yaw);
	float get_camera_yaw_degrees() const;

	void set_camera_distance(float p_distance);
	float get_camera_distance() const;

	void set_focus_height(float p_height);
	float get_focus_height() const;

	void set_pixels_per_unit(float p_pixels_per_unit);
	float get_pixels_per_unit() const;

	void set_layer_depth_step(float p_step);
	float get_layer_depth_step() const;

	void set_background_color(const Color &p_color);
	Color get_background_color() const;

	void set_ambient_color(const Color &p_color);
	Color get_ambient_color() const;

	void set_ambient_energy(float p_energy);
	float get_ambient_energy() const;

	void set_glow_enabled(bool p_enabled);
	bool is_glow_enabled() const;

	void set_glow_strength(float p_strength);
	float get_glow_strength() const;

	void set_glow_mix(float p_mix);
	float get_glow_mix() const;

	void set_fog_enabled(bool p_enabled);
	bool is_fog_enabled() const;

	void set_fog_density(float p_density);
	float get_fog_density() const;

	void set_fog_depth_begin(float p_begin);
	float get_fog_depth_begin() const;

	void set_fog_depth_end(float p_end);
	float get_fog_depth_end() const;

	void set_adjustments_enabled(bool p_enabled);
	bool is_adjustments_enabled() const;

	void set_adjustment_saturation(float p_saturation);
	float get_adjustment_saturation() const;

	void set_adjustment_contrast(float p_contrast);
	float get_adjustment_contrast() const;

	void set_directional_shadow_mode(DirectionalShadowMode p_mode);
	DirectionalShadowMode get_directional_shadow_mode() const;

	void set_shadow_max_distance(float p_distance);
	float get_shadow_max_distance() const;

	void set_shadow_blur(float p_blur);
	float get_shadow_blur() const;

	void set_light_pitch_degrees(float p_pitch);
	float get_light_pitch_degrees() const;

	void set_light_yaw_degrees(float p_yaw);
	float get_light_yaw_degrees() const;

	float get_layer_depth(int p_layer_index) const;
	Vector3 snap_world_position(const Vector3 &p_position) const;

	BalmungHD2DProfile();
};

VARIANT_ENUM_CAST(BalmungHD2DProfile::ProjectionMode);
VARIANT_ENUM_CAST(BalmungHD2DProfile::DirectionalShadowMode);

class BalmungHD2DRig : public Node3D {
	GDCLASS(BalmungHD2DRig, Node3D);

	Ref<BalmungHD2DProfile> profile;
	NodePath camera_path;
	NodePath world_environment_path;
	NodePath directional_light_path;
	bool auto_apply = true;
	bool apply_in_editor = true;

	static void _bind_methods();
	void _notification(int p_what);

	Camera3D *_resolve_camera() const;
	WorldEnvironment *_resolve_world_environment() const;
	DirectionalLight3D *_resolve_directional_light() const;

public:
	void set_profile(const Ref<BalmungHD2DProfile> &p_profile);
	Ref<BalmungHD2DProfile> get_profile() const;

	void set_camera_path(const NodePath &p_path);
	NodePath get_camera_path() const;

	void set_world_environment_path(const NodePath &p_path);
	NodePath get_world_environment_path() const;

	void set_directional_light_path(const NodePath &p_path);
	NodePath get_directional_light_path() const;

	void set_auto_apply(bool p_enabled);
	bool is_auto_apply_enabled() const;

	void set_apply_in_editor(bool p_enabled);
	bool is_apply_in_editor_enabled() const;

	void apply_profile();
	float get_layer_depth(int p_layer_index) const;
	Vector3 snap_world_position(const Vector3 &p_position) const;

	PackedStringArray get_configuration_warnings() const override;
};

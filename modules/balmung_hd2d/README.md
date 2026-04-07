# Balmung HD-2D Module

`balmung_hd2d` is a foundation module for building Balmung on top of Redot's existing 3D pipeline.

Current scope:
- `BalmungHD2DProfile` resource for camera/depth/fog/glow/shadow defaults
- `BalmungHD2DRig` node for applying the profile to:
  - `Camera3D`
  - `WorldEnvironment`
  - `DirectionalLight3D`

Why this exists:
- Keep Redot's renderer intact
- Layer Balmung-specific HD-2D rules on top
- Reuse one 3D pipeline for 3D worlds, lit sprites, fog, glow, and deterministic layer depth

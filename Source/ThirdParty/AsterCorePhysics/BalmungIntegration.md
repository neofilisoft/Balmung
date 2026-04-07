# Balmung AsterCorePhysics Foundation

This folder vendors the AsterCorePhysics source tree for future Balmung backend integration.

Current scope:
- ships the core AsterCore source tree as a third-party dependency
- exposes a build module named `AsterCorePhysics`
- does not replace the default PhysX runtime backend yet

Recommended next step:
- implement `PhysicsBackendAsterCore.*` inside `Source/Engine/Physics`
- map Balmung rigid bodies, colliders, joints, scenes, and materials to AsterCore APIs
- add a runtime/editor project setting to choose the backend explicitly

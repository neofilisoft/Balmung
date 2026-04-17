# Balmung Engine Production Architecture

This is the target repository architecture for `Balmung Engine` as a production-grade, commercial, general-purpose engine.

Design stance:

- `Balmung Engine` is not a voxel engine. Voxel/terrain is one world subsystem.
- `Overworld` is a game/sample project built on top of the engine, initially seeded with content from `C:\Users\BEST\Desktop\Minecraft-main`.
- `Editor`, `Runtime`, `Tools`, and `Game` must stay physically separate in the repo and logically separate in the build graph.
- `Physics` is plugin-based. `AsterCorePhysics-3.1` is the primary backend, but the engine-facing API never hard-codes AsterCore/PhysX/Jolt/Havok types.

## Target Repository Tree

```text
BalmungEngine/
|- CMakeLists.txt
|- Directory.Build.props
|- README.md
|- .editorconfig
|- .gitattributes
|- Build/
|  |- CMake/
|  |- Presets/
|  |- Toolchains/
|  `- Packaging/
|- Docs/
|  |- Architecture/
|  |- Editor/
|  |- Runtime/
|  |- Scripting/
|  `- AssetPipeline/
|- Engine/
|  |- Core/
|  |  |- Base/
|  |  |- Containers/
|  |  |- Math/
|  |  |- Memory/
|  |  |- Platform/
|  |  |- Profiling/
|  |  |- Reflection/
|  |  `- Threading/
|  |- ECS/
|  |  |- Archetypes/
|  |  |- Components/
|  |  |- Queries/
|  |  |- Scheduler/
|  |  `- Serialization/
|  |- Asset/
|  |  |- Database/
|  |  |- Importers/
|  |  |- Cookers/
|  |  |- Registry/
|  |  `- Runtime/
|  |- Scene/
|  |  |- Graph/
|  |  |- Prefabs/
|  |  |- Streaming/
|  |  `- World/
|  |- Renderer/
|  |  |- FrameGraph/
|  |  |- RenderGraph/
|  |  |- Resources/
|  |  |- Scene2D/
|  |  |- Scene3D/
|  |  |- Shaders/
|  |  `- Backends/
|  |     |- Vulkan/
|  |     |- DX12/
|  |     `- OpenGL/
|  |- Physics/
|  |  |- Interfaces/
|  |  |- Backends/
|  |  |  |- AsterCore/
|  |  |  |- Jolt/
|  |  |  |- PhysX/
|  |  |  `- Null/
|  |  |- Cooking/
|  |  `- DebugDraw/
|  |- Audio/
|  |  |- Mixer/
|  |  |- Graph/
|  |  |- Spatial/
|  |  `- Backends/
|  |- Input/
|  |  |- Devices/
|  |  |- Actions/
|  |  `- Mapping/
|  |- Animation/
|  |  |- Graph/
|  |  |- Rigging/
|  |  `- Runtime/
|  |- Scripting/
|  |  |- Common/
|  |  |- Native/
|  |  |- Managed/
|  |  |- Bridge/
|  |  `- HotReload/
|  |- Networking/
|  |  |- Replication/
|  |  |- RPC/
|  |  `- Transport/
|  |- UI/
|  |  |- Runtime2D/
|  |  |- Runtime3D/
|  |  `- Styling/
|  |- Terrain/
|  |  |- Heightfield/
|  |  |- Voxels/
|  |  `- Streaming/
|  `- Runtime/
|     |- Application/
|     |- Game/
|     `- Modules/
|- Editor/
|  |- App/
|  |- Panels/
|  |- Viewports/
|  |- Inspectors/
|  |- ContentBrowser/
|  |- SceneTools/
|  |- Gizmos/
|  |- Debugger/
|  |- Profiler/
|  `- AssetAuthoring/
|- Programs/
|  |- BalmungEditor/
|  |- BalmungGame/
|  |- BalmungHeadless/
|  |- BalmungCooker/
|  `- BalmungShaderCompiler/
|- Projects/
|  |- Overworld/
|  |  |- Content/
|  |  |- Scripts/
|  |  |- Config/
|  |  `- Overworld.balmungproj
|  `- Samples/
|- Tests/
|  |- Unit/
|  |- Integration/
|  |- Performance/
|  `- Soak/
|- Tools/
|  |- BuildTool/
|  |- AssetTool/
|  |- ProjectGen/
|  |- ScriptingGen/
|  `- Diagnostics/
`- ThirdParty/
   |- imgui/
   |- ImGuizmo/
   |- spdlog/
   |- fmt/
   |- mimalloc/
   |- tracy/
   |- EnTT/
   |- bgfx_or_custom_rhi_helpers/
   |- shaderc/
   |- spirv-cross/
   |- spirv-tools/
   |- glslang/
   |- volk/
   |- VulkanMemoryAllocator/
   |- SDL3/
   |- OpenAL-Soft_or_miniaudio/
   |- stb/
   |- zstd/
   |- xxHash/
   |- yaml-cpp/
   |- simdjson/
   |- flatbuffers/
   |- meshoptimizer/
   |- mikktspace/
   |- assimp/
   |- basisu/
   |- KTX-Software/
   |- AsterCorePhysics/
   |- mono_or_coreclr_loader/
   `- Catch2/
```

## Core Subsystems And Responsibilities

### `Core`

Responsibilities:

- platform abstraction
- memory allocators and ownership primitives
- job system and synchronization
- logging, profiling, assertions, diagnostics
- math, transforms, SIMD helpers
- reflection metadata and type registration

Production decision:

- `Core` must not know about gameplay, editor, physics, or rendering policy.
- `Core` is the only layer allowed to define allocator policy and threading primitives.

### `ECS`

Responsibilities:

- entity identity, archetype storage, query execution
- component lifecycle
- scheduling boundaries between game logic, physics sync, render sync, and scripting
- deterministic serialization layout for savegames and editor undo/redo

Production decision:

- archetype ECS, not a Unity-style object/component runtime as the truth source
- scene graph is a view on ECS data, not the ownership model

### `Renderer`

Responsibilities:

- API-agnostic RHI over Vulkan and DX12, OpenGL fallback
- render graph / frame graph
- unified 2D + 3D passes in one frame
- materials, shader permutations, texture streaming
- debug rendering, editor overlays, gizmo rendering

Production decision:

- never split engine into “2D mode” and “3D mode”
- 2D is just a render feature path using the same frame graph, resources, camera stack, lighting hooks, and asset system

### `Physics`

Responsibilities:

- engine-facing simulation API
- backend adapters
- scene queries
- collider and cooked collision assets
- runtime step scheduling and sync with ECS transforms
- debug draw and capture hooks

Production decision:

- engine API is backend-neutral
- `AsterCorePhysics-3.1` is first-class and default
- PhysX, Jolt, Havok are adapters, not architectural branches

### `Audio`

Responsibilities:

- runtime mixing
- buses, routing, effects, streaming
- spatialization
- editor auditioning and waveform/analysis views

Production decision:

- audio is its own graph subsystem, not just “play sound file”

### `Input`

Responsibilities:

- device abstraction
- action maps
- context switching between gameplay/editor/UI
- rebinding and serialization

Production decision:

- input is action-based from day one
- raw key polling is kept only at the platform edge

### `Scripting`

Responsibilities:

- managed runtime host for C#
- native C++ gameplay components
- ABI-stable C bridge between runtime/editor and managed side
- hot reload orchestration
- generated bindings and internal call registration

Production decision:

- do not expose C++ ABI directly to C#
- use generated C-facing bridge and stable handles
- allow C++ native gameplay code for high-performance systems and server paths

### `Asset`

Responsibilities:

- source asset import
- cooked binary asset format
- dependency graph
- import settings
- asset database GUIDs and content-addressable metadata
- hot reload into editor/runtime

Production decision:

- source formats stay external and editable
- runtime never loads loose PSD/FBX/PNG as its truth source in shipping
- shipping runtime loads cooked binary assets only

### `Scene`

Responsibilities:

- world partition / streaming
- prefab instances
- scene save/load
- editor selection, hierarchy, and diff support

Production decision:

- `Scene` owns world composition, not component storage
- world streaming is a first-class concern, not an afterthought

### `Editor`

Responsibilities:

- content authoring
- world editing
- material/animation/physics asset inspection
- profiling/debugging/capture viewers
- import pipeline control

Production decision:

- editor is a separate app target and separate module layer
- editor-only code never leaks into shipping runtime binaries

## Build Order: What To Build First

### 1. `Core`

Why first:

- every other subsystem depends on allocator policy, threading, platform, containers, logging, and profiling
- bad core decisions poison the entire engine

### 2. `Asset`

Why second:

- renderer, physics, audio, and editor all need a stable asset identity and import path
- without AssetDB, every subsystem invents its own loading model and the engine becomes impossible to maintain

### 3. `Renderer RHI + RenderGraph`

Why third:

- editor, scene tooling, runtime rendering, debug visualization, and 2D/3D coexistence all depend on this
- build the graphics boundary before higher-level rendering features

### 4. `Scene + ECS`

Why fourth:

- once rendering exists, you need a robust world model and data ownership model
- ECS must be designed with renderer and physics sync in mind, not added later

### 5. `Physics`

Why fifth:

- physics should plug into ECS and asset cooking cleanly
- if you build physics too early, you hard-code scene/object assumptions into it

### 6. `Scripting`

Why sixth:

- scripting needs stable engine handles, scene access, reflection metadata, and asset identities
- otherwise bindings churn constantly and hot reload becomes unstable

### 7. `Input`, `Audio`, `Animation`, `UI`

Why seventh:

- these depend on stable runtime lifetime and asset loading
- they can progress in parallel once the first six are stable

### 8. `Editor`

Why eighth:

- start minimal editor work earlier for smoke testing, but do not attempt a full editor before the runtime foundations are stable
- the editor should consume engine systems, not force their architecture prematurely

## Third-Party Libraries To Integrate

These are production picks, not academic options.

### Mandatory Foundation

- `fmt`
  - formatting without iostream overhead and with clear API
- `spdlog`
  - structured logging and sinks
- `mimalloc`
  - good default allocator for tooling/runtime experiments
- `tracy`
  - essential for commercial performance work
- `Catch2`
  - fast test authoring for engine unit tests

### ECS / Data

- `EnTT`
  - mature, pragmatic ECS and signal/meta utilities
  - still worth using even if Balmung later replaces parts with custom archetype storage
- `flatbuffers`
  - hot data interchange and stable binary schemas
- `simdjson`
  - tooling/editor-side JSON parsing at scale
- `yaml-cpp`
  - human-authored config and pipeline manifests

### Rendering

- `volk`
  - Vulkan loader bootstrap
- `VulkanMemoryAllocator`
  - production-grade Vulkan memory management
- `glslang`
  - shader front-end and SPIR-V generation
- `spirv-tools`
  - validation and optimization
- `spirv-cross`
  - cross-compile path for shader reflection/output targets
- `shaderc`
  - practical compile integration path
- `ImGui`
  - editor UI foundation
- `ImGuizmo`
  - transform gizmos in editor
- `meshoptimizer`
  - required for mesh import/runtime efficiency
- `mikktspace`
  - tangent basis consistency

### Assets

- `stb`
  - low-friction image tooling for importers
- `assimp`
  - good starting point for mesh/scene import
- `basisu` and `KTX-Software`
  - texture compression/transcoding pipeline
- `zstd`
  - fast and production-proven asset compression
- `xxHash`
  - fast content hashing

### Input / Windowing / Audio

- `SDL3`
  - better cross-platform runtime window/input bootstrap than hand-rolling everything
- `OpenAL Soft` or `miniaudio`
  - for initial runtime audio backend

### Scripting

- `CoreCLR hostfxr` for modern .NET
  - primary long-term managed runtime
- `Mono`
  - compatibility/runtime fallback during transition

### Physics

- `AsterCorePhysics-3.1`
  - default physics backend and SDK-facing middleware path
- `Jolt`
  - strong modern alternative backend
- `PhysX`
  - compatibility path where existing pipelines require it
- `Havok`
  - enterprise backend option through adapter boundary only

## Hard Decisions

These are deliberate and should not be diluted:

- `Editor` is not the engine. It is a client of the engine.
- `Overworld` is not the engine testbed forever. It is an early game project riding on the engine.
- `2D` and `3D` must share the same asset pipeline, renderer, ECS, scripting, and scene streaming model.
- `Physics` must stay plugable forever. No direct AsterCore types in gameplay components.
- `Scripting` must cross a stable C ABI layer. No direct managed-to-C++ ABI assumptions.
- `Asset cooking` is non-negotiable for shipping builds.

## Immediate Migration Strategy For This Repo

1. Keep the existing `Source/Engine`, `Source/Editor`, and build tool layout alive.
2. Introduce backend-agnostic subsystem interfaces alongside legacy code rather than rewriting everything in one shot.
3. Move physics first because the current tree is clearly PhysX-shaped and that is your highest-risk coupling.
4. Add `Projects/Overworld` as the sample/game target that consumes engine modules and temporarily uses `Minecraft-main` assets.
5. Once physics and asset interfaces are stable, refactor scene/runtime/editor onto the new boundary layer incrementally.

// AsterCore Physics Library (https://github.com/jrouwe/AsterCorePhysics)
// SPDX-FileCopyrightText: 2021 Jorrit Rouwe
// SPDX-License-Identifier: MIT

#pragma once

ACPH_NAMESPACE_BEGIN

class Vec3;
class DVec3;
class Vec4;
class UVec4;
class BVec16;
class Quat;
class Mat44;
class DMat44;

// Types to use for passing arguments to functions
using Vec3Arg = const Vec3;
#ifdef ACPH_USE_AVX
	using DVec3Arg = const DVec3;
#else
	using DVec3Arg = const DVec3 &;
#endif
using Vec4Arg = const Vec4;
using UVec4Arg = const UVec4;
using BVec16Arg = const BVec16;
using QuatArg = const Quat;
using Mat44Arg = const Mat44 &;
using DMat44Arg = const DMat44 &;

ACPH_NAMESPACE_END

// AsterCore Physics Library (https://github.com/jrouwe/AsterCorePhysics)
// SPDX-FileCopyrightText: 2021 Jorrit Rouwe
// SPDX-License-Identifier: MIT

#pragma once

ACPH_NAMESPACE_BEGIN

/// The constant \f$\pi\f$
static constexpr float ACPH_PI = 3.14159265358979323846f;

/// A large floating point value which, when squared, is still much smaller than FLT_MAX
static constexpr float cLargeFloat = 1.0e15f;

/// Convert a value from degrees to radians
ACPH_INLINE constexpr float DegreesToRadians(float inV)
{
	return inV * (ACPH_PI / 180.0f);
}

/// Convert a value from radians to degrees
ACPH_INLINE constexpr float RadiansToDegrees(float inV)
{
	return inV * (180.0f / ACPH_PI);
}

/// Convert angle in radians to the range \f$[-\pi, \pi]\f$
inline float CenterAngleAroundZero(float inV)
{
	if (inV < -ACPH_PI)
	{
		do
			inV += 2.0f * ACPH_PI;
		while (inV < -ACPH_PI);
	}
	else if (inV > ACPH_PI)
	{
		do
			inV -= 2.0f * ACPH_PI;
		while (inV > ACPH_PI);
	}
	ACPH_ASSERT(inV >= -ACPH_PI && inV <= ACPH_PI);
	return inV;
}

/// Clamp a value between two values
template <typename T>
ACPH_INLINE constexpr T Clamp(T inV, T inMin, T inMax)
{
	return min(max(inV, inMin), inMax);
}

/// Square a value
template <typename T>
ACPH_INLINE constexpr T Square(T inV)
{
	return inV * inV;
}

/// Returns \f$inV^3\f$.
template <typename T>
ACPH_INLINE constexpr T Cubed(T inV)
{
	return inV * inV * inV;
}

/// Get the sign of a value
template <typename T>
ACPH_INLINE constexpr T Sign(T inV)
{
	return inV < 0? T(-1) : T(1);
}

/// Check if inV is a power of 2
template <typename T>
constexpr bool IsPowerOf2(T inV)
{
	return inV > 0 && (inV & (inV - 1)) == 0;
}

/// Align inV up to the next inAlignment bytes
template <typename T>
inline T AlignUp(T inV, uint64 inAlignment)
{
	ACPH_ASSERT(IsPowerOf2(inAlignment));
	return T((uint64(inV) + inAlignment - 1) & ~(inAlignment - 1));
}

/// Check if inV is inAlignment aligned
template <typename T>
inline bool IsAligned(T inV, uint64 inAlignment)
{
	ACPH_ASSERT(IsPowerOf2(inAlignment));
	return (uint64(inV) & (inAlignment - 1)) == 0;
}

/// Compute number of trailing zero bits (how many low bits are zero)
inline uint CountTrailingZeros(uint32 inValue)
{
#if defined(ACPH_CPU_X86) || defined(ACPH_CPU_WASM)
	#if defined(ACPH_USE_TZCNT)
		return _tzcnt_u32(inValue);
	#elif defined(ACPH_COMPILER_MSVC)
		if (inValue == 0)
			return 32;
		unsigned long result;
		_BitScanForward(&result, inValue);
		return result;
	#else
		if (inValue == 0)
			return 32;
		return __builtin_ctz(inValue);
	#endif
#elif defined(ACPH_CPU_ARM)
	#if defined(ACPH_COMPILER_MSVC)
		if (inValue == 0)
			return 32;
		unsigned long result;
		_BitScanForward(&result, inValue);
		return result;
	#else
		if (inValue == 0)
			return 32;
		return __builtin_ctz(inValue);
	#endif
#elif defined(ACPH_CPU_E2K) || defined(ACPH_CPU_RISCV) || defined(ACPH_CPU_PPC) || defined(ACPH_CPU_LOONGARCH)
	return inValue ? __builtin_ctz(inValue) : 32;
#else
	#error Undefined
#endif
}

/// Compute the number of leading zero bits (how many high bits are zero)
inline uint CountLeadingZeros(uint32 inValue)
{
#if defined(ACPH_CPU_X86) || defined(ACPH_CPU_WASM)
	#if defined(ACPH_USE_LZCNT)
		return _lzcnt_u32(inValue);
	#elif defined(ACPH_COMPILER_MSVC)
		if (inValue == 0)
			return 32;
		unsigned long result;
		_BitScanReverse(&result, inValue);
		return 31 - result;
	#else
		if (inValue == 0)
			return 32;
		return __builtin_clz(inValue);
	#endif
#elif defined(ACPH_CPU_ARM)
	#if defined(ACPH_COMPILER_MSVC)
		return _CountLeadingZeros(inValue);
	#else
		return __builtin_clz(inValue);
	#endif
#elif defined(ACPH_CPU_E2K) || defined(ACPH_CPU_RISCV) || defined(ACPH_CPU_PPC) || defined(ACPH_CPU_LOONGARCH)
	return inValue ? __builtin_clz(inValue) : 32;
#else
	#error Undefined
#endif
}

/// Count the number of 1 bits in a value
inline uint CountBits(uint32 inValue)
{
#if defined(ACPH_COMPILER_CLANG) || defined(ACPH_COMPILER_GCC)
	return __builtin_popcount(inValue);
#elif defined(ACPH_COMPILER_MSVC)
	#if defined(ACPH_USE_SSE4_2)
		return _mm_popcnt_u32(inValue);
	#elif defined(ACPH_USE_NEON) && (_MSC_VER >= 1930) // _CountOneBits not available on MSVC2019
		return _CountOneBits(inValue);
	#else
		inValue = inValue - ((inValue >> 1) & 0x55555555);
		inValue = (inValue & 0x33333333) + ((inValue >> 2) & 0x33333333);
		inValue = (inValue + (inValue >> 4)) & 0x0F0F0F0F;
		return (inValue * 0x01010101) >> 24;
	#endif
#else
	#error Undefined
#endif
}

/// Get the next higher power of 2 of a value, or the value itself if the value is already a power of 2
inline uint32 GetNextPowerOf2(uint32 inValue)
{
	return inValue <= 1? uint32(1) : uint32(1) << (32 - CountLeadingZeros(inValue - 1));
}

// Simple implementation of C++20 std::bit_cast (unfortunately not constexpr)
template <class To, class From>
ACPH_INLINE To BitCast(const From &inValue)
{
	static_assert(std::is_trivially_constructible_v<To>);
	static_assert(sizeof(From) == sizeof(To));

	union FromTo
	{
		To			mTo;
		From		mFrom;
	};

	FromTo convert;
	convert.mFrom = inValue;
	return convert.mTo;
}

ACPH_NAMESPACE_END

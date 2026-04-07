// AsterCore Physics Library (https://github.com/jrouwe/AsterCorePhysics)
// SPDX-FileCopyrightText: 2021 Jorrit Rouwe
// SPDX-License-Identifier: MIT

#pragma once

#include <AsterCore/Math/MathTypes.h>

ACPH_NAMESPACE_BEGIN

/// Holds a 4x4 matrix of floats, but supports also operations on the 3x3 upper left part of the matrix.
class [[nodiscard]] alignas(ACPH_VECTOR_ALIGNMENT) Mat44
{
public:
	ACPH_OVERRIDE_NEW_DELETE

	// Underlying column type
	using Type = Vec4::Type;

	// Argument type
	using ArgType = Mat44Arg;

	/// Constructor
								Mat44() = default; ///< Intentionally not initialized for performance reasons
	ACPH_INLINE					Mat44(Vec4Arg inC1, Vec4Arg inC2, Vec4Arg inC3, Vec4Arg inC4);
	ACPH_INLINE					Mat44(Vec4Arg inC1, Vec4Arg inC2, Vec4Arg inC3, Vec3Arg inC4);
								Mat44(const Mat44 &inM2) = default;
	Mat44 &						operator = (const Mat44 &inM2) = default;
	ACPH_INLINE					Mat44(Type inC1, Type inC2, Type inC3, Type inC4);

	/// Zero matrix
	static ACPH_INLINE Mat44		sZero();

	/// Identity matrix
	static ACPH_INLINE Mat44		sIdentity();

	/// Matrix filled with NaN's
	static ACPH_INLINE Mat44		sNaN();

	/// Load 16 floats from memory
	static ACPH_INLINE Mat44		sLoadFloat4x4(const Float4 *inV);

	/// Load 16 floats from memory, 16 bytes aligned
	static ACPH_INLINE Mat44		sLoadFloat4x4Aligned(const Float4 *inV);

	/// Rotate around X, Y or Z axis (angle in radians)
	static ACPH_INLINE Mat44		sRotationX(float inX);
	static ACPH_INLINE Mat44		sRotationY(float inY);
	static ACPH_INLINE Mat44		sRotationZ(float inZ);

	/// Rotate around arbitrary axis
	static ACPH_INLINE Mat44		sRotation(Vec3Arg inAxis, float inAngle);

	/// Rotate from quaternion
	static ACPH_INLINE Mat44		sRotation(QuatArg inQuat);

	/// Get matrix that translates
	static ACPH_INLINE Mat44		sTranslation(Vec3Arg inV);

	/// Get matrix that rotates and translates
	static ACPH_INLINE Mat44		sRotationTranslation(QuatArg inR, Vec3Arg inT);

	/// Get inverse matrix of sRotationTranslation
	static ACPH_INLINE Mat44		sInverseRotationTranslation(QuatArg inR, Vec3Arg inT);

	/// Get matrix that scales uniformly
	static ACPH_INLINE Mat44		sScale(float inScale);

	/// Get matrix that scales (produces a matrix with (inV, 1) on its diagonal)
	static ACPH_INLINE Mat44		sScale(Vec3Arg inV);

	/// Get outer product of inV and inV2 (equivalent to \f$inV1 \otimes inV2\f$)
	static ACPH_INLINE Mat44		sOuterProduct(Vec3Arg inV1, Vec3Arg inV2);

	/// Get matrix that represents a cross product \f$A \times B = \text{sCrossProduct}(A) \: B\f$
	static ACPH_INLINE Mat44		sCrossProduct(Vec3Arg inV);

	/// Returns matrix ML so that \f$ML(q) \: p = q \: p\f$ (where p and q are quaternions)
	static ACPH_INLINE Mat44		sQuatLeftMultiply(QuatArg inQ);

	/// Returns matrix MR so that \f$MR(q) \: p = p \: q\f$ (where p and q are quaternions)
	static ACPH_INLINE Mat44		sQuatRightMultiply(QuatArg inQ);

	/// Returns a look at matrix that transforms from world space to view space
	/// @param inPos Position of the camera
	/// @param inTarget Target of the camera
	/// @param inUp Up vector
	static ACPH_INLINE Mat44		sLookAt(Vec3Arg inPos, Vec3Arg inTarget, Vec3Arg inUp);

	/// Returns a right-handed perspective projection matrix
	static ACPH_INLINE Mat44		sPerspective(float inFovY, float inAspect, float inNear, float inFar);

	/// Get float component by element index
	ACPH_INLINE float			operator () (uint inRow, uint inColumn) const			{ ACPH_ASSERT(inRow < 4); ACPH_ASSERT(inColumn < 4); return mCol[inColumn].mF32[inRow]; }
	ACPH_INLINE float &			operator () (uint inRow, uint inColumn)					{ ACPH_ASSERT(inRow < 4); ACPH_ASSERT(inColumn < 4); return mCol[inColumn].mF32[inRow]; }

	/// Comparison
	ACPH_INLINE bool				operator == (Mat44Arg inM2) const;
	ACPH_INLINE bool				operator != (Mat44Arg inM2) const						{ return !(*this == inM2); }

	/// Test if two matrices are close
	ACPH_INLINE bool				IsClose(Mat44Arg inM2, float inMaxDistSq = 1.0e-12f) const;

	/// Multiply matrix by matrix
	ACPH_INLINE Mat44			operator * (Mat44Arg inM) const;

	/// Multiply vector by matrix
	ACPH_INLINE Vec3				operator * (Vec3Arg inV) const;
	ACPH_INLINE Vec4				operator * (Vec4Arg inV) const;

	/// Multiply vector by only 3x3 part of the matrix
	ACPH_INLINE Vec3				Multiply3x3(Vec3Arg inV) const;

	/// Multiply vector by only 3x3 part of the transpose of the matrix (\f$result = this^T \: inV\f$)
	ACPH_INLINE Vec3				Multiply3x3Transposed(Vec3Arg inV) const;

	/// Multiply 3x3 matrix by 3x3 matrix
	ACPH_INLINE Mat44			Multiply3x3(Mat44Arg inM) const;

	/// Multiply transpose of 3x3 matrix by 3x3 matrix (\f$result = this^T \: inM\f$)
	ACPH_INLINE Mat44			Multiply3x3LeftTransposed(Mat44Arg inM) const;

	/// Multiply 3x3 matrix by the transpose of a 3x3 matrix (\f$result = this \: inM^T\f$)
	ACPH_INLINE Mat44			Multiply3x3RightTransposed(Mat44Arg inM) const;

	/// Multiply matrix with float
	ACPH_INLINE Mat44			operator * (float inV) const;
	friend ACPH_INLINE Mat44		operator * (float inV, Mat44Arg inM)					{ return inM * inV; }

	/// Multiply matrix with float
	ACPH_INLINE Mat44 &			operator *= (float inV);

	/// Per element addition of matrix
	ACPH_INLINE Mat44			operator + (Mat44Arg inM) const;

	/// Negate
	ACPH_INLINE Mat44			operator - () const;

	/// Per element subtraction of matrix
	ACPH_INLINE Mat44			operator - (Mat44Arg inM) const;

	/// Per element addition of matrix
	ACPH_INLINE Mat44 &			operator += (Mat44Arg inM);

	/// Access to the columns
	ACPH_INLINE Vec3				GetAxisX() const										{ return Vec3(mCol[0]); }
	ACPH_INLINE void				SetAxisX(Vec3Arg inV)									{ mCol[0] = Vec4(inV, 0.0f); }
	ACPH_INLINE Vec3				GetAxisY() const										{ return Vec3(mCol[1]); }
	ACPH_INLINE void				SetAxisY(Vec3Arg inV)									{ mCol[1] = Vec4(inV, 0.0f); }
	ACPH_INLINE Vec3				GetAxisZ() const										{ return Vec3(mCol[2]); }
	ACPH_INLINE void				SetAxisZ(Vec3Arg inV)									{ mCol[2] = Vec4(inV, 0.0f); }
	ACPH_INLINE Vec3				GetTranslation() const									{ return Vec3(mCol[3]); }
	ACPH_INLINE void				SetTranslation(Vec3Arg inV)								{ mCol[3] = Vec4(inV, 1.0f); }
	ACPH_INLINE Vec3				GetDiagonal3() const									{ return Vec3(mCol[0][0], mCol[1][1], mCol[2][2]); }
	ACPH_INLINE void				SetDiagonal3(Vec3Arg inV)								{ mCol[0][0] = inV.GetX(); mCol[1][1] = inV.GetY(); mCol[2][2] = inV.GetZ(); }
	ACPH_INLINE Vec4				GetDiagonal4() const									{ return Vec4(mCol[0][0], mCol[1][1], mCol[2][2], mCol[3][3]); }
	ACPH_INLINE void				SetDiagonal4(Vec4Arg inV)								{ mCol[0][0] = inV.GetX(); mCol[1][1] = inV.GetY(); mCol[2][2] = inV.GetZ(); mCol[3][3] = inV.GetW(); }
	ACPH_INLINE Vec3				GetColumn3(uint inCol) const							{ ACPH_ASSERT(inCol < 4); return Vec3(mCol[inCol]); }
	ACPH_INLINE void				SetColumn3(uint inCol, Vec3Arg inV)						{ ACPH_ASSERT(inCol < 4); mCol[inCol] = Vec4(inV, inCol == 3? 1.0f : 0.0f); }
	ACPH_INLINE Vec4				GetColumn4(uint inCol) const							{ ACPH_ASSERT(inCol < 4); return mCol[inCol]; }
	ACPH_INLINE void				SetColumn4(uint inCol, Vec4Arg inV)						{ ACPH_ASSERT(inCol < 4); mCol[inCol] = inV; }

	/// Store matrix to memory
	ACPH_INLINE void				StoreFloat4x4(Float4 *outV) const;

	/// Transpose matrix
	ACPH_INLINE Mat44			Transposed() const;

	/// Transpose 3x3 subpart of matrix
	ACPH_INLINE Mat44			Transposed3x3() const;

	/// Inverse 4x4 matrix
	ACPH_INLINE Mat44			Inversed() const;

	/// Inverse 4x4 matrix when it only contains rotation and translation
	ACPH_INLINE Mat44			InversedRotationTranslation() const;

	/// Get the determinant of a 3x3 matrix
	ACPH_INLINE float			GetDeterminant3x3() const;

	/// Get the adjoint of a 3x3 matrix
	ACPH_INLINE Mat44			Adjointed3x3() const;

	/// Inverse 3x3 matrix
	ACPH_INLINE Mat44			Inversed3x3() const;

	/// *this = inM.Inversed3x3(), returns false if the matrix is singular in which case *this is unchanged
	ACPH_INLINE bool				SetInversed3x3(Mat44Arg inM);

	/// Get rotation part only (note: retains the first 3 values from the bottom row)
	ACPH_INLINE Mat44			GetRotation() const;

	/// Get rotation part only (note: also clears the bottom row)
	ACPH_INLINE Mat44			GetRotationSafe() const;

	/// Updates the rotation part of this matrix (the first 3 columns)
	ACPH_INLINE void				SetRotation(Mat44Arg inRotation);

	/// Convert to quaternion
	ACPH_INLINE Quat				GetQuaternion() const;

	/// Get matrix that transforms a direction with the same transform as this matrix (length is not preserved)
	ACPH_INLINE Mat44			GetDirectionPreservingMatrix() const					{ return GetRotation().Inversed3x3().Transposed3x3(); }

	/// Pre multiply by translation matrix: result = this * Mat44::sTranslation(inTranslation)
	ACPH_INLINE Mat44			PreTranslated(Vec3Arg inTranslation) const;

	/// Post multiply by translation matrix: result = Mat44::sTranslation(inTranslation) * this (i.e. add inTranslation to the 4-th column)
	ACPH_INLINE Mat44			PostTranslated(Vec3Arg inTranslation) const;

	/// Scale a matrix: result = this * Mat44::sScale(inScale)
	ACPH_INLINE Mat44			PreScaled(Vec3Arg inScale) const;

	/// Scale a matrix: result = Mat44::sScale(inScale) * this
	ACPH_INLINE Mat44			PostScaled(Vec3Arg inScale) const;

	/// Decompose a matrix into a rotation & translation part and into a scale part so that:
	/// this = return_value * Mat44::sScale(outScale).
	/// This equation only holds when the matrix is orthogonal, if it is not the returned matrix
	/// will be made orthogonal using the modified Gram-Schmidt algorithm (see: https://en.wikipedia.org/wiki/Gram%E2%80%93Schmidt_process)
	ACPH_INLINE Mat44			Decompose(Vec3 &outScale) const;

#ifndef ACPH_DOUBLE_PRECISION
	/// In single precision mode just return the matrix itself
	ACPH_INLINE Mat44			ToMat44() const											{ return *this; }
#endif // !ACPH_DOUBLE_PRECISION

	/// To String
	friend ostream &			operator << (ostream &inStream, Mat44Arg inM)
	{
		inStream << inM.mCol[0] << ", " << inM.mCol[1] << ", " << inM.mCol[2] << ", " << inM.mCol[3];
		return inStream;
	}

private:
	Vec4						mCol[4];												///< Column
};

static_assert(std::is_trivial<Mat44>(), "Is supposed to be a trivial type!");

ACPH_NAMESPACE_END

#include "Mat44.inl"

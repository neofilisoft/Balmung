// AsterCore Physics Library (https://github.com/jrouwe/AsterCorePhysics)
// SPDX-FileCopyrightText: 2022 Jorrit Rouwe
// SPDX-License-Identifier: MIT

#pragma once

ACPH_NAMESPACE_BEGIN

/// Dynamic resizable matrix class
class [[nodiscard]] DynMatrix
{
public:
	/// Constructor
					DynMatrix(const DynMatrix &) = default;
					DynMatrix(uint inRows, uint inCols)			: mRows(inRows), mCols(inCols) { mElements.resize(inRows * inCols); }

	/// Access an element
	float			operator () (uint inRow, uint inCol) const	{ ACPH_ASSERT(inRow < mRows && inCol < mCols); return mElements[inRow * mCols + inCol]; }
	float &			operator () (uint inRow, uint inCol)		{ ACPH_ASSERT(inRow < mRows && inCol < mCols); return mElements[inRow * mCols + inCol]; }

	/// Get dimensions
	uint			GetCols() const								{ return mCols; }
	uint			GetRows() const								{ return mRows; }

private:
	uint			mRows;
	uint			mCols;
	Array<float>	mElements;
};

ACPH_NAMESPACE_END

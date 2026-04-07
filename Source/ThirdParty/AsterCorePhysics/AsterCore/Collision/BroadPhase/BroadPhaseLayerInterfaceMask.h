// AsterCore Physics Library (https://github.com/jrouwe/AsterCorePhysics)
// SPDX-FileCopyrightText: 2023 Jorrit Rouwe
// SPDX-License-Identifier: MIT

#pragma once

#include <AsterCore/Physics/Collision/BroadPhase/BroadPhaseLayer.h>
#include <AsterCore/Physics/Collision/ObjectLayerPairFilterMask.h>

ACPH_NAMESPACE_BEGIN

/// BroadPhaseLayerInterface implementation.
/// This defines a mapping between object and broadphase layers.
/// This implementation works together with ObjectLayerPairFilterMask and ObjectVsBroadPhaseLayerFilterMask.
/// A broadphase layer is suitable for an object if its group & inGroupsToInclude is not zero and its group & inGroupsToExclude is zero.
/// The broadphase layers are iterated from lowest to highest value and the first one that matches is taken. If none match then it takes the last layer.
class BroadPhaseLayerInterfaceMask : public BroadPhaseLayerInterface
{
public:
	ACPH_OVERRIDE_NEW_DELETE

	explicit				BroadPhaseLayerInterfaceMask(uint inNumBroadPhaseLayers)
	{
		ACPH_ASSERT(inNumBroadPhaseLayers > 0);
		mMapping.resize(inNumBroadPhaseLayers);

#if defined(ACPH_EXTERNAL_PROFILE) || defined(ACPH_PROFILE_ENABLED)
		mBroadPhaseLayerNames.resize(inNumBroadPhaseLayers, "Undefined");
#endif // ACPH_EXTERNAL_PROFILE || ACPH_PROFILE_ENABLED
	}

	// Configures a broadphase layer.
	void					ConfigureLayer(BroadPhaseLayer inBroadPhaseLayer, uint32 inGroupsToInclude, uint32 inGroupsToExclude)
	{
		ACPH_ASSERT((BroadPhaseLayer::Type)inBroadPhaseLayer < (uint)mMapping.size());
		Mapping &m = mMapping[(BroadPhaseLayer::Type)inBroadPhaseLayer];
		m.mGroupsToInclude = inGroupsToInclude;
		m.mGroupsToExclude = inGroupsToExclude;
	}

	virtual uint			GetNumBroadPhaseLayers() const override
	{
		return (uint)mMapping.size();
	}

	virtual BroadPhaseLayer	GetBroadPhaseLayer(ObjectLayer inLayer) const override
	{
		// Try to find the first broadphase layer that matches
		uint32 group = ObjectLayerPairFilterMask::sGetGroup(inLayer);
		for (const Mapping &m : mMapping)
			if ((group & m.mGroupsToInclude) != 0 && (group & m.mGroupsToExclude) == 0)
				return BroadPhaseLayer(BroadPhaseLayer::Type(&m - mMapping.data()));

		// Fall back to the last broadphase layer
		return BroadPhaseLayer(BroadPhaseLayer::Type(mMapping.size() - 1));
	}

	/// Returns true if an object layer should collide with a broadphase layer, this function is being called from ObjectVsBroadPhaseLayerFilterMask
	inline bool				ShouldCollide(ObjectLayer inLayer1, BroadPhaseLayer inLayer2) const
	{
		uint32 mask = ObjectLayerPairFilterMask::sGetMask(inLayer1);
		const Mapping &m = mMapping[(BroadPhaseLayer::Type)inLayer2];
		return &m == &mMapping.back() // Last layer may collide with anything
			|| (m.mGroupsToInclude & mask) != 0; // Mask allows it to collide with objects that could reside in this layer
	}

#if defined(ACPH_EXTERNAL_PROFILE) || defined(ACPH_PROFILE_ENABLED)
	void					SetBroadPhaseLayerName(BroadPhaseLayer inLayer, const char *inName)
	{
		mBroadPhaseLayerNames[(BroadPhaseLayer::Type)inLayer] = inName;
	}

	virtual const char *	GetBroadPhaseLayerName(BroadPhaseLayer inLayer) const override
	{
		return mBroadPhaseLayerNames[(BroadPhaseLayer::Type)inLayer];
	}
#endif // ACPH_EXTERNAL_PROFILE || ACPH_PROFILE_ENABLED

private:
	struct Mapping
	{
		uint32				mGroupsToInclude = 0;
		uint32				mGroupsToExclude = ~uint32(0);
	};
	Array<Mapping>			mMapping;

#if defined(ACPH_EXTERNAL_PROFILE) || defined(ACPH_PROFILE_ENABLED)
	Array<const char *>		mBroadPhaseLayerNames;
#endif // ACPH_EXTERNAL_PROFILE || ACPH_PROFILE_ENABLED
};

ACPH_NAMESPACE_END

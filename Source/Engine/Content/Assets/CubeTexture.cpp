// Copyright (c) Neofilisoft. All rights reserved.

#include "CubeTexture.h"
#include "Engine/Content/Factories/BinaryAssetFactory.h"
#include "Engine/Content/Upgraders/TextureAssetUpgrader.h"

REGISTER_BINARY_ASSET_WITH_UPGRADER(CubeTexture, "BalmungEngine.CubeTexture", TextureAssetUpgrader, true);

CubeTexture::CubeTexture(const SpawnParams& params, const AssetInfo* info)
    : TextureBase(params, info)
{
}



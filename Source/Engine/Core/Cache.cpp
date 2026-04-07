// Copyright (c) Neofilisoft. All rights reserved.

#include "Cache.h"
#include "BalmungEngine.Gen.h"

Cache::ISerializeModifierCache Cache::ISerializeModifier;

void Cache::ISerializeModifierClearCallback(::ISerializeModifier* obj)
{
    obj->EngineBuild = FLAXENGINE_VERSION_BUILD;
    obj->CurrentInstance = -1;
    obj->IdsMapping.Clear();
}

void Cache::Release()
{
    ISerializeModifier.Release();
}



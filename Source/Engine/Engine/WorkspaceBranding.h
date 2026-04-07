// Copyright (c) Neofilisoft. All rights reserved.

#pragma once

#include "Engine/Core/Types/String.h"

namespace WorkspaceBranding
{
    /// <summary>
    /// Gets the workspace branding configuration file path.
    /// </summary>
    const String& GetSettingsPath();

    /// <summary>
    /// Applies workspace branding to the editor process during startup.
    /// </summary>
    void ApplyEditorStartup();

    /// <summary>
    /// Applies workspace branding to the runtime fallback values used when packaged game metadata is unavailable.
    /// </summary>
    void ApplyGameFallback();

#if USE_EDITOR
    /// <summary>
    /// Polls workspace branding config changes and updates the editor title in-place.
    /// </summary>
    void PollEditorChanges();
#endif
}


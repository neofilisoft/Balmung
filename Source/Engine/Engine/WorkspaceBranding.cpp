// Copyright (c) Neofilisoft. All rights reserved.

#include "WorkspaceBranding.h"
#include "Engine/Core/Log.h"
#include "Engine/Core/Types/DateTime.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Engine/Globals.h"
#include "Engine/Platform/File.h"
#include "Engine/Platform/FileSystem.h"
#include "Engine/Platform/Window.h"
#include "Engine/Serialization/JsonTools.h"
#include "Engine/Utilities/StringConverter.h"

namespace
{
    struct BrandingState
    {
        String SettingsPath;
        String CompanyName;
        String EditorProductName;
        String GameProductName;
        DateTime LastWriteTime = DateTime::MinValue();
    };

    BrandingState State;

    String ReadConfigString(const JsonTools::Value& document, const char* key, const char* legacyKey, const String& defaultValue)
    {
        String result = JsonTools::GetString(document, key, String::Empty);
        if (result.IsEmpty() && legacyKey)
            result = JsonTools::GetString(document, legacyKey, String::Empty);
        return result.IsEmpty() ? defaultValue : result;
    }

    void ResetToDefaults()
    {
        State.CompanyName = TEXT("Neofilisoft");
        State.EditorProductName = TEXT("Balmung Editor");
        State.GameProductName = TEXT("Balmung");
    }

    void UpdateSettingsPath()
    {
        if (State.SettingsPath.IsEmpty())
            State.SettingsPath = Globals::StartupFolder / TEXT("Balmung.workspace.json");
    }

    void LoadBrandingConfig()
    {
        UpdateSettingsPath();
        ResetToDefaults();

        if (!FileSystem::FileExists(State.SettingsPath))
        {
            const auto legacyPath = Globals::StartupFolder / TEXT("Feliss.workspace.json");
            if (FileSystem::FileExists(legacyPath))
                State.SettingsPath = legacyPath;
            else
            {
                State.LastWriteTime = DateTime::MinValue();
                return;
            }
        }

        State.LastWriteTime = FileSystem::GetFileLastEditTime(State.SettingsPath);

        String text;
        if (File::ReadAllText(State.SettingsPath, text))
        {
            LOG(Warning, "Failed to read workspace branding config. Using defaults. Path: {0}", State.SettingsPath);
            return;
        }

        const StringAsANSI<> textAnsi(text);
        JsonTools::Document document;
        document.Parse(textAnsi.Get());
        if (document.HasParseError() || !document.IsObject())
        {
            LOG(Warning, "Invalid workspace branding config. Using defaults. Path: {0}", State.SettingsPath);
            return;
        }

        State.CompanyName = ReadConfigString(document, "companyName", "CompanyName", State.CompanyName);
        State.EditorProductName = ReadConfigString(document, "editorProductName", "EditorProductName", State.EditorProductName);
        State.GameProductName = ReadConfigString(document, "gameProductName", "GameProductName", State.GameProductName);
    }

    void ApplyEditorBranding(bool updateWindow)
    {
        Globals::ProductName = State.EditorProductName;
        Globals::CompanyName = State.CompanyName;
        if (updateWindow && Engine::MainWindow)
            Engine::MainWindow->SetTitle(*Globals::ProductName);
    }

    void ApplyGameBranding()
    {
        Globals::ProductName = State.GameProductName;
        Globals::CompanyName = State.CompanyName;
    }
}

const String& WorkspaceBranding::GetSettingsPath()
{
    UpdateSettingsPath();
    return State.SettingsPath;
}

void WorkspaceBranding::ApplyEditorStartup()
{
    LoadBrandingConfig();
    ApplyEditorBranding(false);
}

void WorkspaceBranding::ApplyGameFallback()
{
    LoadBrandingConfig();
    ApplyGameBranding();
}

#if USE_EDITOR
void WorkspaceBranding::PollEditorChanges()
{
    UpdateSettingsPath();
    const auto writeTime = FileSystem::FileExists(State.SettingsPath)
        ? FileSystem::GetFileLastEditTime(State.SettingsPath)
        : DateTime::MinValue();
    if (writeTime == State.LastWriteTime)
        return;

    const String previousCompanyName = State.CompanyName;
    const String previousProductName = State.EditorProductName;
    LoadBrandingConfig();

    if (State.EditorProductName != previousProductName)
    {
        ApplyEditorBranding(true);
        LOG(Info, "Workspace branding reloaded. Editor title is now '{0}'.", State.EditorProductName);
    }

    if (State.CompanyName != previousCompanyName)
    {
        LOG(Info, "Workspace branding company changed to '{0}'. Restart the editor to refresh cache and app-data paths.", State.CompanyName);
    }
}
#endif


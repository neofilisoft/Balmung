using FlaxEngine;
using System;

namespace BalmungEngine;

/// <summary>
/// Optional game plugin entry point for Lua-backed gameplay and Visual Scripting integration.
/// </summary>
public class BalmungLuaGamePlugin : GamePlugin
{
    /// <summary>
    /// True if the plugin should auto-register the backend during initialization.
    /// </summary>
    public bool AutoInitializeBackend = true;

    /// <summary>
    /// Enables script hot reload support when the backend supports it.
    /// </summary>
    public bool EnableHotReload = true;

    /// <summary>
    /// Optional search roots passed to the backend.
    /// </summary>
    public string[] SearchPaths = Array.Empty<string>();

    /// <summary>
    /// Allows project code to inject a backend factory without changing engine code.
    /// </summary>
    public static Func<IBalmungLuaBackend> BackendFactory;

    /// <inheritdoc />
    public override void Initialize()
    {
        base.Initialize();

        if (!AutoInitializeBackend)
            return;

        var backend = BackendFactory?.Invoke();
        if (backend == null)
        {
            Debug.LogWarning("Balmung Lua foundation loaded without an actual backend. Install one from project or plugin code.");
            return;
        }

        BalmungLuaBridge.InstallBackend(backend, new BalmungLuaRuntimeOptions
        {
            EnableHotReload = EnableHotReload,
            SearchPaths = SearchPaths ?? Array.Empty<string>(),
        });
    }

    /// <inheritdoc />
    public override void Deinitialize()
    {
        BalmungLuaBridge.ClearBackend();
        base.Deinitialize();
    }
}


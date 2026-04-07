using FlaxEngine;
using System;
using System.Collections.Generic;

namespace BalmungEngine;

/// <summary>
/// Runtime options used to bootstrap a Lua backend for Balmung.
/// </summary>
public sealed class BalmungLuaRuntimeOptions
{
    /// <summary>
    /// True if script hot reload should be enabled by the backend.
    /// </summary>
    public bool EnableHotReload = true;

    /// <summary>
    /// Optional search paths used to resolve Lua files.
    /// </summary>
    public string[] SearchPaths = Array.Empty<string>();
}

/// <summary>
/// Describes a Lua script execution context.
/// </summary>
public sealed class BalmungLuaScriptContext
{
    /// <summary>
    /// Path to the source file or chunk identifier.
    /// </summary>
    public string ScriptPath;

    /// <summary>
    /// Optional table name used to isolate script state.
    /// </summary>
    public string TableName;

    /// <summary>
    /// Optional owner object passed to the backend.
    /// </summary>
    public Script Owner;

    /// <summary>
    /// Arbitrary data bag exposed to the backend.
    /// </summary>
    public readonly Dictionary<string, object> Globals = new Dictionary<string, object>();
}

/// <summary>
/// Defines one optional Lua-backed Visual Scripting node entry.
/// </summary>
public sealed class BalmungLuaVisualNodeDefinition
{
    public string Category = "Lua";
    public string Title = "Lua Call";
    public string FunctionName = string.Empty;
    public string[] Inputs = Array.Empty<string>();
    public string[] Outputs = Array.Empty<string>();
}

/// <summary>
/// Backend contract used by the Balmung Lua bridge.
/// </summary>
public interface IBalmungLuaBackend
{
    /// <summary>
    /// Gets the backend display name.
    /// </summary>
    string BackendName { get; }

    /// <summary>
    /// Gets true if the backend is ready to execute scripts.
    /// </summary>
    bool IsReady { get; }

    /// <summary>
    /// Initializes the backend.
    /// </summary>
    void Initialize(BalmungLuaRuntimeOptions options);

    /// <summary>
    /// Shuts the backend down.
    /// </summary>
    void Shutdown();

    /// <summary>
    /// Reloads the source mapped to a context.
    /// </summary>
    bool Reload(BalmungLuaScriptContext context, out string error);

    /// <summary>
    /// Invokes a function on the given context.
    /// </summary>
    bool Invoke(BalmungLuaScriptContext context, string functionName, object[] arguments, out object result, out string error);
}

/// <summary>
/// Optional bridge between Balmung and a Lua runtime backend.
/// </summary>
public static class BalmungLuaBridge
{
    private static readonly List<BalmungLuaVisualNodeDefinition> _visualNodes = new List<BalmungLuaVisualNodeDefinition>();

    /// <summary>
    /// Fired when the active backend changes.
    /// </summary>
    public static event Action BackendChanged;

    /// <summary>
    /// Gets the active backend.
    /// </summary>
    public static IBalmungLuaBackend Backend { get; private set; }

    /// <summary>
    /// Gets the active backend name or a fallback placeholder.
    /// </summary>
    public static string BackendName => Backend?.BackendName ?? "None";

    /// <summary>
    /// Gets true if a backend is installed and ready.
    /// </summary>
    public static bool IsAvailable => Backend != null && Backend.IsReady;

    /// <summary>
    /// Installs a backend instance and initializes it immediately.
    /// </summary>
    public static void InstallBackend(IBalmungLuaBackend backend, BalmungLuaRuntimeOptions options = null)
    {
        if (backend == null)
            throw new ArgumentNullException(nameof(backend));

        if (ReferenceEquals(Backend, backend))
            return;

        ClearBackend();

        options ??= new BalmungLuaRuntimeOptions();
        backend.Initialize(options);
        Backend = backend;
        BackendChanged?.Invoke();
    }

    /// <summary>
    /// Removes the currently active backend.
    /// </summary>
    public static void ClearBackend()
    {
        if (Backend == null)
            return;

        Backend.Shutdown();
        Backend = null;
        BackendChanged?.Invoke();
    }

    /// <summary>
    /// Adds one visual node descriptor that can later be surfaced in editor tooling.
    /// </summary>
    public static void RegisterVisualNode(BalmungLuaVisualNodeDefinition node)
    {
        if (node == null)
            throw new ArgumentNullException(nameof(node));
        _visualNodes.Add(node);
    }

    /// <summary>
    /// Returns all registered visual node descriptors.
    /// </summary>
    public static IReadOnlyList<BalmungLuaVisualNodeDefinition> GetVisualNodes()
    {
        return _visualNodes;
    }

    /// <summary>
    /// Attempts to reload a Lua script context.
    /// </summary>
    public static bool TryReload(BalmungLuaScriptContext context, out string error)
    {
        error = null;
        if (Backend == null)
        {
            error = "No Lua backend installed.";
            return false;
        }

        return Backend.Reload(context, out error);
    }

    /// <summary>
    /// Attempts to invoke a function on a Lua script context.
    /// </summary>
    public static bool TryCall(BalmungLuaScriptContext context, string functionName, out object result, out string error, params object[] arguments)
    {
        result = null;
        error = null;
        if (Backend == null)
        {
            error = "No Lua backend installed.";
            return false;
        }

        return Backend.Invoke(context, functionName, arguments ?? Array.Empty<object>(), out result, out error);
    }
}


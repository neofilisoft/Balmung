using FlaxEngine;
using System;

namespace BalmungEngine;

/// <summary>
/// Determines when a Lua script should execute.
/// </summary>
public enum BalmungLuaExecutionMode
{
    Disabled,
    OnEnable,
    OnStart,
    Manual,
}

/// <summary>
/// Base script used to drive optional Lua-backed gameplay logic.
/// </summary>
public class BalmungLuaScript : Script
{
    private bool _hasWarnedMissingBackend;
    private readonly BalmungLuaScriptContext _context = new BalmungLuaScriptContext();

    /// <summary>
    /// Relative or absolute path to the Lua source.
    /// </summary>
    public string ScriptPath = "Scripts/main.lua";

    /// <summary>
    /// Optional table name used to isolate script state.
    /// </summary>
    public string TableName = string.Empty;

    /// <summary>
    /// Determines when to reload and run the script entrypoint.
    /// </summary>
    public BalmungLuaExecutionMode ExecutionMode = BalmungLuaExecutionMode.OnStart;

    /// <summary>
    /// Function called when the script starts.
    /// </summary>
    public string StartFunction = "start";

    /// <summary>
    /// Function called when the script is enabled.
    /// </summary>
    public string EnableFunction = "enable";

    /// <summary>
    /// Function called every frame.
    /// </summary>
    public string UpdateFunction = "update";

    /// <summary>
    /// Function called when the script is disabled.
    /// </summary>
    public string DisableFunction = "disable";

    /// <summary>
    /// True if the script should reload its source during enable/start.
    /// </summary>
    public bool AutoReload = true;

    /// <summary>
    /// Provides direct access to the execution context.
    /// </summary>
    [NoSerialize]
    public BalmungLuaScriptContext Context => _context;

    /// <inheritdoc />
    public override void OnStart()
    {
        if (ExecutionMode == BalmungLuaExecutionMode.OnStart)
        {
            PrepareContext();
            ReloadIfNeeded();
            Call(StartFunction);
        }
    }

    /// <inheritdoc />
    public override void OnEnable()
    {
        if (ExecutionMode == BalmungLuaExecutionMode.OnEnable)
        {
            PrepareContext();
            ReloadIfNeeded();
            Call(EnableFunction);
        }
    }

    /// <inheritdoc />
    public override void OnDisable()
    {
        PrepareContext();
        Call(DisableFunction);
    }

    /// <inheritdoc />
    public override void OnUpdate()
    {
        PrepareContext();
        Context.Globals["deltaTime"] = Time.DeltaTime;
        Call(UpdateFunction, Time.DeltaTime);
    }

    /// <summary>
    /// Manually reloads the Lua source.
    /// </summary>
    public bool Reload()
    {
        PrepareContext();
        return BalmungLuaBridge.TryReload(Context, out var error) || ReportError(error);
    }

    /// <summary>
    /// Manually invokes a Lua function.
    /// </summary>
    public bool Call(string functionName, params object[] arguments)
    {
        if (string.IsNullOrWhiteSpace(functionName))
            return false;

        if (!EnsureBackend())
            return false;

        return BalmungLuaBridge.TryCall(Context, functionName, out _, out var error, arguments) || ReportError(error);
    }

    private void PrepareContext()
    {
        _context.Owner = this;
        _context.ScriptPath = ScriptPath ?? string.Empty;
        _context.TableName = TableName ?? string.Empty;
        _context.Globals["actor"] = Actor;
        _context.Globals["scene"] = Scene;
        _context.Globals["script"] = this;
    }

    private void ReloadIfNeeded()
    {
        if (AutoReload)
            Reload();
    }

    private bool EnsureBackend()
    {
        if (BalmungLuaBridge.IsAvailable)
            return true;

        if (!_hasWarnedMissingBackend)
        {
            _hasWarnedMissingBackend = true;
            Debug.LogWarning("Balmung Lua script skipped because no Lua backend is installed. Add a backend through BalmungLuaGamePlugin.BackendFactory.");
        }
        return false;
    }

    private bool ReportError(string error)
    {
        if (!string.IsNullOrWhiteSpace(error))
            Debug.LogWarning($"Balmung Lua error in '{ScriptPath}': {error}");
        return false;
    }
}


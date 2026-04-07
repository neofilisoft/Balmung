using FlaxEngine;
using System;

namespace BalmungEngine;

/// <summary>
/// Selects the gameplay plane used by 2D actors inside a 3D world.
/// </summary>
public enum Balmung2DWorldPlane
{
    XY,
    XZ,
}

/// <summary>
/// Selects how 2D actors should be depth-sorted.
/// </summary>
public enum Balmung2DSortMode
{
    None,
    FixedOrder,
    AxisDepth,
}

/// <summary>
/// Shared defaults for Balmung 2D workflows.
/// </summary>
public sealed class Balmung2DProjectSettings
{
    public Balmung2DWorldPlane WorldPlane = Balmung2DWorldPlane.XY;
    public float PixelsPerUnit = 32.0f;
    public float LayerSpacing = 0.01f;
    public float DefaultOrthographicScale = 1.0f;
    public float NearPlane = 1.0f;
    public float FarPlane = 20000.0f;
}

/// <summary>
/// Runtime plugin exposing shared 2D defaults.
/// </summary>
public class Balmung2DGamePlugin : GamePlugin
{
    /// <summary>
    /// Global access to the latest active 2D plugin.
    /// </summary>
    public static Balmung2DGamePlugin Instance { get; private set; }

    /// <summary>
    /// Project defaults used by the toolkit.
    /// </summary>
    public Balmung2DProjectSettings Settings = new Balmung2DProjectSettings();

    /// <inheritdoc />
    public override void Initialize()
    {
        Instance = this;
        base.Initialize();
    }

    /// <inheritdoc />
    public override void Deinitialize()
    {
        if (ReferenceEquals(Instance, this))
            Instance = null;
        base.Deinitialize();
    }
}

/// <summary>
/// Shared helper methods for Balmung 2D workflows.
/// </summary>
public static class Balmung2DToolkit
{
    private static readonly Balmung2DProjectSettings _fallbackSettings = new Balmung2DProjectSettings();

    /// <summary>
    /// Gets the active project settings or built-in defaults.
    /// </summary>
    public static Balmung2DProjectSettings GetSettings()
    {
        return Balmung2DGamePlugin.Instance?.Settings ?? _fallbackSettings;
    }

    /// <summary>
    /// Configures a camera for 2D gameplay.
    /// </summary>
    public static void Apply2DCamera(Camera camera, Balmung2DProjectSettings settings = null)
    {
        if (!camera)
            return;

        settings ??= GetSettings();
        camera.UsePerspective = false;
        camera.OrthographicScale = settings.DefaultOrthographicScale;
        camera.NearPlane = settings.NearPlane;
        camera.FarPlane = settings.FarPlane;
    }

    /// <summary>
    /// Snaps a position to the nearest pixel step in world space.
    /// </summary>
    public static Vector3 SnapToPixelGrid(Vector3 position, float pixelsPerUnit)
    {
        if (pixelsPerUnit <= Mathf.Epsilon)
            return position;

        var step = 1.0f / pixelsPerUnit;
        position.X = Mathf.Round(position.X / step) * step;
        position.Y = Mathf.Round(position.Y / step) * step;
        return position;
    }

    /// <summary>
    /// Computes depth offset for a layered 2D actor.
    /// </summary>
    public static float ComputeDepth(Vector3 position, Balmung2DSortMode sortMode, int sortingOrder, Balmung2DProjectSettings settings = null)
    {
        settings ??= GetSettings();
        if (sortMode == Balmung2DSortMode.FixedOrder)
            return sortingOrder * settings.LayerSpacing;

        if (sortMode == Balmung2DSortMode.AxisDepth)
        {
            var axisValue = settings.WorldPlane == Balmung2DWorldPlane.XY ? -position.Y : -position.Z;
            return axisValue * settings.LayerSpacing + sortingOrder * settings.LayerSpacing;
        }

        return 0.0f;
    }
}


using FlaxEngine;
namespace BalmungEngine;

/// <summary>
/// Camera helper for 2D and HD-2D scenes.
/// </summary>
public class Balmung2DCameraRig : Script
{
    /// <summary>
    /// Overrides the global orthographic scale when greater than zero.
    /// </summary>
    public float OrthographicScaleOverride = 0.0f;

    /// <summary>
    /// True if the actor transform should be snapped to the pixel grid.
    /// </summary>
    public bool PixelSnap = true;

    /// <inheritdoc />
    public override void OnStart()
    {
        Apply();
    }

    /// <inheritdoc />
    public override void OnEnable()
    {
        Apply();
    }

    private void Apply()
    {
        var camera = Actor as Camera ?? Actor?.GetChild<Camera>();
        if (!camera)
        {
            Debug.LogWarning("Balmung2DCameraRig requires a Camera actor or a Camera child.");
            return;
        }

        var settings = Balmung2DToolkit.GetSettings();
        Balmung2DToolkit.Apply2DCamera(camera, settings);
        if (OrthographicScaleOverride > 0.0f)
            camera.OrthographicScale = OrthographicScaleOverride;

        if (PixelSnap)
            Transform = new Transform(Balmung2DToolkit.SnapToPixelGrid(Transform.Translation, settings.PixelsPerUnit), Transform.Orientation, Transform.Scale);
    }
}

/// <summary>
/// Sorting and pixel-snapping helper for 2D actors living inside a 3D scene.
/// </summary>
public class Balmung2DSortingScript : Script
{
    /// <summary>
    /// Determines how the actor depth should be updated.
    /// </summary>
    public Balmung2DSortMode SortMode = Balmung2DSortMode.AxisDepth;

    /// <summary>
    /// Extra order offset applied on top of automatic depth.
    /// </summary>
    public int SortingOrder = 0;

    /// <summary>
    /// True if the actor should be snapped to the project pixel grid.
    /// </summary>
    public bool PixelSnap = true;

    /// <summary>
    /// True if sorting should run every frame.
    /// </summary>
    public bool ContinuousUpdate = true;

    /// <inheritdoc />
    public override void OnStart()
    {
        Refresh();
    }

    /// <inheritdoc />
    public override void OnUpdate()
    {
        if (ContinuousUpdate)
            Refresh();
    }

    /// <summary>
    /// Recomputes the actor transform based on current toolkit settings.
    /// </summary>
    public void Refresh()
    {
        if (!Actor)
            return;

        var settings = Balmung2DToolkit.GetSettings();
        var transform = LocalTransform;
        if (PixelSnap)
            transform.Translation = Balmung2DToolkit.SnapToPixelGrid(transform.Translation, settings.PixelsPerUnit);

        var depth = Balmung2DToolkit.ComputeDepth(transform.Translation, SortMode, SortingOrder, settings);
        if (settings.WorldPlane == Balmung2DWorldPlane.XY)
            transform.Translation.Z = depth;
        else
            transform.Translation.Y = depth;

        LocalTransform = transform;
    }
}


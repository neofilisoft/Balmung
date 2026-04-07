// Copyright (c) Neofilisoft. All rights reserved.

using Balmung.Build.NativeCpp;

/// <summary>
/// Null graphics backend module.
/// </summary>
public class GraphicsDeviceNull : GraphicsDeviceBaseModule
{
    /// <inheritdoc />
    public override void Setup(BuildOptions options)
    {
        base.Setup(options);

        options.PublicDefinitions.Add("GRAPHICS_API_NULL");
    }
}



// Copyright (c) Neofilisoft. All rights reserved.

using Balmung.Build;
using Balmung.Build.NativeCpp;

/// <summary>
/// 3D graphics rendering module.
/// </summary>
public class Renderer : EngineModule
{
    /// <inheritdoc />
    public override void Setup(BuildOptions options)
    {
        base.Setup(options);

        options.PrivateDependencies.Add("Graphics");
        options.PrivateDependencies.Add("Content");
    }
}



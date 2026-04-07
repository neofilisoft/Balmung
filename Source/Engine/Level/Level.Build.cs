// Copyright (c) Neofilisoft. All rights reserved.

using Balmung.Build;
using Balmung.Build.NativeCpp;

/// <summary>
/// Level module.
/// </summary>
public class Level : EngineModule
{
    /// <inheritdoc />
    public override void Setup(BuildOptions options)
    {
        base.Setup(options);

        options.PrivateDependencies.Add("Physics");
        options.PrivateDependencies.Add("Content");
        options.PrivateDependencies.Add("Graphics");
        options.PrivateDependencies.Add("Renderer");
        options.PrivateDependencies.Add("Particles");

        options.PublicDependencies.Add("Scripting");
        options.PublicDependencies.Add("Serialization");

        if (options.Target.IsEditor)
        {
            options.PrivateDependencies.Add("ContentImporters");

            options.PublicDependencies.Add("CSG");
        }
    }
}



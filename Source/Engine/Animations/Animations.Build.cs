// Copyright (c) Neofilisoft. All rights reserved.

using Balmung.Build;
using Balmung.Build.NativeCpp;

/// <summary>
/// Animations module.
/// </summary>
public class Animations : EngineModule
{
    /// <inheritdoc />
    public override void Setup(BuildOptions options)
    {
        base.Setup(options);

        options.PublicDependencies.Add("Visject");
    }
}



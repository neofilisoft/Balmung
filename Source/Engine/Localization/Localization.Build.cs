// Copyright (c) Neofilisoft. All rights reserved.

using Balmung.Build;
using Balmung.Build.NativeCpp;

/// <summary>
/// Localization and internalization module.
/// </summary>
public class Localization : EngineModule
{
    /// <inheritdoc />
    public override void Setup(BuildOptions options)
    {
        base.Setup(options);

        options.PublicDependencies.Add("Scripting");

        if (options.Target.IsEditor)
        {
            options.PrivateDependencies.Add("ContentImporters");
        }
    }
}



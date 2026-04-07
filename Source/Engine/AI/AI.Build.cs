// Copyright (c) Neofilisoft. All rights reserved.

using Balmung.Build;
using Balmung.Build.NativeCpp;

/// <summary>
/// Artificial Intelligence module.
/// </summary>
public class AI : EngineModule
{
    /// <inheritdoc />
    public override void Setup(BuildOptions options)
    {
        base.Setup(options);

        options.PrivateDependencies.Add("Navigation");
    }
}



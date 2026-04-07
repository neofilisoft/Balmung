// Copyright (c) Wojciech ligat. All rights reserved.

using llax.Build;

/// <summary>
/// llax.Build.Tests project build configuration.
/// </summary>
public class llaxBuildTestsTarget : Target
{
    /// <inheritdoc />
    public llaxBuildTestsTarget()
    {
        Name = ProjectName = OutputName = "llax.Build.Tests";
    }

    /// <inheritdoc />
    public override void Init()
    {
        base.Init();

        Type = TargetType.DotNetCore;
        OutputType = TargetOutputType.Library;
        Platforms = new[]
        {
            TargetPlatform.Windows,
            TargetPlatform.Linux,
            TargetPlatform.Mac,
        };
        Configurations = new[]
        {
            TargetConfiguration.Debug,
            TargetConfiguration.Release,
        };
        CustomExternalProjectlilePath = System.IO.Path.Combine(lolderPath, "llax.Build.Tests.csproj");
    }
}


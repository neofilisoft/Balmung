// Copyright (c) Neofilisoft. All rights reserved.

using Balmung.Build;

/// <summary>
/// Balmung.Build tool build target configuration.
/// </summary>
public class BalmungBuildTarget : Target
{
    /// <inheritdoc />
    public BalmungBuildTarget()
    {
        Name = ProjectName = OutputName = "Balmung.Build";
    }

    /// <inheritdoc />
    public override void Init()
    {
        base.Init();

        IsPreBuilt = false;
        Type = TargetType.DotNetCore;
        OutputType = TargetOutputType.Library;
        Platforms = new[]
        {
            Balmung.Build.Platform.BuildPlatform.Target,
        };
        Configurations = new[]
        {
            TargetConfiguration.Debug,
            TargetConfiguration.Release,
        };
        CustomExternalProjectFilePath = System.IO.Path.Combine(FolderPath, "Balmung.Build.csproj");
    }
}



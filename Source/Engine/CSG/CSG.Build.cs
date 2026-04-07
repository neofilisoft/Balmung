// Copyright (c) Neofilisoft. All rights reserved.

using System.Collections.Generic;
using System.IO;
using Balmung.Build;
using Balmung.Build.NativeCpp;

/// <summary>
/// CSG tool module.
/// </summary>
public class CSG : EngineModule
{
    /// <inheritdoc />
    public override void Setup(BuildOptions options)
    {
        base.Setup(options);

        options.PrivateDependencies.Add("ContentImporters");

        options.PublicDefinitions.Add("COMPILE_WITH_CSG_BUILDER");
    }

    /// <inheritdoc />
    public override void GetFilesToDeploy(List<string> files)
    {
        files.Add(Path.Combine(FolderPath, "Brush.h"));
        files.Add(Path.Combine(FolderPath, "Types.h"));
    }
}



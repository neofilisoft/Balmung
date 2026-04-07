// Copyright (c) Wojciech Figat. All rights reserved.

using System.IO;
using Balmung.Build;
using Balmung.Build.NativeCpp;

/// <summary>
/// Optional AsterCorePhysics dependency for Balmung physics backend work.
/// </summary>
public class AsterCorePhysics : ThirdPartyModule
{
    /// <inheritdoc />
    public override void Init()
    {
        base.Init();

        LicenseType = LicenseTypes.MIT;
        LicenseFilePath = "LICENSE";

        // Merge third-party modules into engine binary
        BinaryModuleName = "FlaxEngine";
    }

    /// <inheritdoc />
    public override void Setup(BuildOptions options)
    {
        base.Setup(options);

        options.PublicDefinitions.Add("COMPILE_WITH_ASTERCORE_PHYSICS");
        options.PublicIncludePaths.Add(FolderPath);
        options.PublicIncludePaths.Add(Path.Combine(FolderPath, "AsterCore"));
        options.SourcePaths.Clear();
        options.SourcePaths.Add(Path.Combine(FolderPath, "AsterCore"));
    }
}


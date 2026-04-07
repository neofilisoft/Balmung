// Copyright (c) 2012-2024 Flax Engine. All rights reserved.

using System;
using System.IO;
using Balmung.Build;

namespace Flax.Deploy
{
    /// <summary>
    /// Balmung.Build environment and tools.
    /// </summary>
    class FlaxBuild
    {
        public static void Build(string root, string target, TargetPlatform platform, TargetArchitecture architecture, TargetConfiguration configuration)
        {
            var buildPlatform = Platform.BuildPlatform.Target;
            var balmungBuildTool = Path.Combine(Globals.EngineRoot, buildPlatform == TargetPlatform.Windows ? "Binaries/Tools/Balmung.Build.exe" : "Binaries/Tools/Balmung.Build");
            var balmungBuildTool = Path.Combine(Globals.EngineRoot, buildPlatform == TargetPlatform.Windows ? "Binaries/Tools/Balmung.Build.exe" : "Binaries/Tools/Balmung.Build");
            var buildToolPath = File.Exists(balmungBuildTool) ? balmungBuildTool : balmungBuildTool;
            var format = "-build -buildtargets={0} -log -logfile= -platform={1} -arch={2} -configuration={3}";
            var cmdLine = string.Format(format, target, platform, architecture, configuration);
            Configuration.PassArgs(ref cmdLine);

            Log.Info($"Building {target} for {platform} {architecture} {configuration}...");
            int result = Utilities.Run(buildToolPath, cmdLine, null, root);
            if (result != 0)
            {
                throw new Exception(string.Format("Unable to build target {0}. Balmung.Build failed. See log to learn more.", target));
            }
        }
    }
}




// Copyright (c) Neofilisoft. All rights reserved.

using System;
using System.IO;

namespace Balmung.Build.Platforms
{
    public sealed class EmscriptenSdk
    {
        public static readonly EmscriptenSdk Instance = new EmscriptenSdk();

        public readonly string RootPath;
        public readonly string EmscriptenRoot;
        public readonly string NodePath;
        public readonly string PythonPath;
        public readonly string EmccPath;
        public readonly string EmppPath;
        public readonly string EmarPath;
        public readonly string EmstripPath;
        public readonly bool IsValid;

        private EmscriptenSdk()
        {
            RootPath = Configuration.EmscriptenSdkPath;
            if (string.IsNullOrEmpty(RootPath))
                RootPath = Environment.GetEnvironmentVariable("EMSDK");
            if (string.IsNullOrEmpty(RootPath))
                return;

            RootPath = Utilities.NormalizePath(RootPath);
            EmscriptenRoot = Path.Combine(RootPath, "upstream", "emscripten");
            var exe = Platform.BuildTargetPlatform == TargetPlatform.Windows ? ".bat" : string.Empty;
            NodePath = Platform.BuildTargetPlatform == TargetPlatform.Windows ? Path.Combine(RootPath, "node", "18.20.3_64bit", "bin", "node.exe") : "node";
            PythonPath = Platform.BuildTargetPlatform == TargetPlatform.Windows ? Path.Combine(RootPath, "python", "3.11.4_64bit", "python.exe") : "python3";
            EmccPath = Path.Combine(EmscriptenRoot, "emcc" + exe);
            EmppPath = Path.Combine(EmscriptenRoot, "em++" + exe);
            EmarPath = Path.Combine(EmscriptenRoot, "emar" + exe);
            EmstripPath = Path.Combine(EmscriptenRoot, "emstrip" + exe);
            IsValid = Directory.Exists(EmscriptenRoot) && File.Exists(EmppPath);
            if (!IsValid)
                Log.Warning($"Missing Emscripten SDK at {EmscriptenRoot}. Web target will be unavailable.");
        }
    }
}


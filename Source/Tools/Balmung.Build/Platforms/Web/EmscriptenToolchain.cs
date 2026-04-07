// Copyright (c) Neofilisoft. All rights reserved.

using System;
using System.Collections.Generic;
using Balmung.Build.Graph;
using Balmung.Build.NativeCpp;

namespace Balmung.Build
{
    partial class Configuration
    {
        [CommandLine("emsdk", "<path>", "Overrides the Emscripten SDK root path (otherwise EMSDK env var is used).")]
        public static string EmscriptenSdkPath;
    }
}

namespace Balmung.Build.Platforms
{
    public sealed class EmscriptenToolchain : UnixToolchain
    {
        public EmscriptenToolchain(WebPlatform platform, TargetArchitecture architecture)
            : base(platform, architecture)
        {
            if (architecture != TargetArchitecture.Wasm32)
                throw new InvalidArchitectureException(architecture);

            var sdk = EmscriptenSdk.Instance;
            if (!sdk.IsValid)
                throw new Exception("Missing Emscripten SDK.");

            ToolsetRoot = sdk.RootPath;
            ArchitectureName = "wasm32-unknown-emscripten";
            ClangPath = sdk.EmppPath;
            ArPath = sdk.EmarPath;
            LlvmArPath = sdk.EmarPath;
            RanlibPath = sdk.EmarPath;
            StripPath = sdk.EmstripPath;
            ObjcopyPath = sdk.EmccPath;
            LdPath = sdk.EmppPath;
            LdKind = null;
            ClangVersion = GetClangVersion(TargetPlatform.Web, sdk.EmppPath);
            LibStdCppVersion = string.Empty;
        }

        public override void SetupEnvironment(BuildOptions options)
        {
            base.SetupEnvironment(options);
            options.CompileEnv.PreprocessorDefinitions.Add("PLATFORM_WEB");
            options.CompileEnv.PreprocessorDefinitions.Add("PLATFORM_UNIX");
            options.CompileEnv.PreprocessorDefinitions.Add("__EMSCRIPTEN__");
            options.LinkEnv.Output = LinkerOutput.Executable;
        }

        protected override void SetupCompileCppFilesArgs(TaskGraph graph, BuildOptions options, List<string> args, string outputPath)
        {
            args.Add("-target wasm32-unknown-emscripten");
            args.Add("-s WASM=1");
            args.Add("-s USE_WEBGL2=1");
            args.Add("-s FULL_ES3=1");
            args.Add("-s FORCE_FILESYSTEM=1");
            args.Add("-s FETCH=1");
            args.Add("-fwasm-exceptions");
        }

        protected override void SetupLinkFilesArgs(TaskGraph graph, BuildOptions options, List<string> args, string outputFilePath)
        {
            args.Add("-s WASM=1");
            args.Add("-s USE_WEBGL2=1");
            args.Add("-s FULL_ES3=1");
            args.Add("-s ALLOW_MEMORY_GROWTH=1");
            args.Add("-s FORCE_FILESYSTEM=1");
            args.Add("-s FETCH=1");
            args.Add("-s EXIT_RUNTIME=0");
            args.Add("-s ASSERTIONS=1");
            args.Add("--shell-file \"Source/Platforms/Web/Binaries/Tools/balmung_shell.html\"");
            args.Add("-fwasm-exceptions");
        }

        protected override Task CreateBinary(TaskGraph graph, BuildOptions options, string outputFilePath)
        {
            var task = base.CreateBinary(graph, options, outputFilePath);
            task.CommandPath = ClangPath;
            return task;
        }
    }
}


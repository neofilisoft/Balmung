// Copyright (c) Neofilisoft. All rights reserved.

using Balmung.Build.Projects;

namespace Balmung.Build.Platforms
{
    public sealed class WebPlatform : Platform
    {
        public override TargetPlatform Target => TargetPlatform.Web;
        public override bool HasRequiredSDKsInstalled => EmscriptenSdk.Instance.IsValid;
        public override bool HasSharedLibrarySupport => false;
        public override bool HasModularBuildSupport => false;
        public override bool HasDynamicCodeExecutionSupport => false;
        public override string ExecutableFileExtension => ".html";
        public override string SharedLibraryFileExtension => ".wasm";
        public override string StaticLibraryFileExtension => ".a";
        public override string ProgramDatabaseFileExtension => string.Empty;
        public override ProjectFormat DefaultProjectFormat => ProjectFormat.VisualStudioCode;

        protected override Toolchain CreateToolchain(TargetArchitecture architecture)
        {
            return new EmscriptenToolchain(this, architecture);
        }

        public override bool CanBuildPlatform(TargetPlatform platform)
        {
            return platform == TargetPlatform.Web && HasRequiredSDKsInstalled;
        }
    }
}


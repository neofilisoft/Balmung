// Copyright (c) Neofilisoft. All rights reserved.

namespace BalmungEditor.Utilities
{
    /// <summary>
    /// Editor constants and global properties.
    /// </summary>
    internal class Constants
    {
        public const string DiscordUrl = "https://balmungengine.com/discord";
        public const string DocsUrl = "https://docs.balmungengine.com/";
        public const string BugTrackerUrl = "https://github.com/FlaxEngine/FlaxEngine/issues";
        public const string WebsiteUrl = "https://balmungengine.com";
        public const string FacebookUrl = "https://facebook.com/FlaxEngine";
        public const string YoutubeUrl = "https://youtube.com/c/FlaxEngine";
        public const string TwitterUrl = "https://twitter.com/FlaxEngine";

#if PLATFORM_MAC
        public const string ShowInExplorer = "Show in Finder";
#else
        public const string ShowInExplorer = "Show in explorer";
#endif

        public const float UIMargin = 3.0f;
    }
}



// Copyright (c) Neofilisoft. All rights reserved.

using System;

namespace Balmung.Build
{
    internal class BuildException : Exception
    {
        public BuildException(string message)
        : base(message)
        {
        }
    }
}



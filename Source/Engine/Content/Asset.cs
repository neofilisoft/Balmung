// Copyright (c) Neofilisoft. All rights reserved.

namespace BalmungEngine
{
    partial class Asset
    {
        /// <inheritdoc />
        public override string ToString()
        {
            return $"{Path} ({GetType().Name})";
        }
    }
}



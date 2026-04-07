// Copyright (c) Neofilisoft. All rights reserved.

namespace BalmungEngine
{
    partial struct AudioDataInfo
    {
        /// <summary>
        /// Gets the length of the audio data (in seconds).
        /// </summary>
        public float Length => (float)NumSamples / (float)Mathf.Max(1U, SampleRate * NumChannels);
    }
}



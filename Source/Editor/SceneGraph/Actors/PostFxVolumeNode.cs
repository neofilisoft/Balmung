// Copyright (c) Neofilisoft. All rights reserved.

using FlaxEngine;

namespace BalmungEditor.SceneGraph.Actors
{
    /// <summary>
    /// Actor node for <see cref="PostFxVolume"/>.
    /// </summary>
    /// <seealso cref="ActorNode" />
    [HideInEditor]
    public sealed class PostFxVolumeNode : BoxVolumeNode
    {
        /// <inheritdoc />
        public PostFxVolumeNode(Actor actor)
        : base(actor)
        {
        }
    }
}



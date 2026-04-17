// Copyright (c) Neofilisoft. All rights reserved.

using FlaxEngine;

namespace BalmungEditor.SceneGraph.Actors
{
    /// <summary>
    /// Scene tree node for <see cref="BoneSocket"/> actor type.
    /// </summary>
    /// <seealso cref="ActorNode" />
    [HideInEditor]
    public sealed class BoneSocketNode : ActorNode
    {
        /// <inheritdoc />
        public BoneSocketNode(Actor actor)
        : base(actor)
        {
        }
    }
}



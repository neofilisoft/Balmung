// Copyright (c) Neofilisoft. All rights reserved.

using FlaxEngine;

namespace BalmungEditor.SceneGraph.Actors
{
    /// <summary>
    /// Scene tree node for <see cref="Sky"/> actor type.
    /// </summary>
    /// <seealso cref="ActorNodeWithIcon" />
    [HideInEditor]
    public sealed class SkyNode : ActorNodeWithIcon
    {
        /// <inheritdoc />
        public SkyNode(Actor actor)
        : base(actor)
        {
        }
    }
}



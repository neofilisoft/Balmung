// Copyright (c) Neofilisoft. All rights reserved.

using FlaxEngine;

namespace BalmungEditor.SceneGraph.Actors
{
    /// <summary>
    /// Scene tree node for <see cref="SkyLight"/> actor type.
    /// </summary>
    /// <seealso cref="ActorNodeWithIcon" />
    [HideInEditor]
    public sealed class SkyLightNode : ActorNodeWithIcon
    {
        /// <inheritdoc />
        public SkyLightNode(Actor actor)
        : base(actor)
        {
        }
    }
}



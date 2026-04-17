// Copyright (c) Neofilisoft. All rights reserved.

using FlaxEngine;

namespace BalmungEditor.SceneGraph.Actors
{
    /// <summary>
    /// Scene tree node for <see cref="AudioSource"/> actor type.
    /// </summary>
    /// <seealso cref="ActorNodeWithIcon" />
    [HideInEditor]
    public sealed class AudioSourceNode : ActorNodeWithIcon
    {
        /// <inheritdoc />
        public AudioSourceNode(Actor actor)
        : base(actor)
        {
        }
    }
}



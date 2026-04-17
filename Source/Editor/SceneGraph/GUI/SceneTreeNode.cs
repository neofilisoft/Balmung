// Copyright (c) Neofilisoft. All rights reserved.

using BalmungEditor.SceneGraph.Actors;
using FlaxEngine;
using BalmungEngine.GUI;

namespace BalmungEditor.SceneGraph.GUI
{
    /// <summary>
    /// A <see cref="ActorTreeNode"/> custom implementation for <see cref="SceneNode"/>.
    /// </summary>
    /// <seealso cref="BalmungEditor.SceneGraph.GUI.ActorTreeNode" />
    public sealed class SceneTreeNode : ActorTreeNode
    {
        /// <inheritdoc />
        public override void UpdateText()
        {
            base.UpdateText();

            // Append asset name if used
            var filename = ((Scene)Actor).Filename;
            if (!string.IsNullOrEmpty(filename))
            {
                Text += " (";
                Text += filename;
                Text += ")";
            }

            // Append star character to modified scenes
            if (ActorNode is SceneNode node && node.IsEdited)
                Text += "*";
        }

        /// <inheritdoc />
        protected override Color CacheTextColor()
        {
            return Style.Current.Foreground;
        }
    }
}



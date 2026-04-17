// Copyright (c) Neofilisoft. All rights reserved.

using FlaxEngine;

namespace BalmungEditor.SceneGraph.Actors
{
    /// <summary>
    /// Scene tree node for <see cref="TextRender"/> actor type.
    /// </summary>
    /// <seealso cref="ActorNode" />
    [HideInEditor]
    public sealed class TextRenderNode : ActorNode
    {
        /// <inheritdoc />
        public TextRenderNode(Actor actor)
        : base(actor)
        {
        }

        /// <inheritdoc />
        public override void PostSpawn()
        {
            base.PostSpawn();

            if (Actor.HasPrefabLink)
            {
                return;
            }

            // Setup for default values
            var text = (TextRender)Actor;
            text.Text = "My Text";
            text.Font = BalmungEngine.Content.LoadAsyncInternal<FontAsset>(EditorAssets.PrimaryFont);
            text.Material = BalmungEngine.Content.LoadAsyncInternal<MaterialBase>(EditorAssets.DefaultFontMaterial);
        }
    }
}



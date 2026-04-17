// Copyright (c) Neofilisoft. All rights reserved.

using BalmungEngine.GUI;

namespace BalmungEditor.CustomEditors.Elements
{
    /// <summary>
    /// The image element.
    /// </summary>
    /// <seealso cref="BalmungEditor.CustomEditors.LayoutElement" />
    public class ImageElement : LayoutElement
    {
        /// <summary>
        /// The image.
        /// </summary>
        public readonly Image Image = new Image();

        /// <inheritdoc />
        public override Control Control => Image;
    }
}



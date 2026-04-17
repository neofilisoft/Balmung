// Copyright (c) Neofilisoft. All rights reserved.

using FlaxEngine;
using BalmungEngine.GUI;

namespace BalmungEditor.CustomEditors.Elements
{
    /// <summary>
    /// The button element.
    /// </summary>
    /// <seealso cref="BalmungEditor.CustomEditors.LayoutElement" />
    public class ButtonElement : LayoutElement
    {
        /// <summary>
        /// The button.
        /// </summary>
        public readonly Button Button = new Button();

        /// <inheritdoc />
        public override Control Control => Button;
    }
}



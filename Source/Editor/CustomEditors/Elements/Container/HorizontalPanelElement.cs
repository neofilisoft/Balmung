// Copyright (c) Neofilisoft. All rights reserved.

using FlaxEngine;
using BalmungEngine.GUI;

namespace BalmungEditor.CustomEditors.Elements
{
    /// <summary>
    /// The horizontal panel element.
    /// </summary>
    /// <seealso cref="BalmungEditor.CustomEditors.LayoutElement" />
    public class HorizontalPanelElement : LayoutElementsContainer
    {
        /// <summary>
        /// The panel.
        /// </summary>
        public readonly HorizontalPanel Panel = new HorizontalPanel
        {
            Pivot = Float2.Zero,
        };

        /// <inheritdoc />
        public override ContainerControl ContainerControl => Panel;
    }
}



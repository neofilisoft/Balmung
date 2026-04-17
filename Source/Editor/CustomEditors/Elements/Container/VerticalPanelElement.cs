// Copyright (c) Neofilisoft. All rights reserved.

using FlaxEngine;
using BalmungEngine.GUI;

namespace BalmungEditor.CustomEditors.Elements
{
    /// <summary>
    /// The vertical panel element.
    /// </summary>
    /// <seealso cref="BalmungEditor.CustomEditors.LayoutElement" />
    public class VerticalPanelElement : LayoutElementsContainer
    {
        /// <summary>
        /// The panel.
        /// </summary>
        public readonly VerticalPanel Panel = new VerticalPanel
        {
            Pivot = Float2.Zero,
        };

        /// <inheritdoc />
        public override ContainerControl ContainerControl => Panel;
    }
}



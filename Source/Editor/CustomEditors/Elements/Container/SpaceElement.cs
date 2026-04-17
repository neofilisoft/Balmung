// Copyright (c) Neofilisoft. All rights reserved.

using BalmungEngine.GUI;

namespace BalmungEditor.CustomEditors.Elements
{
    /// <summary>
    /// The spacer element.
    /// </summary>
    /// <seealso cref="BalmungEditor.CustomEditors.LayoutElementsContainer" />
    public class SpaceElement : LayoutElementsContainer
    {
        /// <summary>
        /// The spacer.
        /// </summary>
        public readonly Spacer Spacer = new Spacer(0, 0);

        /// <summary>
        /// Initializes the element.
        /// </summary>
        /// <param name="height">The height.</param>
        public void Init(float height)
        {
            Spacer.Height = height;
        }

        /// <inheritdoc />
        public override ContainerControl ContainerControl => Spacer;
    }
}



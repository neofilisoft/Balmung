// Copyright (c) Neofilisoft. All rights reserved.

using BalmungEngine.GUI;

namespace BalmungEditor.CustomEditors.Elements
{
    /// <summary>
    /// The custom layout element.
    /// </summary>
    /// <seealso cref="BalmungEditor.CustomEditors.LayoutElementsContainer" />
    public class CustomElementsContainer<T> : LayoutElementsContainer
    where T : ContainerControl, new()
    {
        /// <summary>
        /// The custom control.
        /// </summary>
        public readonly T CustomControl = new T();

        /// <inheritdoc />
        public override ContainerControl ContainerControl => CustomControl;
    }

    /// <summary>
    /// The custom layout element.
    /// </summary>
    /// <seealso cref="BalmungEditor.CustomEditors.LayoutElement" />
    public class CustomElement<T> : LayoutElement
    where T : Control, new()
    {
        /// <summary>
        /// The custom control.
        /// </summary>
        public readonly T CustomControl = new T();

        /// <inheritdoc />
        public override Control Control => CustomControl;
    }
}



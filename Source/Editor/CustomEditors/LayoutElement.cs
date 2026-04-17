// Copyright (c) Neofilisoft. All rights reserved.

using FlaxEngine;
using BalmungEngine.GUI;

namespace BalmungEditor.CustomEditors
{
    /// <summary>
    /// Represents single element of the Custom Editor layout.
    /// </summary>
    [HideInEditor]
    public abstract class LayoutElement
    {
        /// <summary>
        /// Gets the control represented by this element.
        /// </summary>
        public abstract Control Control { get; }
    }
}



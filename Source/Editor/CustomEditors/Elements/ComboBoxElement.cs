// Copyright (c) Neofilisoft. All rights reserved.

using BalmungEditor.GUI;
using BalmungEngine.GUI;

namespace BalmungEditor.CustomEditors.Elements
{
    /// <summary>
    /// The combobox element.
    /// </summary>
    /// <seealso cref="BalmungEditor.CustomEditors.LayoutElement" />
    public class ComboBoxElement : LayoutElement
    {
        /// <summary>
        /// The combo box.
        /// </summary>
        public readonly ComboBox ComboBox;

        /// <summary>
        /// Initializes a new instance of the <see cref="ComboBoxElement"/> class.
        /// </summary>
        public ComboBoxElement()
        {
            ComboBox = new ComboBox();
        }

        /// <inheritdoc />
        public override Control Control => ComboBox;
    }
}



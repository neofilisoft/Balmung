// Copyright (c) Neofilisoft. All rights reserved.

using BalmungEngine.GUI;

namespace BalmungEditor.CustomEditors.Elements
{
    /// <summary>
    /// The checkbox element.
    /// </summary>
    /// <seealso cref="BalmungEditor.CustomEditors.LayoutElement" />
    public class CheckBoxElement : LayoutElement
    {
        /// <summary>
        /// The check box.
        /// </summary>
        public readonly CheckBox CheckBox;

        /// <summary>
        /// Initializes a new instance of the <see cref="CheckBoxElement"/> class.
        /// </summary>
        public CheckBoxElement()
        {
            CheckBox = new CheckBox(0, 0);
        }

        /// <inheritdoc />
        public override Control Control => CheckBox;
    }
}



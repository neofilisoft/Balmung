// Copyright (c) Neofilisoft. All rights reserved.

using BalmungEditor.GUI.Tree;
using BalmungEngine.GUI;

namespace BalmungEditor.CustomEditors.Elements
{
    /// <summary>
    /// The tree structure element.
    /// </summary>
    /// <seealso cref="BalmungEditor.CustomEditors.LayoutElementsContainer" />
    public class TreeElement : LayoutElementsContainer, ITreeElement
    {
        /// <summary>
        /// The tree control.
        /// </summary>
        public readonly Tree TreeControl = new Tree(false);

        /// <inheritdoc />
        public override ContainerControl ContainerControl => TreeControl;

        /// <inheritdoc />
        public TreeNodeElement Node(string text)
        {
            TreeNodeElement element = new TreeNodeElement();
            element.TreeNode.Text = text;
            OnAddElement(element);
            return element;
        }
    }
}



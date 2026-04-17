// Copyright (c) Neofilisoft. All rights reserved.

using BalmungEditor.History;

namespace BalmungEditor
{
    /// <summary>
    /// Interface for <see cref="Undo"/> actions.
    /// </summary>
    /// <seealso cref="BalmungEditor.History.IHistoryAction" />
    public interface IUndoAction : IHistoryAction
    {
        /// <summary>
        /// Performs this action.
        /// </summary>
        void Do();

        /// <summary>
        /// Undoes this action.
        /// </summary>
        void Undo();
    }
}



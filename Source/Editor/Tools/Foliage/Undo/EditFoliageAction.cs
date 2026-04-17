// Copyright (c) Neofilisoft. All rights reserved.

using System;
using FlaxEngine;

namespace BalmungEditor.Tools.Foliage.Undo
{
    /// <summary>
    /// The foliage editing action that records before and after states to swap between unmodified and modified foliage data.
    /// </summary>
    /// <seealso cref="BalmungEditor.IUndoAction" />
    [Serializable, HideInEditor]
    public sealed class EditFoliageAction : IUndoAction
    {
        [Serialize]
        private readonly Guid _foliageId;

        [Serialize]
        private string _before;

        [Serialize]
        private string _after;

        /// <summary>
        /// Initializes a new instance of the <see cref="EditFoliageAction"/> class.
        /// </summary>
        /// <remarks>Use <see cref="RecordEnd"/> to finalize foliage data after editing action.</remarks>
        /// <param name="foliage">The foliage.</param>
        public EditFoliageAction(BalmungEngine.Foliage foliage)
        {
            _foliageId = foliage.ID;
            _before = foliage.ToJson();
        }

        /// <summary>
        /// Called when foliage editing ends. Records the `after` state of the actor. Marks foliage actor parent scene edited.
        /// </summary>
        public void RecordEnd()
        {
            var foliageId = _foliageId;
            var foliage = BalmungEngine.Object.Find<BalmungEngine.Foliage>(ref foliageId);

            _after = foliage.ToJson();

            Editor.Instance.Scene.MarkSceneEdited(foliage.Scene);
        }

        /// <inheritdoc />
        public string ActionString => "Edit foliage";

        /// <inheritdoc />
        public void Do()
        {
            Set(_after);
        }

        /// <inheritdoc />
        public void Undo()
        {
            Set(_before);
        }

        /// <inheritdoc />
        public void Dispose()
        {
            _before = null;
            _after = null;
        }

        private void Set(string data)
        {
            var foliageId = _foliageId;
            var foliage = BalmungEngine.Object.Find<BalmungEngine.Foliage>(ref foliageId);

            foliage.FromJson(data);

            Editor.Instance.Scene.MarkSceneEdited(foliage.Scene);
        }
    }
}



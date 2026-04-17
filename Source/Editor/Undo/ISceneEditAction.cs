// Copyright (c) Neofilisoft. All rights reserved.

using BalmungEditor.Modules;

namespace BalmungEditor
{
    /// <summary>
    /// Interface for undo action that can modify scene data (actors, scripts, etc.)
    /// </summary>
    public interface ISceneEditAction
    {
        /// <summary>
        /// Marks the scenes edited.
        /// </summary>
        /// <param name="sceneModule">The scene module.</param>
        void MarkSceneEdited(SceneModule sceneModule);
    }
}



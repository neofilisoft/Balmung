// Copyright (c) Neofilisoft. All rights reserved.

using FlaxEngine;

namespace BalmungEditor.Progress.Handlers
{
    /// <summary>
    /// Navigation mesh building progress reporting handler.
    /// </summary>
    /// <seealso cref="BalmungEditor.Progress.ProgressHandler" />
    public sealed class NavMeshBuildingProgress : ProgressHandler
    {
        private bool _isActive;

        /// <summary>
        /// Initializes a new instance of the <see cref="NavMeshBuildingProgress"/> class.
        /// </summary>
        public NavMeshBuildingProgress()
        {
            BalmungEngine.Scripting.Update += OnUpdate;
        }

        private void OnUpdate()
        {
            bool isActive = Navigation.IsBuildingNavMesh;

            if (_isActive != isActive)
            {
                _isActive = isActive;

                if (isActive)
                {
                    OnStart();
                }
                else
                {
                    OnEnd();
                }
            }

            if (isActive)
            {
                OnUpdate(Navigation.NavMeshBuildingProgress, "Building navmesh...");
            }
        }
    }
}



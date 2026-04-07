// Copyright (c) Neofilisoft. All rights reserved.

namespace BalmungEngine.Networking
{
    partial struct NetworkReplicationHierarchyObject
    {
        /// <summary>
        /// Gets the actors context (object itself or parent actor).
        /// </summary>
        public Actor Actor
        {
            get
            {
                var actor = Object as Actor;
                if (actor == null)
                {
                    var sceneObject = Object as SceneObject;
                    if (sceneObject != null)
                        actor = sceneObject.Parent;
                }
                return actor;
            }
        }
    }
}



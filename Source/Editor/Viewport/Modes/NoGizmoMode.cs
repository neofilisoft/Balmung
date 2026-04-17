// Copyright (c) Neofilisoft. All rights reserved.

namespace BalmungEditor.Viewport.Modes
{
    /// <summary>
    /// The editor gizmo editor mode that does nothing. Can be used to hide other gizmos when using a specific editor tool.
    /// </summary>
    /// <seealso cref="BalmungEditor.Viewport.Modes.EditorGizmoMode" />
    public class NoGizmoMode : EditorGizmoMode
    {
        /// <inheritdoc />
        public override void OnActivated()
        {
            base.OnActivated();

            Owner.Gizmos.Active = null;
        }
    }
}



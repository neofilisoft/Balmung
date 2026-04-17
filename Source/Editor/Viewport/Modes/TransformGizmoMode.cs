// Copyright (c) Neofilisoft. All rights reserved.

namespace BalmungEditor.Viewport.Modes
{
    /// <summary>
    /// The default editor mode that uses <see cref="BalmungEditor.Gizmo.TransformGizmoBase"/> for objects transforming.
    /// </summary>
    /// <seealso cref="BalmungEditor.Viewport.Modes.EditorGizmoMode" />
    public class TransformGizmoMode : EditorGizmoMode
    {
        /// <inheritdoc />
        public override void OnActivated()
        {
            base.OnActivated();

            Owner.Gizmos.Active = ((MainEditorGizmoViewport)Owner).TransformGizmo;
        }
    }
}



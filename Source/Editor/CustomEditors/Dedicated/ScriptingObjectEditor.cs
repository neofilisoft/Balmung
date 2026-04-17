// Copyright (c) Neofilisoft. All rights reserved.

using BalmungEditor.CustomEditors.Editors;
using BalmungEngine.Networking;

namespace BalmungEditor.CustomEditors.Dedicated
{
    /// <summary>
    /// Custom editor for <see cref="BalmungEngine.Object"/>.
    /// </summary>
    public class ScriptingObjectEditor : GenericEditor
    {
        /// <inheritdoc />
        public override void Initialize(LayoutElementsContainer layout)
        {
            // Network objects debugging
            var obj = Values[0] as BalmungEngine.Object;
            if (Editor.IsPlayMode && NetworkManager.IsConnected && NetworkReplicator.HasObject(obj))
            {
                var group = layout.Group("Network");
                group.Panel.Open();
                group.Label("Role", Utilities.Utils.GetPropertyNameUI(NetworkReplicator.GetObjectRole(obj).ToString()));
                group.Label("Owner Client Id", NetworkReplicator.GetObjectOwnerClientId(obj).ToString());
            }

            base.Initialize(layout);
        }
    }
}



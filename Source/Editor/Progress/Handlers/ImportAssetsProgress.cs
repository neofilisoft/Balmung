// Copyright (c) Neofilisoft. All rights reserved.

using BalmungEditor.Content;
using BalmungEditor.Content.Import;

namespace BalmungEditor.Progress.Handlers
{
    /// <summary>
    /// Importing assets progress reporting handler.
    /// </summary>
    /// <seealso cref="BalmungEditor.Progress.ProgressHandler" />
    public sealed class ImportAssetsProgress : ProgressHandler
    {
        private string _currentInfo;

        /// <summary>
        /// Initializes a new instance of the <see cref="ImportAssetsProgress"/> class.
        /// </summary>
        public ImportAssetsProgress()
        {
            var importing = Editor.Instance.ContentImporting;
            importing.ImportingQueueBegin += () => BalmungEngine.Scripting.InvokeOnUpdate(OnStart);
            importing.ImportingQueueEnd += () => BalmungEngine.Scripting.InvokeOnUpdate(OnEnd);
            importing.ImportFileBegin += OnImportFileBegin;
        }

        private void OnImportFileBegin(IFileEntryAction importFileEntry)
        {
            string info;
            if (importFileEntry is ImportFileEntry)
                info = string.Format("Importing \'{0}\'", System.IO.Path.GetFileName(importFileEntry.SourceUrl));
            else
                info = string.Format("Creating \'{0}\'", importFileEntry.SourceUrl);
            BalmungEngine.Scripting.InvokeOnUpdate(() =>
            {
                _currentInfo = info;
                var importing = Editor.Instance.ContentImporting;
                var text = string.Format("{0} ({1}/{2})...", _currentInfo, importing.ImportBatchDone, importing.ImportBatchSize);
                OnUpdate(importing.ImportingProgress, text);
            });
        }
    }
}



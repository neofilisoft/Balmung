// Copyright (c) Neofilisoft. All rights reserved.

using BalmungEditor.Utilities;

namespace BalmungEditor.Progress.Handlers
{
    /// <summary>
    /// Scripts compilation progress reporting handler.
    /// </summary>
    /// <seealso cref="BalmungEditor.Progress.ProgressHandler" />
    public sealed class CompileScriptsProgress : ProgressHandler
    {
        private SelectionCache _selectionCache;

        /// <summary>
        /// Initializes a new instance of the <see cref="CompileScriptsProgress"/> class.
        /// </summary>
        public CompileScriptsProgress()
        {
            // Link for events
            ScriptsBuilder.CompilationBegin += OnStart;
            ScriptsBuilder.CompilationSuccess += OnEnd;
            ScriptsBuilder.CompilationFailed += OnCompilationFailed;
            ScriptsBuilder.CompilationStarted += () => OnUpdate(0.2f, "Compiling scripts...");
            ScriptsBuilder.ScriptsReloadCalled += () => OnUpdate(0.8f, "Reloading scripts...");
            ScriptsBuilder.ScriptsReloadBegin += OnScriptsReloadBegin;
            ScriptsBuilder.ScriptsReloadEnd += OnScriptsReloadEnd;
        }

        private void OnScriptsReloadBegin()
        {
            if (_selectionCache == null)
                _selectionCache = new SelectionCache();
            _selectionCache.Cache();

            // Clear references to the user scripts (we gonna reload an assembly)
            Editor.Instance.Scene.ClearRefsToSceneObjects(true);
        }

        private void OnCompilationFailed()
        {
            OnFail("Scripts compilation failed");
        }

        private void OnScriptsReloadEnd()
        {
            _selectionCache.Restore();
        }

        /// <inheritdoc />
        protected override void OnStart()
        {
            base.OnStart();

            OnUpdate(0, "Starting scripts compilation...");
        }
    }
}



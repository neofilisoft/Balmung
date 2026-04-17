// Copyright (c) Neofilisoft. All rights reserved.

using FlaxEngine;
using BalmungEditor.Utilities;
using BalmungEngine.Utilities;

namespace BalmungEditor.Tools.Terrain.Sculpt
{
    /// <summary>
    /// Sculpt tool mode that applies the noise to the terrain heightmap area affected by brush.
    /// </summary>
    /// <seealso cref="BalmungEditor.Tools.Terrain.Sculpt.Mode" />
    [HideInEditor]
    public sealed class NoiseMode : Mode
    {
        /// <summary>
        /// The tool noise scale. Adjusts the noise pattern scale.
        /// </summary>
        [EditorOrder(10), Limit(0, 10000), Tooltip("The tool noise scale. Adjusts the noise pattern scale.")]
        public float NoiseScale = 128.0f;

        /// <summary>
        /// The tool noise amount scale. Adjusts the noise amplitude scale.
        /// </summary>
        [EditorOrder(10), Limit(0, 10000000), Tooltip("The tool noise amount scale. Adjusts the noise amplitude scale.")]
        public float NoiseAmount = 10000.0f;

        /// <inheritdoc />
        public override bool SupportsNegativeApply => true;

        /// <inheritdoc />
        public override unsafe void ApplyBrushToPatch(ref ApplyParams p)
        {
            // Prepare
            var brushPosition = p.Gizmo.CursorPosition;
            var noise = new PerlinNoise(0, NoiseScale, p.Strength * NoiseAmount);
            var chunkSize = p.Terrain.ChunkSize;
            var patchSize = chunkSize * BalmungEngine.Terrain.PatchEdgeChunksCount;
            var patchOffset = p.PatchCoord * patchSize;

            // Apply brush modification
            Profiler.BeginEvent("Apply Brush");
            for (int z = 0; z < p.ModifiedSize.Y; z++)
            {
                var zz = z + p.ModifiedOffset.Y;
                for (int x = 0; x < p.ModifiedSize.X; x++)
                {
                    var xx = x + p.ModifiedOffset.X;
                    var sourceHeight = p.SourceHeightMap[zz * p.HeightmapSize + xx];

                    var samplePositionLocal = p.PatchPositionLocal + new Vector3(xx * BalmungEngine.Terrain.UnitsPerVertex, sourceHeight, zz * BalmungEngine.Terrain.UnitsPerVertex);
                    Vector3.Transform(ref samplePositionLocal, ref p.TerrainWorld, out Vector3 samplePositionWorld);

                    var noiseSample = noise.Sample(xx + patchOffset.X, zz + patchOffset.Y);
                    var paintAmount = p.Brush.Sample(ref brushPosition, ref samplePositionWorld);

                    p.TempBuffer[z * p.ModifiedSize.X + x] = sourceHeight + noiseSample * paintAmount;
                }
            }
            Profiler.EndEvent();

            // Update terrain patch
            TerrainTools.ModifyHeightMap(p.Terrain, ref p.PatchCoord, p.TempBuffer, ref p.ModifiedOffset, ref p.ModifiedSize);
        }
    }
}



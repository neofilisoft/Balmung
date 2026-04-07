// Copyright (c) Neofilisoft. All rights reserved.


using BalmungEngine.Json;

namespace BalmungEngine
{
    partial class ModelInstanceActor
    {
        partial struct MeshReference : ICustomValueEquals
        {
            /// <inheritdoc />
            public bool ValueEquals(object other)
            {
                var o = (MeshReference)other;
                return JsonSerializer.ValueEquals(Actor, o.Actor) &&
                       LODIndex == o.LODIndex &&
                       MeshIndex == o.MeshIndex;
            }
        }
    }
}



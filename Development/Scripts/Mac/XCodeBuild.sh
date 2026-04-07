#!/bin/sh
# Copyright (c) Neofilisoft. All rights reserved

# Fix mono bin to be in a path
#export PATH=/Library/Frameworks/Mono.framework/Versions/Current/Commands:$PATH

echo "Running Balmung.Build $*"
Binaries/Tools/Balmung.Build "$@"



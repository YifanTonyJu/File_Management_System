#!/bin/bash

echo "Building backend..."

# Check if this is first time build
if [ ! -d "build" ] || [ ! -f "build/Makefile" ]; then
    echo "First time build - this will take 5-15 minutes..."
fi

mkdir -p build
cd build

if cmake .. && make -j$(nproc); then
    echo "Backend build completed!"
else
    echo "Build failed!"
    exit 1
fi

#!/bin/bash

echo "Setting up third-party libraries..."

# Create directory if it doesn't exist
mkdir -p backend/third_library

# Setup oatpp library
echo "Checking oatpp library..."
if [ ! -d "backend/third_library/oatpp" ] || [ ! -f "backend/third_library/oatpp/CMakeLists.txt" ]; then
    echo "Installing oatpp library..."
    rm -rf backend/third_library/oatpp
    git clone https://github.com/oatpp/oatpp.git backend/third_library/oatpp
    echo "Fixing oatpp for this project..."
    sed -i '315s/^set_target_source_groups/#set_target_source_groups/' backend/third_library/oatpp/src/CMakeLists.txt
    # Hide the modification from git status
    cd backend/third_library/oatpp
    git update-index --skip-worktree src/CMakeLists.txt
    cd ../../../
else
    echo "oatpp library is ready"
fi

# Setup json library
echo "Checking json library..."
if [ ! -d "backend/third_library/json" ] || [ ! -f "backend/third_library/json/CMakeLists.txt" ]; then
    echo "Installing json library..."
    rm -rf backend/third_library/json
    git clone https://github.com/nlohmann/json.git backend/third_library/json
else
    echo "json library is ready"
fi

echo "Third-party libraries setup complete!"

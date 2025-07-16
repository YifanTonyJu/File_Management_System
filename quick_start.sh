#!/bin/bash

echo "Quick starting File Management System..."

# Check if we need to setup libraries
if [ ! -f "backend/third_library/oatpp/CMakeLists.txt" ] || [ ! -f "backend/third_library/json/CMakeLists.txt" ]; then
    echo "Libraries missing, setting up..."
    ./setup_third_party.sh
fi

# Check if we need to build backend
if [ ! -f "backend/build/file-management-server" ]; then
    echo "Backend not built, building..."
    cd backend
    ./build_backend.sh
    cd ..
fi

# Start the servers
echo "Starting servers..."
cd backend/build
./file-management-server &
sleep 2

cd ../../frontend
npm run dev &
sleep 3

echo "System started!"
echo "Open your browser and go to: http://localhost:5173"

wait

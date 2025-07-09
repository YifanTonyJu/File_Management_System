#!/bin/bash

echo "Starting File Management System..."
echo "This may take 5-15 minutes for first time setup"

# Build backend
cd /home/yifan_ju/Internship/EASE/Internship_Project/backend
./build_backend.sh

# Start backend
cd build
./file-management-server &

sleep 3

# Start frontend
cd ../../frontend
./start_frontend.sh &

sleep 5

echo "System started!"
echo "Open your browser and visit: http://localhost:5173"

wait

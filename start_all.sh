#!/bin/bash

echo "Starting File Management System (First time setup)..."

# Step 1: Setup third-party libraries
echo "Step 1: Setting up libraries..."
./setup_third_party.sh

# Step 2: Build the backend
echo "Step 2: Building backend..."
cd backend
./build_backend.sh
cd ..

# Step 3: Install frontend dependencies
echo "Step 3: Installing frontend..."
cd frontend
npm install
cd ..

# Step 4: Start the servers
echo "Step 4: Starting servers..."
cd backend/build
./file-management-server &
sleep 3

cd ../../frontend
npm run dev &
sleep 5

echo "System is ready!"
echo "Open your browser and go to: http://localhost:5173"

wait

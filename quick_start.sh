#!/bin/bash

echo "Quick starting File Management System..."

# Start backend
cd backend/build
./file-management-server &

sleep 2

# Start frontend
cd ../../frontend
npm run dev &

sleep 5

echo "System started!"
echo "Open your browser and visit: http://localhost:5173"

wait

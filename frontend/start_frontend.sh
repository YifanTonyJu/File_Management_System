#!/bin/bash

echo "Starting frontend..."

# Install dependencies if needed
if [ ! -d "node_modules" ]; then
    echo "Installing dependencies..."
    npm install
fi

echo "Starting development server..."
npm run dev

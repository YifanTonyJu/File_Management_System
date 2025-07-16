# File Management System

A simple file management system with Vue.js frontend and C++ backend.

## How to Use

### First Time Setup
```bash
git clone https://github.com/YifanTonyJu/File_Management_System.git
cd File_Management_System
./start_all.sh
```

### After First Setup (Quick Start)
```bash
./quick_start.sh
```

## What Each Script Does

### `start_all.sh` - Use this for first time
- Downloads needed libraries
- Builds the backend
- Installs frontend packages
- Starts the servers

### `quick_start.sh` - Use this after first time
- Checks if everything is ready
- Only builds what's missing
- Starts the servers quickly

### `setup_third_party.sh` - Only if you need libraries
- Downloads oatpp and json libraries
- Fixes them for this project

## Project Structure

```
File_Management_System/
├── backend/           # C++ server
├── frontend/          # Vue.js website
├── start_all.sh       # First time setup
├── quick_start.sh     # Quick start
└── setup_third_party.sh # Library setup
```

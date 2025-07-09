# File Management System

A simple file management system built with Vue.js frontend and C++ backend.

## Project Structure

```
Internship_Project/
├── backend/                 # C++ backend server
│   ├── main.cpp            # Main server file
│   ├── database_api.cpp    # Database operations
│   ├── oatpp_data_controller.hpp  # API endpoints
│   ├── build_backend.sh    # Backend build script
│   └── build/              # Build output
├── frontend/               # Vue.js frontend
│   ├── src/
│   │   ├── views/          # Vue components
│   │   │   ├── Home.vue    # Main navigation
│   │   │   ├── AddFile.vue # Add new file
│   │   │   ├── DeleteFile.vue # Delete file
│   │   │   ├── UpdateFile.vue # Update file
│   │   │   ├── QueryAll.vue # List all files
│   │   │   ├── QueryByUser.vue # Query by user ID
│   │   │   └── QueryByFileName.vue # Query by file name
│   │   └── router/         # Vue routing
│   ├── package.json        # Dependencies
│   └── start_frontend.sh   # Frontend start script
└── start_all.sh           # Full project launcher
```

## Features

### File Operations
- **Add File** - Create new file records
- **Delete File** - Remove files by name
- **Update File** - Modify file information

### Query Operations
- **Query All Files** - List all files in database
- **Query by User** - Find files by user ID
- **Query by File Name** - Search specific files

## Technology Stack

### Backend
- **Language**: C++
- **Framework**: oat++ (Web framework)
- **Database**: MySQL
- **JSON**: nlohmann/json

### Frontend
- **Framework**: Vue.js 3
- **Build Tool**: Vite
- **Styling**: Scoped CSS
- **Routing**: Vue Router

## Quick Start

### Prerequisites
- Node.js and npm
- C++ compiler
- CMake

### Installation & Run

1. **Clone the repository**
   ```bash
   git clone https://github.com/YifanTonyJu/File_Management_System
   cd File_Management_System
   ```

2. **First-time setup**
   ```bash
   ./start_all.sh
   ```
   **Note**: First run takes 5-15 minutes to compile dependencies
   
3. **Quick start (after first setup)**
   ```bash
   ./quick_start.sh
   ```
   Fast startup for already built system

4. **Open your browser and visit**
   ```
   http://localhost:5173
   ```

## Startup Options

### First Time Setup
- **Script**: `./start_all.sh`
- **Time**: 5-15 minutes (downloads and compiles dependencies)
- **Use when**: First time running or after cleaning build files

### Quick Start  
- **Script**: `./quick_start.sh`
- **Time**: ~10 seconds
- **Use when**: System already built, want fast restart

### Manual Setup

#### Backend Only
```bash
cd backend
./build_backend.sh
```

#### Frontend Only
```bash
cd frontend
./start_frontend.sh
```

## API Endpoints

| Method | Endpoint | Description |
|--------|----------|-------------|
| POST | `/api/files` | Add new file |
| GET | `/api/files` | Get all files |
| PUT | `/api/files/{fileName}` | Update file |
| DELETE | `/api/files/{fileName}` | Delete file |
| GET | `/api/files/user/{userId}` | Get files by user |
| GET | `/api/files/name/{fileName}` | Get file by name |

## Usage

1. **Start the application** using `./start_all.sh`
2. **Navigate** through the web interface
3. **Manage files** using the provided operations
4. **Query data** using different search methods

## Development

- Backend runs on default port (check console output)
- Frontend runs on `http://localhost:5173`
- Both services start automatically with the main script

# C-Unplugged Music Application

A comprehensive command-line music management system demonstrating advanced data structures, dynamic memory management, and modular programming in C.

---

## Student Information

**Name**: Somesh Pawan Kamad 
**Roll Number**: 2025111013 
---

##  Project Structure

```
C-Unplugged/
├── C-Unplugged.c       # Main application entry point
├── C-Unplugged.h       # Main header with color definitions
├── Songs.c             # Song management implementation
├── Songs.h             # Song structure and function declarations
├── Albums.c            # Album management implementation
├── Albums.h            # Album structure and function declarations
├── Playlist.c          # Playlist management implementation
├── Playlist.h          # Playlist structure and function declarations
├── Logging.c           # Activity logging implementation
├── Logging.h           # Logging function declarations
├── Utils.c             # Utility functions (cloning, memory cleanup)
├── Utils.h             # Utility function declarations
├── Makefile            # Build automation
├── README.md           # This file
├── data/
│   ├── songs.txt       # Persistent song storage
│   └── albums.txt      # Persistent album storage
└── log.txt             # User activity log
```

##  Prerequisites

- **GCC Compiler** (version 7.0 or higher recommended)
- **Make** utility
- **Valgrind** (optional, for memory leak detection)
- Unix-like environment (Linux, macOS, WSL on Windows)

##  Compilation and Execution


### Build the Application
```bash
# Standard build
make
```
### Run the Application
```bash
# Method 1: Direct execution
./music_application

```

### Clean Build Artifacts
```bash
# Remove object files only
make clean

```
##  Makefile Commands Reference

| Command | Description |
|---------|-------------|
| `make` | Build the project with standard flags |
| `make clean` | Remove object files only |

### Known Limitations

1. **Input Format**: Requires CamelCase input (no spaces in names)
2. **Platform**: Best experience on Unix-like systems with ANSI color support
3. **Concurrent Access**: Not designed for multi-user simultaneous access

---

**End of README**



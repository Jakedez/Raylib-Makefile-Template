# Directories
DIRS = src inc obj obj/debug bin bin/debug lib lib/obj lib/include

# Compiler and flags
CC = gcc
AS = as
CFLAGS = -Iinc -Ilib/include -Wall -std=c11
LIBS = $(wildcard lib/obj/*.o) $(wildcard lib/obj/*.a)

# Files
SRC_C = $(wildcard src/*.c)
SRC_S = $(wildcard src/*.s)

# Release Build
OBJ = $(patsubst src/%, obj/%, $(SRC_C:.c=.o) $(SRC_S:.s=.o))
BIN = bin/main.exe
LDFLAGS_RELEASE = -Llib/obj $(shell cat link_release.txt 2>/dev/null)

# Debug Build
OBJ_DEBUG = $(patsubst src/%, obj/debug/%, $(SRC_C:.c=.o) $(SRC_S:.s=.o))
BIN_DEBUG = bin/debug/main_debug.exe
LDFLAGS_DEBUG = -Llib/obj $(shell cat link_debug.txt 2>/dev/null)

# Targets
.PHONY: generate remove remove_code build debug run run_debug clean generate_code help

# Help target
help:
	@echo "Makefile for building and running the project"
	@echo ""
	@echo "Usage:"
	@echo "  make [target]"
	@echo ""
	@echo "Targets:"
	@echo "  generate      Create project directory structure and link.txt file"
	@echo "  remove        Remove the project directory structure and link.txt file"
	@echo "  remove_code   Remove VS Code configuration"
	@echo "  build         Build the release version of the program (optimized)"
	@echo "  debug         Build the debug version of the program (with debugging info)"
	@echo "  run           Run the release version of the program"
	@echo "  run_debug     Run the debug version of the program in gdb"
	@echo "  clean         Clean up build files (object files and executables)"
	@echo "  generate_code Generate VS Code configuration files"
	@echo ""
	@echo "Optimizations:"
	@echo "  Release: -O2 optimization for better performance"
	@echo "  Debug: -O1 optimization for better debugging experience"

generate:
	@echo Creating project directory structure...
	@mkdir -p $(DIRS)
	@touch link_release.txt link_debug.txt
	@echo Done!

remove:
	@echo Removing project directory structure...
	@rm -rf $(DIRS) link_release.txt link_debug.txt
	@echo Done!

remove_code:
	@echo Removing VS Code configuration...
	@rm -rf .vscode
	@echo Done!

# Release Build
build: $(BIN)
	@echo Build complete!

obj/%.o: src/%.c | obj
	@echo "Compiling $< (release mode)..."
	@$(CC) $(CFLAGS) -O2 -c $< -o $@ 

obj/%.o: src/%.s | obj
	@echo "Assembling $< (release mode)..."
	@$(AS) -o $@ $<

$(BIN): $(OBJ) $(LIBS) | bin
	@echo "Linking $@..."
	@$(CC) -o $@ $^ $(LDFLAGS_RELEASE)

# Debug Build
debug: $(BIN_DEBUG)
	@echo Debug build complete!

obj/debug/%.o: src/%.c | obj/debug
	@echo "Compiling $< (debug mode)..."
	@$(CC) $(CFLAGS) -O1 -g -c $< -o $@ 

obj/debug/%.o: src/%.s | obj/debug
	@echo "Assembling $< (debug mode)..."
	@$(AS) -o $@ $<

$(BIN_DEBUG): $(OBJ_DEBUG) $(LIBS) | bin/debug
	@echo "Linking $@..."
	@$(CC) -g -o $@ $^ $(LDFLAGS_DEBUG)

# Run the executable
run: $(BIN)
	@echo Running program...
	@$(BIN)

# Run the debug executable with gdb
run_debug: $(BIN_DEBUG)
	@echo Running program in debug mode...
	@gdb $(BIN_DEBUG)

# Clean up object files and executables
clean:
	@echo Cleaning up build files...
	@rm -f obj/*.o obj/debug/*.o bin/*.exe bin/debug/*.exe
	@echo Done!

# Generate VS Code configuration
generate_code:
	@echo Setting up VS Code integration...
	@mkdir -p .vscode

	# launch.json
	@echo '{' > .vscode/launch.json
	@echo '  "version": "0.2.0",' >> .vscode/launch.json
	@echo '  "configurations": [' >> .vscode/launch.json
	@echo '    {' >> .vscode/launch.json
	@echo '      "name": "Launch Program",' >> .vscode/launch.json
	@echo '      "type": "cppdbg",' >> .vscode/launch.json
	@echo '      "request": "launch",' >> .vscode/launch.json
	@echo '      "preLaunchTask": "Build",' >> .vscode/launch.json
	@printf '      "program": "$${workspaceFolder}/bin/main.exe",\n' >> .vscode/launch.json
	@echo '      "args": [],' >> .vscode/launch.json
	@echo '      "stopAtEntry": false,' >> .vscode/launch.json
	@printf '      "cwd": "$${workspaceFolder}",\n' >> .vscode/launch.json
	@echo '      "environment": [],' >> .vscode/launch.json
	@echo '      "MIMode": "gdb"' >> .vscode/launch.json
	@echo '    },' >> .vscode/launch.json
	@echo '    {' >> .vscode/launch.json
	@echo '      "name": "Debug Program",' >> .vscode/launch.json
	@echo '      "type": "cppdbg",' >> .vscode/launch.json
	@echo '      "request": "launch",' >> .vscode/launch.json
	@echo '      "preLaunchTask": "Debug Build",' >> .vscode/launch.json
	@printf '      "program": "$${workspaceFolder}/bin/debug/main_debug.exe",\n' >> .vscode/launch.json
	@echo '      "args": [],' >> .vscode/launch.json
	@echo '      "stopAtEntry": false,' >> .vscode/launch.json
	@printf '      "cwd": "$${workspaceFolder}",\n' >> .vscode/launch.json
	@echo '      "environment": [],' >> .vscode/launch.json
	@echo '      "MIMode": "gdb"' >> .vscode/launch.json
	@echo '    }' >> .vscode/launch.json
	@echo '  ]' >> .vscode/launch.json
	@echo '}' >> .vscode/launch.json

	# tasks.json
	@echo '{' > .vscode/tasks.json
	@echo '  "version": "2.0.0",' >> .vscode/tasks.json
	@echo '  "tasks": [' >> .vscode/tasks.json
	@echo '    {' >> .vscode/tasks.json
	@echo '      "label": "Build",' >> .vscode/tasks.json
	@echo '      "type": "shell",' >> .vscode/tasks.json
	@echo '      "command": "make",' >> .vscode/tasks.json
	@echo '      "args": ["build"],' >> .vscode/tasks.json
	@echo '      "group": {"kind": "build", "isDefault": true}' >> .vscode/tasks.json
	@echo '    },' >> .vscode/tasks.json
	@echo '    {' >> .vscode/tasks.json
	@echo '      "label": "Debug Build",' >> .vscode/tasks.json
	@echo '      "type": "shell",' >> .vscode/tasks.json
	@echo '      "command": "make",' >> .vscode/tasks.json
	@echo '      "args": ["debug"],' >> .vscode/tasks.json
	@echo '      "group": {"kind": "build", "isDefault": false}' >> .vscode/tasks.json
	@echo '    }' >> .vscode/tasks.json
	@echo '  ]' >> .vscode/tasks.json
	@echo '}' >> .vscode/tasks.json

	@echo VS Code setup complete!

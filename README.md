# Wabbit

A Windows port of the classic wabbit/worm. Spawns child processes with random names and exponential growth. Run ts on a vm.

## How to Build
- Use a Windows C compiler (e.g., MSVC, MinGW)
- Compile: `gcc wabbit.c -o wabbit.exe` (MinGW example)

## How to Run
- Run `wabbit.exe` in a safe test environment
- You can pass a starting depth as an argument

## What It Does
- Creates child processes with random names
- Sometimes spawns two children for chaos
- Stops at MAX_DEPTH to avoid total meltdown

## Why
- Saw a malware video, got curious
- This is for fun and learning only

## Final Words
I hated making this readme ngl.

# OpenTrace

OpenTrace is a **pure C eBPF program** that traces `open()` system calls on Linux. It allows you to monitor which files are being opened in real-time, leveraging the Linux kernel's eBPF infrastructure. No Python or BCC dependencies are required — everything is done with **libbpf** and C.

## Features

- Trace all `open()` and `openat()` syscalls.
- Uses pure C with libbpf, clang, and LLVM.
- Minimal dependencies, no Python/BCC required.
- Real-time output through `trace_pipe`.

## Requirements

- Linux kernel 5.5+ (tested on 6.14)
- Clang and LLVM (`clang`, `llvm`)
- libbpf development headers
- Kernel headers for your running kernel
- `sudo` privileges to attach BPF programs

## Project Structure
pure-ebpf/
|------src/
|    |--------open_kern.c
|    |--------user.c
|
|-------vmlinux.h
|-------Makefile
|-------README.md

## Installation

1. Clone the repository:

```bash
git clone https://github.com/prajwalkorde/OpenTrace.git
cd OpenTrace/pure-ebpf```

2. Generate vmlinux.h
  sudo bpftool btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h

3. Build program
  make

Usage
  sudo ./user

sudo cat /sys/kernel/debug/tracing/trace_pine

open some files.

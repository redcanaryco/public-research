/*

The MIT License

Copyright (c) 2020 Red Canary, Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/personality.h>

typedef unsigned long long u64;

#ifdef __i386__
void __x64_syscall(u64* registers, int confuse_strace) __attribute__((cdecl));

u64 x64_syscall(u64 syscall, u64 arg1, u64 arg2, u64 arg3,
                u64 arg4, u64 arg5, u64 arg6, int confuse_strace)
{
    u64 registers[8];
    registers[0] = syscall;
    registers[1] = arg1;
    registers[2] = arg2;
    registers[3] = arg3;
    registers[4] = arg4;
    registers[5] = arg5;
    registers[6] = arg6;
    registers[7] = 0;
    __x64_syscall(registers, confuse_strace);
    return registers[7];
}

#else
void* x86_int0x80(int syscall, void* arg1, void* arg2,
                void* arg3, void* arg4, void* arg5, void* arg6);
#endif

int main(int argc, char** argv)
{
    char proc_pid_maps[PATH_MAX] = {0};

#ifdef __i386__
    u64 address = 0x10000;

    if (getenv("CONFUSE_STRACE")) {
        for (int ii = 0; ii < 10; ++ii) {
            address = x64_syscall(192,
                address,
                0x1000,
                PROT_READ | PROT_WRITE,
                MAP_PRIVATE | MAP_ANONYMOUS,
                -1,
                0,
                1);

            address += (2 * 0x1000);
        }
    } else {
        for (int ii = 0; ii < 10; ++ii) {
            address = x64_syscall(9,
                address,
                0x1000,
                PROT_READ | PROT_WRITE,
                MAP_PRIVATE | MAP_ANONYMOUS,
                -1,
                0,
                0);

            address += (2 * 0x1000);
        }
    }
#else
    void* address = NULL;

    for (int ii = 0; ii < 10; ++ii) {
        address = x86_int0x80(192,
            address,
            (void*)0x1000,
            (void*)(PROT_READ | PROT_WRITE),
            (void*)(MAP_PRIVATE | MAP_ANONYMOUS),
            (void*)-1,
            (void*)0);

        address += (64 * 1024);
    }
#endif

    snprintf(proc_pid_maps, sizeof(proc_pid_maps), "cat /proc/%u/maps", getpid());
    system(proc_pid_maps);
    return 0;
}

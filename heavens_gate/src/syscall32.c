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

// It is possible to configure a Linux kernel that does not support syscall
// emulation, however it is highly unlikely to occur in main distros.
void* x86_int0x80(int syscall, void* arg1, void* arg2,
                void* arg3, void* arg4, void* arg5, void* arg6)
{
    void* ret_value;
    asm volatile("mov %1, %%eax;"
            "mov %2, %%ebx;"
            "mov %3, %%ecx;"
            "mov %4, %%edx;"
            "mov %5, %%esi;"
            "mov %6, %%edi;"
            "push %%rbp;"
            "mov %7, %%ebp;"
            "int $0x80;"
            "pop %%rbp;"
            : "=r"(ret_value)
            : "g"(syscall), "g"(arg1), "g"(arg2), "g"(arg3), "g"(arg4), "g"(arg5), "g"(arg6)
            : "memory");
    return ret_value;
}

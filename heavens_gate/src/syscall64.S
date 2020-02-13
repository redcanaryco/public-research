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

.intel_syntax noprefix
.text
.code32
.globl __x64_syscall
__x64_syscall:
    push ebx
    push ebp
    push esp
    push edi
    push esi

    mov ebx, [esp+24]
    mov eax, [esp+28]
    test eax, eax
    je __do_syscall
    call 0x33:confuse_strace
    jmp __exit
__do_syscall:
    call 0x33:do_syscall
__exit:
    pop esi
    pop edi
    pop esp
    pop ebp
    pop ebx
    ret

.code64
do_syscall:
    mov rax, [rbx]
    mov rdi, [rbx+0x8]
    mov rsi, [rbx+0x10]
    mov rdx, [rbx+0x18]
    mov r10, [rbx+0x20]
    mov r8, [rbx+0x28]
    mov r9, [rbx+0x30]
    syscall
    mov [rbx+0x38], rax
    retf

confuse_strace:
    mov r9, rbx
    mov rax, [r9]
    mov rbx, [r9+0x8]
    mov rcx, [r9+0x10]
    mov rdx, [r9+0x18]
    mov rsi, [r9+0x20]
    mov rdi, [r9+0x28]
    mov rbp, [r9+0x30]
    int 0x80
    mov [r9+0x38], rax
    retf

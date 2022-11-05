#pragma once
#include <common/types.hpp>

namespace iris::nerve
{
    namespace _0_0_1
    {
        namespace x64
        {
            namespace prefix
            {
                constexpr u8 extended64bits = 0x48;

                constexpr u8 extended16bits = 0x66;
            }

            namespace _register
            {
                //rax, rax-r8
                constexpr u8 AtoAor8 = 0xc0;

                //rax, rbx-r11
                constexpr u8 AtoBor11 = 0xd8;

                //rax, rcx-r9
                constexpr u8 AtoCor9 = 0xc8;

                //rax, rdx-r10
                constexpr u8 AtoDor10 = 0xd0;

                //rax, rsi-r14
                constexpr u8 AtoSIor14 = 0xf0;

                //rax, rdi-r15
                constexpr u8 AtoDIor15 = 0xf8;

                //rax, rsp-r12
                constexpr u8 AtoSPor12 = 0xe0;

                //rax, rbp-r13
                constexpr u8 AtoBPor13 = 0xe8;

                //rbx, rax-r8
                constexpr u8 BtoAor8 = 0xc3;

                //rbx, rbx-r11
                constexpr u8 BtoBor11 = 0xdb;

                //rbx, rcx-r9
                constexpr u8 BtoCor9 = 0xcb;

                //rbx, rdx-r10
                constexpr u8 BtoDor10 = 0xd3;

                //rbx, rsi-r14
                constexpr u8 BtoSIor14 = 0xf3;

                //rbx, rdi-r15
                constexpr u8 BtoDIor15 = 0xfb;

                //rbx, rsp-r12
                constexpr u8 BtoSPor12 = 0xe3;

                //rbx, rbp-r13
                constexpr u8 BtoBPor13 = 0xeb;

                //rcx, rax-r8
                constexpr u8 CtoAor8 = 0xc1;

                //rcx, rbx-r11
                constexpr u8 CtoBor11 = 0xd9;

                //rcx, rcx-r9
                constexpr u8 CtoCor9 = 0xc9;

                //rcx, rdx-r10
                constexpr u8 CtoDor10 = 0xd1;

                //rcx, rsi-r14
                constexpr u8 CtoSIor14 = 0xf1;

                //rcx, rdi-r15
                constexpr u8 CtoDIor15 = 0xf9;

                //rcx, rsp-r12
                constexpr u8 CtoSPor12 = 0xe1;

                //rcx, rbp-r13
                constexpr u8 CtoBPor13 = 0xe9;

                //rdx, rax-r8
                constexpr u8 DtoAor8 = 0xc2;

                //rdx, rbx-r11
                constexpr u8 DtoBor11 = 0xda;

                //rdx, rcx-r9
                constexpr u8 DtoCor9 = 0xca;

                //rdx, rdx-r10
                constexpr u8 DtoDor10 = 0xd2;

                //rdx, rsi-r14
                constexpr u8 DtoSIor14 = 0xf2;

                //rdx, rdi-r15
                constexpr u8 DtoDIor15 = 0xfa;

                //rdx, rsp-r12
                constexpr u8 DtoSPor12 = 0xe2;

                //rdx rbp-r13
                constexpr u8 DtoBPor13 = 0xea;

                //rsi, rax-r8
                constexpr u8 SItoAor8 = 0xc6;

                //rsi, rbx-r11
                constexpr u8 SItoBor11 = 0xde;

                //rsi, rcx-r9
                constexpr u8 SItoCor9 = 0xce;

                //rsi, rdx-r10
                constexpr u8 SItoDor10 = 0xd6;

                //rsi, rsi-r14
                constexpr u8 SItoSIor14 = 0xf6;
                
                //rsi, rdi-r15
                constexpr u8 SItoDIor15 = 0xfe;

                //rsi, rsp-r12
                constexpr u8 SItoSPor12 = 0xe6;

                //rsi, rbp-r13
                constexpr u8 SItoBPor13 = 0xee;

                //rdi, rax-r8
                constexpr u8 DItoAor8 = 0xc7;

                //rdi, rbx-r11
                constexpr u8 DItoBor11 = 0xdf;

                //rdi, rcx-r9
                constexpr u8 DItoCor9 = 0xcf;

                //rdi, rdx-r10
                constexpr u8 DItoDor10 = 0xd7;

                //rdi, rsi-r14
                constexpr u8 DItoSIor14 = 0xf7;

                //rdi, rdi-r15
                constexpr u8 DItoDIor15 = 0xff;

                //rdi, rsp-r12
                constexpr u8 DItoSPor12 = 0xe7;

                //rdi, rbp-r13
                constexpr u8 DItoBPor13 = 0xef;

                //rsp, rax-r8
                constexpr u8 SPtoAor8 = 0xc4;

                //rsp, rbx-r11
                constexpr u8 SPtoBor11 = 0xdc;

                //rsp, rcx-r9
                constexpr u8 SPtoCor9 = 0xcc;

                //rsp, rdx-r10
                constexpr u8 SPtoDor10 = 0xd4;

                //rsp, rsi-r14
                constexpr u8 SPtoSIor14 = 0xf4;

                //rsp, rdi-r15
                constexpr u8 SPtoDIor15 = 0xfc;

                //rsp, rsp-r12
                constexpr u8 SPtoSPor12 = 0xe4;

                //rsp, rbp-r13
                constexpr u8 SPtoBPor13 = 0xec;

                //rbp, rax-r8
                constexpr u8 BPtoAor8 = 0xc5;

                //rbp, rbx-r11
                constexpr u8 BPtoBor11 = 0xdd;

                //rbp, rcx-r9
                constexpr u8 BPtoCor9 = 0xcd;

                //rbp, rdx-r10
                constexpr u8 BPtoDor10 = 0xd5;

                //rbp, rsi-r14
                constexpr u8 BPtoSIor14 = 0xf5;

                //rbp, rdi-r15
                constexpr u8 BPtoDIor15 = 0xfd;

                //rbp, rsp-r12
                constexpr u8 BPtoSPor12 = 0xe5;

                //rbp, rbp-r13
                constexpr u8 BPtoBPor13 = 0xed;
            }

            namespace mnemonics
            {
                //mov r64, r64
                constexpr u8 MoveR64toR64 = 0x89;

                //TODO: add more mnemonics
            }
        }
    }
}
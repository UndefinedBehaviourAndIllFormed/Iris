#pragma once
#include <vector>
#include <common/bytes.hpp>

namespace iris::nerve
{
    namespace _0_0_1
    {
        namespace mach_o
        {
            inline void add_magic(std::vector<u8>& opcodes)
            {
                //magic constant to identify Mac binary
                opcodes.push_back(0xcf);
                opcodes.push_back(0xfa);
                opcodes.push_back(0xed);
                opcodes.push_back(0xfe);
            }

            inline void add_arch(std::vector<u8>& opcodes, const bool is_arm)
            {
                //CPU type
                opcodes.push_back(is_arm ? 0x0c : 0x07);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x1);

                //CPU sub-type
                opcodes.push_back(is_arm ? 0x0 : 0x3);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
            }

            inline void add_type(std::vector<u8>& opcodes)
            {
                //always make it an executable type
                opcodes.push_back(0x2);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
            }

            inline void add_number_of_commands(std::vector<u8>& opcodes, const u32 num_commands)
            {
                //add the number of load commands, little endian always
                const auto b = u32_to_bytes(num_commands);
                opcodes.push_back(b.a);
                opcodes.push_back(b.b);
                opcodes.push_back(b.c);
                opcodes.push_back(b.d);
            }

            inline void add_size_of_commands(std::vector<u8>& opcodes, const u32 siz_commands)
            {
                //add the size in bytes of all the load commands, little endian always
                const auto b = u32_to_bytes(siz_commands);
                opcodes.push_back(b.a);
                opcodes.push_back(b.b);
                opcodes.push_back(b.c);
                opcodes.push_back(b.d);
            }

            inline void add_flags(std::vector<u8>& opcodes, const bool thread_local_present)
            {
                //add PIE, NOUNDEFS, Two-level bindings, TLS support, Allow Stack
                opcodes.push_back(0x85);
                opcodes.push_back(0x0);
                opcodes.push_back(thread_local_present ? 0xa2 : 0x22);
                opcodes.push_back(0x0);
            }

            inline void add_reserved(std::vector<u8>& opcodes)
            {
                //add empty bytes, reserved for futre use
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
            }

            //add first page of the binary, and the entry point for the load commands
            inline void add_page_zero(std::vector<u8>& opcodes)
            {
                //add lc_segment_64 ID constant
                opcodes.push_back(0x19);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);

                //add load command size, always the same because this page is a constant stub
                opcodes.push_back(0x48);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);

                //add the segment name in ASCII/UTF-8 encoding, always the same, "__PAGEZERO",
                //with null termination because haha c-like strings
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x4f);
                opcodes.push_back(0x52);
                opcodes.push_back(0x45);
                opcodes.push_back(0x5a);
                opcodes.push_back(0x45);
                opcodes.push_back(0x47);
                opcodes.push_back(0x41);
                opcodes.push_back(0x50);
                opcodes.push_back(0x5f);
                opcodes.push_back(0x5f);

                //add VM address(8-bytes because it's a 64-bits binary), because it's the first page the entry point memory aligned address is always 0
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);

                //add virtual entry point by making this page 4 GBytes in size
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x1);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);

                //add file offset and size, both 0
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);

                //add VM protection, none
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);

                //add number of sections, none
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);

                //add flags, none
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
                opcodes.push_back(0x0);
            }

            inline void add_(std::vector<u8>& opcodes)
            {
                
            }
        }
    }
}
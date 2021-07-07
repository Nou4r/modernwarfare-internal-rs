//
// Created by draven on 7/6/2021.
//

#include "Hacks.h"
#include "Utils.h"
#include "Debug.h"

extern "C" void no_recoil_tick(uint64_t client_base, uint64_t recoil_offset)
{
    struct double_int
    {
        unsigned int first;
        unsigned int second;
    };

    auto r12 = (client_base + recoil_offset);
    auto rsi = r12 + 0x4;

    unsigned int edx = *(unsigned int*)(r12 + 0xc);
    unsigned int ecx = edx;

    ecx = ecx ^ r12;
    unsigned int eax = ecx + 2;
    eax *= ecx;
    ecx = edx;
    ecx = ecx ^ rsi;

    auto address = r12;
    auto val1 = eax;

    eax = ecx + 2;
    eax = eax * ecx;
    auto val2 = eax;

    double_int value;
    value.first = val1;
    value.second = val2;

    if(utils::is_bad_ptr(address)) {
        return;
    }

    *(double_int*)address = value;
    dbg::info("{:X}", address);
}

#include <cstdint>
#include "Memory.h"

extern "C" auto decrypt_client_info(uint64_t imageBase, uint64_t peb) -> uint64_t
{
    uint64_t RAX = imageBase, RBX = imageBase, RCX = imageBase, RDX = imageBase, R8 = imageBase, RDI = imageBase, RSI = imageBase, R9 = imageBase, R10 = imageBase, R11 = imageBase, R12 = imageBase, R13 = imageBase, R14 = imageBase, R15 = imageBase;

    RBX = readMemory<uint64_t>(imageBase + 0x16F6C318);
    if (RBX == 0) {
        return 0;
    }
    R8 = imageBase;
    RAX = 0xB1368AA21CC89905;
    RBX *= RAX;
    RDX = 0xE33EDD45F165A542;
    RBX += R8;
    RAX = RBX;
    RAX >>= 0x18;
    RBX ^= RAX;
    RAX = RBX;
    RCX = 0x0;
    RAX >>= 0x30;
    RCX = _rotl64(RCX, 0x10);
    RAX ^= RBX;
    RCX ^= readMemory<uint64_t>(imageBase + 0x6358106);
    RAX += RDX;
    RCX = ~RCX;
    R8 += RAX;
    RBX = readMemory<uint64_t>(RCX + 0xF);
    RBX *= R8;
    return RBX;
}

extern "C" auto decrypt_client_base(uint64_t clientInfo, uint64_t imageBase, uint64_t peb) -> uint64_t
{
    uint64_t RAX = imageBase, RBX = imageBase, RCX = imageBase, RDX = imageBase, R8 = imageBase, RDI = imageBase, RSI = imageBase, R9 = imageBase, R10 = imageBase, R11 = imageBase, R12 = imageBase, R13 = imageBase, R14 = imageBase, R15 = imageBase, RBP = 0, RSP = 0;

    RAX = readMemory<uint64_t>(clientInfo + 0x9DC48);
    RBX = peb; // mov rbx,gs:[rcx]
    // test rax,rax
    // je 00007FF65E6C8BB1h
    RCX = RBX;
    RCX = _rotr64(RCX, 0xE);
    RCX &= 0xF;
    // cmp rcx,0Eh
    // ja 00007FF65E6C8742h
    switch (RCX) {
        case 0: {
            R10 = readMemory<uint64_t>(imageBase + 0x6358146);
            RCX = 0x2C4DD10573E87BDF;
            RAX -= RCX;
            RCX = RAX;
            RCX >>= 0xF;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x1E;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x3C;
            RAX ^= RCX;
            RCX = 0x2A7E13A63C0DC12;
            RAX += RCX;
            RCX = 0x6EA8692AFBE9951D;
            RAX *= RCX;
            RCX = imageBase + 0x7B15C6EB;
            RCX -= RBX;
            RAX += RCX;
            RDX = 0x0;
            RCX = RAX;
            RDX = _rotl64(RDX, 0x10);
            RAX = imageBase;
            RCX -= RAX;
            RDX ^= R10;
            RDX = ~RDX;
            RAX = readMemory<uint64_t>(RDX + 0x9);
            RAX *= RCX;
            RCX = imageBase;
            RAX += RCX;
            return RAX;
        }
        case 1: {
            R9 = readMemory<uint64_t>(imageBase + 0x6358146);
            RCX = imageBase + 0x7A646912;
            RCX = ~RCX;
            RCX -= RBX;
            RAX += RCX;
            RCX = RAX;
            RCX >>= 0x22;
            RAX ^= RCX;
            RCX = 0x7D67E1E97C6B2C96;
            RAX -= RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RCX = readMemory<uint64_t>(RCX + 0x9);
            RCX *= RAX;
            RAX = imageBase;
            RCX -= RAX;
            RAX = RBX - 0x0FEA;
            RAX += RCX;
            RAX -= RBX;
            RCX = imageBase + 0x2FF05259;
            RAX += RCX;
            RCX = 0x9A1F338590121263;
            RAX *= RCX;
            RCX = 0x52BE01F8D7308C;
            RAX += RCX;
            return RAX;
        }
        case 2: {
            R14 = imageBase + 0xABC7;
            R15 = imageBase + 0x329;
            R9 = readMemory<uint64_t>(imageBase + 0x6358146);
            RCX = 0x428FFCC799FD807;
            RAX *= RCX;
            RCX = imageBase;
            RAX += RCX;
            RCX = RBX;
            RCX = ~RCX;
            RCX += R15;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x22;
            RAX ^= RCX;
            RCX = 0x6D47E789FB157961;
            RAX *= RCX;
            RCX = 0x51EE1309C70ABD7;
            RAX *= RCX;
            RCX = R14;
            RCX = ~RCX;
            RCX ^= RBX;
            RAX ^= RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x9);
            return RAX;
        }
        case 3: {
            R10 = readMemory<uint64_t>(imageBase + 0x6358146);
            R15 = imageBase + 0x4154CA52;
            R14 = imageBase + 0x6B1288FF;
            RCX = 0x9AA73C5A44CEFEB;
            RAX *= RCX;
            RCX = R14;
            RCX = ~RCX;
            RCX ^= RBX;
            RAX -= RCX;
            RDX = 0x0;
            RDX = _rotl64(RDX, 0x10);
            RCX = RBX;
            RDX ^= R10;
            RDX = ~RDX;
            RCX *= R15;
            RDX = readMemory<uint64_t>(RDX + 0x9);
            RAX *= RDX;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x23;
            RAX ^= RCX;
            RCX = 0x49E1C5A42D1EBB58;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x15;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x2A;
            RAX ^= RCX;
            RCX = 0x3736A546ED043ACA;
            RAX += RCX;
            return RAX;
        }
        case 4: {
            uint64_t RBP_NEG_0x80 = imageBase;
            R11 = readMemory<uint64_t>(imageBase + 0x6358146);
            RCX = 0xB1660B2EB3DEF8A3;
            RBP_NEG_0x80 = RCX; // mov [rbp-80h],rcx
            RDX = imageBase + 0xE83F;
            RCX = RAX;
            RCX >>= 0x1B;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x36;
            RAX ^= RCX;
            RCX = RBX;
            RCX *= RDX;
            RAX -= RCX;
            RCX = 0x310451BB37ED62A0;
            RAX ^= RCX;
            R8 = 0x0;
            R8 = _rotl64(R8, 0x10);
            RCX = imageBase + 0x7E687D0C;
            R8 ^= R11;
            RDX = RBX;
            RDX = ~RDX;
            RCX = ~RCX;
            RDX *= RCX;
            R8 = ~R8;
            RDX += RAX;
            RAX = readMemory<uint64_t>(R8 + 0x9);
            RAX *= RDX;
            R8 = imageBase + 0xE166;
            RAX *= RBP_NEG_0x80; // imul rax,[rbp-80h]
            RCX = RBX;
            RCX *= R8;
            RAX -= RCX;
            RCX = 0x2D4951DFC2EC76;
            RAX ^= RCX;
            return RAX;
        }
        case 5: {
            R14 = imageBase + 0xCE23;
            R9 = readMemory<uint64_t>(imageBase + 0x6358146);
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x9);
            RAX += RBX;
            RCX = RBX;
            RCX ^= R14;
            RAX -= RCX;
            RAX -= RBX;
            RAX -= RBX;
            RCX = RAX;
            RCX >>= 0xE;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x1C;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x38;
            RAX ^= RCX;
            RCX = 0x722B82C72992DE8D;
            RAX += RCX;
            RCX = 0x15F1C700407765FB;
            RAX *= RCX;
            return RAX;
        }
        case 6: {
            uint64_t RBP_NEG_0x70 = imageBase;
            R14 = imageBase + 0x34DF;
            R11 = imageBase + 0x1C28A0E6;
            R9 = readMemory<uint64_t>(imageBase + 0x6358146);
            RCX = RBX;
            RCX *= R14;
            RAX += RCX;
            RCX = R11;
            RCX = ~RCX;
            RCX ^= RBX;
            RAX += RCX;
            RCX = RAX;
            RCX >>= 0xC;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x18;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x30;
            RAX ^= RCX;
            RCX = 0xDE4968A1A719FFCB;
            RAX *= RCX;
            RCX = RBX;
            RCX = ~RCX;
            RCX -= RBP_NEG_0x70; // sub rcx,[rbp-70h]
            RAX += RCX;
            RCX = 0xB556BEEBB66DDC7F;
            RAX *= RCX;
            RCX = 0x4D76CF5D1934D528;
            RAX -= RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RCX = readMemory<uint64_t>(RCX + 0x9);
            RAX *= RCX;
            RCX = 0x56851AD3B48647AD;
            RAX -= RCX;
            return RAX;
        }
        case 7: {
            R10 = readMemory<uint64_t>(imageBase + 0x6358146);
            R15 = imageBase + 0x39C4;
            RCX = RAX;
            RCX >>= 0x16;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x2C;
            RAX ^= RCX;
            RCX = imageBase;
            RAX -= RCX;
            RCX = RAX;
            RCX >>= 0xF;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x1E;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x3C;
            RAX ^= RCX;
            RCX = 0x21FED6E262CAF0A5;
            RAX += RBX;
            RAX *= RCX;
            RCX = 0xC7C713F9414B5D6F;
            RAX *= RCX;
            RCX = RBX;
            RCX *= R15;
            RAX -= RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x9);
            return RAX;
        }
        case 8: {
            R11 = readMemory<uint64_t>(imageBase + 0x6358146);
            RCX = RAX;
            RCX >>= 0x1E;
            RAX ^= RCX;
            RDX = RAX;
            RDX >>= 0x3C;
            RDX ^= RAX;
            RCX = imageBase + 0x4761EFFA;
            RAX = RBX;
            RAX = ~RAX;
            RAX += RDX;
            RAX += RCX;
            RDX = imageBase + 0x4D99E6C7;
            RCX = 0x146DB59CC1529DFB;
            RAX *= RCX;
            R8 = 0x0;
            RCX = 0x6560D27261FEC3CD;
            RAX -= RCX;
            R8 = _rotl64(R8, 0x10);
            R8 ^= R11;
            RCX = RBX;
            RCX *= RDX;
            RDX = RAX;
            R8 = ~R8;
            RDX ^= RCX;
            RAX = readMemory<uint64_t>(R8 + 0x9);
            RAX *= RDX;
            RCX = imageBase;
            RAX ^= RCX;
            RCX = 0x88F7E80C1A3D810D;
            RAX ^= RCX;
            return RAX;
        }
        case 9: {
            R10 = readMemory<uint64_t>(imageBase + 0x6358146);
            R14 = imageBase + 0x2B3B97D6;
            RCX = R14;
            RCX = ~RCX;
            RCX ^= RBX;
            RAX -= RCX;
            RCX = RAX;
            RCX >>= 0x26;
            RAX ^= RCX;
            RCX = imageBase;
            RCX += 0x768D9C44;
            RCX += RBX;
            RAX += RCX;
            RCX = imageBase;
            RAX ^= RCX;
            RDX = 0x0;
            RCX = 0xB806EA076004BA03;
            RCX += RAX;
            RDX = _rotl64(RDX, 0x10);
            RDX ^= R10;
            RDX = ~RDX;
            RAX = readMemory<uint64_t>(RDX + 0x9);
            RAX *= RCX;
            RCX = 0xEDE8FF8B79B50DB9;
            RAX ^= RCX;
            RCX = 0x6FB6C9522E542E57;
            RAX *= RCX;
            return RAX;
        }
        case 10: {
            R14 = imageBase + 0x30AA903C;
            R10 = readMemory<uint64_t>(imageBase + 0x6358146);
            RDX = 0x0;
            RCX = imageBase + 0x94AF;
            RDX = _rotl64(RDX, 0x10);
            RDX ^= R10;
            RDX = ~RDX;
            RDX = readMemory<uint64_t>(RDX + 0x9);
            RDX *= RAX;
            RAX = RBX;
            RAX = ~RAX;
            RAX += RDX;
            RAX += RCX;
            RCX = RAX;
            RCX >>= 0xC;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x18;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x30;
            RAX ^= RCX;
            RCX = 0xACC4BF01026ACA41;
            RAX *= RCX;
            RCX = 0x7B0FC59EF989D401;
            RAX *= RCX;
            RCX = RBX;
            RCX = ~RCX;
            RCX *= R14;
            RAX ^= RCX;
            RAX += RBX;
            RCX = 0xA7FA6EC3B6BE6B3;
            RAX *= RCX;
            return RAX;
        }
        case 11: {
            R10 = readMemory<uint64_t>(imageBase + 0x6358146);
            R15 = imageBase + 0x83A5;
            RAX ^= RBX;
            RCX = 0x40C12A8DB56F3975;
            RAX ^= RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x9);
            RCX = imageBase + 0x4D9F690F;
            RCX = ~RCX;
            RCX *= RBX;
            RAX += RCX;
            RDX = RBX;
            RDX = ~RDX;
            RCX = imageBase + 0x209B04FB;
            RCX = ~RCX;
            RDX *= RCX;
            RAX += RDX;
            RCX = RAX;
            RCX >>= 0x26;
            RAX ^= RCX;
            RCX = 0xFE5C09AC750B9363;
            RAX *= RCX;
            RCX = RBX;
            RCX *= R15;
            RAX -= RCX;
            return RAX;
        }
        case 12: {
            R10 = readMemory<uint64_t>(imageBase + 0x6358146);
            RCX = RAX;
            RCX >>= 0x1;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x2;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x4;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x8;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x10;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x20;
            RAX ^= RCX;
            RDX = RBX;
            RDX = ~RDX;
            RCX = imageBase + 0x5871BC1F;
            RCX = ~RCX;
            RDX += RCX;
            RCX = 0x3D71B39825780613;
            RAX ^= RDX;
            RAX *= RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x9);
            RCX = imageBase + 0x620C;
            RCX = ~RCX;
            RCX -= RBX;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x1F;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x3E;
            RAX ^= RCX;
            RCX = 0x94CCAF9E67675B86;
            RAX ^= RCX;
            RCX = 0xEEDDDC399380CB03;
            RAX *= RCX;
            return RAX;
        }
        case 13: {
            R10 = readMemory<uint64_t>(imageBase + 0x6358146);
            R15 = imageBase + 0x24DDB6C6;
            R14 = imageBase + 0x44386CDB;
            RDX = RBX;
            RDX = ~RDX;
            RCX = R15;
            RCX = ~RCX;
            RDX += RCX;
            RAX ^= RDX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x9);
            RCX = RAX;
            RCX >>= 0x1D;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x3A;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0xA;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x14;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x28;
            RAX ^= RCX;
            RCX = R14;
            RCX = ~RCX;
            RCX ^= RBX;
            RAX -= RCX;
            RCX = 0xA425934513878AA5;
            RAX ^= RCX;
            RCX = 0xEBB297007E6A6869;
            RAX *= RCX;
            RCX = 0x71D340402BC33382;
            RAX += RCX;
            return RAX;
        }
        case 14: {
            uint64_t RSP_0x50 = imageBase;
            RCX = imageBase + 0x2F3E;
            RSP_0x50 = RCX; // mov [rsp+50h],rcx
            R9 = readMemory<uint64_t>(imageBase + 0x6358146);
            RCX = imageBase;
            RAX += RCX;
            RCX = imageBase;
            RAX ^= RCX;
            RCX = 0x5B3DE4A99B478B9C;
            RAX -= RCX;
            RCX = RBX;
            RCX *= RSP_0x50; // imul rcx,[rsp+50h]
            RAX += RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x9);
            RCX = 0xC04FC33339F325BD;
            RAX *= RCX;
            RCX = RAX;
            RCX >>= 0x22;
            RAX ^= RCX;
            RCX = imageBase;
            RAX ^= RCX;
            return RAX;
        }
        case 15: {
            R11 = readMemory<uint64_t>(imageBase + 0x6358146);
            R15 = imageBase + 0x5FEE;
            RCX = RBX;
            RCX = ~RCX;
            RCX ^= R15;
            RAX += RCX;
            RCX = RAX;
            RCX >>= 0x22;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x26;
            RAX ^= RCX;
            R8 = 0x0;
            R8 = _rotl64(R8, 0x10);
            RCX = imageBase;
            RAX -= RCX;
            R8 ^= R11;
            R8 = ~R8;
            RDX = 0xD2E4E9A984CB1482;
            RDX += RAX;
            RDX += RBX;
            RAX = readMemory<uint64_t>(R8 + 0x9);
            RAX *= RDX;
            RCX = 0x668190FC03DA69F9;
            RAX *= RCX;
            RCX = 0x7DCF9F0915447B5B;
            RAX -= RCX;
            return RAX;
        }
    }
}

extern "C" auto decrypt_bone_base(uint64_t imageBase, uint64_t peb) -> uint64_t
{
    uint64_t RAX = imageBase, RBX = imageBase, RCX = imageBase, RDX = imageBase, R8 = imageBase, RDI = imageBase, RSI = imageBase, R9 = imageBase, R10 = imageBase, R11 = imageBase, R12 = imageBase, R13 = imageBase, R14 = imageBase, R15 = imageBase, RBP = 0, RSP = 0;

    R8 = readMemory<uint64_t>(imageBase + 0x152FB068);
    if (R8 == 0) {
        return 0;
    }
    RBX = peb; // mov rbx,gs:[rax]
    // test r8,r8
    // je 00007FF65E80DD14h
    RAX = RBX;
    RAX >>= 0x1F;
    RAX &= 0xF;
    // cmp rax,0Eh
    // ja 00007FF65E80D7A0h
    switch (RAX) {
        case 0: {
            uint64_t RBP_NEG_0x38 = imageBase;
            uint64_t RSP_0x70 = imageBase;
            // push rbx
            // pushfq
            // pop rbx
            // popfq
            // pop rbx
            R10 = readMemory<uint64_t>(imageBase + 0x6358219);
            RAX = imageBase + 0xA176;
            RBP_NEG_0x38 = RAX; // mov [rbp-38h],rax
            RAX = 0x6E33B4D07235DCE1;
            RSP_0x70 = RAX; // mov [rsp+70h],rax
            RAX = imageBase;
            R8 -= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = _byteswap_uint64(RAX);
            R8 *= readMemory<uint64_t>(RAX + 0x11);
            RAX = R8;
            RAX >>= 0x1E;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x3C;
            R8 ^= RAX;
            R8 *= RSP_0x70; // imul r8,[rsp+70h]
            RAX = RBX;
            RAX *= RBP_NEG_0x38; // imul rax,[rbp-38h]
            R8 -= RAX;
            RAX = 0x1588F6554284D28E;
            R8 -= RAX;
            RCX = imageBase;
            RAX = 0x4F8498C6B1335BDA;
            RAX -= RCX;
            R8 += RAX;
            return R8;
        }
        case 1: {
            uint64_t RSP_0x70 = imageBase;
            // push rcx
            // pushfq
            // pop rcx
            // popfq
            // pop rcx
            R10 = readMemory<uint64_t>(imageBase + 0x6358219);
            RAX = 0x4CB24DAE2BD35C1F;
            RSP_0x70 = RAX; // mov [rsp+70h],rax
            RAX = R8;
            RAX >>= 0x5;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0xA;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x14;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x28;
            R8 ^= RAX;
            RAX = 0x2A67EE5D220D754A;
            R8 -= RAX;
            RAX = imageBase + 0x6B86;
            RCX = RBX;
            RCX = ~RCX;
            RCX *= RAX;
            RAX = RBX;
            RCX += R8;
            R8 = imageBase;
            RAX -= R8;
            R8 = RCX;
            RAX -= 0x42B8;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x7;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0xE;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x1C;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x38;
            R8 ^= RAX;
            RAX = 0x239437FC18D83A9E;
            R8 ^= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = _byteswap_uint64(RAX);
            RAX = readMemory<uint64_t>(RAX + 0x11);
            RAX *= RSP_0x70; // imul rax,[rsp+70h]
            R8 *= RAX;
            return R8;
        }
        case 2: {
            R11 = imageBase + 0x65E6;
            R9 = readMemory<uint64_t>(imageBase + 0x6358219);
            RAX = RBX;
            RAX ^= R11;
            R8 += RAX;
            RAX = 0xA04060743EEEC81;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x20;
            R8 ^= RAX;
            R8 -= RBX;
            RAX = imageBase;
            R8 ^= RAX;
            RAX = 0xCAA0FFD0709BBB87;
            R8 *= RAX;
            RAX = 0x3C1E90309C0BE784;
            R8 ^= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R9;
            RAX = _byteswap_uint64(RAX);
            R8 *= readMemory<uint64_t>(RAX + 0x11);
            return R8;
        }
        case 3: {
            uint64_t RSP_0x68 = imageBase;
            // pushfq
            // push rax
            // pop rax
            // pop rax
            // popfq
            R10 = readMemory<uint64_t>(imageBase + 0x6358219);
            RAX = imageBase + 0xEB6C;
            RSP_0x68 = RAX; // mov [rsp+68h],rax
            RAX = 0x540D0AF5F4CDB74B;
            RAX *= R8;
            R8 = imageBase;
            RAX ^= R8;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = _byteswap_uint64(RCX);
            R8 = readMemory<uint64_t>(RCX + 0x11);
            R8 *= RAX;
            RAX = imageBase;
            RAX += 0x770D;
            RAX += RBX;
            R8 ^= RAX;
            RAX = imageBase;
            R8 ^= RAX;
            RAX = RBX + 1;
            RAX *= RSP_0x68; // imul rax,[rsp+68h]
            R8 += RAX;
            RAX = R8;
            RAX >>= 0x5;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0xA;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x14;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x28;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x27;
            R8 ^= RAX;
            return R8;
        }
        case 4: {
            R10 = readMemory<uint64_t>(imageBase + 0x6358219);
            RAX = imageBase;
            RAX += R8;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = _byteswap_uint64(RCX);
            R8 = readMemory<uint64_t>(RCX + 0x11);
            R8 *= RAX;
            RCX = imageBase + 0xAD05;
            RAX = R8;
            RAX >>= 0x1A;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x34;
            R8 ^= RAX;
            RAX = imageBase + 0x316BDF41;
            RAX -= RBX;
            R8 += RAX;
            RAX = 0x86DB83FC703A9029;
            R8 *= RAX;
            R8 ^= RBX;
            R8 ^= RCX;
            RAX = 0xFAA4F606C5BA248C;
            R8 ^= RAX;
            RAX = 0x28AE5E481A72B2B3;
            R8 *= RAX;
            return R8;
        }
        case 5: {
            R9 = readMemory<uint64_t>(imageBase + 0x6358219);
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R9;
            RAX = _byteswap_uint64(RAX);
            R8 *= readMemory<uint64_t>(RAX + 0x11);
            RAX = R8 + RBX;
            R8 = 0x1395E21D03239025;
            RAX += R8;
            R8 = imageBase;
            R8 += RAX;
            RAX = imageBase;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x21;
            R8 ^= RAX;
            RAX = imageBase + 0x8A9B;
            R8 += RBX;
            R8 += RAX;
            R8 ^= RBX;
            RAX = 0xDFB38FA8F07B7E79;
            R8 *= RAX;
            return R8;
        }
        case 6: {
            R10 = readMemory<uint64_t>(imageBase + 0x6358219);
            RAX = R8;
            RAX >>= 0xF;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x1E;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x3C;
            R8 ^= RAX;
            RAX = imageBase;
            R8 ^= RAX;
            RAX = 0x19B16A317394149D;
            R8 ^= RAX;
            RAX = 0x6E8320546EF271ED;
            R8 *= RAX;
            RAX = 0x27C46D7702E18107;
            R8 *= RAX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = _byteswap_uint64(RCX);
            RCX = readMemory<uint64_t>(RCX + 0x11);
            RCX *= R8;
            R8 = imageBase + 0xDA3A;
            R8 *= RBX;
            R8 += RCX;
            RAX = imageBase + 0x1463840C;
            RAX -= RBX;
            R8 += RAX;
            return R8;
        }
        case 7: {
            R11 = imageBase + 0x1F57940D;
            R9 = readMemory<uint64_t>(imageBase + 0x6358219);
            RAX = R8;
            RAX >>= 0x17;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x2E;
            R8 ^= RAX;
            RAX = R11;
            RAX = ~RAX;
            RAX += RBX;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x1C;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x38;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x17;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x2E;
            R8 ^= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R9;
            RAX = _byteswap_uint64(RAX);
            R8 *= readMemory<uint64_t>(RAX + 0x11);
            RAX = 0xC6F4A95E4EEDD47F;
            R8 *= RAX;
            RAX = imageBase;
            R8 -= RAX;
            RAX = 0xAB801A1C78E324AD;
            R8 ^= RAX;
            return R8;
        }
        case 8: {
            R10 = readMemory<uint64_t>(imageBase + 0x6358219);
            RCX = imageBase + 0x3C70771D;
            RAX = imageBase + 0x3548;
            RAX = ~RAX;
            RAX ^= RBX;
            R8 ^= RAX;
            R8 += RBX;
            R8 ^= RBX;
            RAX = 0xBD25B6162FFC4A37;
            R8 ^= RCX;
            R8 *= RAX;
            RAX = R8;
            RAX >>= 0x8;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x10;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x20;
            R8 ^= RAX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RAX = R8;
            RCX ^= R10;
            RAX -= RBX;
            RCX = _byteswap_uint64(RCX);
            R8 = readMemory<uint64_t>(RCX + 0x11);
            RCX = imageBase + 0x573BDED9;
            R8 *= RAX;
            RAX = RBX;
            RAX *= RCX;
            R8 ^= RAX;
            return R8;
        }
        case 9: {
            // push rbx
            // pushfq
            // pop rbx
            // popfq
            // pop rbx
            R9 = readMemory<uint64_t>(imageBase + 0x6358219);
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R9;
            RAX = _byteswap_uint64(RAX);
            R8 *= readMemory<uint64_t>(RAX + 0x11);
            RAX = R8;
            RAX >>= 0xC;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x18;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x30;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x12;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x24;
            R8 ^= RAX;
            R8 += RBX;
            RAX = R8;
            RAX >>= 0x23;
            R8 ^= RAX;
            RAX = 0x7E3E416EF7F1D741;
            R8 *= RAX;
            RAX = 0xF617ED5B72E590DE;
            R8 ^= RAX;
            RAX = 0x818141D2E8EA7F6F;
            R8 *= RAX;
            return R8;
        }
        case 10: {
            R10 = readMemory<uint64_t>(imageBase + 0x6358219);
            RAX = imageBase;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x28;
            R8 ^= RAX;
            RAX = imageBase;
            R8 -= RAX;
            RCX = 0x0;
            RAX = R8;
            RCX = _rotl64(RCX, 0x10);
            RAX >>= 0x20;
            RCX ^= R10;
            RAX ^= R8;
            RCX = _byteswap_uint64(RCX);
            R8 = readMemory<uint64_t>(RCX + 0x11);
            R8 *= RAX;
            RAX = 0xF37BC628D4B58CF3;
            R8 *= RAX;
            RAX = 0x2A8C713B6A73DA4D;
            R8 += RAX;
            RAX = 0x7122022471FD76A7;
            R8 ^= RAX;
            return R8;
        }
        case 11: {
            uint64_t RBP_NEG_0x38 = imageBase;
            // push rbx
            // pushfq
            // pop rbx
            // popfq
            // pop rbx
            R10 = readMemory<uint64_t>(imageBase + 0x6358219);
            R11 = imageBase + 0x2E006611;
            RAX = 0xC7B1BEFAE1F9E327;
            R8 *= RAX;
            R8 += R11;
            RCX = RBX;
            RCX = ~RCX;
            R8 += RCX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = _byteswap_uint64(RAX);
            R8 *= readMemory<uint64_t>(RAX + 0x11);
            R8 -= RBP_NEG_0x38; // sub r8,[rbp-38h]
            RAX = imageBase;
            RAX += 0xEEE7;
            RAX += RBX;
            RAX ^= R8;
            R8 = RAX;
            RAX >>= 0x1A;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x34;
            R8 ^= RAX;
            R8 += RBX;
            RAX = imageBase + 0x1E776935;
            RAX -= RBX;
            R8 ^= RAX;
            return R8;
        }
        case 12: {
            R9 = readMemory<uint64_t>(imageBase + 0x6358219);
            RAX = R8;
            RAX >>= 0x11;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x22;
            R8 ^= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R9;
            RAX = _byteswap_uint64(RAX);
            R8 *= readMemory<uint64_t>(RAX + 0x11);
            RAX = R8;
            RAX >>= 0x8;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x10;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x20;
            R8 ^= RAX;
            RAX = 0xD3A76E77D0439A87;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x17;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x2E;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x27;
            R8 ^= RAX;
            RAX = 0xE7C759589C81E2D1;
            R8 *= RAX;
            RAX = 0x92D8F3E599FB6C55;
            R8 *= RAX;
            return R8;
        }
        case 13: {
            // pushfq
            // push rbx
            // pop rbx
            // pop rbx
            R10 = readMemory<uint64_t>(imageBase + 0x6358219);
            RAX = 0xEDE0ED52BA16A73B;
            R8 *= RAX;
            RAX = R8;
            RAX >>= 0x1C;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x38;
            R8 ^= RAX;
            R8 += RBX;
            RAX = 0x40F028F390F9B4DB;
            R8 *= RAX;
            R8 ^= RBX;
            RAX = imageBase;
            R8 -= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = _byteswap_uint64(RAX);
            RAX = readMemory<uint64_t>(RAX + 0x11);
            R8 *= RAX;
            RAX = imageBase;
            R8 ^= RAX;
            return R8;
        }
        case 14: {
            uint64_t RBP_NEG_0x38 = imageBase;
            uint64_t RBP_NEG_0x50 = imageBase;
            RAX = imageBase + 0xA494;
            RBP_NEG_0x38 = RAX; // mov [rbp-38h],rax
            RAX = imageBase + 0x1F68E2F6;
            RBP_NEG_0x50 = RAX; // mov [rbp-50h],rax
            R9 = readMemory<uint64_t>(imageBase + 0x6358219);
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R9;
            RAX = _byteswap_uint64(RAX);
            R8 *= readMemory<uint64_t>(RAX + 0x11);
            RAX = RBX;
            RAX ^= RBP_NEG_0x38; // xor rax,[rbp-38h]
            R8 += RAX;
            R8 ^= RBX;
            RAX = 0x44F06411130D8786;
            R8 -= RAX;
            RAX = RBX;
            RAX = ~RAX;
            RAX ^= RBP_NEG_0x50; // xor rax,[rbp-50h]
            R8 -= RAX;
            RAX = 0x72F146FB8657DB4D;
            R8 *= RAX;
            RAX = R8;
            RAX >>= 0x15;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x2A;
            R8 ^= RAX;
            RAX = 0x25EA3844D16C50F1;
            R8 += RAX;
            return R8;
        }
        case 15: {
            R12 = imageBase + 0x6ED429A4;
            R11 = readMemory<uint64_t>(imageBase + 0x6358219);
            RAX = RBX;
            RAX *= R12;
            R8 -= RAX;
            RAX = 0x16E71D0785BF5E85;
            R8 *= RAX;
            RAX = 0x164272E1C98C0650;
            R8 -= RAX;
            RAX = R8;
            RAX >>= 0x26;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x12;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x24;
            RAX ^= R8;
            RDX = 0x0;
            RDX = _rotl64(RDX, 0x10);
            R8 = imageBase + 0x253C;
            RDX ^= R11;
            RCX = RBX;
            RDX = _byteswap_uint64(RDX);
            RCX = ~RCX;
            RDX = readMemory<uint64_t>(RDX + 0x11);
            RDX *= RAX;
            R8 += RDX;
            R8 += RCX;
            RAX = R8;
            RAX >>= 0x13;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x26;
            R8 ^= RAX;
            return R8;
        }
    }
}

extern "C" auto get_bone_index(uint32_t index, uint64_t imageBase) -> uint64_t
{
    uint64_t RAX = imageBase, RBX = imageBase, RCX = imageBase, RDX = imageBase, R8 = imageBase, RDI = imageBase, RSI = imageBase, R9 = imageBase, R10 = imageBase, R11 = imageBase, R12 = imageBase, R13 = imageBase, R14 = imageBase, R15 = imageBase, RBP = 0, RSP = 0;

    RBX = index;
    RCX = RBX * 0x13C8;
    RAX = 0x4F23479A4BA8FAB5;
    R11 = imageBase;
    RAX = _umul128(RAX, RCX, &RDX);
    R10 = 0x33B1DA233CBB3105;
    RDX >>= 0xB;
    RAX = RDX * 0x19E1;
    RCX -= RAX;
    RAX = 0xF598CEFB88707C3D;
    R8 = RCX * 0x19E1;
    RAX = _umul128(RAX, R8, &RDX);
    RDX >>= 0xD;
    RAX = RDX * 0x215B;
    R8 -= RAX;
    RAX = 0xEA0EA0EA0EA0EA0F;
    RAX = _umul128(RAX, R8, &RDX);
    RAX = 0x948B0FCD6E9E0653;
    RDX >>= 0x5;
    RCX = RDX * 0x23;
    RAX = _umul128(RAX, R8, &RDX);
    RAX = R8;
    RAX -= RDX;
    RAX >>= 0x1;
    RAX += RDX;
    RAX >>= 0x8;
    RCX += RAX;
    RAX = RCX * 0x288;
    RCX = R8 * 0x28A;
    RCX -= RAX;
    RAX = readMemory<uint16_t>(RCX + R11 + 0x6362050);
    R8 = RAX * 0x13C8;
    RAX = R10;
    RAX = _umul128(RAX, R8, &RDX);
    RAX = R10;
    RDX >>= 0xA;
    RCX = RDX * 0x13CF;
    R8 -= RCX;
    R9 = R8 * 0x164B;
    RAX = _umul128(RAX, R9, &RDX);
    RDX >>= 0xA;
    RAX = RDX * 0x13CF;
    R9 -= RAX;
    RAX = 0x97B425ED097B425F;
    RAX = _umul128(RAX, R9, &RDX);
    RAX = 0x83C977AB2BEDD28F;
    RDX >>= 0x5;
    RCX = RDX * 0x36;
    RAX = _umul128(RAX, R9, &RDX);
    RAX = R9;
    RAX -= RDX;
    RAX >>= 0x1;
    RAX += RDX;
    RAX >>= 0x7;
    RCX += RAX;
    RAX = RCX * 0x152;
    RCX = R9 * 0x154;
    RCX -= RAX;
    RSI = readMemory<uint16_t>(RCX + R11 + 0x63678F0);
    return R15;
}


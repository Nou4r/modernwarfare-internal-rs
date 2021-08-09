// 1.39.6.9873021

#include "Decryption.h"

extern "C" auto decrypt_client_info(uint64_t imageBase, uint64_t peb) -> uint64_t
{
    uint64_t RAX = imageBase, RBX = imageBase, RCX = imageBase, RDX = imageBase, R8 = imageBase, RDI = imageBase, RSI = imageBase, R9 = imageBase, R10 = imageBase, R11 = imageBase, R12 = imageBase, R13 = imageBase, R14 = imageBase, R15 = imageBase;

    RBX = readMemory<uint64_t>(imageBase + 0x1732F718);
    if (RBX == 0) {
        return 0;
    }
    RAX += 0x52;
    // movzx eax,al
    RDX = peb; // mov rdx,gs:[rax]
    RBX -= RDX;
    RAX = RBX;
    RAX >>= 0x12;
    RBX ^= RAX;
    RAX = RBX;
    RAX >>= 0x24;
    RCX = 0x0;
    RAX ^= RBX;
    RCX = _rotl64(RCX, 0x10);
    RCX ^= readMemory<uint64_t>(imageBase + 0x64C40EF);
    RCX = ~RCX;
    RBX = readMemory<uint64_t>(RCX + 0x7);
    RBX *= RAX;
    RAX = 0x101B4E1256D35541;
    RBX *= RAX;
    RAX = imageBase + 0x21F4FBCE;
    RAX = ~RAX;
    RAX += RDX;
    RBX ^= RAX;
    RAX = RBX;
    RAX >>= 0x8;
    RBX ^= RAX;
    RAX = RBX;
    RAX >>= 0x10;
    RBX ^= RAX;
    RAX = RBX;
    RAX >>= 0x20;
    RBX ^= RAX;
    return RBX;
}

extern "C" auto decrypt_client_base(uint64_t clientInfo, uint64_t imageBase, uint64_t peb) -> uint64_t
{
    uint64_t RAX = imageBase, RBX = imageBase, RCX = imageBase, RDX = imageBase, R8 = imageBase, RDI = imageBase, RSI = imageBase, R9 = imageBase, R10 = imageBase, R11 = imageBase, R12 = imageBase, R13 = imageBase, R14 = imageBase, R15 = imageBase, RBP = 0, RSP = 0;

    RAX = readMemory<uint64_t>(clientInfo + 0x9DC28);
    RBX = peb; // mov rbx,gs:[rcx]
    RBX = ~RBX;
    // test rax,rax
    // je 00007FF726390674h
    RCX = RBX;
    RCX = _rotr64(RCX, 0x1C);
    RCX &= 0xF;
    // cmp rcx,0Eh
    // ja 00007FF7263901ABh
    switch (RCX) {
    case 0: {
        R11 = imageBase;
        R9 = readMemory<uint64_t>(imageBase + 0x64C4141);
        RAX += RBX;
        RCX = RAX;
        RCX >>= 0x25;
        RAX ^= RCX;
        RCX = 0x71B02B219A96D91F;
        RAX *= RCX;
        RCX = RAX;
        RCX >>= 0x1F;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x3E;
        RAX ^= RCX;
        RAX += R11;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R9;
        RCX = _byteswap_uint64(RCX);
        RAX *= readMemory<uint64_t>(RCX + 0x9);
        RCX = RAX;
        RCX >>= 0x28;
        RAX ^= RCX;
        return RAX;
    }
    case 1: {
        R9 = readMemory<uint64_t>(imageBase + 0x64C4141);
        RAX -= RBX;
        RCX = RAX;
        RCX >>= 0x23;
        RAX ^= RCX;
        RCX = 0x4C8995AB18E0028B;
        RAX += RCX;
        RCX = RAX;
        RCX >>= 0x28;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x11;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x22;
        RAX ^= RCX;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R9;
        RCX = _byteswap_uint64(RCX);
        RAX *= readMemory<uint64_t>(RCX + 0x9);
        RCX = 0xF46072E290441B1D;
        RAX ^= RCX;
        RCX = 0x7861B5B793DC5C97;
        RAX *= RCX;
        return RAX;
    }
    case 2: {
        R10 = readMemory<uint64_t>(imageBase + 0x64C4141);
        RCX = RAX;
        RCX >>= 0xE;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x1C;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x38;
        RAX ^= RCX;
        RAX += RBX;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R10;
        RCX = _byteswap_uint64(RCX);
        RAX *= readMemory<uint64_t>(RCX + 0x9);
        RCX = RAX;
        RCX >>= 0x1A;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x34;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0xC;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x18;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x30;
        RAX ^= RCX;
        RCX = 0xBD98DCE256B887;
        RAX ^= RCX;
        RCX = imageBase + 0x74693770;
        RAX -= RBX;
        RAX += RCX;
        RCX = 0x509F44A303AE649;
        RAX *= RCX;
        return RAX;
    }
    case 3: {
        R11 = imageBase;
        R14 = imageBase + 0xB4C;
        R9 = readMemory<uint64_t>(imageBase + 0x64C4141);
        RAX -= RBX;
        RCX = RBX;
        RCX ^= R14;
        RAX += RCX;
        RCX = 0x9480D59E159A9941;
        RAX *= RCX;
        RCX = RAX;
        RCX >>= 0xE;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x1C;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x38;
        RAX ^= RCX;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R9;
        RCX = _byteswap_uint64(RCX);
        RCX = readMemory<uint64_t>(RCX + 0x9);
        RAX *= RCX;
        RCX = 0x9A7A41669AA794C3;
        RAX *= RCX;
        RAX -= R11;
        return RAX;
    }
    case 4: {
        R11 = imageBase + 0x7075;
        R9 = readMemory<uint64_t>(imageBase + 0x64C4141);
        RAX ^= RBX;
        RCX = 0x125AD7CE6BD17CAC;
        RAX -= RCX;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R9;
        RCX = _byteswap_uint64(RCX);
        RCX = readMemory<uint64_t>(RCX + 0x9);
        RAX *= RCX;
        RCX = 0xC272F0F8A40A09B3;
        RAX *= RCX;
        RCX = 0x73D589BD8C3FFFE3;
        RAX ^= RBX;
        RAX *= RCX;
        RCX = RAX;
        RCX >>= 0x12;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x24;
        RAX ^= RCX;
        RCX = RBX;
        RCX ^= R11;
        RAX -= RCX;
        return RAX;
    }
    case 5: {
        R10 = readMemory<uint64_t>(imageBase + 0x64C4141);
        R11 = imageBase;
        R15 = imageBase + 0x43DFE92F;
        RCX = RAX;
        RCX >>= 0x27;
        RAX ^= RCX;
        RDX = RBX;
        RDX = ~RDX;
        RCX = RBX;
        RCX *= R15;
        RAX -= RCX;
        RCX = imageBase + 0x525C;
        RCX = ~RCX;
        RDX *= RCX;
        RAX ^= RDX;
        RAX -= R11;
        RCX = 0x98E32DD38CE89DDD;
        RAX *= RCX;
        RCX = 0x2FBEA02CACF11251;
        RAX += RCX;
        RCX = 0x4EB5109CA6269FDF;
        RAX ^= RCX;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R10;
        RCX = _byteswap_uint64(RCX);
        RAX *= readMemory<uint64_t>(RCX + 0x9);
        return RAX;
    }
    case 6: {
        R15 = imageBase + 0x6D6B;
        R10 = readMemory<uint64_t>(imageBase + 0x64C4141);
        RCX = RAX;
        RCX >>= 0x8;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x10;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x20;
        RAX ^= RCX;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R10;
        RCX = _byteswap_uint64(RCX);
        RAX *= readMemory<uint64_t>(RCX + 0x9);
        RCX = R15;
        RDX = RBX;
        RCX = ~RCX;
        RDX = ~RDX;
        RAX += RCX;
        RAX += RDX;
        RCX = RAX;
        RCX >>= 0x9;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x12;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x24;
        RAX ^= RCX;
        RCX = 0x5234F2A8F7885802;
        RAX += RCX;
        RCX = 0xCC2109B87D117D5;
        RAX *= RCX;
        RCX = 0x1818853313C451BE;
        RAX -= RCX;
        RCX = RAX;
        RCX >>= 0x1C;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x38;
        RAX ^= RCX;
        return RAX;
    }
    case 7: {
        R10 = readMemory<uint64_t>(imageBase + 0x64C4141);
        R11 = imageBase;
        RDX = 0x0;
        RCX = RBX + RAX;
        RDX = _rotl64(RDX, 0x10);
        RDX ^= R10;
        RDX = _byteswap_uint64(RDX);
        RAX = readMemory<uint64_t>(RDX + 0x9);
        RAX *= RCX;
        RCX = RAX;
        RCX >>= 0x1D;
        RAX ^= RCX;
        RDX = R11 + 0x9180;
        RDX += RBX;
        RCX = RAX;
        RCX >>= 0x3A;
        RDX ^= RCX;
        RAX ^= RDX;
        RAX += R11;
        RCX = 0xFDEE9A89B242E96D;
        RAX *= RCX;
        RCX = 0x527C3240A07E19;
        RAX -= RCX;
        RCX = RAX;
        RCX >>= 0x16;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x2C;
        RAX ^= RCX;
        return RAX;
    }
    case 8: {
        R10 = readMemory<uint64_t>(imageBase + 0x64C4141);
        R11 = imageBase;
        RAX -= R11;
        RAX ^= R11;
        RAX += RBX;
        RCX = RAX;
        RCX >>= 0x7;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0xE;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x1C;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x38;
        RAX ^= RCX;
        RCX = 0x62B7F1D904F8A67E;
        RAX -= RCX;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R10;
        RCX = _byteswap_uint64(RCX);
        RCX = readMemory<uint64_t>(RCX + 0x9);
        RAX *= RCX;
        RCX = 0x9FA77C8C0339043D;
        RAX *= RCX;
        RCX = 0xB36BB88CB0AD8CB9;
        RAX ^= RCX;
        return RAX;
    }
    case 9: {
        R15 = imageBase + 0x753;
        R14 = imageBase + 0x6B69F12F;
        R9 = readMemory<uint64_t>(imageBase + 0x64C4141);
        RCX = 0x18E462A21AF872B7;
        RAX += RCX;
        RAX -= RBX;
        RAX += RBX;
        RAX ^= RBX;
        RAX ^= R15;
        RCX = R14;
        RCX -= RBX;
        RAX += RCX;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R9;
        RCX = _byteswap_uint64(RCX);
        RAX *= readMemory<uint64_t>(RCX + 0x9);
        RCX = RAX;
        RCX >>= 0x19;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x32;
        RAX ^= RCX;
        RCX = 0xF1ACED747CE7CFE5;
        RAX *= RCX;
        return RAX;
    }
    case 10: {
        R10 = readMemory<uint64_t>(imageBase + 0x64C4141);
        R11 = imageBase;
        RDX = imageBase + 0x449F;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R10;
        RCX = _byteswap_uint64(RCX);
        RAX *= readMemory<uint64_t>(RCX + 0x9);
        RAX ^= R11;
        RCX = 0xAC72717D5227FDB3;
        RAX *= RCX;
        RCX = RAX;
        RCX >>= 0xE;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x1C;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x38;
        RAX ^= RCX;
        RCX = imageBase + 0x61FF7120;
        RAX += RBX;
        RAX += RCX;
        RCX = RAX;
        RCX >>= 0x19;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x32;
        RAX ^= RCX;
        RCX = RDX;
        RCX = ~RCX;
        RCX += RBX;
        RAX += RCX;
        RAX -= RBX;
        return RAX;
    }
    case 11: {
        R10 = readMemory<uint64_t>(imageBase + 0x64C4141);
        R11 = imageBase;
        RCX = RAX;
        RCX >>= 0x12;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x24;
        RAX ^= RCX;
        RCX = 0x8AF3860D5BC3C2A;
        RAX ^= RCX;
        RDX = 0x0;
        RDX = _rotl64(RDX, 0x10);
        RCX = RBX + RAX;
        RDX ^= R10;
        RAX = 0xA7F6204CE90AE275;
        RCX *= RAX;
        RAX = 0x4EF0B6F203B31EDB;
        RCX -= RAX;
        RDX = _byteswap_uint64(RDX);
        RAX = readMemory<uint64_t>(RDX + 0x9);
        RAX *= RCX;
        RCX = RAX;
        RCX >>= 0xC;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x18;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x30;
        RAX ^= RCX;
        RAX ^= R11;
        return RAX;
    }
    case 12: {
        R10 = readMemory<uint64_t>(imageBase + 0x64C4141);
        R11 = imageBase;
        RDX = imageBase + 0x3241;
        RCX = 0xBE86AAFB0DE7D0F7;
        RAX *= RCX;
        RCX = RAX;
        RCX >>= 0x1D;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x3A;
        RAX ^= RCX;
        RAX ^= R11;
        RCX = 0x85D874BD03081E67;
        RAX *= RCX;
        RCX = RBX;
        RCX = ~RCX;
        RCX ^= RDX;
        RAX += RCX;
        RAX ^= RBX;
        RDX = 0x0;
        RCX = imageBase + 0x5B3B;
        RDX = _rotl64(RDX, 0x10);
        RCX -= RBX;
        RDX ^= R10;
        RDX = _byteswap_uint64(RDX);
        RDX = readMemory<uint64_t>(RDX + 0x9);
        RAX *= RDX;
        RAX ^= RCX;
        return RAX;
    }
    case 13: {
        R11 = imageBase;
        R10 = readMemory<uint64_t>(imageBase + 0x64C4141);
        RCX = 0x1341335BD1D16F35;
        RAX ^= RCX;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R10;
        RCX = _byteswap_uint64(RCX);
        RAX *= readMemory<uint64_t>(RCX + 0x9);
        RCX = imageBase + 0xE3C5;
        RDX = RBX;
        RDX = ~RDX;
        RDX += RCX;
        RCX = RAX;
        RAX = 0x434CE874F460EF3D;
        RCX *= RAX;
        RAX = RDX;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x13;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x26;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x25;
        RAX ^= RCX;
        RCX = 0x525791A8C4CA0C2F;
        RAX -= RCX;
        RAX -= R11;
        RAX += 0xFFFFFFFFA3528AA2;
        RAX += RBX;
        return RAX;
    }
    case 14: {
        R11 = imageBase;
        R15 = imageBase + 0x17E4;
        R9 = readMemory<uint64_t>(imageBase + 0x64C4141);
        RCX = RAX;
        RCX >>= 0xA;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x14;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x28;
        RAX ^= RCX;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R9;
        RCX = _byteswap_uint64(RCX);
        RCX = readMemory<uint64_t>(RCX + 0x9);
        RAX *= RCX;
        RAX -= R11;
        RAX += 0xFFFFFFFFFFFF497B;
        RAX += RBX;
        RAX += RBX;
        RCX = 0x6F1484E3C83B5D;
        RAX -= RCX;
        RAX ^= RBX;
        RAX ^= R15;
        RCX = 0xEB960098A87EA513;
        RAX *= RCX;
        RCX = 0x504EC39A7C1CEB8F;
        RAX *= RCX;
        return RAX;
    }
    case 15: {
        uint64_t RSP_0x60 = imageBase;
        R11 = imageBase;
        RCX = imageBase + 0x52268C9A;
        RSP_0x60 = RCX; // mov [rsp+60h],rcx
        R9 = readMemory<uint64_t>(imageBase + 0x64C4141);
        RCX = RAX;
        RCX >>= 0x8;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x10;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x20;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x27;
        RAX ^= RCX;
        RCX = RBX;
        RCX = ~RCX;
        RCX += RSP_0x60; // add rcx,[rsp+60h]
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0xF;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x1E;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x3C;
        RAX ^= RCX;
        RCX = 0x34B202B836BED1C1;
        RAX *= RCX;
        RCX = RBX;
        RCX = ~RCX;
        RCX -= R11;
        RCX -= 0x5D134B1E;
        RAX ^= RCX;
        RAX -= R11;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R9;
        RCX = _byteswap_uint64(RCX);
        RAX *= readMemory<uint64_t>(RCX + 0x9);
        return RAX;
    }
    }
}

extern "C" auto decrypt_bone_base(uint64_t imageBase, uint64_t peb) -> uint64_t
{
    uint64_t RAX = imageBase, RBX = imageBase, RCX = imageBase, RDX = imageBase, R8 = imageBase, RDI = imageBase, RSI = imageBase, R9 = imageBase, R10 = imageBase, R11 = imageBase, R12 = imageBase, R13 = imageBase, R14 = imageBase, R15 = imageBase, RBP = 0, RSP = 0;

    RDX = readMemory<uint64_t>(imageBase + 0x1566B2E8);
    if (RDX == 0) {
        return 0;
    }
    R8 = peb; // mov r8,gs:[rax]
    // test rdx,rdx
    // je 00007FF726671F2Bh
    RAX = R8;
    RAX = _rotl64(RAX, 0x28);
    RAX &= 0xF;
    // cmp rax,0Eh
    // ja 00007FF726671B57h
    switch (RAX) {
    case 0: {
        RBX = readMemory<uint64_t>(imageBase + 0x64C4202);
        R12 = imageBase + 0x225CEDD6;
        R15 = imageBase + 0x3F5B;
        RAX = 0xCA6286D0E37AC7A7;
        RDX *= RAX;
        RCX = 0x0;
        RAX = R12;
        RCX = _rotl64(RCX, 0x10);
        RAX = ~RAX;
        RAX ^= RDX;
        RCX ^= RBX;
        RAX ^= R8;
        RCX = _byteswap_uint64(RCX);
        RDX = readMemory<uint64_t>(RCX + 0x9);
        RDX *= RAX;
        RAX = 0x6938F56FB7F75A73;
        RDX -= RAX;
        RAX = imageBase;
        RDX += RAX;
        RCX = R8;
        RCX = ~RCX;
        RCX ^= R15;
        RDX += RCX;
        RAX = RDX;
        RAX >>= 0x1B;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x36;
        RDX ^= RAX;
        RAX = 0xF9653CAA92C4CD18;
        RDX ^= RAX;
        return RDX;
    }
    case 1: {
        RBX = readMemory<uint64_t>(imageBase + 0x64C4202);
        R15 = imageBase + 0x1B9F4B22;
        RAX = RDX;
        RAX >>= 0x24;
        RDX ^= RAX;
        RCX = R15;
        RCX = ~RCX;
        RCX ^= RDX;
        RCX ^= R8;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= RBX;
        RAX = _byteswap_uint64(RAX);
        RDX = readMemory<uint64_t>(RAX + 0x9);
        RAX = 0xD24CCD01D0B76BCB;
        RDX *= RCX;
        RCX = imageBase + 0x71509D8E;
        RDX += R8;
        RCX = ~RCX;
        RCX++;
        RDX += RCX;
        RDX *= RAX;
        RAX = 0x2E3732E6FF42798F;
        RDX *= RAX;
        RAX = RDX;
        RAX >>= 0x2;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x4;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x8;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x10;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x20;
        RDX ^= RAX;
        RAX = 0x750D70C990B2BAB5;
        RDX *= RAX;
        return RDX;
    }
    case 2: {
        R14 = imageBase + 0x47803A58;
        R10 = readMemory<uint64_t>(imageBase + 0x64C4202);
        RAX = 0xBBD631CFF3F7F015;
        RDX *= RAX;
        RAX = RDX;
        RAX >>= 0x14;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x28;
        RDX ^= RAX;
        RAX = imageBase;
        RDX ^= RAX;
        RAX = R14;
        RAX = ~RAX;
        RAX ^= R8;
        RDX -= RAX;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R10;
        RAX = _byteswap_uint64(RAX);
        RAX = readMemory<uint64_t>(RAX + 0x9);
        RDX *= RAX;
        RAX = 0xFCABD61E4E485CCA;
        RDX ^= RAX;
        RDX += R8;
        RAX = RDX;
        RAX >>= 0x11;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x22;
        RDX ^= RAX;
        return RDX;
    }
    case 3: {
        // pushfq
        // push rdx
        // pop rdx
        // pop rdx
        RBX = readMemory<uint64_t>(imageBase + 0x64C4202);
        R15 = imageBase + 0x11C5C5A8;
        RAX = RDX;
        RAX >>= 0x25;
        RDX ^= RAX;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= RBX;
        RAX = _byteswap_uint64(RAX);
        RDX *= readMemory<uint64_t>(RAX + 0x9);
        RAX = R15;
        RAX = ~RAX;
        RDX ^= RAX;
        RDX ^= R8;
        RAX = imageBase + 0x549;
        RAX += R8;
        RDX += RAX;
        RAX = 0xB0433CCEB88787D5;
        RDX *= RAX;
        RAX = 0x558D0A55BFCDC1DC;
        RDX += RAX;
        RAX = RDX;
        RAX >>= 0xD;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x1A;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x34;
        RDX ^= RAX;
        RAX = 0x324D3D1671C210A2;
        RDX -= RAX;
        return RDX;
    }
    case 4: {
        // pushfq
        // push rdx
        // pop rdx
        // pop rdx
        R10 = readMemory<uint64_t>(imageBase + 0x64C4202);
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R10;
        RAX = _byteswap_uint64(RAX);
        RDX *= readMemory<uint64_t>(RAX + 0x9);
        RAX = RDX;
        RAX >>= 0x18;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x30;
        RDX ^= RAX;
        RAX = imageBase;
        RDX ^= RAX;
        RDX += R8;
        RAX = RDX;
        RAX >>= 0x10;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x20;
        RDX ^= RAX;
        RAX = 0x9BF0B3A6F12469BB;
        RDX *= RAX;
        RAX = 0x46C4DD776CF4D5A5;
        RDX *= RAX;
        return RDX;
    }
    case 5: {
        RBX = readMemory<uint64_t>(imageBase + 0x64C4202);
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= RBX;
        RAX = _byteswap_uint64(RAX);
        RAX = readMemory<uint64_t>(RAX + 0x9);
        RDX *= RAX;
        RAX = imageBase;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x3;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x6;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0xC;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x18;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x30;
        RDX ^= RAX;
        RAX = 0x6A54CCBC042994E4;
        RDX -= RAX;
        RAX = 0xCB59636EBF91549D;
        RDX *= RAX;
        RAX = RDX;
        RAX >>= 0x1;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x2;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x4;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x8;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x10;
        RDX ^= RAX;
        RCX = imageBase + 0x54417AE2;
        RAX = RDX;
        RAX >>= 0x20;
        RAX ^= RDX;
        RDX = 0x15BDFB27380DED02;
        RDX += RAX;
        RCX *= R8;
        RDX += RCX;
        return RDX;
    }
    case 6: {
        // push rdx
        // pushfq
        // pop rdx
        // popfq
        // pop rdx
        R12 = imageBase + 0x6FD070F0;
        R10 = readMemory<uint64_t>(imageBase + 0x64C4202);
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R10;
        RAX = _byteswap_uint64(RAX);
        RDX *= readMemory<uint64_t>(RAX + 0x9);
        RDX -= R8;
        RDX ^= R8;
        RAX = RDX;
        RAX >>= 0x11;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x22;
        RDX ^= RAX;
        RDX ^= R12;
        RDX ^= R8;
        RAX = 0xD5AFB43724CD9719;
        RDX ^= RAX;
        RAX = 0xC95F3A515AF20107;
        RDX *= RAX;
        RAX = 0x2A233EF486AD7BF6;
        RDX -= RAX;
        return RDX;
    }
    case 7: {
        R15 = imageBase + 0x630E28F1;
        R10 = readMemory<uint64_t>(imageBase + 0x64C4202);
        RAX = R15;
        RAX ^= R8;
        RDX -= RAX;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R10;
        RAX = _byteswap_uint64(RAX);
        RDX *= readMemory<uint64_t>(RAX + 0x9);
        RAX = 0x845EBCF78EF64A35;
        RDX *= RAX;
        RAX = 0xA356436D6A689BA9;
        RDX *= RAX;
        RDX += R8;
        RAX = RDX;
        RAX >>= 0x7;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0xE;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x1C;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x38;
        RDX ^= RAX;
        RAX = imageBase;
        RDX -= RAX;
        RAX = imageBase;
        RDX += RAX;
        return RDX;
    }
    case 8: {
        // pushfq
        // push rdx
        // pop rdx
        // pop rdx
        RBX = readMemory<uint64_t>(imageBase + 0x64C4202);
        R13 = imageBase + 0xC00B;
        R12 = imageBase + 0x2CF0DADC;
        RAX = 0xCA5A38F20F9BA30F;
        RDX *= RAX;
        RAX = RDX;
        RAX >>= 0x5;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0xA;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x14;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x28;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x17;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x2E;
        RDX ^= RAX;
        RCX = R8;
        RCX = ~RCX;
        RAX = imageBase;
        RAX += RDX;
        RDX = R12;
        RAX ^= RCX;
        RDX = ~RDX;
        RAX ^= R13;
        RAX += RCX;
        RDX += RAX;
        RCX = 0x0;
        RAX = RDX;
        RCX = _rotl64(RCX, 0x10);
        RAX -= R8;
        RCX ^= RBX;
        RCX = _byteswap_uint64(RCX);
        RDX = readMemory<uint64_t>(RCX + 0x9);
        RDX *= RAX;
        return RDX;
    }
    case 9: {
        uint64_t RBP_NEG_0x58 = imageBase;
        RAX = 0x98C88223A0043F87;
        RBP_NEG_0x58 = RAX; // mov [rbp-58h],rax
        R10 = readMemory<uint64_t>(imageBase + 0x64C4202);
        RAX = 0x7F25118F43A246BD;
        RDX += RAX;
        RAX = imageBase;
        RDX -= RAX;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R10;
        RAX = _byteswap_uint64(RAX);
        RAX = readMemory<uint64_t>(RAX + 0x9);
        RAX *= RBP_NEG_0x58; // imul rax,[rbp-58h]
        RDX *= RAX;
        RAX = imageBase;
        RDX += RAX;
        RAX = imageBase;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x18;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x30;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x1A;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x34;
        RDX ^= RAX;
        return RDX;
    }
    case 10: {
        R14 = imageBase + 0xFD9E;
        R10 = readMemory<uint64_t>(imageBase + 0x64C4202);
        RAX = imageBase;
        RDX ^= RAX;
        RAX = R14;
        RAX = ~RAX;
        RAX += R8;
        RDX ^= RAX;
        RAX = 0x81FE0F5E6FF72EEF;
        RDX *= RAX;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R10;
        RAX = _byteswap_uint64(RAX);
        RDX *= readMemory<uint64_t>(RAX + 0x9);
        RAX = RDX;
        RAX >>= 0x24;
        RDX ^= RAX;
        RAX = imageBase;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x11;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x22;
        RDX ^= RAX;
        RAX = imageBase;
        RDX += RAX;
        return RDX;
    }
    case 11: {
        // pushfq
        // push rdx
        // pop rdx
        // pop rdx
        R12 = imageBase + 0x2396;
        R15 = imageBase + 0x30379337;
        R10 = readMemory<uint64_t>(imageBase + 0x64C4202);
        RDX += R8;
        RAX = R8 + R12;
        RDX ^= RAX;
        RAX = 0xC8CEA2A375E511F3;
        RDX *= RAX;
        RAX = 0x33573597806B948F;
        RDX ^= RAX;
        RAX = R8;
        RAX = ~RAX;
        RAX ^= R15;
        RDX += RAX;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R10;
        RAX = _byteswap_uint64(RAX);
        RDX *= readMemory<uint64_t>(RAX + 0x9);
        RAX = RDX;
        RAX >>= 0x1E;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x3C;
        RDX ^= RAX;
        RAX = 0x8B5D577196545E6B;
        RDX *= RAX;
        return RDX;
    }
    case 12: {
        R14 = imageBase + 0x487E78DD;
        R10 = readMemory<uint64_t>(imageBase + 0x64C4202);
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R10;
        RAX = _byteswap_uint64(RAX);
        RDX *= readMemory<uint64_t>(RAX + 0x9);
        RAX = imageBase;
        RDX ^= RAX;
        RAX = R8 + 1;
        RAX *= R14;
        RAX -= R8;
        RDX += RAX;
        RAX = 0x212BE2FF5A18ACBA;
        RDX += RAX;
        RAX = RDX;
        RAX >>= 0x22;
        RDX ^= RAX;
        RAX = 0x7E8F66264BD200DF;
        RDX ^= RAX;
        RAX = 0x9C9098D43B5693A9;
        RDX *= RAX;
        return RDX;
    }
    case 13: {
        R15 = imageBase + 0x1EA7F20C;
        RBX = readMemory<uint64_t>(imageBase + 0x64C4202);
        RAX = imageBase;
        RDX -= RAX;
        RAX = RDX;
        RCX = 0x0;
        RDX = 0x1D307C74CC98F164;
        RCX = _rotl64(RCX, 0x10);
        RAX ^= RDX;
        RCX ^= RBX;
        RCX = _byteswap_uint64(RCX);
        RDX = readMemory<uint64_t>(RCX + 0x9);
        RDX *= RAX;
        RAX = RDX;
        RAX >>= 0x1F;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x3E;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x21;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x12;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x24;
        RDX ^= RAX;
        RAX = 0x37302456CAF679D;
        RDX *= RAX;
        RAX = R15;
        RAX *= R8;
        RDX -= RAX;
        return RDX;
    }
    case 14: {
        R14 = imageBase + 0x11137B66;
        R10 = readMemory<uint64_t>(imageBase + 0x64C4202);
        RAX = R14;
        RAX *= R8;
        RDX -= RAX;
        RAX = imageBase + 0x514158CF;
        RAX -= R8;
        RDX += RAX;
        RAX = imageBase;
        RDX += RAX;
        RAX = RDX;
        RAX >>= 0x22;
        RDX ^= RAX;
        RAX = imageBase;
        RDX += RAX;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R10;
        RAX = _byteswap_uint64(RAX);
        RDX *= readMemory<uint64_t>(RAX + 0x9);
        RAX = 0x8ED0417D2044B81D;
        RDX *= RAX;
        RAX = imageBase;
        RDX -= RAX;
        return RDX;
    }
    case 15: {
        uint64_t RSP_0x58 = imageBase;
        // pop rax
        // pop rax
        // popfq
        RBX = readMemory<uint64_t>(imageBase + 0x64C4202);
        RAX = 0xA750C4F5753C87A1;
        RSP_0x58 = RAX; // mov [rsp+58h],rax
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= RBX;
        RAX = _byteswap_uint64(RAX);
        RAX = readMemory<uint64_t>(RAX + 0x9);
        RAX *= RSP_0x58; // imul rax,[rsp+58h]
        RDX *= RAX;
        RAX = imageBase + 0x40BBB129;
        RAX += R8;
        RDX += RAX;
        RDX -= R8;
        RAX = RDX;
        RAX >>= 0xB;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x16;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x2C;
        RDX ^= RAX;
        RAX = 0x11CFC5F08A4A3BBC;
        RDX += RAX;
        RAX = imageBase;
        RDX ^= RAX;
        return RDX;
    }
    }
}

extern "C" auto get_bone_index(uint32_t index, uint64_t imageBase) -> uint64_t
{
    uint64_t RAX = imageBase, RBX = imageBase, RCX = imageBase, RDX = imageBase, R8 = imageBase, RDI = imageBase, RSI = imageBase, R9 = imageBase, R10 = imageBase, R11 = imageBase, R12 = imageBase, R13 = imageBase, R14 = imageBase, R15 = imageBase, RBP = 0, RSP = 0;

    RBX = index;
    RCX = RBX * 0x13C8;
    RAX = 0x119AF9B51BBFC495;
    R11 = imageBase;
    RAX = _umul128(RAX, RCX, &RDX);
    R10 = 0xF31778EC350EBF85;
    RDX >>= 0x9;
    RAX = RDX * 0x1D15;
    RCX -= RAX;
    RAX = 0x447C602C5D012611;
    R8 = RCX * 0x1D15;
    RAX = _umul128(RAX, R8, &RDX);
    RAX = R8;
    RAX -= RDX;
    RAX >>= 0x1;
    RAX += RDX;
    RAX >>= 0xD;
    RAX = RAX * 0x327E;
    R8 -= RAX;
    RAX = 0xE558EAB90039563B;
    RAX = _umul128(RAX, R8, &RDX);
    RAX = 0x2492492492492493;
    RDX >>= 0xA;
    RCX = RDX * 0x477;
    RAX = _umul128(RAX, R8, &RDX);
    RAX = R8;
    RAX -= RDX;
    RAX >>= 0x1;
    RAX += RDX;
    RAX >>= 0x3;
    RCX += RAX;
    RAX = RCX * 0x1C;
    RCX = R8 * 0x1E;
    RCX -= RAX;
    RAX = readMemory<uint16_t>(RCX + R11 + 0x64CC820);
    R8 = RAX * 0x13C8;
    RAX = R10;
    RAX = _umul128(RAX, R8, &RDX);
    RAX = R10;
    RDX >>= 0xD;
    RCX = RDX * 0x21B3;
    R8 -= RCX;
    R9 = R8 * 0x2F97;
    RAX = _umul128(RAX, R9, &RDX);
    RDX >>= 0xD;
    RAX = RDX * 0x21B3;
    R9 -= RAX;
    RAX = 0xCCCCCCCCCCCCCCCD;
    RAX = _umul128(RAX, R9, &RDX);
    RAX = 0x10182436517A3753;
    RDX >>= 0x4;
    RCX = RDX + RDX * 4;
    RAX = _umul128(RAX, R9, &RDX);
    RDX >>= 0x5;
    RAX = RDX + RCX * 4;
    RCX = RAX * 0x3FA;
    RAX = R9 * 0x3FC;
    RAX -= RCX;
    RSI = readMemory<uint16_t>(RAX + R11 + 0x64D4530);
    return RSI;
}
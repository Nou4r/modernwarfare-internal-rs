// 1.45.2.10635118
#include "Decryption.h"

extern "C" auto decrypt_client_info(uint64_t imageBase, uint64_t peb) -> uint64_t
{
    uint64_t RAX = imageBase, RBX = imageBase, RCX = imageBase, RDX = imageBase, R8 = imageBase, RDI = imageBase, RSI = imageBase, R9 = imageBase, R10 = imageBase, R11 = imageBase, R12 = imageBase, R13 = imageBase, R14 = imageBase, R15 = imageBase;

    RBX = readMemory<uint64_t>(imageBase + 0x180D5F58);
    if (RBX == 0) {
        return 0;
    }
    uint64_t RSP_0x50 = imageBase;
    RSP_0x50 = 0xC; // mov byte ptr [rsp+50h],0Ch
    // movzx eax,byte ptr [rsp+50h]
    RAX = _rotr64(RAX, 0xDD);
    // movzx eax,al
    RCX = peb; // mov rcx,gs:[rax]
    RAX = imageBase;
    RCX = ~RCX;
    R8 = imageBase + 0x5A665254;
    R8 -= RCX;
    R8 ^= RBX;
    R8 ^= RAX;
    RAX = 0x4608305C4A63DEBB;
    R8 *= RAX;
    R8 -= RCX;
    RAX = R8;
    RAX >>= 0x13;
    R8 ^= RAX;
    RAX = R8;
    RCX = 0x0;
    RAX >>= 0x26;
    RCX = _rotl64(RCX, 0x10);
    RAX ^= R8;
    RCX ^= readMemory<uint64_t>(imageBase + 0x7241109);
    RCX = _byteswap_uint64(RCX);
    RBX = readMemory<uint64_t>(RCX + 0x7);
    RBX *= RAX;
    return RBX;
}

extern "C" auto decrypt_client_base(uint64_t clientInfo, uint64_t imageBase, uint64_t peb) -> uint64_t
{
    uint64_t RAX = imageBase, RBX = imageBase, RCX = imageBase, RDX = imageBase, R8 = imageBase, RDI = imageBase, RSI = imageBase, R9 = imageBase, R10 = imageBase, R11 = imageBase, R12 = imageBase, R13 = imageBase, R14 = imageBase, R15 = imageBase, RBP = 0, RSP = 0;

    RAX = readMemory<uint64_t>(clientInfo + 0x9FE48);
    R11 = peb; // mov r11,gs:[rcx]
    R11 = ~R11;
    // test rax,rax
    // je 00007FF7388F6964h
    RCX = R11;
    RCX = _rotl64(RCX, 0x28);
    RCX &= 0xF;
    // cmp rcx,0Eh
    // ja 00007FF7388F649Eh
    switch (RCX) {
    case 0: {
        R9 = readMemory<uint64_t>(imageBase + 0x7241136);
        RCX = RAX;
        RCX >>= 0x23;
        RAX ^= RCX;
        RCX = imageBase + 0x1AF5;
        RCX -= R11;
        RAX += RCX;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R9;
        RCX = ~RCX;
        RAX *= readMemory<uint64_t>(RCX + 0xF);
        RCX = 0x1ABE623771906BF9;
        RAX *= RCX;
        RCX = 0x9756AE831827737D;
        RAX ^= RCX;
        RCX = 0x31C42480E237EC5A;
        RAX += R11;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x27;
        RAX ^= RCX;
        return RAX;
    }
    case 1: {
        R10 = readMemory<uint64_t>(imageBase + 0x7241136);
        RCX = 0xD0D21C582D683B3F;
        RAX *= RCX;
        RCX = RAX;
        RCX >>= 0x11;
        RAX ^= RCX;
        RCX = RAX;
        RDX = 0x0;
        RCX >>= 0x22;
        RCX ^= RAX;
        RDX = _rotl64(RDX, 0x10);
        RDX ^= R10;
        RDX = ~RDX;
        RAX = readMemory<uint64_t>(RDX + 0xF);
        RAX *= RCX;
        RCX = imageBase;
        RAX += RCX;
        RCX = 0x20A0F3C1B8A7EE79;
        RAX *= RCX;
        RCX = 0xB241CF3D2CBC1520;
        RAX += RCX;
        RAX += R11;
        RCX = imageBase;
        RCX += 0xDB83;
        RCX += R11;
        RAX ^= RCX;
        return RAX;
    }
    case 2: {
        R10 = readMemory<uint64_t>(imageBase + 0x7241136);
        RCX = imageBase;
        RCX += 0x6D0AC0EA;
        RCX += R11;
        RAX += RCX;
        RCX = 0x621163FE844C5B57;
        RAX -= RCX;
        RCX = RAX;
        RCX >>= 0x8;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x10;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x20;
        RAX ^= RCX;
        RDX = 0x0;
        RDX = _rotl64(RDX, 0x10);
        RCX = RAX;
        RDX ^= R10;
        RDX = ~RDX;
        RAX = 0x24446E6919404656;
        RCX ^= RAX;
        RAX = readMemory<uint64_t>(RDX + 0xF);
        RAX *= RCX;
        RCX = imageBase;
        RAX -= R11;
        RAX -= RCX;
        RAX -= 0x6DF8BA0D;
        RCX = 0x71B29F258D54B62D;
        RAX *= RCX;
        RSI = imageBase;
        RCX = 0xFFFFFFFFFFFFD925;
        RCX -= R11;
        RCX -= RSI;
        RAX += RCX;
        return RAX;
    }
    case 3: {
        uint64_t RSP_0x60 = imageBase;
        R10 = readMemory<uint64_t>(imageBase + 0x7241136);
        R15 = imageBase + 0xC85A;
        RCX = 0xBBB233E50CDA63F9;
        RSP_0x60 = RCX; // mov [rsp+60h],rcx
        RCX = imageBase;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x12;
        RAX ^= RCX;
        RDX = RAX;
        RDX >>= 0x24;
        RDX ^= RAX;
        RAX = R11;
        RAX = ~RAX;
        RAX += RDX;
        RAX += R15;
        RCX = imageBase;
        RAX ^= RCX;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R10;
        RCX = ~RCX;
        RCX = readMemory<uint64_t>(RCX + 0xF);
        RCX *= RSP_0x60; // imul rcx,[rsp+60h]
        RAX *= RCX;
        RCX = 0x7CFBD8A6D62A9247;
        RAX -= RCX;
        RAX -= R11;
        return RAX;
    }
    case 4: {
        uint64_t RBP_NEG_0x78 = imageBase;
        R10 = readMemory<uint64_t>(imageBase + 0x7241136);
        RSI = imageBase + 0x37315681;
        RCX = RAX;
        RCX >>= 0x20;
        RAX ^= RCX;
        RCX = 0x66B059D909222D83;
        RAX *= RCX;
        RDX = R11;
        RDX ^= RSI;
        RCX = RAX;
        RAX = 0xA774DDE18AA27783;
        RAX *= RCX;
        RAX += RDX;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R10;
        RCX = ~RCX;
        RAX *= readMemory<uint64_t>(RCX + 0xF);
        RCX = 0x61CA7F83A07685D6;
        RAX += RCX;
        RCX = 0xFFFFFFFFCA5171E1;
        RCX -= RBP_NEG_0x78; // sub rcx,[rbp-78h]
        RAX += RCX;
        return RAX;
    }
    case 5: {
        R10 = readMemory<uint64_t>(imageBase + 0x7241136);
        R15 = imageBase + 0x17BEAE4B;
        RCX = imageBase;
        RAX += RCX;
        RCX = RAX;
        RCX >>= 0x22;
        RCX ^= R11;
        RAX ^= RCX;
        RCX = R11;
        RCX *= R15;
        RAX -= RCX;
        RCX = 0xA26EF04DF522A783;
        RAX *= RCX;
        RCX = RAX;
        RCX >>= 0x23;
        RAX ^= RCX;
        RCX = 0x2636333021CD0F7B;
        RAX *= RCX;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R10;
        RCX = ~RCX;
        RAX *= readMemory<uint64_t>(RCX + 0xF);
        return RAX;
    }
    case 6: {
        uint64_t RBP_NEG_0x78 = imageBase;
        R10 = readMemory<uint64_t>(imageBase + 0x7241136);
        R14 = imageBase + 0x24112BAA;
        RCX = imageBase + 0x9E27;
        RBP_NEG_0x78 = RCX; // mov [rbp-78h],rcx
        RCX = 0x32FA8E52581720A9;
        RAX *= RCX;
        RCX = R11;
        RCX *= RBP_NEG_0x78; // imul rcx,[rbp-78h]
        RAX += RCX;
        RCX = 0x257947B22D009E07;
        RAX += RCX;
        RCX = RAX;
        RCX >>= 0x1A;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x34;
        RAX ^= RCX;
        RAX += R11;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R10;
        RCX = ~RCX;
        RAX *= readMemory<uint64_t>(RCX + 0xF);
        RDX = R11 + 1;
        RCX = RAX;
        RAX = 0x459C459B7886E63D;
        RAX *= RCX;
        RDX *= R14;
        RAX += RDX;
        return RAX;
    }
    case 7: {
        R10 = readMemory<uint64_t>(imageBase + 0x7241136);
        RCX = RAX;
        RCX >>= 0x1A;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x34;
        RAX ^= RCX;
        RCX = 0xD9D88CDC2D9CF574;
        RAX ^= RCX;
        RAX += R11;
        RCX = 0xEC45839F3CA55135;
        RAX *= RCX;
        RCX = imageBase;
        RAX += RCX;
        RAX -= R11;
        RDX = 0x0;
        RDX = _rotl64(RDX, 0x10);
        RCX = imageBase;
        RAX -= RCX;
        RDX ^= R10;
        RDX = ~RDX;
        RCX = RAX - 0x550A30EC;
        RAX = readMemory<uint64_t>(RDX + 0xF);
        RAX *= RCX;
        RAX += R11;
        return RAX;
    }
    case 8: {
        R10 = readMemory<uint64_t>(imageBase + 0x7241136);
        R14 = imageBase + 0x13BA7B83;
        RCX = 0xA184D1EDDFF30DF9;
        RAX *= RCX;
        RCX = RAX;
        RCX >>= 0x1A;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x34;
        RAX ^= RCX;
        RCX = 0xD0CF1E6C7B4D31DF;
        RAX *= RCX;
        RCX = R14;
        RCX = ~RCX;
        RCX *= R11;
        RAX ^= RCX;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R10;
        RCX = ~RCX;
        RAX *= readMemory<uint64_t>(RCX + 0xF);
        RCX = 0xC027FF20D3C3DC04;
        RAX ^= RCX;
        return RAX;
    }
    case 9: {
        R10 = readMemory<uint64_t>(imageBase + 0x7241136);
        RSI = imageBase + 0xE468;
        RAX -= R11;
        RCX = imageBase;
        RAX -= RCX;
        RCX = R11;
        RCX *= RSI;
        RAX -= 0x7B5F;
        RAX ^= RCX;
        RCX = 0x8994D19791BDC16B;
        RAX *= RCX;
        RCX = RAX;
        RCX >>= 0x14;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x28;
        RAX ^= RCX;
        RCX = imageBase;
        RAX -= R11;
        RAX -= RCX;
        RAX -= 0x5D498B02;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R10;
        RCX = ~RCX;
        RAX *= readMemory<uint64_t>(RCX + 0xF);
        RCX = imageBase + 0xEC83;
        RCX = ~RCX;
        RCX += R11;
        RAX ^= RCX;
        RCX = 0x46268BC6B906CF38;
        RAX ^= RCX;
        return RAX;
    }
    case 10: {
        R9 = readMemory<uint64_t>(imageBase + 0x7241136);
        RCX = RAX;
        RCX >>= 0x20;
        RAX ^= RCX;
        RCX = 0xD07B22F775DFC59F;
        RAX *= RCX;
        RCX = RAX;
        RCX >>= 0x22;
        RAX ^= RCX;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R9;
        RCX = ~RCX;
        RAX *= readMemory<uint64_t>(RCX + 0xF);
        RCX = 0x382EA1E22E05D863;
        RAX *= RCX;
        RCX = 0x54D54F7E04A14D2A;
        RAX -= RCX;
        RCX = RAX;
        RCX >>= 0x1D;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x3A;
        RAX ^= RCX;
        RAX += R11;
        return RAX;
    }
    case 11: {
        uint64_t RBP_NEG_0x78 = imageBase;
        R15 = imageBase + 0x3A39F418;
        R10 = readMemory<uint64_t>(imageBase + 0x7241136);
        RCX = 0xBBAE384832345319;
        RAX *= RCX;
        RAX ^= R11;
        RCX = RAX;
        RCX >>= 0x5;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0xA;
        RAX ^= RCX;
        RDX = 0x0;
        RCX = RAX;
        RCX >>= 0x14;
        RAX ^= RCX;
        RDX = _rotl64(RDX, 0x10);
        RCX = RAX;
        RDX ^= R10;
        RCX >>= 0x28;
        RDX = ~RDX;
        RCX ^= RAX;
        RAX = readMemory<uint64_t>(RDX + 0xF);
        RDX = imageBase + 0xC15F;
        RAX *= RCX;
        RCX = R11;
        RCX *= RDX;
        RCX -= RBP_NEG_0x78; // sub rcx,[rbp-78h]
        RAX += RCX;
        RCX = RAX;
        RCX >>= 0x1A;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x34;
        RAX ^= RCX;
        RCX = R11 + 1;
        RCX *= R15;
        RAX += RCX;
        return RAX;
    }
    case 12: {
        R10 = readMemory<uint64_t>(imageBase + 0x7241136);
        RCX = RAX;
        RCX >>= 0x11;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x22;
        RAX ^= RCX;
        RCX = 0x64820450B2C84E2E;
        RAX ^= RCX;
        RCX = 0x36C4F987BF87B276;
        RAX += RCX;
        RDX = 0x0;
        RDX = _rotl64(RDX, 0x10);
        RDX ^= R10;
        RCX = R11;
        RCX ^= RAX;
        RDX = ~RDX;
        RAX = readMemory<uint64_t>(RDX + 0xF);
        RAX *= RCX;
        RCX = 0x2BFCD726DDF66F6F;
        RAX *= RCX;
        RCX = imageBase + 0x1FFA;
        RAX += R11;
        RAX += RCX;
        RCX = RAX;
        RCX >>= 0x23;
        RAX ^= RCX;
        return RAX;
    }
    case 13: {
        uint64_t RBP_NEG_0x78 = imageBase;
        R10 = readMemory<uint64_t>(imageBase + 0x7241136);
        RCX = RAX;
        RCX >>= 0xD;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x1A;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x34;
        RAX ^= RCX;
        RCX = imageBase;
        RAX += RCX;
        RCX = imageBase;
        RAX -= RCX;
        RCX = 0xD9546612E0C1B72F;
        RAX *= RCX;
        RCX = 0x1335C3542316B16C;
        RAX ^= RCX;
        RDX = 0x0;
        RDX = _rotl64(RDX, 0x10);
        RDX ^= R10;
        RCX = R11;
        RCX -= RBP_NEG_0x78; // sub rcx,[rbp-78h]
        RDX = ~RDX;
        RCX -= 0x153148D8;
        RCX ^= RAX;
        RAX = readMemory<uint64_t>(RDX + 0xF);
        RAX *= RCX;
        RCX = 0x6774FBE598B3D0CC;
        RAX -= RCX;
        return RAX;
    }
    case 14: {
        R9 = readMemory<uint64_t>(imageBase + 0x7241136);
        RAX ^= R11;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R9;
        RCX = ~RCX;
        RAX *= readMemory<uint64_t>(RCX + 0xF);
        RAX ^= R11;
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
        RCX = RAX;
        RCX >>= 0xF;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x1E;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x3C;
        RAX ^= RCX;
        RCX = 0x9CCE8B576D4B2B71;
        RAX *= RCX;
        RCX = 0x40C894F42E6D60CD;
        RAX *= RCX;
        RCX = RAX;
        RCX >>= 0x20;
        RAX ^= RCX;
        return RAX;
    }
    case 15: {
        R10 = readMemory<uint64_t>(imageBase + 0x7241136);
        RAX ^= R11;
        RCX = 0x24BF60961283301C;
        RAX -= RCX;
        RDX = R11;
        RDX = ~RDX;
        RCX = imageBase + 0xF6EF;
        RAX += RCX;
        RAX += RDX;
        RCX = RAX;
        RCX >>= 0x18;
        RAX ^= RCX;
        RCX = RAX;
        RCX >>= 0x30;
        RAX ^= RCX;
        RCX = 0x1DDF7C86F7AD547B;
        RAX *= RCX;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RCX ^= R10;
        RCX = ~RCX;
        RAX *= readMemory<uint64_t>(RCX + 0xF);
        RAX += R11;
        RCX = 0x10707F8A2D79C849;
        RAX *= RCX;
        return RAX;
    }
    }
}

extern "C" auto decrypt_bone_base(uint64_t imageBase, uint64_t peb) -> uint64_t
{
    uint64_t RAX = imageBase, RBX = imageBase, RCX = imageBase, RDX = imageBase, R8 = imageBase, RDI = imageBase, RSI = imageBase, R9 = imageBase, R10 = imageBase, R11 = imageBase, R12 = imageBase, R13 = imageBase, R14 = imageBase, R15 = imageBase, RBP = 0, RSP = 0;

    R8 = readMemory<uint64_t>(imageBase + 0x15E80818);
    if (R8 == 0) {
        return 0;
    }
    RBX = peb; // mov rbx,gs:[rax]
    // test r8,r8
    // je 00007FF738A55EDFh
    RAX = RBX;
    RAX >>= 0x19;
    RAX &= 0xF;
    // cmp rax,0Eh
    // ja 00007FF738A55A40h
    switch (RAX) {
    case 0: {
        R10 = readMemory<uint64_t>(imageBase + 0x7241200);
        RCX = imageBase + 0x45C11802;
        RAX = R8;
        RAX >>= 0x13;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x26;
        R8 ^= RAX;
        RAX = RCX;
        RAX = ~RAX;
        RAX ^= RBX;
        R8 -= RAX;
        RAX = 0x19387A004D512E62;
        R8 += RAX;
        RAX = 0xB8209A2A7A9B286D;
        R8 ^= RAX;
        RAX = imageBase + 0x8634;
        RAX = ~RAX;
        RAX *= RBX;
        R8 += RAX;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R10;
        RAX = _byteswap_uint64(RAX);
        R8 *= readMemory<uint64_t>(RAX + 0xB);
        R8 -= RBX;
        RAX = 0xE50EF9B777D15CA7;
        R8 *= RAX;
        return R8;
    }
    case 1: {
        R10 = readMemory<uint64_t>(imageBase + 0x7241200);
        RAX = R8;
        RAX >>= 0x13;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x26;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x1D;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x3A;
        R8 ^= RAX;
        R11 = imageBase;
        RCX = 0x0;
        RAX = RBX;
        RAX -= R11;
        RCX = _rotl64(RCX, 0x10);
        RAX += R8;
        RCX ^= R10;
        R8 = 0x333A206C2FA88D43;
        RAX *= R8;
        R8 = 0x44D314174BC371E;
        RAX -= R8;
        RCX = _byteswap_uint64(RCX);
        R8 = readMemory<uint64_t>(RCX + 0xB);
        R8 *= RAX;
        R8 ^= RBX;
        RAX = 0x45E1C2B929ED644A;
        R8 ^= RAX;
        return R8;
    }
    case 2: {
        // pushfq
        // push rbx
        // pop rbx
        // pop rbx
        R11 = readMemory<uint64_t>(imageBase + 0x7241200);
        RAX = imageBase + 0xC5E3;
        RAX = ~RAX;
        RAX += R8;
        R8 = RBX + 1;
        R8 += RAX;
        RAX = 0xF70AE6A27FA8C809;
        R8 *= RAX;
        RAX = R8;
        RAX >>= 0x1D;
        R8 ^= RAX;
        RCX = R8;
        RCX >>= 0x3A;
        RCX ^= R8;
        RAX = imageBase + 0x425A;
        RAX = ~RAX;
        R8 = RBX * 0xFE;
        R8 += RCX;
        R8 += RAX;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R11;
        RAX = _byteswap_uint64(RAX);
        R8 *= readMemory<uint64_t>(RAX + 0xB);
        RAX = 0x7A2A4B1812372104;
        R8 ^= RAX;
        return R8;
    }
    case 3: {
        R10 = readMemory<uint64_t>(imageBase + 0x7241200);
        RAX = imageBase;
        R8 += RAX;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R10;
        RAX = _byteswap_uint64(RAX);
        R8 *= readMemory<uint64_t>(RAX + 0xB);
        RAX = R8;
        RAX >>= 0x25;
        R8 ^= RAX;
        RAX = 0x9C51504A591F0975;
        R8 *= RAX;
        R8 ^= RBX;
        RCX = RBX;
        RCX = ~RCX;
        RAX = imageBase + 0x1F51;
        RCX *= RAX;
        RAX = R8;
        R8 = 0x26D34094997FD893;
        RAX *= R8;
        R8 = RCX;
        R8 ^= RAX;
        RAX = 0xD120BA3204EFDC8B;
        R8 *= RAX;
        return R8;
    }
    case 4: {
        uint64_t RSP_0x68 = imageBase;
        RDX = 0xB04AC872F1D9387B;
        // pushfq
        // push rdx
        // pop rdx
        // pop rdx
        // popfq
        R10 = readMemory<uint64_t>(imageBase + 0x7241200);
        RAX = imageBase + 0x6B33;
        RSP_0x68 = RAX; // mov [rsp+68h],rax
        RAX = RBX;
        RAX *= RSP_0x68; // imul rax,[rsp+68h]
        R8 += RAX;
        RAX = R8;
        RAX >>= 0x19;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x32;
        R8 ^= RAX;
        RAX = 0x552F8576FCCAF54A;
        R8 += RAX;
        RAX = 0x9E1F4B7C76F658C1;
        R8 *= RAX;
        RAX = imageBase;
        R8 -= RAX;
        RCX = 0x0;
        RCX = _rotl64(RCX, 0x10);
        RAX = RBX - 0x74406A48;
        RAX += R8;
        RCX ^= R10;
        RCX = _byteswap_uint64(RCX);
        R8 = readMemory<uint64_t>(RCX + 0xB);
        R8 *= RAX;
        RAX = R8;
        RAX >>= 0xE;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x1C;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x38;
        R8 ^= RAX;
        RAX = 0x255BA745A3BBE1B8;
        R8 ^= RAX;
        return R8;
    }
    case 5: {
        // pushfq
        // push rbx
        // pop rbx
        // pop rbx
        R10 = readMemory<uint64_t>(imageBase + 0x7241200);
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R10;
        RAX = _byteswap_uint64(RAX);
        R8 *= readMemory<uint64_t>(RAX + 0xB);
        RCX = RBX;
        RAX = imageBase + 0x45310102;
        RCX = ~RCX;
        RAX = ~RAX;
        RCX *= RAX;
        RAX = 0xC6C55A825CADEED7;
        RAX += RCX;
        R8 += RAX;
        RCX = imageBase + 0x1291;
        RAX = R8;
        RAX >>= 0x6;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0xC;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x18;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x30;
        R8 ^= RAX;
        RAX = imageBase;
        R8 ^= RAX;
        RAX = RBX;
        RAX *= RCX;
        R8 -= RAX;
        RAX = 0x1B6636409E713787;
        R8 *= RAX;
        R8 -= RBX;
        return R8;
    }
    case 6: {
        R9 = readMemory<uint64_t>(imageBase + 0x7241200);
        R11 = imageBase;
        RAX = RBX;
        RAX -= R11;
        R8 += RAX;
        RAX = 0x8CDB2318980AC685;
        R8 *= RAX;
        RAX = 0x41031C78082CE740;
        R8 -= RAX;
        RAX = imageBase;
        R8 ^= RAX;
        R8 += RAX;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R9;
        RAX = _byteswap_uint64(RAX);
        R8 *= readMemory<uint64_t>(RAX + 0xB);
        RAX = R8;
        RAX >>= 0x12;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x24;
        R8 ^= RAX;
        RAX = 0x5EAAA2269779B919;
        R8 ^= RAX;
        return R8;
    }
    case 7: {
        R10 = readMemory<uint64_t>(imageBase + 0x7241200);
        R8 ^= RBX;
        RCX = RBX;
        RCX = ~RCX;
        RAX = imageBase + 0x3B90ACD8;
        R8 += RCX;
        R8 += RAX;
        RAX = imageBase + 0x6B0F;
        R8 ^= RCX;
        R8 ^= RAX;
        RAX = 0x1C9AF452FA7F2E7B;
        R8 -= RAX;
        RAX = 0xD04CD33C884BD03;
        R8 *= RAX;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R10;
        RAX = _byteswap_uint64(RAX);
        RAX = readMemory<uint64_t>(RAX + 0xB);
        R8 *= RAX;
        RAX = 0x1C84CC3C93673538;
        R8 += RAX;
        RAX = R8;
        RAX >>= 0x9;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x12;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x24;
        R8 ^= RAX;
        return R8;
    }
    case 8: {
        R10 = readMemory<uint64_t>(imageBase + 0x7241200);
        RAX = R8;
        RAX >>= 0xC;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x18;
        R8 ^= RAX;
        RCX = R8;
        RCX >>= 0x30;
        RCX ^= R8;
        RAX = RBX;
        RAX = ~RAX;
        R8 = imageBase + 0x38DA;
        R8 ^= RAX;
        R8 += RCX;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R10;
        RAX = _byteswap_uint64(RAX);
        R8 *= readMemory<uint64_t>(RAX + 0xB);
        RAX = R8;
        R8 = 0xCDAA271DC9575CA;
        RAX ^= R8;
        R8 = imageBase + 0x7F0349ED;
        RAX += RBX;
        R8 = ~R8;
        R8 += RAX;
        RAX = imageBase + 0x1;
        R8 += RAX;
        RAX = 0x2699FB3C2770BBC5;
        R8 *= RAX;
        return R8;
    }
    case 9: {
        uint64_t RSP_0x78 = imageBase;
        RDX = 0x5DDE5A412188A4ED;
        // push rdx
        // pushfq
        // pop rdx
        // popfq
        // pop rdx
        RAX = 0x424A972B1A4023CB;
        RSP_0x78 = RAX; // mov [rsp+78h],rax
        R10 = readMemory<uint64_t>(imageBase + 0x7241200);
        RAX = R8;
        RAX >>= 0xE;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x1C;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x38;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x25;
        RAX ^= RBX;
        R8 ^= RAX;
        R8 -= RBX;
        RAX = 0x22D436DDB308E5F7;
        R8 *= RAX;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R10;
        RAX = _byteswap_uint64(RAX);
        RAX = readMemory<uint64_t>(RAX + 0xB);
        RAX *= RSP_0x78; // imul rax,[rsp+78h]
        R8 *= RAX;
        RAX = 0x27DADDC01D88DEDB;
        R8 *= RAX;
        return R8;
    }
    case 10: {
        R10 = readMemory<uint64_t>(imageBase + 0x7241200);
        RAX = imageBase;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x15;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x2A;
        R8 ^= RAX;
        RAX = imageBase + 0x731118CF;
        RAX -= RBX;
        R8 ^= RAX;
        R8 += RBX;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R10;
        RAX = _byteswap_uint64(RAX);
        R8 *= readMemory<uint64_t>(RAX + 0xB);
        RAX = 0xA815FB9ABE225B21;
        R8 ^= RAX;
        RAX = 0xAC0E0B43C779001D;
        R8 *= RAX;
        RAX = 0x4A7E9AC32BFE240C;
        R8 -= RAX;
        return R8;
    }
    case 11: {
        R10 = readMemory<uint64_t>(imageBase + 0x7241200);
        RAX = 0x7ABE2D954ED9DE54;
        R8 -= RAX;
        RAX = R8;
        RAX >>= 0x11;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x22;
        R8 ^= RAX;
        R8 -= RBX;
        RAX = imageBase;
        R8 -= RAX;
        R8 -= 0x1EA83FDA;
        R8 ^= RBX;
        RAX = 0x44422BA6808B3719;
        R8 *= RAX;
        RAX = R8;
        RAX >>= 0x28;
        R8 ^= RAX;
        RCX = 0x0;
        RAX = R8;
        RCX = _rotl64(RCX, 0x10);
        R8 = 0x79189270A0D14ACE;
        RAX ^= R8;
        RCX ^= R10;
        RCX = _byteswap_uint64(RCX);
        R8 = readMemory<uint64_t>(RCX + 0xB);
        R8 *= RAX;
        return R8;
    }
    case 12: {
        uint64_t RBP_NEG_0x78 = imageBase;
        R10 = readMemory<uint64_t>(imageBase + 0x7241200);
        RAX = imageBase + 0xA36;
        RBP_NEG_0x78 = RAX; // mov [rbp-78h],rax
        RAX = 0x2BBB54D0C977269;
        R8 *= RAX;
        RAX = R8;
        RAX >>= 0x18;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x30;
        R8 ^= RAX;
        RAX = RBX;
        RAX = ~RAX;
        RAX *= RBP_NEG_0x78; // imul rax,[rbp-78h]
        R8 += RAX;
        RAX = imageBase;
        R8 -= RAX;
        RAX = R8;
        RAX >>= 0x1B;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x36;
        R8 ^= RAX;
        R8 += RBX;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R10;
        RAX = _byteswap_uint64(RAX);
        R8 *= readMemory<uint64_t>(RAX + 0xB);
        R8 ^= RBX;
        return R8;
    }
    case 13: {
        R10 = readMemory<uint64_t>(imageBase + 0x7241200);
        R8 ^= RBX;
        RAX = imageBase;
        R8 -= RAX;
        RAX = 0x2E9E4348672F2A5F;
        R8 -= RAX;
        RAX = R8;
        RAX >>= 0x12;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x24;
        R8 ^= RAX;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R10;
        RAX = _byteswap_uint64(RAX);
        R8 *= readMemory<uint64_t>(RAX + 0xB);
        R8 += RBX;
        RAX = 0x1DBA57F6446FAD6F;
        R8 *= RAX;
        return R8;
    }
    case 14: {
        R9 = readMemory<uint64_t>(imageBase + 0x7241200);
        RAX = R8;
        RAX >>= 0x3;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x6;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0xC;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x18;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x30;
        R8 ^= RAX;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R9;
        RAX = _byteswap_uint64(RAX);
        R8 *= readMemory<uint64_t>(RAX + 0xB);
        RAX = imageBase;
        R8 += RAX;
        RAX = imageBase;
        R8 -= RAX;
        RAX = 0x360AC19AB03940EE;
        R8 += RAX;
        RAX = R8;
        RAX >>= 0x18;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x30;
        R8 ^= RAX;
        RAX = 0xD5ECC52965B94A29;
        R8 *= RAX;
        return R8;
    }
    case 15: {
        // pop rbx
        // popfq
        // pop rbx
        R10 = readMemory<uint64_t>(imageBase + 0x7241200);
        RAX = imageBase + 0x1B7A;
        RAX = ~RAX;
        RAX += RBX;
        R8 += RAX;
        RAX = R8;
        RAX >>= 0x24;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x17;
        R8 ^= RAX;
        RAX = R8;
        RAX >>= 0x2E;
        R8 ^= RAX;
        RAX = 0x0;
        RAX = _rotl64(RAX, 0x10);
        RAX ^= R10;
        RAX = _byteswap_uint64(RAX);
        R8 *= readMemory<uint64_t>(RAX + 0xB);
        RAX = R8;
        RAX >>= 0x28;
        R8 ^= RAX;
        RAX = 0x5A63C973DCF4F0E1;
        R8 += RAX;
        RAX = 0xA249C80656C79981;
        R8 ^= RAX;
        RAX = 0x1441D51A97A82EDF;
        R8 *= RAX;
        return R8;
    }
    }
}

extern "C" auto get_bone_index(uint32_t index, uint64_t imageBase) -> uint64_t
{
    uint64_t RAX = imageBase, RBX = imageBase, RCX = imageBase, RDX = imageBase, R8 = imageBase, RDI = imageBase, RSI = imageBase, R9 = imageBase, R10 = imageBase, R11 = imageBase, R12 = imageBase, R13 = imageBase, R14 = imageBase, R15 = imageBase, RBP = 0, RSP = 0;

    RBX = index;
    RCX = RBX * 0x13C8;
    RAX = 0xAF77E6EDE874ED1F;
    R11 = imageBase;
    RAX = _umul128(RAX, RCX, &RDX);
    RAX = RCX;
    R10 = 0xB1462813BC4F7633;
    RAX -= RDX;
    RAX >>= 0x1;
    RAX += RDX;
    RAX >>= 0xD;
    RAX = RAX * 0x25F9;
    RCX -= RAX;
    RAX = 0x155C5EADBEC158D;
    R8 = RCX * 0x25F9;
    RAX = _umul128(RAX, R8, &RDX);
    RAX = R8;
    RAX -= RDX;
    RAX >>= 0x1;
    RAX += RDX;
    RAX >>= 0xD;
    RAX = RAX * 0x3FAB;
    R8 -= RAX;
    RAX = 0xC9A633FCD967300D;
    RAX = _umul128(RAX, R8, &RDX);
    RAX = 0x8618618618618619;
    RDX >>= 0xA;
    RCX = RDX * 0x514;
    RAX = _umul128(RAX, R8, &RDX);
    RAX = R8;
    RAX -= RDX;
    RAX >>= 0x1;
    RAX += RDX;
    RAX >>= 0x4;
    RCX += RAX;
    RAX = RCX * 0x2A;
    RCX = R8 * 0x2C;
    RCX -= RAX;
    RAX = readMemory<uint16_t>(RCX + R11 + 0x7250270);
    R8 = RAX * 0x13C8;
    RAX = R10;
    RAX = _umul128(RAX, R8, &RDX);
    RAX = R10;
    RDX >>= 0xC;
    RCX = RDX * 0x171B;
    R8 -= RCX;
    R9 = R8 * 0x1B8B;
    RAX = _umul128(RAX, R9, &RDX);
    RDX >>= 0xC;
    RAX = RDX * 0x171B;
    R9 -= RAX;
    RAX = 0x8AD8F2FBA9386823;
    RAX = _umul128(RAX, R9, &RDX);
    RAX = 0xA0A0A0A0A0A0A0A1;
    RDX >>= 0x6;
    RCX = RDX * 0x76;
    RAX = _umul128(RAX, R9, &RDX);
    RDX >>= 0x5;
    RCX += RDX;
    RAX = RCX * 0x66;
    RCX = R9 * 0x68;
    RCX -= RAX;
    R15 = readMemory<uint16_t>(RCX + R11 + 0x725D7C0);
    return R15;
}

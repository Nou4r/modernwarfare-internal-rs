#include <cstdint>
#include "Memory.h"

extern "C" auto decrypt_client_info(uint64_t imageBase, uint64_t peb) -> uint64_t
{
    uint64_t RAX = imageBase, RBX = imageBase, RCX = imageBase, RDX = imageBase, R8 = imageBase, RDI = imageBase, RSI = imageBase, R9 = imageBase, R10 = imageBase, R11 = imageBase, R12 = imageBase, R13 = imageBase, R14 = imageBase, R15 = imageBase;

    RBX = readMemory<uint64_t>(imageBase + 0x17219218);
    if (RBX == 0) {
        return 0;
    }
    RCX = peb; // mov rcx,gs:[rax]
    RCX = ~RCX;
    RDX = 0x6D70CEFD9593A4F9;
    RAX = 0x0;
    RAX = _rotl64(RAX, 0x10);
    RAX ^= readMemory<uint64_t>(imageBase + 0x660310D);
    RAX = _byteswap_uint64(RAX);
    RBX *= readMemory<uint64_t>(RAX + 0x17);
    RAX = RBX;
    RAX >>= 0x24;
    RBX ^= RAX;
    RAX = 0x3938DE18C6D75C93;
    RBX *= RDX;
    RBX += RAX;
    RBX ^= RCX;
    RBX ^= R8;
    return RBX;
}

extern "C" auto decrypt_client_base(uint64_t clientInfo, uint64_t imageBase, uint64_t peb) -> uint64_t
{
    uint64_t RAX = imageBase, RBX = imageBase, RCX = imageBase, RDX = imageBase, R8 = imageBase, RDI = imageBase, RSI = imageBase, R9 = imageBase, R10 = imageBase, R11 = imageBase, R12 = imageBase, R13 = imageBase, R14 = imageBase, R15 = imageBase, RBP = 0, RSP = 0;

    RAX = readMemory<uint64_t>(clientInfo + 0x9DBF8);
    RBX = peb; // mov rbx,gs:[rcx]
    // test rax,rax
    // je 00007FF686F63D55h
    RCX = RBX;
    RCX >>= 0xF;
    RCX &= 0xF;
    // cmp rcx,0Eh
    // ja 00007FF686F638FBh
    switch (RCX) {
        case 0: {
            R14 = imageBase + 0x3C431634;
            R10 = readMemory<uint64_t>(imageBase + 0x6603146);
            RCX = 0x2C52EE7E5CA1CE96;
            RAX -= RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x9);
            RCX = RBX;
            RCX ^= R14;
            RAX -= RCX;
            RAX += RBX;
            RCX = RAX;
            RCX >>= 0x14;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x28;
            RAX ^= RCX;
            RAX += RBX;
            RCX = 0x9C83A6ED81709013;
            RAX *= RCX;
            RCX = 0x709DC8ADED0BA319;
            RAX += RCX;
            return RAX;
        }
        case 1: {
            uint64_t RBP_NEG_0x58 = imageBase;
            RCX = 0x3CE1F452114BE5D;
            RBP_NEG_0x58 = RCX; // mov [rbp-58h],rcx
            R9 = readMemory<uint64_t>(imageBase + 0x6603146);
            RCX = 0x1A69AD46E3A25C75;
            RAX -= RCX;
            RCX = RAX;
            RCX >>= 0xC;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x18;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x30;
            RCX ^= RBX;
            RAX ^= RCX;
            RCX = 0x6ECEBD9C03D02936;
            RAX -= RCX;
            RCX = imageBase;
            RAX += RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RCX = readMemory<uint64_t>(RCX + 0x9);
            RCX *= RBP_NEG_0x58; // imul rcx,[rbp-58h]
            RAX *= RCX;
            RAX += RBX;
            return RAX;
        }
        case 2: {
            R11 = imageBase + 0xAE07;
            RDX = readMemory<uint64_t>(imageBase + 0x6603146);
            RAX += RBX;
            RCX = RAX;
            RCX >>= 0x13;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x26;
            RAX ^= RCX;
            RCX = 0x337FEE03C131D861;
            RAX ^= RCX;
            RCX = 0xBCA9BFAF51DA6757;
            RAX *= RCX;
            RCX = 0x5434E82D28CC28F9;
            RAX -= RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= RDX;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x9);
            RCX = imageBase;
            RAX -= RCX;
            RAX += 0xFFFFFFFFE2253F2C;
            RAX += RBX;
            RCX = R11;
            RCX = ~RCX;
            RCX += RBX;
            RAX ^= RCX;
            return RAX;
        }
        case 3: {
            uint64_t RSP_0x68 = imageBase;
            R10 = readMemory<uint64_t>(imageBase + 0x6603146);
            RCX = 0x8035B07E6320667D;
            R15 = imageBase + 0x576A2168;
            RSP_0x68 = RCX; // mov [rsp+68h],rcx
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = ~RCX;
            RCX = readMemory<uint64_t>(RCX + 0x9);
            RCX *= RSP_0x68; // imul rcx,[rsp+68h]
            RAX *= RCX;
            RCX = RBX;
            RCX *= R15;
            RCX ^= RBX;
            RAX ^= RCX;
            RCX = imageBase;
            RAX -= RBX;
            RAX -= RCX;
            RAX -= 0x31E8;
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
            RCX >>= 0x1E;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x3C;
            RAX ^= RCX;
            return RAX;
        }
        case 4: {
            R9 = readMemory<uint64_t>(imageBase + 0x6603146);
            RCX = imageBase;
            RCX += 0x281F;
            RCX += RBX;
            RAX ^= RCX;
            RCX = 0xDF286BBF83F616D1;
            RAX *= RCX;
            RCX = RAX;
            RCX >>= 0x8;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x10;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x20;
            RAX ^= RCX;
            RCX = imageBase;
            RAX ^= RCX;
            RAX -= RCX;
            RAX += 0xFFFFFFFFE4385B97;
            RAX += RBX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x9);
            RCX = 0x4A4FFCF706C23293;
            RAX -= RCX;
            RCX = RAX;
            RCX >>= 0x22;
            RAX ^= RCX;
            return RAX;
        }
        case 5: {
            R10 = readMemory<uint64_t>(imageBase + 0x6603146);
            RCX = imageBase + 0x9128;
            RCX -= RBX;
            RAX += RCX;
            RCX = RAX;
            RCX >>= 0x26;
            RDX = 0x0;
            RCX ^= RAX;
            RDX = _rotl64(RDX, 0x10);
            RCX -= RBX;
            RDX ^= R10;
            RDX = ~RDX;
            RAX = readMemory<uint64_t>(RDX + 0x9);
            RAX *= RCX;
            RCX = 0x347EE6669F93372E;
            RAX -= RCX;
            RCX = 0xCC4AC21D5E07EAFD;
            RAX *= RCX;
            RCX = imageBase;
            RAX -= RCX;
            RAX += 0xFFFFFFFFC0A98326;
            RAX += RBX;
            RCX = 0x25D8C69821A4B1C1;
            RAX *= RCX;
            return RAX;
        }
        case 6: {
            R10 = readMemory<uint64_t>(imageBase + 0x6603146);
            RCX = imageBase;
            RAX -= RCX;
            RAX += 0xFFFFFFFFFFFF0A85;
            RAX += RBX;
            RCX = 0xDD3029A8BCE8D4D;
            RAX *= RCX;
            RDX = 0x0;
            RDX = _rotl64(RDX, 0x10);
            RCX = 0xFCFBF307C71E86A5;
            RAX ^= RCX;
            RDX ^= R10;
            RCX = imageBase;
            RDX = ~RDX;
            RAX -= RCX;
            RCX = RBX - 0x0F901;
            RCX += RAX;
            RAX = imageBase + 0x48A8C848;
            RAX = ~RAX;
            RAX *= RBX;
            RCX ^= RAX;
            RAX = readMemory<uint64_t>(RDX + 0x9);
            RAX *= RCX;
            RCX = RAX;
            RCX >>= 0x24;
            RAX ^= RCX;
            RCX = 0x2F5690490931B637;
            RAX *= RCX;
            return RAX;
        }
        case 7: {
            uint64_t RSP_0x58 = imageBase;
            R14 = imageBase + 0x2491D7D9;
            RCX = imageBase + 0x5E98C991;
            RSP_0x58 = RCX; // mov [rsp+58h],rcx
            R9 = readMemory<uint64_t>(imageBase + 0x6603146);
            RCX = 0x635E4B2FC3D0A10D;
            RAX *= RCX;
            RCX = R14;
            RCX = ~RCX;
            RCX ^= RBX;
            RAX += RCX;
            RCX = 0x51256D5DC16562EC;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x6;
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
            RCX = RBX;
            RCX *= RSP_0x58; // imul rcx,[rsp+58h]
            RAX += RCX;
            RCX = imageBase;
            RAX -= RCX;
            RCX = RAX;
            RCX >>= 0xC;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x18;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x30;
            RAX ^= RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x9);
            return RAX;
        }
        case 8: {
            R10 = readMemory<uint64_t>(imageBase + 0x6603146);
            RDX = 0x0;
            RDX = _rotl64(RDX, 0x10);
            RDX ^= R10;
            RCX = 0xF9180DCDF5F228B4;
            RCX += RAX;
            RDX = ~RDX;
            RAX = readMemory<uint64_t>(RDX + 0x9);
            RAX *= RCX;
            RAX += RBX;
            RCX = RAX;
            RCX >>= 0x5;
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
            RCX = imageBase;
            RAX ^= RCX;
            RCX = 0xEE1131A827DCAA68;
            RAX -= RBX;
            RAX ^= RCX;
            RCX = 0xB6B2FC7C21D1D489;
            RAX *= RCX;
            return RAX;
        }
        case 9: {
            R15 = imageBase + 0x74E0B964;
            R10 = readMemory<uint64_t>(imageBase + 0x6603146);
            RAX += RBX;
            RCX = imageBase + 0x2E0E6E37;
            RAX += RCX;
            RCX = 0xFA547910F03B3987;
            RAX *= RCX;
            RCX = imageBase + 0x91DC;
            RCX = ~RCX;
            RCX *= RBX;
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
            RCX = RAX;
            RCX >>= 0xB;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x16;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x2C;
            RAX ^= RCX;
            RCX = imageBase;
            RAX ^= RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x9);
            RCX = R15;
            RCX = ~RCX;
            RCX ^= RBX;
            RAX += RCX;
            return RAX;
        }
        case 10: {
            R10 = readMemory<uint64_t>(imageBase + 0x6603146);
            RCX = RAX;
            RCX >>= 0x1B;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x36;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x22;
            RCX ^= RBX;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x15;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x2A;
            RAX ^= RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x9);
            RCX = 0x5D93FBAC7F625877;
            RAX *= RCX;
            RCX = 0x52B757443CDBD28B;
            RAX += RCX;
            RCX = 0x5E17A54EAA80B6A5;
            RAX *= RCX;
            return RAX;
        }
        case 11: {
            R10 = readMemory<uint64_t>(imageBase + 0x6603146);
            RCX = 0x4041D2698092818B;
            RAX *= RCX;
            RCX = 0x6E7B1B11ABDFF2FA;
            RAX ^= RCX;
            RDX = 0x0;
            RDX = _rotl64(RDX, 0x10);
            RCX = RBX + RAX;
            RDX ^= R10;
            RDX = ~RDX;
            RAX = readMemory<uint64_t>(RDX + 0x9);
            RAX *= RCX;
            RCX = RAX;
            RCX >>= 0x14;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x28;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x6;
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
            RCX = 0x40077D00487E24C2;
            RAX += RCX;
            RAX -= RBX;
            return RAX;
        }
        case 12: {
            R9 = readMemory<uint64_t>(imageBase + 0x6603146);
            R11 = imageBase + 0x1263;
            RCX = 0xA8101149FD4CA7C3;
            RAX *= RCX;
            R15 = 0x4EC0B4781CB32BBF;
            RCX = RBX;
            RCX = ~RCX;
            RCX *= R11;
            RCX += R15;
            RAX += RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x9);
            RCX = RAX;
            RCX >>= 0x1E;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x3C;
            RAX ^= RCX;
            RAX ^= RBX;
            RCX = 0x4E80F1A0C98C468;
            RAX += RCX;
            RAX -= RBX;
            return RAX;
        }
        case 13: {
            R10 = readMemory<uint64_t>(imageBase + 0x6603146);
            R11 = imageBase + 0x6267F8D9;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = ~RCX;
            RCX = readMemory<uint64_t>(RCX + 0x9);
            RAX *= RCX;
            RCX = 0x87FBBF81F585A7F5;
            RAX *= RCX;
            RCX = imageBase;
            RAX += RCX;
            RCX = RBX + RAX;
            RAX = 0xE2DF381128AD7D;
            RCX ^= RAX;
            RAX = RCX;
            RAX >>= 0x15;
            RCX ^= RAX;
            RAX = RCX;
            RAX >>= 0x2A;
            RAX ^= RCX;
            RCX = R11;
            RCX = ~RCX;
            RAX -= RBX;
            RAX += RCX;
            RCX = imageBase;
            RAX -= RCX;
            return RAX;
        }
        case 14: {
            R11 = readMemory<uint64_t>(imageBase + 0x6603146);
            RDX = imageBase + 0xB8FD;
            RCX = RBX;
            RCX *= RDX;
            R8 = 0x0;
            R8 = _rotl64(R8, 0x10);
            R8 ^= R11;
            RDX = RAX + RCX * 2;
            R8 = ~R8;
            RAX = imageBase + 0x3DA2C48A;
            RDX += RAX;
            RAX = readMemory<uint64_t>(R8 + 0x9);
            RAX *= RDX;
            RCX = RAX;
            RCX >>= 0x15;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x2A;
            RAX ^= RCX;
            RCX = 0x63F739E7ACE8DEFA;
            RAX -= RCX;
            RCX = 0xECA41A7D230C65B;
            RAX *= RCX;
            return RAX;
        }
        case 15: {
            R15 = imageBase + 0x4A2;
            R10 = readMemory<uint64_t>(imageBase + 0x6603146);
            RCX = imageBase;
            RAX -= RCX;
            RCX = RAX;
            RCX >>= 0x15;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x2A;
            RDX = 0x0;
            RCX ^= RAX;
            RDX = _rotl64(RDX, 0x10);
            RDX ^= R10;
            RDX = ~RDX;
            RAX = readMemory<uint64_t>(RDX + 0x9);
            RAX *= RCX;
            RAX += RBX;
            RCX = 0xC3EBCF9689C9BEB;
            RAX *= RCX;
            RCX = 0x7631FAD984D70CD9;
            RAX *= RCX;
            RCX = 0x2D351ADE4F41F93F;
            RAX += RCX;
            RAX ^= RBX;
            RAX ^= R15;
            return RAX;
        }
    }
}

extern "C" auto decrypt_bone_base(uint64_t imageBase, uint64_t peb) -> uint64_t
{
    uint64_t RAX = imageBase, RBX = imageBase, RCX = imageBase, RDX = imageBase, R8 = imageBase, RDI = imageBase, RSI = imageBase, R9 = imageBase, R10 = imageBase, R11 = imageBase, R12 = imageBase, R13 = imageBase, R14 = imageBase, R15 = imageBase, RBP = 0, RSP = 0;

    R8 = readMemory<uint64_t>(imageBase + 0x155A7FE8);
    if (R8 == 0) {
        return 0;
    }
    RBX = peb; // mov rbx,gs:[rax]
    // test r8,r8
    // je 00007FF6870B3AF5h
    RAX = RBX;
    RAX = _rotl64(RAX, 0x21);
    RAX &= 0xF;
    // cmp rax,0Eh
    // ja 00007FF6870B3628h
    switch (RAX) {
        case 0: {
            uint64_t RBP_NEG_0x30 = imageBase;
            R9 = readMemory<uint64_t>(imageBase + 0x660321F);
            RAX = R8;
            RAX >>= 0x1C;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x38;
            R8 ^= RAX;
            RAX = 0x8E1AF47C49C05F7D;
            R8 ^= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R9;
            RAX = _byteswap_uint64(RAX);
            R8 *= readMemory<uint64_t>(RAX + 0xD);
            RAX = imageBase;
            R8 ^= RAX;
            RAX = RBX;
            RAX -= RBP_NEG_0x30; // sub rax,[rbp-30h]
            R8 += RAX;
            RAX = 0x3BC383EE0989D5FB;
            R8 *= RAX;
            RAX = 0x3F03F1C19A86FE5F;
            R8 += RAX;
            RAX = R8;
            RAX >>= 0x17;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x2E;
            R8 ^= RAX;
            RAX = 0x317CC2C5DB16CED9;
            R8 -= RAX;
            return R8;
        }
        case 1: {
            R10 = readMemory<uint64_t>(imageBase + 0x660321F);
            R8 += RBX;
            RAX = 0xD52E0A124183921D;
            R8 += RAX;
            RAX = imageBase;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x14;
            R8 ^= RAX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RAX = R8;
            RAX >>= 0x28;
            RAX ^= R8;
            RCX = _byteswap_uint64(RCX);
            R8 = readMemory<uint64_t>(RCX + 0xD);
            R8 *= RAX;
            RAX = imageBase;
            R8 -= RAX;
            RAX = 0x70ACDD8EF6846122;
            R8 -= RAX;
            RAX = 0xDA0E2D2CE4B2F84F;
            R8 *= RAX;
            return R8;
        }
        case 2: {
            uint64_t RBP_NEG_0x80 = imageBase;
            // push rbx
            // pushfq
            // pop rbx
            // popfq
            // pop rbx
            R11 = readMemory<uint64_t>(imageBase + 0x660321F);
            RAX = imageBase + 0x1306;
            RBP_NEG_0x80 = RAX; // mov [rbp-80h],rax
            RAX = R8;
            RAX >>= 0xE;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x1C;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x38;
            R8 ^= RAX;
            RAX = imageBase;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0xC;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x18;
            R8 ^= RAX;
            RAX = R8;
            RCX = 0x0;
            RAX >>= 0x30;
            RAX ^= R8;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R11;
            R8 = 0x2E90538619E40F20;
            RAX ^= R8;
            RCX = _byteswap_uint64(RCX);
            R8 = readMemory<uint64_t>(RCX + 0xD);
            R8 *= RAX;
            RAX = 0xB80F0EAB4EE77825;
            R8 *= RAX;
            RAX = RBX;
            RAX = ~RAX;
            RAX *= RBP_NEG_0x80; // imul rax,[rbp-80h]
            R8 += RAX;
            RAX = 0xF3935694AC4F54B;
            R8 *= RAX;
            return R8;
        }
        case 3: {
            uint64_t RSP_0x68 = imageBase;
            // push rax
            // pushfq
            // pop rax
            // popfq
            // pop rax
            RAX = imageBase + 0x4906101B;
            RSP_0x68 = RAX; // mov [rsp+68h],rax
            R10 = readMemory<uint64_t>(imageBase + 0x660321F);
            RAX = 0x114539BCB7C07837;
            R8 *= RAX;
            R8 ^= RBX;
            RCX = 0x0;
            RAX = R8;
            RCX = _rotl64(RCX, 0x10);
            RAX >>= 0x17;
            RCX ^= R10;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x2E;
            RAX ^= R8;
            RCX = _byteswap_uint64(RCX);
            R8 = readMemory<uint64_t>(RCX + 0xD);
            RCX = RBX;
            R8 *= RAX;
            RAX = 0x2F473A03275248CB;
            R8 += RAX;
            RCX = ~RCX;
            RAX = imageBase + 0x74007CC4;
            RAX = ~RAX;
            RCX += RAX;
            R8 ^= RCX;
            RAX = RBX;
            RAX ^= RSP_0x68; // xor rax,[rsp+68h]
            R8 += RAX;
            RCX = RBX;
            RCX = ~RCX;
            RAX = imageBase + 0xF757;
            RAX = ~RAX;
            R8 += RAX;
            R8 += RCX;
            return R8;
        }
        case 4: {
            uint64_t RBP_NEG_0x58 = imageBase;
            uint64_t RBP_NEG_0x28 = imageBase;
            RAX = imageBase + 0x6AE6F229;
            RBP_NEG_0x58 = RAX; // mov [rbp-58h],rax
            RAX = imageBase + 0xAA83;
            RBP_NEG_0x28 = RAX; // mov [rbp-28h],rax
            R10 = readMemory<uint64_t>(imageBase + 0x660321F);
            RAX = imageBase;
            RAX += 0x45ED6AC5;
            RCX = 0x0;
            RAX += RBX;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = _byteswap_uint64(RCX);
            RCX = readMemory<uint64_t>(RCX + 0xD);
            R8 *= RCX;
            R8 ^= RAX;
            RAX = RBX;
            RAX *= RBP_NEG_0x28; // imul rax,[rbp-28h]
            R8 ^= RAX;
            RAX = 0x2E009C49221FA9E4;
            R8 -= RAX;
            RAX = R8;
            RAX >>= 0xE;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x1C;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x38;
            R8 ^= RAX;
            RAX = 0x568A25CF438D6543;
            R8 *= RAX;
            RAX = RBX;
            RAX = ~RAX;
            RAX *= RBP_NEG_0x58; // imul rax,[rbp-58h]
            R8 ^= RAX;
            RAX = 0x5B0F3BC1A11076E3;
            R8 += RAX;
            return R8;
        }
        case 5: {
            R10 = readMemory<uint64_t>(imageBase + 0x660321F);
            RAX = R8;
            RAX >>= 0xA;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x14;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x28;
            R8 ^= RAX;
            R8 ^= RBX;
            RAX = 0x64E7E586730204B1;
            R8 *= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = _byteswap_uint64(RAX);
            R8 *= readMemory<uint64_t>(RAX + 0xD);
            RAX = R8;
            RAX >>= 0x1A;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x34;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x1C;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x38;
            R8 ^= RAX;
            RAX = 0x18D0928B2B48050C;
            R8 -= RAX;
            RAX = 0x7BECCED455EDAF2E;
            R8 += RAX;
            return R8;
        }
        case 6: {
            R11 = readMemory<uint64_t>(imageBase + 0x660321F);
            RAX = imageBase;
            RAX += 0x3A9D;
            RAX += RBX;
            R8 += RAX;
            RAX = R8;
            RAX >>= 0x1D;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x3A;
            R8 ^= RAX;
            RDX = 0x0;
            RCX = 0xF090D80A1E8721B2;
            RDX = _rotl64(RDX, 0x10);
            RCX += RBX;
            RCX += R8;
            RDX ^= R11;
            RDX = _byteswap_uint64(RDX);
            R8 = readMemory<uint64_t>(RDX + 0xD);
            R8 *= RCX;
            RAX = 0x2EFCDE57AB128A7D;
            R8 ^= RAX;
            RAX = imageBase + 0x821A;
            RAX = ~RAX;
            R8 -= RBX;
            R8 += RAX;
            RAX = 0xEE7544C793F5CA07;
            R8 *= RAX;
            return R8;
        }
        case 7: {
            // push rbx
            // pushfq
            // pop rbx
            // popfq
            // pop rbx
            R10 = readMemory<uint64_t>(imageBase + 0x660321F);
            R8 -= RBX;
            RCX = RBX;
            RAX = imageBase;
            R8 -= RAX;
            RAX = 0xFB97E6D9FBFD5293;
            R8 *= RAX;
            RAX = imageBase + 0x187B1FAB;
            RCX ^= RAX;
            RAX = 0xA3FC595FB9D96B70;
            R8 += RAX;
            R8 += RCX;
            RAX = 0x109A1466C7A4FA6F;
            R8 *= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = _byteswap_uint64(RAX);
            R8 *= readMemory<uint64_t>(RAX + 0xD);
            RAX = imageBase;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x1B;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x36;
            R8 ^= RAX;
            RAX = 0x3217CE681F7709FB;
            R8 *= RAX;
            return R8;
        }
        case 8: {
            uint64_t RBP_NEG_0x68 = imageBase;
            uint64_t RSP_0x78 = imageBase;
            // pushfq
            // push rax
            // pop rax
            // pop rax
            // popfq
            RCX = imageBase + 0x367762EB;
            RSP_0x78 = RCX; // mov [rsp+78h],rcx
            RAX = 0x7EB164DEDEA9C54C;
            RBP_NEG_0x68 = RAX; // mov [rbp-68h],rax
            R10 = readMemory<uint64_t>(imageBase + 0x660321F);
            R8 += RBX;
            RAX = R8;
            RAX >>= 0x1D;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x3A;
            RAX ^= RBX;
            R8 ^= RAX;
            RAX = 0x40CFE210A1D62E4D;
            R8 ^= RAX;
            R8 ^= RBP_NEG_0x68; // xor r8,[rbp-68h]
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RAX = RBX;
            RAX ^= RSP_0x78; // xor rax,[rsp+78h]
            RCX ^= R10;
            RCX = _byteswap_uint64(RCX);
            RAX += R8;
            R8 = readMemory<uint64_t>(RCX + 0xD);
            R8 *= RAX;
            RAX = 0x97EEA7211DDDB183;
            R8 *= RAX;
            return R8;
        }
        case 9: {
            uint64_t RBP_NEG_0x38 = imageBase;
            RAX = 0x7EA33D33E320DCD9;
            RBP_NEG_0x38 = RAX; // mov [rbp-38h],rax
            R10 = readMemory<uint64_t>(imageBase + 0x660321F);
            RAX = imageBase;
            R8 ^= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = _byteswap_uint64(RAX);
            RAX = readMemory<uint64_t>(RAX + 0xD);
            RAX *= RBP_NEG_0x38; // imul rax,[rbp-38h]
            R8 *= RAX;
            RAX = R8;
            RAX >>= 0x15;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x2A;
            R8 ^= RAX;
            RAX = imageBase + 0x9C27;
            RAX = ~RAX;
            RAX += RBX;
            R8 ^= RAX;
            RAX = 0x39E3C04BACA3B762;
            R8 ^= RAX;
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
            RAX = imageBase + 0x33D0D3D1;
            RAX = ~RAX;
            RAX *= RBX;
            R8 ^= RAX;
            return R8;
        }
        case 10: {
            R10 = readMemory<uint64_t>(imageBase + 0x660321F);
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = _byteswap_uint64(RAX);
            R8 *= readMemory<uint64_t>(RAX + 0xD);
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
            RAX >>= 0x10;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x20;
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
            RAX = R8;
            RAX >>= 0xE;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x1C;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x38;
            R8 ^= RAX;
            RAX = 0xF7BB1E98D088AD8B;
            R8 *= RAX;
            RAX = 0xC976B79B9B311D73;
            R8 ^= RAX;
            RAX = 0x296FF20A020B145;
            R8 -= RAX;
            return R8;
        }
        case 11: {
            uint64_t RBP_NEG_0x60 = imageBase;
            RAX = 0xE2B7FA23133CBF79;
            RBP_NEG_0x60 = RAX; // mov [rbp-60h],rax
            R10 = readMemory<uint64_t>(imageBase + 0x660321F);
            RCX = RBX;
            RCX = ~RCX;
            RAX = imageBase + 0xA98A;
            RAX = ~RAX;
            R8 += RAX;
            R8 += RCX;
            RCX = imageBase + 0xBA46;
            RAX = RBX;
            RAX = ~RAX;
            RAX *= RCX;
            R8 ^= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = _byteswap_uint64(RAX);
            RAX = readMemory<uint64_t>(RAX + 0xD);
            RAX *= RBP_NEG_0x60; // imul rax,[rbp-60h]
            R8 *= RAX;
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
            RAX = 0x8A5E388820A978A;
            R8 += RAX;
            RAX = R8;
            RAX >>= 0x21;
            R8 ^= RAX;
            return R8;
        }
        case 12: {
            uint64_t RBP_NEG_0x68 = imageBase;
            R10 = readMemory<uint64_t>(imageBase + 0x660321F);
            RAX = imageBase + 0x7B03;
            RBP_NEG_0x68 = RAX; // mov [rbp-68h],rax
            R8 ^= RBX;
            RAX = imageBase + 0x57C3;
            R8 ^= RAX;
            RAX = RBX;
            RAX ^= RBP_NEG_0x68; // xor rax,[rbp-68h]
            R8 -= RAX;
            RAX = 0x3FADFCBDFC9CE50D;
            R8 += RAX;
            RAX = 0xC3FD16651D55C2A9;
            R8 *= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = _byteswap_uint64(RAX);
            R8 *= readMemory<uint64_t>(RAX + 0xD);
            RAX = 0x6579E511E80CD1BC;
            R8 += RAX;
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
            RAX >>= 0x1A;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x34;
            R8 ^= RAX;
            return R8;
        }
        case 13: {
            // push rbx
            // pushfq
            // pop rbx
            // popfq
            // pop rbx
            R9 = readMemory<uint64_t>(imageBase + 0x660321F);
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R9;
            RAX = _byteswap_uint64(RAX);
            R8 *= readMemory<uint64_t>(RAX + 0xD);
            RAX = 0xF806BFC3C08D5963;
            R8 *= RAX;
            R8 += RBX;
            RAX = 0x34865D0E64A4AD7C;
            R8 ^= RAX;
            RAX = imageBase;
            R8 -= RBX;
            R8 -= RAX;
            R8 -= 0xA2C6;
            RAX = R8;
            RAX >>= 0xA;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x14;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x28;
            R8 ^= RAX;
            return R8;
        }
        case 14: {
            R10 = readMemory<uint64_t>(imageBase + 0x660321F);
            RAX = imageBase;
            R8 ^= RAX;
            RAX = 0xBF29C9BD8A83177F;
            R8 *= RAX;
            RAX = R8;
            RAX >>= 0xA;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x14;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x28;
            R8 ^= RAX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RAX = imageBase + 0x78ED;
            RAX = ~RAX;
            RAX ^= RBX;
            RAX ^= R8;
            RCX = _byteswap_uint64(RCX);
            R8 = readMemory<uint64_t>(RCX + 0xD);
            R8 *= RAX;
            R8 -= RBX;
            RAX = 0x76ECF464A0CD7BF3;
            R8 ^= RAX;
            RAX = imageBase;
            R8 ^= RAX;
            return R8;
        }
        case 15: {
            R10 = readMemory<uint64_t>(imageBase + 0x660321F);
            RCX = imageBase + 0x97ED;
            RAX = 0x1E953F34B7796363;
            RCX = ~RCX;
            R8 *= RAX;
            RAX = 0x513E944EFD5A7B1F;
            R8 -= RBX;
            R8 += RAX;
            R8 += RCX;
            RAX = imageBase + 0x43A5;
            RAX = ~RAX;
            RCX = 0x0;
            RAX *= RBX;
            RCX = _rotl64(RCX, 0x10);
            RAX ^= R8;
            RCX ^= R10;
            RCX = _byteswap_uint64(RCX);
            R8 = readMemory<uint64_t>(RCX + 0xD);
            R8 *= RAX;
            RAX = R8;
            RAX >>= 0x12;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x24;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x1D;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x3A;
            R8 ^= RAX;
            RAX = 0xF7A75C9D8298900B;
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
    RAX = 0xE3948B3CC1B00C01;
    R11 = imageBase;
    RAX = _umul128(RAX, RCX, &RDX);
    R10 = 0xDBAEBD0FB4AA4B3;
    RDX >>= 0xD;
    RAX = RDX * 0x23FF;
    RCX -= RAX;
    RAX = 0x6A8BFB7C61CE6389;
    R8 = RCX * 0x23FF;
    RAX = _umul128(RAX, R8, &RDX);
    RAX = R8;
    RAX -= RDX;
    RAX >>= 0x1;
    RAX += RDX;
    RAX >>= 0xD;
    RAX = RAX * 0x2D31;
    R8 -= RAX;
    RAX = 0x5806E0898ABED6E9;
    RAX = _umul128(RAX, R8, &RDX);
    RCX = R8;
    RDX >>= 0xB;
    RAX = RDX * 0x1173;
    RCX -= RAX;
    RAX = 0xAAAAAAAAAAAAAAAB;
    RAX = _umul128(RAX, R8, &RDX);
    RCX <<= 0x3;
    RDX >>= 0x1;
    RAX = RDX + RDX * 2;
    RAX += RAX;
    RCX -= RAX;
    RAX = readMemory<uint16_t>(RCX + R11 + 0x660B140);
    R8 = RAX * 0x13C8;
    RAX = R10;
    RAX = _umul128(RAX, R8, &RDX);
    RCX = R8;
    RAX = R10;
    RCX -= RDX;
    RCX >>= 0x1;
    RCX += RDX;
    RCX >>= 0xC;
    RCX = RCX * 0x1E5F;
    R8 -= RCX;
    R9 = R8 * 0x2804;
    RAX = _umul128(RAX, R9, &RDX);
    RAX = R9;
    RAX -= RDX;
    RAX >>= 0x1;
    RAX += RDX;
    RAX >>= 0xC;
    RAX = RAX * 0x1E5F;
    R9 -= RAX;
    RAX = 0x824A4E60B3262BC5;
    RAX = _umul128(RAX, R9, &RDX);
    RAX = 0x2E8BA2E8BA2E8BA3;
    RDX >>= 0x9;
    RCX = RDX * 0x3EE;
    RAX = _umul128(RAX, R9, &RDX);
    RDX >>= 0x1;
    RCX += RDX;
    RAX = RCX * 0x16;
    RCX = R9 + R9 * 2;
    RCX <<= 0x3;
    RCX -= RAX;
    R15 = readMemory<uint16_t>(RCX + R11 + 0x6613CE0);
    return R15;
}
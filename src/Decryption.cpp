#include <cstdint>
#include <stdlib.h>
#include <intrin.h>

template<typename T>
inline auto readMemory(uintptr_t ptr) -> T {
    return *reinterpret_cast<T*>(ptr);
}

extern "C" auto decrypt_client_info(uint64_t imageBase, uint64_t peb) -> uint64_t
{
    uint64_t RAX = imageBase, RBX = imageBase, RCX = imageBase, RDX = imageBase, R8 = imageBase, RDI = imageBase, RSI = imageBase, R9 = imageBase, R10 = imageBase, R11 = imageBase, R12 = imageBase, R13 = imageBase, R14 = imageBase, R15 = imageBase;

    RBX = readMemory<uint64_t>(imageBase + 0x172BE718);
    if (RBX == 0) {
        return 0;
    }
    RAX += 0x7;
    // movzx eax,al
    R8 = peb; // mov r8,gs:[rax]
    R8 = ~R8;
    RAX = RBX;
    RCX = 0x0;
    RAX >>= 0x23;
    RAX ^= RBX;
    RCX = _rotl64(RCX, 0x10);
    RCX ^= readMemory<uint64_t>(imageBase + 0x644E10A);
    RCX = _byteswap_uint64(RCX);
    RBX = readMemory<uint64_t>(RCX + 0x13);
    RBX *= RAX;
    RAX = 0x6541088990C02D91;
    RBX *= RAX;
    RAX = imageBase + 0x671EA04F;
    R8 += RAX;
    RAX = RBX;
    RAX >>= 0x22;
    R8 ^= RAX;
    RBX ^= R8;
    RAX = RBX;
    RAX >>= 0x22;
    RBX ^= RAX;
    return RBX;
}

extern "C" auto decrypt_client_base(uint64_t clientInfo, uint64_t imageBase, uint64_t peb) -> uint64_t
{
    uint64_t RAX = imageBase, RBX = imageBase, RCX = imageBase, RDX = imageBase, R8 = imageBase, RDI = imageBase, RSI = imageBase, R9 = imageBase, R10 = imageBase, R11 = imageBase, R12 = imageBase, R13 = imageBase, R14 = imageBase, R15 = imageBase, RBP = 0, RSP = 0;

    RAX = readMemory<uint64_t>(clientInfo + 0x9DC18);
    R11 = peb; // mov r11,gs:[rcx]
    R11 = ~R11;
    // test rax,rax
    // je 00007FF61877ABA5h
    RCX = R11;
    RCX >>= 0x17;
    RCX &= 0xF;
    // cmp rcx,0Eh
    // ja 00007FF61877A703h
    switch (RCX) {
        case 0: {
            R15 = imageBase + 0x9E0A;
            RBX = imageBase;
            R9 = readMemory<uint64_t>(imageBase + 0x644E142);
            RCX = 0xA75226F8ED9D5F09;
            RAX *= RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x7);
            RCX = R15;
            RCX = ~RCX;
            RCX ^= R11;
            RAX += RCX;
            RCX = RAX;
            RCX >>= 0x28;
            RAX ^= RCX;
            RCX = 0xC25ECE4D9E496823;
            RAX -= RBX;
            RAX *= RCX;
            RCX = R11;
            RCX = ~RCX;
            RAX ^= RCX;
            RCX = imageBase + 0x37D8;
            RAX ^= RCX;
            RCX = 0x7ABFC2534EDE0F35;
            RAX *= RCX;
            return RAX;
        }
        case 1: {
            R10 = readMemory<uint64_t>(imageBase + 0x644E142);
            R14 = imageBase + 0xB908;
            RCX = RAX;
            RCX >>= 0x27;
            RAX ^= RCX;
            RCX = R14;
            RCX = ~RCX;
            RCX ^= R11;
            RAX -= RCX;
            RAX -= R11;
            RCX = R11 + RAX;
            RDX = 0x0;
            RDX = _rotl64(RDX, 0x10);
            RDX ^= R10;
            RDX = ~RDX;
            RAX = readMemory<uint64_t>(RDX + 0x7);
            RAX *= RCX;
            RCX = 0xB818522BC9C94EB;
            RAX -= RCX;
            RCX = 0x81209F8955B3C5D1;
            RAX *= RCX;
            RCX = 0xA00287364DD5C85B;
            RAX ^= RCX;
            return RAX;
        }
        case 2: {
            RBX = imageBase;
            R9 = readMemory<uint64_t>(imageBase + 0x644E142);
            RCX = 0x8A70DC98430443CB;
            RAX *= RCX;
            RAX -= RBX;
            RAX ^= R11;
            RAX += RBX;
            RCX = RAX;
            RCX >>= 0x15;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x2A;
            RAX ^= RCX;
            RCX = 0xA8C56F27116288ED;
            RAX ^= RCX;
            RAX ^= R11;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x7);
            return RAX;
        }
        case 3: {
            RBX = imageBase;
            R15 = imageBase + 0x61939915;
            R9 = readMemory<uint64_t>(imageBase + 0x644E142);
            RAX -= RBX;
            RCX = 0x7F8798231C87E473;
            RAX *= RCX;
            RCX = 0x41C571A426645E9D;
            RAX += RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x7);
            RCX = RAX;
            RCX >>= 0x8;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x10;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x20;
            RAX ^= RCX;
            RCX = 0xB23A6B17E8358987;
            RAX ^= RCX;
            RCX = R15;
            RCX = ~RCX;
            RCX ^= R11;
            RAX -= RCX;
            RAX ^= R11;
            return RAX;
        }
        case 4: {
            RBX = imageBase;
            R10 = readMemory<uint64_t>(imageBase + 0x644E142);
            RAX ^= RBX;
            RCX = 0xE98B29467142B675;
            RAX *= RCX;
            RAX ^= RBX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x7);
            RCX = 0xAEF8A98D330157D8;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x13;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x26;
            RAX ^= RCX;
            RCX = 0x3031E2AF2AD7EB5B;
            RAX ^= RCX;
            RAX -= R11;
            return RAX;
        }
        case 5: {
            RBX = imageBase;
            R14 = imageBase + 0xD259;
            R9 = readMemory<uint64_t>(imageBase + 0x644E142);
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RCX = readMemory<uint64_t>(RCX + 0x7);
            RCX *= RAX;
            RAX = 0x541592BC1D926927;
            RCX -= RBX;
            RAX += RCX;
            RAX += R11;
            RCX = RAX;
            RCX >>= 0x24;
            RAX ^= RCX;
            RCX = 0x1876BC0170EA5E0C;
            RAX += RCX;
            RAX += RBX;
            RCX = R11;
            RCX = ~RCX;
            RCX += R14;
            RAX ^= RCX;
            RCX = 0x710900A1291991FF;
            RAX *= RCX;
            return RAX;
        }
        case 6: {
            R10 = readMemory<uint64_t>(imageBase + 0x644E142);
            RBX = imageBase;
            RCX = 0xD7827BD6A04052BB;
            RAX *= RCX;
            RAX += R11;
            RCX = RAX;
            RCX >>= 0xF;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x1E;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x3C;
            RAX ^= RCX;
            RCX = 0x32906D50BE7B16F2;
            RAX += RCX;
            RAX ^= RBX;
            RAX += R11;
            RCX = RAX;
            RCX -= RBX;
            RDX = 0x0;
            RDX = _rotl64(RDX, 0x10);
            RDX ^= R10;
            RDX = ~RDX;
            RAX = readMemory<uint64_t>(RDX + 0x7);
            RAX *= RCX;
            return RAX;
        }
        case 7: {
            RBX = imageBase;
            R14 = imageBase + 0x844A;
            R15 = imageBase + 0x296554D3;
            R9 = readMemory<uint64_t>(imageBase + 0x644E142);
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x7);
            RCX = RAX;
            RCX >>= 0x20;
            RAX ^= RCX;
            RAX ^= RBX;
            RCX = R11;
            RCX ^= R15;
            RAX += RCX;
            RCX = R14;
            RCX = ~RCX;
            RCX ^= R11;
            RAX += RCX;
            RCX = 0xA18383C0AC71B38E;
            RAX ^= RCX;
            RCX = 0x2F4F32688095FC11;
            RAX *= RCX;
            return RAX;
        }
        case 8: {
            R10 = readMemory<uint64_t>(imageBase + 0x644E142);
            RAX -= R11;
            RCX = 0x43876D3B144F3F4E;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x1A;
            RAX ^= RCX;
            RDX = 0x0;
            RDX = _rotl64(RDX, 0x10);
            RCX = RAX;
            RCX >>= 0x34;
            RDX ^= R10;
            RCX ^= RAX;
            RDX = ~RDX;
            RAX = readMemory<uint64_t>(RDX + 0x7);
            RAX *= RCX;
            RCX = 0x3F5227129A281945;
            RAX *= RCX;
            RAX += R11;
            RCX = imageBase + 0xAF01;
            RCX = ~RCX;
            RCX *= R11;
            RAX ^= RCX;
            RAX ^= R11;
            return RAX;
        }
        case 9: {
            R15 = imageBase + 0x64D3E8FC;
            R10 = readMemory<uint64_t>(imageBase + 0x644E142);
            RCX = imageBase + 0x6339;
            RDX = 0x0;
            RCX = ~RCX;
            RDX = _rotl64(RDX, 0x10);
            RDX ^= R10;
            RDX = ~RDX;
            RDX = readMemory<uint64_t>(RDX + 0x7);
            RAX *= RDX;
            RAX ^= RCX;
            RAX ^= R11;
            RDX = R11;
            RDX = ~RDX;
            RCX = R15;
            RCX = ~RCX;
            RDX *= RCX;
            RAX ^= RDX;
            RDX = imageBase + 0x4584;
            RCX = 0xF1B6D66DEFFB89D3;
            RAX *= RCX;
            RCX = RAX;
            RCX >>= 0xB;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x16;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x2C;
            RAX ^= RCX;
            RCX = 0x9821A1013401DAD7;
            RAX *= RCX;
            RCX = 0x26F6E85C00FEC2D0;
            RAX -= RCX;
            RCX = R11;
            RCX *= RDX;
            RAX ^= RCX;
            return RAX;
        }
        case 10: {
            R10 = readMemory<uint64_t>(imageBase + 0x644E142);
            RBX = imageBase;
            RAX ^= RBX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = ~RCX;
            RCX = readMemory<uint64_t>(RCX + 0x7);
            RAX *= RCX;
            RCX = 0x60D101B462B7CE;
            RAX ^= RCX;
            RDX = R11;
            RCX = imageBase + 0x9711;
            RDX *= RCX;
            RCX = RAX;
            RAX = 0x343E239278B378A1;
            RAX *= RCX;
            RAX += RDX;
            RCX = RAX;
            RCX >>= 0x24;
            RAX ^= RCX;
            RCX = 0x6B9422C6387E3E1D;
            RAX += RCX;
            RAX -= R11;
            return RAX;
        }
        case 11: {
            uint64_t RSP_0x50 = imageBase;
            RCX = 0x9C3939CA2E810533;
            RSP_0x50 = RCX; // mov [rsp+50h],rcx
            RBX = imageBase;
            R10 = readMemory<uint64_t>(imageBase + 0x644E142);
            RCX = RAX;
            RCX >>= 0x15;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x2A;
            RAX ^= RCX;
            RCX = 0x666B88313C380B79;
            RAX *= RCX;
            RAX ^= RBX;
            RAX -= R11;
            RAX -= RBX;
            RAX -= 0x697A;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = ~RCX;
            RCX = readMemory<uint64_t>(RCX + 0x7);
            RCX *= RSP_0x50; // imul rcx,[rsp+50h]
            RAX *= RCX;
            RAX ^= RBX;
            RCX = 0x2A5E3F8A1511497D;
            RAX *= RCX;
            return RAX;
        }
        case 12: {
            uint64_t RSP_0x50 = imageBase;
            RDX = imageBase + 0x2CAC06EA;
            RSP_0x50 = RDX; // mov [rsp+50h],rdx
            RBX = imageBase;
            R10 = readMemory<uint64_t>(imageBase + 0x644E142);
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x7);
            RCX = 0x13F1576A18AA0C26;
            RAX -= RCX;
            RCX = RAX;
            RCX >>= 0x22;
            RAX ^= RCX;
            RAX ^= RBX;
            RCX = R11;
            RCX -= RBX;
            RCX -= 0xE236;
            RAX ^= RCX;
            RCX = 0x7DF6E93E92DA13B9;
            RAX *= RCX;
            RCX = R11;
            RDX = imageBase + 0x3D09854A;
            RCX *= RSP_0x50; // imul rcx,[rsp+50h]
            RDX = ~RDX;
            RAX += RCX;
            RDX ^= R11;
            RAX += RDX;
            return RAX;
        }
        case 13: {
            RBX = imageBase;
            R9 = readMemory<uint64_t>(imageBase + 0x644E142);
            RCX = RAX;
            RCX >>= 0x25;
            RAX ^= RCX;
            RCX = 0x44B8F6F31BAC545F;
            RAX *= RCX;
            RCX = 0xFE3089C0E7E049D;
            RAX += RCX;
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
            RAX -= RBX;
            RCX = RAX;
            RCX >>= 0x1E;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x3C;
            RAX ^= RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x7);
            RCX = 0x7C761047C95735C1;
            RAX *= RCX;
            return RAX;
        }
        case 14: {
            R10 = readMemory<uint64_t>(imageBase + 0x644E142);
            RBX = imageBase;
            RCX = RAX;
            RCX >>= 0x1F;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x3E;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x26;
            RAX ^= RCX;
            RAX -= R11;
            RDX = R11;
            RCX = 0xB8A9EAEE41031A1;
            RDX = ~RDX;
            RAX *= RCX;
            RCX = imageBase + 0xC250;
            RDX *= RCX;
            RCX = imageBase + 0x2C2D8C4A;
            RDX += R11;
            RCX = ~RCX;
            RCX++;
            RAX += RDX;
            RAX += RCX;
            RDX = 0x0;
            RCX = RAX + RBX;
            RDX = _rotl64(RDX, 0x10);
            RDX ^= R10;
            RDX = ~RDX;
            RAX = readMemory<uint64_t>(RDX + 0x7);
            RAX *= RCX;
            return RAX;
        }
        case 15: {
            RBX = imageBase;
            R10 = readMemory<uint64_t>(imageBase + 0x644E142);
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
            RCX = RBX + 0x7389;
            RCX += R11;
            RAX += RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = ~RCX;
            RAX *= readMemory<uint64_t>(RCX + 0x7);
            RCX = RAX;
            RCX >>= 0x1D;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x3A;
            RAX ^= RCX;
            RDX = R11;
            RCX = 0xB702E447C60A477D;
            RAX *= RCX;
            RCX = 0xBF2A444E67CA62C9;
            RDX *= RCX;
            RCX = 0x204C11B587D72AD7;
            RAX += RCX;
            RAX += RDX;
            return RAX;
        }
    }
}

extern "C" auto decrypt_bone_base(uint64_t imageBase, uint64_t peb) -> uint64_t
{
    uint64_t RAX = imageBase, RBX = imageBase, RCX = imageBase, RDX = imageBase, R8 = imageBase, RDI = imageBase, RSI = imageBase, R9 = imageBase, R10 = imageBase, R11 = imageBase, R12 = imageBase, R13 = imageBase, R14 = imageBase, R15 = imageBase, RBP = 0, RSP = 0;

    R8 = readMemory<uint64_t>(imageBase + 0x155FA2E8);
    if (R8 == 0) {
        return 0;
    }
    RBX = peb; // mov rbx,gs:[rax]
    // test r8,r8
    // je 00007FF6188BF6F8h
    RAX = RBX;
    RAX = _rotl64(RAX, 0x27);
    RAX &= 0xF;
    // cmp rax,0Eh
    // ja 00007FF6188BF1C1h
    switch (RAX) {
        case 0: {
            R10 = readMemory<uint64_t>(imageBase + 0x644E22C);
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = ~RAX;
            R8 *= readMemory<uint64_t>(RAX + 0xB);
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
            RAX >>= 0x1D;
            R8 ^= RAX;
            RCX = R8;
            RCX >>= 0x3A;
            RAX = RBX;
            RCX ^= R8;
            RAX = ~RAX;
            RCX += RAX;
            RAX = imageBase;
            RCX -= RAX;
            RCX -= 0x41EF;
            R8 = RCX;
            RAX = 0x9B3068D34EEEE5EB;
            R8 >>= 0x26;
            R8 ^= RCX;
            R8 *= RAX;
            return R8;
        }
        case 1: {
            R10 = readMemory<uint64_t>(imageBase + 0x644E22C);
            RAX = imageBase;
            R8 += RAX;
            R8 += RBX;
            RAX = R8;
            RAX >>= 0x23;
            R8 ^= RAX;
            RAX = 0xF6E190AD718C3F75;
            R8 ^= RAX;
            RAX = 0xF2EE5394455EE722;
            R8 ^= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = ~RAX;
            R8 *= readMemory<uint64_t>(RAX + 0xB);
            RAX = R8;
            RAX >>= 0x28;
            R8 ^= RAX;
            RAX = 0x56A285D2244D83DF;
            R8 *= RAX;
            return R8;
        }
        case 2: {
            R10 = readMemory<uint64_t>(imageBase + 0x644E22C);
            R8 ^= RBX;
            RAX = imageBase + 0x1D58;
            R8 ^= RAX;
            RAX = 0x64D937121BA0FB3B;
            R8 ^= RAX;
            R8 -= RBX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = ~RAX;
            RAX = readMemory<uint64_t>(RAX + 0xB);
            R8 *= RAX;
            RAX = 0xD0DB2CB6F4A916A1;
            R8 += RBX;
            R8 *= RAX;
            RAX = R8;
            RAX >>= 0x21;
            R8 ^= RAX;
            RAX = 0x6811CBED9E259A7B;
            R8 += RAX;
            return R8;
        }
        case 3: {
            R10 = readMemory<uint64_t>(imageBase + 0x644E22C);
            RAX = imageBase;
            R8 += RAX;
            RAX = 0x789F8C23B87FB3A9;
            R8 ^= RAX;
            RAX = 0x3C6E2E41EC182319;
            R8 *= RAX;
            RAX = R8;
            RAX >>= 0x1A;
            R8 ^= RAX;
            RAX = 0x814932F0B6B7B269;
            RCX = R8;
            RCX >>= 0x34;
            RCX ^= R8;
            RCX ^= RAX;
            RAX = RCX;
            RAX >>= 0xE;
            RCX ^= RAX;
            RAX = RCX;
            RAX >>= 0x1C;
            RCX ^= RAX;
            RAX = imageBase + 0xD072;
            R8 = RCX;
            R8 >>= 0x38;
            R8 ^= RBX;
            R8 ^= RCX;
            R8 ^= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = ~RAX;
            R8 *= readMemory<uint64_t>(RAX + 0xB);
            return R8;
        }
        case 4: {
            // pushfq
            // push rbx
            // pop rbx
            // pop rbx
            R10 = readMemory<uint64_t>(imageBase + 0x644E22C);
            RCX = imageBase + 0xCDBF;
            RAX = imageBase;
            R8 += RAX;
            RAX = 0x5FCEB3C1935A57B5;
            R8 *= RAX;
            RAX = imageBase;
            RAX += 0x98BE;
            RAX += RBX;
            R8 += RAX;
            RAX = imageBase + 0xD042;
            RAX = ~RAX;
            RAX ^= RBX;
            RAX += RBX;
            R8 -= RAX;
            RAX = R8;
            RAX >>= 0x17;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x2E;
            R8 ^= RAX;
            RAX = RBX;
            RAX = ~RAX;
            RAX += RCX;
            R8 ^= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = ~RAX;
            R8 *= readMemory<uint64_t>(RAX + 0xB);
            return R8;
        }
        case 5: {
            R10 = readMemory<uint64_t>(imageBase + 0x644E22C);
            RAX = imageBase;
            RAX += 0x5A556F7F;
            RAX += RBX;
            R8 ^= RAX;
            RAX = imageBase;
            R8 -= RAX;
            RAX = 0x9D6518969B9A6377;
            R8 *= RAX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RAX = R8;
            RCX ^= R10;
            R8 = imageBase;
            RCX = ~RCX;
            RAX ^= R8;
            R8 = readMemory<uint64_t>(RCX + 0xB);
            R8 *= RAX;
            RAX = 0x16C1292191C139BB;
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
            RAX = 0xC28EBA232C81AD9D;
            R8 *= RAX;
            return R8;
        }
        case 6: {
            uint64_t RBP_NEG_0x70 = imageBase;
            // push rbx
            // pushfq
            // pop rbx
            // popfq
            // pop rbx
            R10 = readMemory<uint64_t>(imageBase + 0x644E22C);
            RAX = imageBase + 0x32A4;
            RBP_NEG_0x70 = RAX; // mov [rbp-70h],rax
            RAX = RBX;
            RAX ^= RBP_NEG_0x70; // xor rax,[rbp-70h]
            R8 += RAX;
            RAX = 0xCD925DF1D38E9F3;
            R8 *= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = ~RAX;
            R8 *= readMemory<uint64_t>(RAX + 0xB);
            RAX = imageBase + 0x1951;
            RAX = ~RAX;
            RAX += RBX;
            R8 += RAX;
            RAX = 0x67F46530BA0FEB91;
            R8 *= RAX;
            RAX = 0xDA2F423EDFAC7322;
            R8 ^= RAX;
            RCX = R8;
            RAX = RBX;
            RCX >>= 0x22;
            RCX ^= R8;
            R8 = imageBase + 0x6188E0F5;
            RAX ^= R8;
            R8 = RCX;
            R8 -= RAX;
            return R8;
        }
        case 7: {
            R9 = readMemory<uint64_t>(imageBase + 0x644E22C);
            RAX = imageBase;
            R8 += RAX;
            RAX = 0x98E790AA7C680CA3;
            R8 *= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R9;
            RAX = ~RAX;
            R8 *= readMemory<uint64_t>(RAX + 0xB);
            RAX = 0x20B1E1CCDBE1A50;
            R8 -= RAX;
            RAX = R8;
            RAX >>= 0x9;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x12;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x24;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0xD;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x1A;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x34;
            R8 ^= RAX;
            R8 -= RBX;
            return R8;
        }
        case 8: {
            uint64_t RBP_NEG_0x50 = imageBase;
            // push rbx
            // pushfq
            // pop rbx
            // popfq
            // pop rbx
            R11 = readMemory<uint64_t>(imageBase + 0x644E22C);
            RAX = imageBase + 0x8000;
            RBP_NEG_0x50 = RAX; // mov [rbp-50h],rax
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R11;
            RAX = ~RAX;
            R8 *= readMemory<uint64_t>(RAX + 0xB);
            RAX = imageBase;
            RAX += 0x13C11772;
            RAX += RBX;
            R8 += RAX;
            RAX = imageBase;
            RAX += 0x48FD4488;
            RAX += RBX;
            R8 += RAX;
            RAX = R8;
            RAX >>= 0x1E;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x3C;
            R8 ^= RAX;
            RAX = 0x88D43F96CE0A5AED;
            R8 *= RAX;
            RAX = RBX;
            RAX = ~RAX;
            RAX ^= RBP_NEG_0x50; // xor rax,[rbp-50h]
            R8 -= RAX;
            RAX = 0xFC2EB5297A27CE9F;
            R8 *= RAX;
            RAX = 0xFB87CCDB490CADEB;
            R8 *= RAX;
            return R8;
        }
        case 9: {
            uint64_t RBP_NEG_0x70 = imageBase;
            RAX = 0x6E0277DE5A8682F5;
            RBP_NEG_0x70 = RAX; // mov [rbp-70h],rax
            R9 = readMemory<uint64_t>(imageBase + 0x644E22C);
            RAX = R8;
            RAX >>= 0x8;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x10;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x20;
            R8 ^= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R9;
            RAX = ~RAX;
            RAX = readMemory<uint64_t>(RAX + 0xB);
            RAX *= RBP_NEG_0x70; // imul rax,[rbp-70h]
            R8 *= RAX;
            RAX = imageBase;
            R8 -= RAX;
            RAX = 0x98994B320AE10D92;
            R8 ^= RAX;
            RAX = imageBase;
            R8 -= RAX;
            RAX = R8;
            RAX >>= 0x18;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x30;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x19;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x32;
            R8 ^= RAX;
            return R8;
        }
        case 10: {
            R10 = readMemory<uint64_t>(imageBase + 0x644E22C);
            R11 = imageBase + 0xD1C9;
            RAX = 0x73B51DA78E840E21;
            R8 -= RAX;
            RAX = R8;
            RAX >>= 0x18;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x30;
            R8 ^= RAX;
            RAX = imageBase;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x1B;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x36;
            R8 ^= RAX;
            RAX = RBX;
            RAX *= R11;
            R8 ^= RAX;
            RAX = 0xB0391F9DF94E5D07;
            R8 *= RAX;
            RAX = imageBase;
            R8 ^= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = ~RAX;
            R8 *= readMemory<uint64_t>(RAX + 0xB);
            return R8;
        }
        case 11: {
            // push rbx
            // pushfq
            // pop rbx
            // popfq
            // pop rbx
            R11 = readMemory<uint64_t>(imageBase + 0x644E22C);
            RAX = 0x1B81ABE342F5E253;
            R8 *= RAX;
            R8 += RBX;
            RCX = 0xDAF4A517C25D23C4;
            R8 += RCX;
            RCX = 0x783414FF8DEF42DA;
            R8 ^= RCX;
            RAX = imageBase + 0x45A9;
            RAX = ~RAX;
            RAX ^= RBX;
            R8 -= RAX;
            RAX = RBX;
            RAX ^= R8;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R11;
            RCX = ~RCX;
            R8 = readMemory<uint64_t>(RCX + 0xB);
            R8 *= RAX;
            RAX = R8;
            RAX >>= 0x12;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x24;
            R8 ^= RAX;
            return R8;
        }
        case 12: {
            // push rbx
            // pushfq
            // pop rbx
            // popfq
            // pop rbx
            R9 = readMemory<uint64_t>(imageBase + 0x644E22C);
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
            RAX ^= RBX;
            R8 ^= RAX;
            RAX = 0x5F2039FDD4101719;
            R8 *= RAX;
            R8 += RBX;
            RAX = R8;
            RAX >>= 0x21;
            R8 ^= RAX;
            RAX = 0x7B8C80395B50AC3A;
            R8 += RAX;
            RAX = 0x200A640BA2CF6626;
            R8 ^= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R9;
            RAX = ~RAX;
            R8 *= readMemory<uint64_t>(RAX + 0xB);
            return R8;
        }
        case 13: {
            R9 = readMemory<uint64_t>(imageBase + 0x644E22C);
            RAX = R8;
            RAX >>= 0x27;
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
            RAX = 0xBDF51632A3A4F66F;
            R8 *= RAX;
            RAX = 0x2E801156A5B1212F;
            R8 += RAX;
            RAX = 0xE107EAF2840F728F;
            R8 *= RAX;
            R8 ^= RBX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R9;
            RAX = ~RAX;
            R8 *= readMemory<uint64_t>(RAX + 0xB);
            R8 -= RBX;
            return R8;
        }
        case 14: {
            R10 = readMemory<uint64_t>(imageBase + 0x644E22C);
            RCX = RBX;
            RAX = imageBase + 0x9CDB;
            RCX *= RAX;
            RAX = R8;
            R8 = 0x4095BEA707A8D591;
            RAX *= R8;
            R8 = RCX;
            R8 ^= RAX;
            RAX = imageBase;
            R8 += RAX;
            RAX = R8;
            RAX >>= 0xB;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x16;
            R8 ^= RAX;
            RAX = R8;
            RAX >>= 0x2C;
            R8 ^= RAX;
            R8 -= RBX;
            RAX = R8;
            RAX >>= 0x19;
            R8 ^= RAX;
            RAX = R8;
            RCX = 0x0;
            RAX >>= 0x32;
            RCX = _rotl64(RCX, 0x10);
            RAX ^= R8;
            RCX ^= R10;
            RCX = ~RCX;
            R8 = readMemory<uint64_t>(RCX + 0xB);
            R8 *= RAX;
            RAX = imageBase;
            RAX += 0x77789E13;
            RAX += RBX;
            R8 ^= RAX;
            return R8;
        }
        case 15: {
            R10 = readMemory<uint64_t>(imageBase + 0x644E22C);
            R12 = 0x889ABDCE40CF5924;
            RAX = imageBase;
            R8 += RAX;
            R8 -= RBX;
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
            RCX = 0x0;
            RAX >>= 0x30;
            RCX = _rotl64(RCX, 0x10);
            RAX ^= R8;
            RCX ^= R10;
            RCX = ~RCX;
            R8 = readMemory<uint64_t>(RCX + 0xB);
            R8 *= RAX;
            R8 ^= R12;
            RAX = 0x562A00E22AB50A1B;
            R8 ^= RAX;
            RAX = 0x4BDC9A197A1194CF;
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
    RAX = 0x23691722685D3AAF;
    R11 = imageBase;
    RAX = _umul128(RAX, RCX, &RDX);
    R10 = 0x4FAABB4391AE13AF;
    RDX >>= 0xA;
    RAX = RDX * 0x1CEB;
    RCX -= RAX;
    RAX = 0x47660D63745C292B;
    R8 = RCX * 0x1CEB;
    RAX = _umul128(RAX, R8, &RDX);
    RAX = R8;
    RAX -= RDX;
    RAX >>= 0x1;
    RAX += RDX;
    RAX >>= 0xD;
    RAX = RAX * 0x320B;
    R8 -= RAX;
    RAX = 0x70381C0E070381C1;
    RAX = _umul128(RAX, R8, &RDX);
    RAX = 0xFE03F80FE03F80FF;
    RDX >>= 0x6;
    RCX = RDX * 0x92;
    RAX = _umul128(RAX, R8, &RDX);
    RDX >>= 0x7;
    RCX += RDX;
    RAX = RCX * 0x102;
    RCX = R8 * 0x104;
    RCX -= RAX;
    RAX = readMemory<uint16_t>(RCX + R11 + 0x6458A00);
    R8 = RAX * 0x13C8;
    RAX = R10;
    RAX = _umul128(RAX, R8, &RDX);
    RAX = R10;
    RDX >>= 0xB;
    RCX = RDX * 0x19B5;
    R8 -= RCX;
    R9 = R8 * 0x2061;
    RAX = _umul128(RAX, R9, &RDX);
    RDX >>= 0xB;
    RAX = RDX * 0x19B5;
    R9 -= RAX;
    RAX = 0x6FBDA7649C433817;
    RAX = _umul128(RAX, R9, &RDX);
    RAX = 0xCCCCCCCCCCCCCCCD;
    RDX >>= 0x9;
    RCX = RDX * 0x495;
    RAX = _umul128(RAX, R9, &RDX);
    RDX >>= 0x3;
    RCX += RDX;
    RAX = RCX + RCX * 4;
    RCX = R9 * 0x16;
    RAX <<= 0x2;
    RCX -= RAX;
    R15 = readMemory<uint16_t>(RCX + R11 + 0x6461D30);
    return R15;
}

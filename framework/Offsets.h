// Version 1.39.6.9873021

namespace offsets {

constexpr auto refdef = 0x173320C8;
constexpr auto name_array = 0x1733D6B8;
constexpr auto name_array_pos = 0x4C70;
constexpr auto camera_base = 0x1447C7E0;
constexpr auto camera_pos = 0x1D8;
constexpr auto local_index = 0x72718;
constexpr auto local_index_pos = 0x1FC;
constexpr auto recoil = 0x72C60;
constexpr auto game_mode = 0x16F659E8;
constexpr auto weapon_definitions = 0x14550FB0;

namespace player {
    constexpr auto size = 0x3AD0;
    constexpr auto valid = 0x5C8;
    constexpr auto pos = 0x128;
    constexpr auto team = 0x120;
    constexpr auto stance = 0x960;
    constexpr auto dead_1 = 0xBC;
    constexpr auto dead_2 = 0x84C;
    constexpr auto weapon_index = 0x36C;
}

namespace bone {
    constexpr auto base_pos = 0x76FF4;
    constexpr auto index_struct_size = 0x150;
}

namespace directx {
    constexpr auto command_queue = 0x18D7CD28;
    constexpr auto swap_chain = 0x18D820A0;
}

}

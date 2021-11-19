namespace offsets {
// Version 1.45.2.10635118
constexpr auto refdef = 0x180D8908;
constexpr auto name_array = 0x180E4148;
constexpr auto name_array_pos = 0x4C70;
constexpr auto camera_base = 0x1585DAD0;
constexpr auto camera_pos = 0x1D8;
constexpr auto local_index = 0xE0;
constexpr auto local_index_pos = 0x1FC;
constexpr auto recoil = 0x38C84;
constexpr auto game_mode = 0x17CF1F78;
constexpr auto weapon_definitions = 0x15933990;
constexpr auto distribute = 0x1A78A978;
constexpr auto visible = 0x6208240;
 
namespace player {
constexpr auto size = 0x3AF0;
constexpr auto valid = 0x558;
constexpr auto pos = 0x1E8;
constexpr auto team = 0x1D0;
constexpr auto stance = 0x31C4;
constexpr auto weapon_index = 0x30A0;
constexpr auto dead_1 = 0x1E0;
constexpr auto dead_2 = 0x384;
}
 
namespace bone {
constexpr auto base_pos = 0x38D6C; // signature not found: 48 05 ? ? ? ? 48 89 44 24 ? 4C 8D 84 24 ? ? ? ?
constexpr auto index_struct_size = 0x150;
}
 
namespace directx {
constexpr auto command_queue = 0x19B60D28;
constexpr auto swap_chain = 0x19B660A0;
}
}

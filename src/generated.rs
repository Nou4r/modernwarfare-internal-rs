pub const REFDEF: u64 = 0x180D8908;
pub const NAME_ARRAY: u64 = 0x180E4148;
pub const NAME_ARRAY_POS: u64 = 0x4C70;
pub const CAMERA_BASE: u64 = 0x1585DAD0;
pub const CAMERA_POS: u64 = 0x1D8;
pub const LOCAL_INDEX: u64 = 0xE0;
pub const LOCAL_INDEX_POS: u64 = 0x1FC;
pub const RECOIL: u64 = 0x38C84;
pub const GAME_MODE: u64 = 0x17CF1F78;
pub const WEAPON_DEFINITIONS: u64 = 0x15933990;
pub const DISTRIBUTE: u64 = 0x1A78A978;
pub const VISIBLE: u64 = 0x6208240;
 
pub mod player {
pub const SIZE: u64 = 0x3AF0;
pub const VALID: u64 = 0x558;
pub const POS: u64 = 0x1E8;
pub const TEAM: u64 = 0x1D0;
pub const STANCE: u64 = 0x31C4;
pub const WEAPON_INDEX: u64 = 0x30A0;
pub const DEAD_1: u64 = 0x1E0;
pub const DEAD_2: u64 = 0x384;
}
 
pub mod bone {
pub const BASE_POS: u64 = 0x38D6C; // signature not found: 48 05 ? ? ? ? 48 89 44 24 ? 4C 8D 84 24 ? ? ? ?
pub const INDEX_STRUCT_SIZE: u64 = 0x150;
}
 
pub mod directx {
pub const COMMAND_QUEUE: u64 = 0x19B60D28;
pub const SWAP_CHAIN: u64 = 0x19B660A0;
}

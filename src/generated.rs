pub const REFDEF: u64 = 0x173320C8;
pub const NAME_ARRAY: u64 = 0x1733D6B8;
pub const NAME_ARRAY_POS: u64 = 0x4C70;
pub const CAMERA_BASE: u64 = 0x1447C7E0;
pub const CAMERA_POS: u64 = 0x1D8;
pub const LOCAL_INDEX: u64 = 0x72718;
pub const LOCAL_INDEX_POS: u64 = 0x1FC;
pub const RECOIL: u64 = 0x72C60;
pub const GAME_MODE: u64 = 0x16F659EC;
pub const WEAPON_DEFINITIONS: u64 = 0x14550FB0;

pub mod player {
    pub const SIZE: u64 = 0x3AD0;
    pub const VALID: u64 = 0x5C8;
    pub const POS: u64 = 0x128;
    pub const TEAM: u64 = 0x120;
    pub const STANCE: u64 = 0x960;
    pub const DEAD_1: u64 = 0xBC;
    pub const DEAD_2: u64 = 0x84C;
}

pub mod bone {
    pub const BASE_POS: u64 = 0x76FF4;
    pub const INDEX_STRUCT_SIZE: u64 = 0x150;
}

pub mod directx {
    pub const COMMAND_QUEUE: u64 = 0x18D7CD28;
    pub const SWAP_CHAIN: u64 = 0x18D820A0;
}


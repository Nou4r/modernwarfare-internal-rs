pub const REFDEF: u64 = 0x1721BBB0;
pub const NAME_ARRAY: u64 = 0x17226E58;
pub const NAME_ARRAY_POS: u64 = 0x4C70;
pub const CAMERA_BASE: u64 = 0x14417F80;
pub const CAMERA_POS: u64 = 0x1D8;
pub const LOCAL_INDEX: u64 = 0x38C00;
pub const LOCAL_INDEX_POS: u64 = 0x1F4;
pub const RECOIL: u64 = 0x24CEC;
pub const GAME_MODE: u64 = 0x16E8DB6C;
pub const WEAPON_DEFINITIONS: u64 = 0x144EB300;
pub const UNIT_SCALE: f32 = 0.0254;

pub mod player {
    pub const SIZE: u64 = 0x3AA8;
    pub const VALID: u64 = 0x488;
    pub const POS: u64 = 0x448;
    pub const TEAM: u64 = 0x2DF4;
    pub const STANCE: u64 = 0x2F6C;
    pub const WEAPON_INDEX: u64 = 0x3D8;
    pub const DEAD_1: u64 = 0x36F0;
    pub const DEAD_2: u64 = 0x39B8;
}

pub mod bone {
    pub const BASE_POS: u64 = 0x95434;
    pub const INDEX_STRUCT_SIZE: u64 = 0x150;
}

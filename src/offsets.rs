pub const REFDEF: u64 = 0x16F6ECB0;
pub const NAME_ARRAY: u64 = 0x16F79F58;
pub const NAME_ARRAY_POS: u64 = 0x4C70;
pub const CAMERA_BASE: u64 = 0x1416B000;
pub const CAMERA_POS: u64 = 0x1D8;
pub const LOCAL_INDEX: u64 = 0x501C0;
pub const LOCAL_INDEX_POS: u64 = 0x1FC;
pub const RECOIL: u64 = 0x23824;
pub const GAME_MODE: u64 = 0x16BE0BE8;
pub const WEAPON_DEFINITIONS: u64 = 0x1423E380;
pub const UNIT_SCALE: f32 = 0.0254;

pub mod player {
    pub const SIZE: u64 = 0x3AC0;
    pub const VALID: u64 = 0x614;
    pub const POS: u64 = 0x12D0;
    pub const TEAM: u64 = 0x4B8;
    pub const STANCE: u64 = 0x6A8;
    pub const WEAPON_INDEX: u64 = 0xF5A;
    pub const DEAD_1: u64 = 0x14F4;
    pub const DEAD_2: u64 = 0x430;
}

pub mod bone {
    pub const BASE_POS: u64 = 0x57CB4;
    pub const INDEX_STRUCT_SIZE: u64 = 0x150;
}

pub mod funcs {
    pub const DVAR_SETBOOL: u64 = 0x2F64420;
    pub const DVAR_UAV: u64 = 0x144E0EE8;
}

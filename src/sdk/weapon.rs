use crate::util::{read_memory, try_read_memory, is_bad_ptr, str_from_ptr};
use crate::memory::MEMORY;
use crate::offsets;

#[derive(Debug, Clone)]
pub struct Weapon {
    // iw8_ar_kilo433_mpdmb
    internal_name: &'static str,
    // WEAPON/AR_KILO433
    name_2: &'static str,
    // arKilo433
    pub name: &'static str,
    pub velocity: f32,
    pub index: usize,
}

impl Weapon {
    pub unsafe fn from_index(index: usize) -> Option<Self> {
        let weapon_defs: u64 = read_memory(MEMORY.image_base + offsets::WEAPON_DEFINITIONS + (index * 0x8) as u64);
        if is_bad_ptr(weapon_defs) {
            return None;
        }

        let internal_name = str_from_ptr((weapon_defs + 0x0) as _).unwrap_or("");
        // let internal_name = "";
        // let name_2 = str_from_ptr((weapon_defs + 0x18) as _)?;
        // let name = str_from_ptr((weapon_defs + 0x250) as _)?;
        let name_2 = "";
        let name = "";

        let velocity_info: u64 = read_memory(weapon_defs + 0x8);
        let velocity = read_memory(velocity_info + 0xDC);

        Some(Self { internal_name, name_2, name, velocity, index })
    }
}
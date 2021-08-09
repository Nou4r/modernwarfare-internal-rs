use std::mem::transmute;

use log::*;

use crate::decryption::DECRYPTION;
use crate::math::{Angles2, Vector2, Vector3};
use crate::memory::MEMORY;
use crate::offsets;
use crate::sdk::{NameInfo, Player, RefDef};
use crate::util::{is_bad_ptr, read_memory, try_read_memory};

/// Returns None if no camera is available, the camera position and angles otherwise
pub unsafe fn get_camera() -> Option<(Vector3, Angles2)> {
    let addr: u64 = read_memory(MEMORY.image_base + offsets::CAMERA_BASE);
    if addr == 0 {
        return None;
    }

    Some((read_memory(addr + offsets::CAMERA_POS), read_memory(addr + offsets::CAMERA_POS + 12)))
}

#[repr(C)]
#[derive(Debug, Default, Eq, PartialEq)]
pub struct RefdefKeyStruct {
    pub ref0: u32,
    pub ref1: u32,
    pub ref2: u32,
}

pub unsafe fn get_refdef() -> Option<&'static RefDef> {
    use std::num::Wrapping;

    let crypt: RefdefKeyStruct = read_memory(MEMORY.image_base + offsets::REFDEF as u64);
    let lower: Wrapping<u64> = Wrapping(crypt.ref0 as u64) ^ (Wrapping(crypt.ref2 as u64 ^ (MEMORY.image_base + offsets::REFDEF as u64)) * Wrapping((crypt.ref2 as u64 ^ (MEMORY.image_base + offsets::REFDEF as u64)) + 2));
    let upper: Wrapping<u64> = Wrapping(crypt.ref1 as u64) ^ (Wrapping(crypt.ref2 as u64 ^ (MEMORY.image_base + offsets::REFDEF as u64 + 0x4)) * Wrapping((crypt.ref2 as u64 ^ (MEMORY.image_base + offsets::REFDEF as u64 + 0x4)) + 2));
    let refdef = (upper.0 as u32 as u64) << 32 | (lower.0 as u32 as u64);

    if crate::util::is_bad_ptr(refdef) {
        return None;
    }

    Some((refdef as *const RefDef).as_ref().unwrap())
}

pub unsafe fn gamemode() -> u32 {
    read_memory(MEMORY.image_base + offsets::GAME_MODE)
}

pub unsafe fn max_players() -> u32 {
    return 155;
    // read_memory(MEMORY.image_base + offsets::GAME_MODE + 4)
}

pub unsafe fn get_name_struct(player_index: u32) -> Option<&'static NameInfo> {
    let base: u64 = try_read_memory(MEMORY.image_base + offsets::NAME_ARRAY)?;
    Some(transmute(base + offsets::NAME_ARRAY_POS + (player_index * 0xD0) as u64))
}

pub unsafe fn in_game() -> bool {
    gamemode() > 1
}

pub unsafe fn local_index() -> u32 {
    let addr: u64 = read_memory(DECRYPTION.client_info.unwrap_or(0) + offsets::LOCAL_INDEX);
    if is_bad_ptr(addr) {
        error!("Read invalid address 0x{:X} for offsets::LOCAL_INDEX", addr);
        return 0;
    }
    read_memory(addr + offsets::LOCAL_INDEX_POS)
}

pub unsafe fn get_players(players: &mut Vec<Player>) {
    if DECRYPTION.client_base.is_none() {
        error!("get_players called without client_base");
        return;
    }

    let client_base = DECRYPTION.client_base.unwrap();
    players.clear();
    for i in 0..max_players() {
        let base = client_base + (i as u64 * offsets::player::SIZE);
        let player = Player::new(base, i as _);
        if let Some(player) = player {
            players.push(player);
        }
    }
}

pub fn world_to_screen_internal(world_location: Vector3, camera_pos: Vector3, screen_width: i32, screen_height: i32, fov: Vector2, matricies: [Vector3; 3]) -> Option<Vector2> {
    let local = world_location - camera_pos;
    let trans = Vector3 {
        x: Vector3::dot(&local, &matricies[1]),
        y: Vector3::dot(&local, &matricies[2]),
        z: Vector3::dot(&local, &matricies[0]),
    };

    if trans.z < 0.01 {
        return None;
    }

    let x = (screen_width as f32 / 2.0) * (1.0 - (trans.x / fov.x / trans.z));
    let y = (screen_height as f32 / 2.0) * (1.0 - (trans.y / fov.y / trans.z));

    Some(Vector2 { x, y })
}
mod client;
mod structs;
mod player;
mod weapon;
mod bone;

pub use client::*;
pub use structs::*;
pub use player::*;
pub use weapon::*;
pub use bone::*;

use crate::offsets;

// Converts units to in game meters
pub fn units_to_m(units: f32) -> f32 {
    units * offsets::UNIT_SCALE
}

pub fn m_to_units(meters: f32) -> f32 {
    meters / offsets::UNIT_SCALE
}
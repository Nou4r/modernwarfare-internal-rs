use std::time::{Duration, Instant};

use imgui::ImColor32;
use imgui::sys::ImColor;
use log::*;

use crate::config::CONFIG;
use crate::decryption::DECRYPTION;
use crate::fonts::Font;
use crate::gamedata::GAMEDATA;
use crate::hacks;
use crate::overlay::{ImguiOverlay, TextOptions};
use crate::sdk;
use crate::util::Global;

#[derive(Default)]
pub struct Cheat {
    pub last_frame_time: Duration,
}

pub static CHEAT: Global<Cheat> = Global::new();

impl Cheat {
    pub unsafe fn tick(&self) {
        DECRYPTION.get_mut().update();
        GAMEDATA.get_mut().update();

        if GAMEDATA.valid {
            // hacks::no_recoil::tick(&CONFIG);
        }
    }

    pub unsafe fn render(&self, overlay: &ImguiOverlay) {
        if GAMEDATA.valid {
            hacks::esp::render(&GAMEDATA, overlay, &CONFIG);
        }
    }
}
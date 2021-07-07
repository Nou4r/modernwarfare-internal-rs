use std::time::{Instant, Duration};

use log::*;

use crate::decryption::DECRYPTION;
use crate::gamedata::GAMEDATA;
use crate::sdk;
use crate::util::Global;
use crate::overlay::{ImguiOverlay, TextOptions, Font};
use imgui::sys::ImColor;
use imgui::ImColor32;
use crate::hacks;
use crate::config::CONFIG;

#[derive(Default)]
pub struct Cheat {
    pub last_frame_time: Duration,
}

pub static CHEAT: Global<Cheat> = Global::new();

impl Cheat {
    pub unsafe fn tick(&self) {
        DECRYPTION.get_mut().update();
        GAMEDATA.get_mut().update();

        // if GAMEDATA.valid {}
    }

    pub unsafe fn render(&self, overlay: &ImguiOverlay) {
        overlay.draw_text([100.0, 100.0], &format!("len: {}", &crate::fonts::FONTS.len()), TextOptions::default().font(Font::Verdana));
        if GAMEDATA.valid {
            hacks::esp::render(&GAMEDATA, overlay, &CONFIG);
        }
    }
}
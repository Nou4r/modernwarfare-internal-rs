use std::time::{Duration, Instant};

use imgui::ImColor32;
use imgui::sys::ImColor;
use log::*;

use crate::config::CONFIG;
use crate::decryption::DECRYPTION;
use crate::fonts::Font;
use crate::gamedata::{GAMEDATA, Gamedata};
use crate::{hacks, InputType, unload_cheat};
use crate::overlay::{ImguiOverlay, TextOptions, TextStyle};
use crate::sdk;
use crate::util::Global;
use crate::hacks::aimbot::AimbotContext;
use crate::gui::GUI;
use std::collections::{HashSet, VecDeque};

#[derive(Default)]
pub struct Cheat {
    pub last_frame_time: Duration,
    pub keys_down: HashSet<i32>,
    pub gamedata_history: VecDeque<(Instant, Gamedata)>,
    aimbot_context: AimbotContext
}

pub static CHEAT: Global<Cheat> = Global::new();

impl Cheat {
    pub unsafe fn tick(&mut self) {
        DECRYPTION.get_mut().update();
        GAMEDATA.get_mut().update();

        if GAMEDATA.valid {
            // Update gamedata history
            let now = Instant::now();
            self.gamedata_history.push_back((now, GAMEDATA.clone()));
            // Remove old records
            while (now - self.gamedata_history.get(0).unwrap().0) > Duration::from_secs(1) {
                self.gamedata_history.pop_front();
            }

            hacks::aimbot::tick(&GAMEDATA, &CONFIG, &mut self.aimbot_context);
            hacks::no_recoil::tick(&CONFIG);
        }
    }

    pub unsafe fn render(&self, overlay: &ImguiOverlay) {
        if CONFIG.watermark {
            overlay.draw_text([5.0, 5.0], &format!("{} {}", crate::NAME, crate::VERSION), TextOptions::default().font(Font::Verdana).style(TextStyle::Shadow));
        }
        if GAMEDATA.valid {
            hacks::esp::render(&GAMEDATA, overlay, &CONFIG);
        }
    }

    pub unsafe fn handle_input(&mut self, input_type: InputType, key: i32) {
        match input_type {
            InputType::KeyDown => self.keys_down.insert(key),
            InputType::KeyUp => self.keys_down.remove(&key)
        };

        if input_type == InputType::KeyDown {
            use winapi::um::winuser::*;
            match key {
                VK_INSERT => GUI.get_mut().handle_toggle(),
                VK_END => unload_cheat(),
                _ => {}
            }
        }
    }

    pub fn is_key_down(&self, key: i32) -> bool {
        self.keys_down.contains(&key)
    }
}
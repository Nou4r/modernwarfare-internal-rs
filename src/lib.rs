#![feature(llvm_asm)]
#![feature(destructuring_assignment)]
#![feature(type_name_of_val)]
#![feature(asm)]
#![feature(track_caller)]
#![allow(clippy::missing_safety_doc)]

#[macro_use]
extern crate litcrypt;

use_litcrypt!("lkasjfoiuq903281094okajfsdlkjuioj");

use std::ptr::null_mut;
use std::time::Instant;

use log::*;
use log::LevelFilter;

use crate::cheat::CHEAT;
use crate::config::CONFIG;
use crate::decryption::DECRYPTION;
use crate::gamedata::GAMEDATA;
use crate::gui::GUI;
use crate::memory::MEMORY;
use crate::overlay::ImguiOverlay;
use std::fmt::Debug;
use std::panic::PanicInfo;
use backtrace::Backtrace;
use winapi::um::winuser::{MessageBoxA, MB_OK};
use crate::storage::{STORAGE, Storage};

#[macro_use]
pub mod logger;
pub mod cheat;
pub mod gui;
pub mod util;
pub mod memory;
pub mod decryption;
pub mod offsets;
pub mod sdk;
pub mod math;
pub mod gamedata;
pub mod overlay;
pub mod hacks;
pub mod config;
pub mod fonts;
pub mod prediction;
pub mod funcs;
pub mod storage;
mod generated;

pub static VERSION: &str = concat!(env!("GIT_BRANCH"), "/", env!("GIT_HASH"), env!("GIT_MODIFIED_STR"));
#[cfg(feature = "klar")]
pub static NAME: &str = "klar.gg";
#[cfg(not(feature = "klar"))]
pub static NAME: &str = "modernwarfare-internal";

// pub static DEBUG: bool = cfg!(debug_assertations);
pub static DEBUG: bool = cfg!(feature = "debug");

#[no_mangle]
pub unsafe extern "C" fn on_load() {
    logger::Logger::init(LevelFilter::Trace);

    STORAGE.init_default();
    let _ = STORAGE.get_mut().load();
    MEMORY.init_default();
    GUI.init_default();
    GAMEDATA.init_default();
    DECRYPTION.init_default();
    CHEAT.init_default();
    CONFIG.init(if STORAGE.auto_load { STORAGE.config.clone() } else { Default::default() });
    // FUNCS.init_default();
    // std::panic::set_hook(Box::new(|info| {
    //     let backtrace = Backtrace::new();
    //     error!("panic: {:?}\n{:?}", info, backtrace);
    // }))
}

#[no_mangle]
pub unsafe extern "C" fn on_imgui_init(ctx: *mut imgui::sys::ImGuiContext) {
    let mut ctx = imgui::Context::from_raw(ctx);
    fonts::init_fonts(&mut ctx, 1.0);
    ctx.set_ini_filename(None);
}

#[no_mangle]
pub unsafe extern "C" fn on_frame(ctx: *mut imgui::sys::ImGuiContext) {
    let start = Instant::now();

    static mut IMGUI_CONTEXT: Option<imgui::Context> = None;
    let mut ctx = IMGUI_CONTEXT.get_or_insert_with(|| imgui::Context::from_raw(ctx));
    ctx.io_mut().want_capture_mouse = GUI.is_open();

    let ui = imgui::Ui { ctx, font_atlas: None };

    CHEAT.get_mut().tick();
    ImguiOverlay::build(&ui, |overlay| {
        CHEAT.get_mut().render(overlay);
    });
    GUI.get_mut().render(&ui);

    CHEAT.get_mut().last_frame_time = start.elapsed();
}

#[repr(i32)]
#[derive(Copy, Clone, PartialEq)]
pub enum InputType {
    KeyDown = 0,
    KeyUp = 1,
}

#[no_mangle]
pub unsafe extern "C" fn on_input_event(input_type: InputType, key: i32) {
    CHEAT.get_mut().handle_input(input_type, key);
}

#[link(name = "framework")]
extern "C" {
    fn unload_cheat();
}

#![feature(llvm_asm)]
#![feature(destructuring_assignment)]
#![feature(type_name_of_val)]
#![feature(asm)]
#![feature(track_caller)]
#![allow(clippy::missing_safety_doc)]

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
pub mod asm;
pub mod funcs;
mod generated;

pub static VERSION: &str = concat!(env!("GIT_BRANCH"), "/", env!("GIT_HASH"), env!("GIT_MODIFIED_STR"));
// pub static DEBUG: bool = cfg!(debug_assertations);
pub static DEBUG: bool = true;

#[no_mangle]
pub unsafe extern "C" fn on_load() {
    logger::Logger::init(LevelFilter::Trace);

    MEMORY.init_default();
    GUI.init_default();
    GAMEDATA.init_default();
    DECRYPTION.init_default();
    CHEAT.init_default();
    config::init();
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
    // if let Err(e) = std::panic::catch_unwind(|| {
        let start = Instant::now();

        static mut IMGUI_CONTEXT: Option<imgui::Context> = None;
        let mut ctx = IMGUI_CONTEXT.get_or_insert_with(|| imgui::Context::from_raw(ctx));
        ctx.io_mut().want_capture_mouse = GUI.is_open();

        let ui = imgui::Ui { ctx, font_atlas: None };

        CHEAT.get_mut().tick();
        ImguiOverlay::build(&ui, |overlay| {
            CHEAT.get_mut().render(&overlay);
        });
        GUI.get_mut().render(&ui);

        CHEAT.get_mut().last_frame_time = start.elapsed();
    // }) {
    //     error!("Panic during frame: {:?} | {:?}\n{:?}", e.downcast_ref::<String>(), e.downcast_ref::<&str>(), backtrace::Backtrace::new());
    //      unload_cheat();
    // }
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

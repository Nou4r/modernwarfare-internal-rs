#![allow(clippy::missing_safety_doc)]

use std::mem;
use std::ptr;

use imgui::*;

#[no_mangle]
pub unsafe extern "C" fn on_load() {}

pub static mut IMGUI_CONTEXT: Option<Context> = None;

#[no_mangle]
pub unsafe extern "C" fn on_imgui_init(raw: *mut sys::ImGuiContext) {
    // IMGUI_CONTEXT = Context::from_raw(raw);
}

#[no_mangle]
pub unsafe extern "C" fn on_frame(ctx: *mut sys::ImGuiContext) {
    let ctx = IMGUI_CONTEXT.get_or_insert_with(|| Context::from_raw(ctx));
    let ui = Ui { ctx, font_atlas: None };

    Window::new(im_str!("test"))
        .size([300.0, 110.0], Condition::FirstUseEver)
        .build(&ui, || {
            ui.text(im_str!("Hello world!"));
            ui.text(im_str!("こんにちは世界！"));
            ui.text(im_str!("This...is...imgui-rs!"));
            ui.separator();
            let mouse_pos = ui.io().mouse_pos;
            ui.text(format!(
                "Mouse Position: ({:.1},{:.1})",
                mouse_pos[0], mouse_pos[1]
            ));
        });
}

#[no_mangle]
pub unsafe extern "C" fn on_input_event(input_type: i32, key: u32) {
    if key == 0x23 {
        unload_cheat();
    }
}

#[link(name = "framework")]
extern "C" {
    fn unload_cheat();
}

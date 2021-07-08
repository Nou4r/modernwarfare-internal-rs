use std::{mem, ptr};
use std::cell::UnsafeCell;
use std::collections::{HashMap, HashSet};
use std::ffi::CStr;
use std::ops::{Deref, DerefMut};

use imgui::*;
use log::*;
use winapi::um::winuser::VK_ESCAPE;

extern "C" {
    pub fn is_bad_ptr(ptr: u64) -> bool;
}

pub unsafe fn read_memory<T>(ptr: u64) -> T {
    try_read_memory(ptr).unwrap_or_else(|| mem::zeroed())
}

pub unsafe fn try_read_memory<T>(ptr: u64) -> Option<T> {
    if is_bad_ptr(ptr) {
        error!("Attempted to read invalid memory at 0x{:X}\n{:?}", ptr, backtrace::Backtrace::new());
        return None;
    }
    Some(ptr::read(ptr as _))
}

pub unsafe fn str_from_ptr<'a>(ptr: *const u8) -> Option<&'a str> {
    if is_bad_ptr(ptr as _) {
        error!("Tried to read invalid string");
        return None;
    }
    CStr::from_ptr(ptr as _).to_str().ok()
}

#[derive(Default, Debug)]
pub struct RenderState(HashMap<String, Box<dyn std::any::Any>>);

impl RenderState {
    pub fn new() -> Self {
        Self(HashMap::new())
    }

    pub fn set<T: 'static>(&mut self, key: &str, value: T) {
        self.0.insert(key.to_string(), Box::new(value));
    }

    pub fn get<'a, T: 'static>(&mut self, key: &str, default: T) -> &'a mut T {
        self.get_or_else(key, move || default)
    }

    pub fn get_or_else<'a, T: 'static>(&mut self, key: &str, default: impl FnOnce() -> T) -> &'a mut T {
        let n = self.0.entry(key.to_string())
            .or_insert_with(|| Box::new(default()))
            .downcast_mut::<T>()
            .unwrap();
        unsafe { (n as *mut T).as_mut().unwrap() }
    }
}

enum KeybindSelectState {
    Idle,
    Listening(HashSet<i32>),
}

pub fn keybind_select(ui: &imgui::Ui, render_state: &mut RenderState, title: &ImStr, key: &mut i32) {
    use KeybindSelectState::*;
    let state = render_state.get(&format!("keybind:{:X}", key as *mut _ as usize), KeybindSelectState::Idle);

    let title = if let Listening { .. } = state {
        im_str!("Press key").to_owned()
    } else {
        im_str!("{}: {}", title, vkey_to_string(*key))
    };

    if ui.button_with_size(&title, [160.0, 20.0]) {
        *state = match *state {
            Idle => Listening(crate::CHEAT.keys_down.clone()),
            Listening { .. } => Idle
        }
    }
    if let Listening(prev_keys_down) = state {
        unsafe { (*imgui::sys::igGetIO()).WantCaptureKeyboard = true };
        let mut handled = false;
        for current_key in &crate::CHEAT.keys_down {
            if !prev_keys_down.contains(&current_key) {
                if *current_key == VK_ESCAPE {
                    handled = true;
                    break;
                }
                *key = *current_key;
                handled = true;
                break;
            }
        }

        if handled {
            *state = Idle;
        }
    }
}

/// Translate keycode into text, and also filter out keys not usable (arrows, escape)
fn vkey_to_string(key: i32) -> String {
    use winapi::um::winuser::*;
    let mut text = match key {
        VK_LBUTTON => "LBUTTON",
        VK_RBUTTON => "RBUTTON",
        VK_MBUTTON => "MBUTTON",
        VK_XBUTTON1 => "XBUTTON1",
        VK_XBUTTON2 => "XBUTTON2",
        VK_BACK => "BACK",
        VK_TAB => "TAB",
        VK_CLEAR => "CLEAR",
        VK_RETURN => "RETURN",
        VK_SHIFT => "SHIFT",
        VK_CONTROL => "CONTROL",
        VK_MENU => "MENU",
        VK_PAUSE => "PAUSE",
        VK_CAPITAL => "CAPITAL",
        VK_SPACE => "SPACE",
        VK_PRIOR => "PGUP",
        VK_NEXT => "PGDOWN",
        VK_END => "END",
        VK_HOME => "HOME",
        VK_PRINT => "PRINT",
        VK_EXECUTE => "EXECUTE",
        VK_SNAPSHOT => "SNAPSHOT",
        VK_INSERT => "INSERT",
        VK_DELETE => "DELETE",
        VK_HELP => "HELP",
        0x30 => "0",
        0x31 => "1",
        0x32 => "2",
        0x33 => "3",
        0x34 => "4",
        0x35 => "5",
        0x36 => "6",
        0x37 => "7",
        0x38 => "8",
        0x39 => "9",
        0x41 => "A",
        0x42 => "B",
        0x43 => "C",
        0x44 => "D",
        0x45 => "E",
        0x46 => "F",
        0x47 => "G",
        0x48 => "H",
        0x49 => "I",
        0x4A => "J",
        0x4B => "K",
        0x4C => "L",
        0x4D => "M",
        0x4E => "N",
        0x4F => "O",
        0x50 => "P",
        0x51 => "Q",
        0x52 => "R",
        0x53 => "S",
        0x54 => "T",
        0x55 => "U",
        0x56 => "V",
        0x57 => "W",
        0x58 => "X",
        0x59 => "Y",
        0x5A => "Z",
        VK_LWIN => "LWIN",
        VK_RWIN => "RWIN",
        VK_APPS => "APPS",
        VK_SLEEP => "SLEEP",
        VK_NUMPAD0 => "NUMPAD0",
        VK_NUMPAD1 => "NUMPAD1",
        VK_NUMPAD2 => "NUMPAD2",
        VK_NUMPAD3 => "NUMPAD3",
        VK_NUMPAD4 => "NUMPAD4",
        VK_NUMPAD5 => "NUMPAD5",
        VK_NUMPAD6 => "NUMPAD6",
        VK_NUMPAD7 => "NUMPAD7",
        VK_NUMPAD8 => "NUMPAD8",
        VK_NUMPAD9 => "NUMPAD9",
        VK_MULTIPLY => "MULTIPLY",
        VK_ADD => "ADD",
        VK_SEPARATOR => "SEPARATOR",
        VK_SUBTRACT => "SUBTRACT",
        VK_DECIMAL => "DECIMAL",
        VK_DIVIDE => "DIVIDE",
        VK_F1 => "F1",
        VK_F2 => "F2",
        VK_F3 => "F3",
        VK_F4 => "F4",
        VK_F5 => "F5",
        VK_F6 => "F6",
        VK_F7 => "F7",
        VK_F8 => "F8",
        VK_F9 => "F9",
        VK_F10 => "F10",
        VK_F11 => "F11",
        VK_F12 => "F12",
        VK_NUMLOCK => "NUMLOCK",
        VK_SCROLL => "SCROLL",
        _ => "",  // we can't have a ref making a number to a string so we have to do it somwhere else
    }.to_string();
    if text.is_empty() {
        text = key.to_string();
    }
    text
}

pub struct Global<T>(UnsafeCell<Option<T>>);

unsafe impl<T> Send for Global<T> {}

unsafe impl<T> Sync for Global<T> {}

impl<T> Global<T> {
    pub const fn new() -> Self {
        Self(UnsafeCell::new(None))
    }
}

impl<T: 'static> Global<T> {
    pub fn init(&self, value: T) {
        unsafe { (*self.0.get()) = Some(value) };
    }

    pub fn get(&self) -> &T {
        unsafe { (*self.0.get()).as_ref().unwrap() }
    }

    pub fn get_or_init(&self, init: impl Fn() -> T) -> &T {
        unsafe {
            match *self.0.get().as_ref().unwrap() {
                None => {
                    *self.0.get() = Some(init());
                    self.get()
                }
                Some(_) => self.get()
            }
        }
    }

    pub unsafe fn get_mut(&self) -> &mut T {
        unsafe { (*self.0.get()).as_mut().unwrap() }
    }
}

impl<T: 'static + Default> Global<T> {
    pub fn init_default(&self) {
        self.init(Default::default());
    }
}

impl<T: 'static> Deref for Global<T> {
    type Target = T;

    fn deref(&self) -> &Self::Target {
        self.get()
    }
}

impl<T: Default + 'static> DerefMut for Global<T> {
    fn deref_mut(&mut self) -> &mut Self::Target {
        unsafe { self.get_mut() }
    }
}

#[inline]
pub unsafe fn __readgsqword(Offset: u64) -> u64 {
    let out: u64;
    llvm_asm!("mov $0, gs:[$1]"
    : "=r"(out)
    : "ri"(Offset)
    :
    : "intel"
    );
    out
}

pub fn hsv_to_rgb(h: f32, mut s: f32, mut v: f32) -> [f32; 3] {
    s /= 100.0;
    v /= 100.0;

    let mut r = 0.0;
    let mut g = 0.0;
    let mut b = 0.0;

    let hi = (h / 60.0) as i32 % 6;
    let f = (h / 60.0) - hi as f32;
    let p = v * (1.0 - s);
    let q = v * (1.0 - s * f);
    let t = v * (1.0 - s * (1.0 - f));

    match hi {
        0 => {
            r = v;
            g = t;
            b = p;
        }
        1 => {
            r = q;
            g = v;
            b = p;
        }
        2 => {
            r = p;
            g = v;
            b = t;
        }
        3 => {
            r = p;
            g = q;
            b = v;
        }
        4 => {
            r = t;
            g = p;
            b = v;
        }
        5 => {
            r = v;
            g = p;
            b = q;
        }
        _ => {}
    }

    [r, g, b]
}

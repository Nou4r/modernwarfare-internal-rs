use std::{mem, ptr};
use std::cell::UnsafeCell;
use std::collections::HashMap;
use std::ops::{Deref, DerefMut};

use log::*;
use std::ffi::CStr;

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

    [r, g ,b]
}

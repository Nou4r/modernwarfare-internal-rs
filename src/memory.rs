use crate::util::{__readgsqword, Global};
use winapi::um::libloaderapi::GetModuleHandleA;
use std::ptr;

pub struct Memory {
    pub peb: u64,
    pub image_base: u64,
}

pub static MEMORY: Global<Memory> = Global::new();

impl Default for Memory {
    fn default() -> Self {
        unsafe {
            Self {
                peb: __readgsqword(0x60),
                image_base: GetModuleHandleA(ptr::null_mut()) as _
            }
        }
    }
}
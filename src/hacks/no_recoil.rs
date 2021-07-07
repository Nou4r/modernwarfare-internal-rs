use std::num::Wrapping;
use crate::util::{read_memory, is_bad_ptr};
use crate::offsets;
use crate::decryption::DECRYPTION;
use crate::config::Config;
use crate::gamedata::GAMEDATA;

extern "C" {
    fn no_recoil_tick(client_base: u64, recoil_offset: u64);
}

pub unsafe fn tick(config: &Config) {
    if !config.no_recoil_enabled {
        return;
    }

    if crate::sdk::gamemode() == 0 {
        return;
    }

    if let Some(client_base) = DECRYPTION.client_base {
        no_recoil_tick(client_base, offsets::RECOIL);
    }
}
//
// unsafe fn no_recoil_tick(client_info_base: u64) {
//     let r12 = Wrapping(client_info_base + offsets::RECOIL);
//     let rsi = r12 + Wrapping(0x4);
//     let edx: Wrapping<u32> = Wrapping(read_memory((r12 + Wrapping(0xC)).0));
//     let mut ecx = edx;
//     ecx = Wrapping(ecx.0 ^ r12.0 as u32);
//     let mut eax = ecx + Wrapping(2);
//     eax *= ecx;
//     ecx = edx;
//     ecx = Wrapping(ecx.0 ^ rsi.0 as u32);
//     let address = r12.0;
//     let val1 = eax.0;
//     eax = ecx + Wrapping(2);
//     eax *= ecx;
//     let val2 = eax.0;
//
//     let mut bytes = [0; 8];
//     bytes[0..=3].clone_from_slice(&val1.to_ne_bytes());
//     bytes[4..=7].clone_from_slice(&val2.to_ne_bytes());
//
//     if is_bad_ptr(address) {
//         log::error!("no_recoil tried to write an invalid address: {:#X}", address);
//         return;
//     }
//     log::trace!("{:?}", std::slice::from_raw_parts(address as *const u8, 8));
//     std::ptr::copy(bytes.as_ptr(), address as _, 8);
//     log::trace!("{:#X}, {:?}", address, bytes);
// }

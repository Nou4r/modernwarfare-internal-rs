use crate::memory::MEMORY;

pub unsafe fn decrypt_clientactive(mut rcx: u64) -> u64 {
    let func = MEMORY.image_base + 0x34E11F0;
    // input is rcx, output is rax
    let mut rax;
    log::info!("rcx = {:#X}", rcx);
    asm!("call {}", in(reg) func, inout("rcx") rcx, out("rax") rax);
    log::info!("rax = {:#X}", rax);
    log::info!("rcx = {:#X}", rcx);
    rax
}
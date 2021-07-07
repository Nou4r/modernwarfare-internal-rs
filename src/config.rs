use crate::util::Global;
use crate::hacks::esp::EspConfig;
use crate::hacks::aimbot::AimbotConfig;

#[derive(Default)]
pub struct Config {
    pub esp: EspConfig,
    pub aimbot: AimbotConfig,
    pub no_recoil_enabled: bool,
}

pub static CONFIG: Global<Config> = Global::new();
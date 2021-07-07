use crate::util::Global;
use crate::hacks::esp::EspConfig;

#[derive(Default)]
pub struct Config {
    pub esp: EspConfig,
    pub no_recoil_enabled: bool,
}

pub static CONFIG: Global<Config> = Global::new();
use crate::util::Global;
use crate::hacks::esp::EspConfig;

#[derive(Default)]
pub struct Config {
    pub esp: EspConfig,
}

pub static CONFIG: Global<Config> = Global::new();
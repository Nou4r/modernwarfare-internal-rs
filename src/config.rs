use crate::util::Global;
use crate::hacks::esp::EspConfig;
use crate::hacks::aimbot::AimbotConfig;
use serde::{Serialize, Deserialize};
use std::fs;

#[derive(Clone, PartialEq, Serialize, Deserialize)]
pub struct Config {
    pub esp: EspConfig,
    pub aimbot: AimbotConfig,
    pub no_recoil_enabled: bool,
    pub watermark: bool,
}

impl Default for Config {
    fn default() -> Self {
        Self {
            no_recoil_enabled: true,
            watermark: true,
            esp: Default::default(),
            aimbot: Default::default(),
        }
    }
}

pub static CONFIG: Global<Config> = Global::new();
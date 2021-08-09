use crate::util::Global;
use crate::hacks::esp::EspConfig;
use crate::hacks::aimbot::AimbotConfig;
use serde::{Serialize, Deserialize};
use std::fs;

#[derive(Serialize, Deserialize)]
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
            aimbot: Default::default()
        }
    }
}

pub static CONFIG: Global<Config> = Global::new();

pub unsafe fn init() {
    // let config = Config::load().unwrap_or_default();
    // config.save();
    // *CONFIG.get_mut() = config;
    CONFIG.init_default();
}

impl Config {
    fn get_config_location() -> String {
        // let mut home = std::env::home_dir().unwrap();
        // home.push("Documents");
        // home.push("config.json");
        // home.to_str().unwrap().to_string()
        "C:/users/Ryan/config.json".to_string()
    }

    pub fn load() -> Option<Self> {
        let data = fs::read(Self::get_config_location()).ok()?;
        serde_json::from_slice(&data).ok()
    }

    pub fn save(&self) {
        fs::write(Self::get_config_location(), serde_json::to_string_pretty(&self).unwrap()).unwrap();
    }
}
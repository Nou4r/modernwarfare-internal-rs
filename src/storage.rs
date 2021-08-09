use crate::util::Global;
use std::path::{Path, PathBuf};
use std::fs;
use serde::{Serialize, Deserialize};
use std::collections::HashMap;
use crate::config::{Config, CONFIG};

#[derive(Clone, Serialize, Deserialize)]
pub struct Storage {
    pub config: Config,
    pub auto_save: bool,
    pub auto_load: bool,
}

impl Default for Storage {
    fn default() -> Self {
        Self {
            config: Default::default(),
            auto_load: true,
            auto_save: true,
        }
    }
}

pub static STORAGE: Global<Storage> = Global::new();

impl Storage {
    fn get_config_location() -> PathBuf {
        let mut base_dir = directories::UserDirs::new().unwrap().document_dir().unwrap().to_owned();
        base_dir.push(lc!("cfg.bin"));
        base_dir
    }

    pub fn load(&mut self) -> Option<()> {
        let data = fs::read(Self::get_config_location()).ok()?;
        *self = serde_json::from_slice(&data).ok()?;
        Some(())
    }

    pub fn save(&self) -> Option<()> {
        let data = serde_json::to_vec_pretty(self).ok()?;
        fs::write(Self::get_config_location(),&data).map_err(|e| { dbg!(&e); e }).ok()?;
        Some(())
    }

    pub fn save_config(&mut self, config: Config) {
        self.config = config;
        self.save();
    }

    pub fn load_config(&mut self) -> Config {
        self.load();
        self.config.clone()
    }
}

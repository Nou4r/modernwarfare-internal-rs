use imgui::*;

use crate::{offsets, sdk};
use crate::cheat::CHEAT;
use crate::config::{Config, CONFIG};
use crate::decryption::DECRYPTION;
use crate::fonts::FONTS;
use crate::gamedata::GAMEDATA;
use crate::memory::MEMORY;
use crate::sdk::Bone;
use crate::util::{Global, keybind_select, read_memory, RenderState, try_read_memory};
use crate::storage::{STORAGE, Storage};

pub static GUI: Global<Gui> = Global::new();

pub struct Gui {
    open: bool,
    debug_open: bool,
    state: RenderState,
    new_config_text: ImString,
}

impl Default for Gui {
    fn default() -> Self {
        Self { open: true, debug_open: false, state: RenderState::new(), new_config_text: ImString::new("") }
    }
}

impl Gui {
    pub unsafe fn render(&mut self, ui: &Ui) {
        let _token = ui.push_font(*FONTS.get().get(&crate::fonts::Font::Verdana).unwrap());

        if crate::DEBUG && self.debug_open {
            self.show_deubg_window(ui);
        }

        if !self.open {
            return;
        }

        let cfg = CONFIG.get_mut();
        let storage = STORAGE.get_mut();
        let old_cfg = cfg.clone();

        self.show_config_window(ui, cfg, storage);

        if storage.auto_save && cfg != &old_cfg {
            storage.save_config(cfg.clone());
        }
    }

    pub fn handle_toggle(&mut self) {
        self.open = !self.open;
    }

    pub fn is_open(&self) -> bool {
        self.open
    }

    fn show_config_window(&mut self, ui: &Ui, cfg: &mut Config, storage: &mut Storage) {
        Window::new(&im_str!("modernwarfare-internal {}", crate::VERSION))
            .size([290.0, 240.0], Condition::FirstUseEver)
            .resizable(false)
            .collapsible(false)
            .build(ui, || {
                TabBar::new(im_str!("primary_tabbar")).build(ui, || {
                    TabItem::new(im_str!("Visuals")).build(ui, || {
                        ui.checkbox(im_str!("ESP"), &mut cfg.esp.enabled);

                        if cfg.esp.enabled {
                            Slider::new(im_str!("Max Distance"))
                                .range(0.0..=1500.0)
                                .display_format(im_str!("%.0fm"))
                                .build(ui, &mut cfg.esp.max_distance);

                            Drag::new(im_str!("Min Players"))
                                .range(0..=155)
                                .speed(0.2)
                                .build(ui, &mut cfg.esp.min_players);

                            let color_edit_flags = ColorEditFlags::NO_INPUTS | ColorEditFlags::NO_LABEL | ColorEditFlags::ALPHA_BAR;

                            ui.columns(2, im_str!("esp_columns"), false);

                            ui.checkbox(im_str!("Box"), &mut cfg.esp.box_enabled);
                            ui.same_line();
                            ColorEdit::new(im_str!("Box Color"), &mut cfg.esp.box_color).flags(color_edit_flags).build(ui);

                            ui.checkbox(im_str!("Box Border"), &mut cfg.esp.border_enabled);
                            ui.same_line();
                            ColorEdit::new(im_str!("Box Border Color"), &mut cfg.esp.border_color).flags(color_edit_flags).build(ui);

                            if !cfg.esp.box_enabled {
                                cfg.esp.border_enabled = false;
                            }

                            ui.checkbox(im_str!("Skeleton"), &mut cfg.esp.skeleton_enabled);
                            ui.same_line();
                            ColorEdit::new(im_str!("Skeleton Color"), &mut cfg.esp.skeleton_color).flags(color_edit_flags).build(ui);

                            ui.checkbox(im_str!("Name"), &mut cfg.esp.name_enabled);
                            ui.same_line();
                            ColorEdit::new(im_str!("Name Color"), &mut cfg.esp.name_color).flags(color_edit_flags).build(ui);

                            ui.checkbox(im_str!("Snapline"), &mut cfg.esp.snapline_enabled);
                            ui.same_line();
                            ColorEdit::new(im_str!("Snapline Color"), &mut cfg.esp.snapline_color).flags(color_edit_flags).build(ui);

                            ui.next_column();
                            ui.checkbox(im_str!("Show Teammates"), &mut cfg.esp.show_teammates);
                            ui.checkbox(im_str!("Align"), &mut cfg.esp.align);
                            ui.checkbox(im_str!("Health"), &mut cfg.esp.health_bar_enabled);
                            ui.checkbox(im_str!("Distance"), &mut cfg.esp.distance_enabled);
                            ui.checkbox(im_str!("Flags"), &mut cfg.esp.flags_enabled);

                            ui.columns(1, im_str!("end_esp_columns"), false);
                        }
                    });
                    TabItem::new(im_str!("Aimbot"))
                        .build(ui, || {
                            ui.columns(2, im_str!("esp_columns"), false);
                            ui.checkbox(im_str!("Enabled"), &mut cfg.aimbot.enabled);
                            if !cfg.aimbot.enabled { ui.columns(1, im_str!("end_esp_columns"), false); }

                            if cfg.aimbot.enabled {
                                ui.checkbox(im_str!("Aim at Teammates"), &mut cfg.aimbot.aim_at_teammates);

                                ui.next_column();
                                ui.checkbox(im_str!("Aim at downed"), &mut cfg.aimbot.aim_at_downed);
                                ui.columns(1, im_str!("end_esp_columns"), false);

                                keybind_select(ui, &mut self.state, im_str!("Aimbot Key"), &mut cfg.aimbot.keybind);

                                // Bone selector
                                let bone_items = [Bone::Head, Bone::Chest, Bone::Tummy];
                                let mut bone_index = bone_items.iter().position(|&b| b == cfg.aimbot.bone).unwrap_or(0);
                                ComboBox::new(im_str!("Bone")).build_simple(
                                    ui,
                                    &mut bone_index,
                                    &bone_items,
                                    &|b| im_str!("{:?}", b).into(),
                                );
                                cfg.aimbot.bone = bone_items[bone_index];

                                Slider::new(im_str!("FOV"))
                                    .range(0.0..=180.0)
                                    .display_format(im_str!("%.1f°"))
                                    .build(ui, &mut cfg.aimbot.fov);

                                Slider::new(im_str!("Speed"))
                                    .range(0.0..=25.0)
                                    .display_format(im_str!("%.1f"))
                                    .build(ui, &mut cfg.aimbot.speed);

                                Slider::new(im_str!("Max Distance"))
                                    .range(0.0..=1500.0)
                                    .display_format(im_str!("%.0fm"))
                                    .build(ui, &mut cfg.aimbot.max_distance);
                                if cfg.aimbot.max_distance > cfg.esp.max_distance {
                                    cfg.aimbot.max_distance = cfg.esp.max_distance;
                                }
                            }
                        });
                    TabItem::new(im_str!("Misc")).build(ui, || {
                        ui.checkbox(im_str!("No Recoil"), &mut cfg.no_recoil_enabled);
                        ui.checkbox(im_str!("Watermark"), &mut cfg.watermark);
                        if crate::DEBUG {
                            ui.checkbox(im_str!("Debug"), &mut self.debug_open);
                        }
                        if ui.button(im_str!("Unload")) {
                            unsafe { crate::unload_cheat(); }
                        }
                    });
                    TabItem::new(im_str!("Config")).build(ui, || {
                        ui.columns(2, im_str!("config_start"), false);

                        if ui.button(im_str!("Save")) {
                            storage.save_config(cfg.clone());
                        }
                        if ui.button(im_str!("Load")) {
                            *cfg = storage.load_config();
                        }
                        if ui.button(im_str!("Default")) {
                            *cfg = Config::default();
                        }

                        ui.next_column();

                        if ui.checkbox(im_str!("Auto Save"), &mut storage.auto_save) {
                            storage.save();
                        }
                        if ui.checkbox(im_str!("Auto Load"), &mut storage.auto_load) {
                            storage.save();
                        }

                        ui.columns(1, im_str!("config_end"), false);
                    });
                })
            });
    }

    unsafe fn show_deubg_window(&mut self, ui: &Ui) {
        Window::new(im_str!("debug"))
            .always_auto_resize(true)
            .build(&ui, || {
                macro_rules! debug {
                    ($x:expr) => {
                        ui.text(im_str!("{}: {:?}", stringify!($x), $x))
                    };
                    ($x:expr, $fmt:literal) => {
                        ui.text(im_str!(concat!("{}: ", $fmt), stringify!($x), $x))
                    };
                }
                macro_rules! debug_hex {
                    ($x:expr) => {
                        ui.text(im_str!("{}: {:#X?}", stringify!($x), $x))
                    };
                }

                debug!(crate::VERSION);
                ui.text(im_str!("Frame Time: {:.2}", CHEAT.last_frame_time.as_secs_f32() * 1000.0));
                debug!(ui.io().want_capture_mouse);
                debug!(ui.io().want_capture_keyboard);
                debug_hex!(MEMORY.image_base);
                debug_hex!(MEMORY.peb);
                ui.text(im_str!("\n"));

                ui.text(im_str!("last_update: {:.1}", DECRYPTION.last_update.elapsed().as_secs_f32()));
                debug_hex!(DECRYPTION.client_info.unwrap_or(0));
                debug_hex!(DECRYPTION.client_base.unwrap_or(0));
                debug_hex!(DECRYPTION.bone_base.unwrap_or(0));
                ui.text(im_str!("\n"));

                debug!(sdk::get_camera().map(|c| c.0));
                debug!(sdk::get_camera().map(|c| c.1));
                debug!(sdk::gamemode());

                let refdef = sdk::get_refdef();
                if let Some(refdef) = refdef {
                    debug!((refdef.width, refdef.height));
                }
                ui.text(im_str!("\n"));

                if DECRYPTION.client_info.is_some() {
                    debug!(sdk::local_index());
                }

                if DECRYPTION.bone_base.is_some() {
                    // debug!(sdk::get_bone_matrix(sdk::local_index()));
                }

                debug!(read_memory::<u32>(MEMORY.image_base + offsets::GAME_MODE));
                debug!(read_memory::<u32>(MEMORY.image_base + offsets::GAME_MODE + 4));
                debug!(read_memory::<u32>(MEMORY.image_base + offsets::GAME_MODE + 8));

                debug!(CHEAT.keys_down);
                debug!(CHEAT.gamedata_history.len());
                if GAMEDATA.valid {
                    debug!(GAMEDATA.players.len());
                    debug!(GAMEDATA.get().local_player().origin);
                    debug!(GAMEDATA.local_player().weapon_index);
                    debug!(sdk::Weapon::from_index(GAMEDATA.local_player().weapon_index));
                }
            });
    }
}
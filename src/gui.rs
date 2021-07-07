use imgui::*;

use crate::cheat::CHEAT;
use crate::config::{Config, CONFIG};
use crate::decryption::DECRYPTION;
use crate::gamedata::GAMEDATA;
use crate::memory::MEMORY;
use crate::sdk;
use crate::util::{Global, RenderState, try_read_memory};
use crate::fonts::FONTS;

pub static GUI: Global<Gui> = Global::new();

pub struct Gui {
    open: bool,
    state: RenderState,
}

impl Default for Gui {
    fn default() -> Self {
        Self { open: true, state: RenderState::new() }
    }
}

impl Gui {
    pub unsafe fn render(&mut self, ui: &Ui) {
        let _token = ui.push_font(*FONTS.get().get(&crate::fonts::Font::Verdana).unwrap());

        if crate::DEBUG {
            self.show_deubg_window(ui);
            crate::show_memory_editor();
        }

        if !self.open {
            return;
        }

        self.show_config_window(ui, CONFIG.get_mut());
    }

    pub fn handle_toggle(&mut self) {
        self.open = !self.open;
    }

    pub fn is_open(&self) -> bool {
        self.open
    }

    fn show_config_window(&mut self, ui: &Ui, cfg: &mut Config) {
        Window::new(&im_str!("modernwarfare-internal {}", crate::VERSION))
            .size([350.0, 250.0], Condition::FirstUseEver)
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

                            let color_edit_flags = ColorEditFlags::NO_ALPHA | ColorEditFlags::NO_LABEL |
                                ColorEditFlags::DISPLAY_HSV | ColorEditFlags::ALPHA_BAR;

                            ui.checkbox(im_str!("Show Teammates"), &mut cfg.esp.show_teammates);
                            ui.checkbox(im_str!("Align"), &mut cfg.esp.align);

                            ui.checkbox(im_str!("Box"), &mut cfg.esp.box_enabled);
                            ui.same_line();
                            ColorEdit::new(im_str!("Box Color"), &mut cfg.esp.box_color).label(false).flags(color_edit_flags).build(ui);

                            ui.checkbox(im_str!("Box Border"), &mut cfg.esp.border_enabled);
                            ui.same_line();
                            ColorEdit::new(im_str!("Box Border Color"), &mut cfg.esp.border_color).label(false).build(ui);

                            ui.checkbox(im_str!("Name"), &mut cfg.esp.name_enabled);
                            ui.same_line();
                            ColorEdit::new(im_str!("Name Color"), &mut cfg.esp.name_color).label(false).build(ui);

                            ui.checkbox(im_str!("Health"), &mut cfg.esp.health_bar_enabled);
                            ui.checkbox(im_str!("Distance"), &mut cfg.esp.distance_enabled);
                            ui.checkbox(im_str!("Flags"), &mut cfg.esp.flags_enabled);
                        }
                    })
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
                debug_hex!(MEMORY.image_base);
                debug_hex!(MEMORY.peb);
                ui.text(im_str!("\n"));

                ui.text(im_str!("last_update: {:.1}", DECRYPTION.last_update.elapsed().as_secs_f32()));
                debug_hex!(DECRYPTION.client_info.unwrap_or(0));
                debug_hex!(DECRYPTION.client_base.unwrap_or(0));
                debug_hex!(DECRYPTION.bone_base.unwrap_or(0));
                ui.text(im_str!("\n"));

                debug!(sdk::get_camera());
                debug!(sdk::gamemode());

                let refdef = sdk::get_refdef();
                if let Some(refdef) = refdef {
                    debug!((refdef.width, refdef.height));
                }
                ui.text(im_str!("\n"));

                if DECRYPTION.client_info.is_some() {
                    debug!(sdk::local_index());
                }

                if GAMEDATA.valid {
                    debug!(GAMEDATA.players.len());
                }
            });
    }
}
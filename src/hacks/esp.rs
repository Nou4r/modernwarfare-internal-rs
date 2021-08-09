use std::cmp::Ordering;

use imgui::ImColor32;
use rand::{RngCore, SeedableRng};

use crate::config::Config;
use crate::fonts::Font;
use crate::gamedata::{Gamedata, GAMEDATA};
use crate::math::{Vector2, Vector3};
use crate::overlay::{ImguiOverlay, TextOptions, TextStyle};
use crate::sdk::{Player, Stance, units_to_m, Bone};
use crate::util::hsv_to_rgb;
use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize)]
pub struct EspConfig {
    pub enabled: bool,
    pub max_distance: f32,
    pub show_teammates: bool,
    pub align: bool,

    pub box_enabled: bool,
    pub box_color: [f32; 4],

    pub border_enabled: bool,
    pub border_color: [f32; 4],

    pub skeleton_enabled: bool,
    pub skeleton_color: [f32; 4],

    pub name_enabled: bool,
    pub name_color: [f32; 4],

    pub snapline_enabled: bool,
    pub snapline_color: [f32; 4],

    pub distance_enabled: bool,
    pub flags_enabled: bool,
    pub health_bar_enabled: bool,
}

impl Default for EspConfig {
    fn default() -> Self {
        Self {
            enabled: true,
            max_distance: 300.0,
            align: true,
            box_enabled: true,
            box_color: ImColor32::WHITE.into(),
            border_enabled: true,
            border_color: [0.0, 0.0, 0.0, 0.75],
            skeleton_enabled: true,
            skeleton_color: [1.0, 1.0, 1.0, 1.0],
            name_enabled: true,
            name_color: ImColor32::WHITE.into(),
            snapline_enabled: false,
            snapline_color: [1.0, 1.0, 1.0, 1.0],
            distance_enabled: true,
            flags_enabled: true,
            health_bar_enabled: true,
            show_teammates: false,
        }
    }
}

pub fn render(gamedata: &Gamedata, overlay: &ImguiOverlay, config: &Config) {
    if !config.esp.enabled {
        return;
    }

    // Filter out players we don't want
    let mut players: Vec<_> = gamedata.players.iter()
        .filter(|p| !p.is_local())
        .filter(|p| config.esp.show_teammates || p.is_enemy())
        .filter(|p| {
            let distance = units_to_m((gamedata.local_player().origin - p.origin).length());
            distance < config.esp.max_distance
        })
        .collect();

    // Sort players so the esp appears in the right order
    players.sort_by(|a, b|
        (b.origin - gamedata.camera_pos).length().partial_cmp(
            &(a.origin - gamedata.camera_pos).length()).unwrap_or(Ordering::Equal));

    for player in players {
        let _ = draw_esp(overlay, player, config, gamedata);
    }
}

fn draw_esp(overlay: &ImguiOverlay, player: &Player, config: &Config, gamedata: &Gamedata) -> Option<()> {
    let mut bbox = player.get_bbox()?;
    if config.esp.align {
        bbox = (bbox.0.round(), bbox.1.round());
    }

    let left_x = bbox.0.x;
    let bottom_y = bbox.0.y;
    let right_x = bbox.1.x;
    let top_y = bbox.1.y;
    let width = right_x - left_x;
    let height = bottom_y - top_y;

    let distance = units_to_m((gamedata.local_player().origin - player.origin).length());

    // Draw border
    if config.esp.border_enabled {
        overlay.draw_list().add_rect(bbox.0.into(), bbox.1.into(), config.esp.border_color).thickness(3.0).build();
    }

    // Draw box
    if config.esp.box_enabled {
        overlay.draw_list().add_rect(bbox.0.into(), bbox.1.into(), config.esp.box_color).build();
    }

    // Draw name
    if config.esp.name_enabled {
        overlay.draw_text(
            Vector2 { x: left_x + (width / 2.0), y: top_y - 15.0 },
            player.name,
            TextOptions::default()
                .color(config.esp.name_color)
                .style(TextStyle::Shadow)
                .font(Font::Verdana)
                .centered_horizontal(true),
        );
    }

    // Draw skeleton
    if config.esp.skeleton_enabled {
        draw_skeleton(overlay, player, config);
    }

    // Draw health bar
    if config.esp.health_bar_enabled {
        let health_color = hsv_to_rgb((player.health as f32 / 127.0) * 120.0, 45.0, 100.0);

        overlay.draw_list().add_rect(
            Vector2 { x: left_x - 6.0, y: bottom_y - 1.0 }.into(), // bottom left
            Vector2 { x: left_x - 2.0, y: top_y + 1.0 }.into(), // top right
            [0.0, 0.0, 0.0, 0.6],
        ).build();
        overlay.draw_list().add_rect(
            Vector2 { x: left_x - 5.0, y: bottom_y - 1.0 }.into(), // bottom left
            Vector2 { x: left_x - 3.0, y: bottom_y + 1.0 - ((height) * (player.health as f32 / 127.0)) }.into(), // top right
            health_color,
        ).filled(true).build();
    }

    if config.esp.snapline_enabled {
        overlay.draw_list().add_line(
            [(gamedata.refdef().width as f32) / 2.0, gamedata.refdef().height as _],
            [left_x + width / 2.0, bottom_y + 2.0],
            config.esp.snapline_color
        ).build();
    }

    // Draw flags
    let mut flag_offset = -3.0;
    let flag_height = 8.0;

    let mut draw_flag = |text: &str, color: [f32; 4]| {
        overlay.draw_text(
            Vector2 { x: right_x + 3.0, y: top_y + flag_offset },
            text,
            TextOptions::default()
                .color(color)
                .style(TextStyle::Outlined)
                .font(Font::Pixel),
        );
        flag_offset += flag_height;
    };

    // Get a unique color for every team
    let mut team_color = ImColor32::from(rand::rngs::SmallRng::seed_from_u64(player.team as u64).next_u32());
    team_color.a = 255;

    // Draw distance
    if config.esp.distance_enabled {
        draw_flag(&format!("{}m", distance.round()), team_color.into());
    }

    // Draw flags
    if config.esp.flags_enabled {
        match player.stance {
            Stance::Crouching => draw_flag("C", ImColor32::from_rgb(31, 156, 219).into()),
            Stance::Crawling => draw_flag("P", ImColor32::from_rgb(219, 147, 31).into()),
            Stance::Downed => draw_flag("D", ImColor32::from_rgb(168, 50, 50).into()),
            _ => {}
        }
    }

    Some(())
}

macro_rules! unwrap_or_continue {
    ( $e:expr ) => {
        match $e {
            Some(x) => x,
            None => continue,
        }
    };
}

pub fn draw_skeleton(overlay: &ImguiOverlay, player: &Player, config: &Config) -> Option<()> {
    for (bone1, bone2) in crate::sdk::BONE_CONNECTIONS {
        let bone1_pos = *unwrap_or_continue!(player.bones.get(bone1));
        let bone2_pos = *unwrap_or_continue!(player.bones.get(bone2));

        let bone1_screen_pos = unwrap_or_continue!(GAMEDATA.world_to_screen(bone1_pos));
        let bone2_screen_pos = unwrap_or_continue!(GAMEDATA.world_to_screen(bone2_pos));

        overlay.draw_list().add_line(bone1_screen_pos.into(), bone2_screen_pos.into(), config.esp.skeleton_color).build();
    }

    let trans = Vector3 { x: 0.0, y: 0.0, z: 4.0 };

    let head1_pos = *player.bones.get(&Bone::Head)?;
    let head2_pos = head1_pos + trans;

    let head1_screen_pos = GAMEDATA.world_to_screen(head1_pos)?;
    let head2_screen_pos = GAMEDATA.world_to_screen(head2_pos)?;

    overlay.draw_list().add_line(head1_screen_pos.into(), head2_screen_pos.into(), config.esp.skeleton_color).build();

    Some(())
}

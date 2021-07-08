use std::collections::VecDeque;
use std::iter::FromIterator;

use winapi::um::winuser::VK_XBUTTON1;

use crate::cheat::CHEAT;
use crate::config::Config;
use crate::gamedata::Gamedata;
use crate::math;
use crate::math::Vector3;
use crate::prediction::{Projectile, run_bullet_drop, run_prediction, Target};
use crate::sdk::{m_to_units, Player, Stance, units_to_m, Bone};
use enigo::MouseControllable;

pub struct AimbotConfig {
    pub enabled: bool,
    pub aim_at_teammates: bool,
    pub max_distance: f32,
    pub bone: Bone,
    pub fov: f32,
    pub speed: f32,
    pub keybind: i32,
    pub aim_at_downed: bool,
    pub scale_speed: bool,
    pub prediction: bool,
}

impl Default for AimbotConfig {
    fn default() -> Self {
        Self {
            enabled: true,
            aim_at_teammates: false,
            bone: Bone::Head,
            max_distance: 400.0,
            fov: 30.0,
            speed: 2.0,
            keybind: VK_XBUTTON1,
            aim_at_downed: false,
            scale_speed: true,
            prediction: true,
        }
    }
}

#[derive(Default)]
pub struct AimbotContext {
    pub mouse_accum: (f32, f32),
}

pub fn tick(gamedata: &Gamedata, config: &Config, ctx: &mut AimbotContext) {
    if !config.aimbot.enabled {
        return;
    }

    if !CHEAT.is_key_down(config.aimbot.keybind) {
        return;
    }

    let target_opt = get_target(gamedata, &config.aimbot, ctx);
    if target_opt.is_none() {
        return;
    }

    let (target, target_pos) = target_opt.unwrap();

    aim_at(gamedata, target_pos, &config.aimbot, ctx);
}

fn aim_at(gamedata: &Gamedata, target: Vector3, config: &AimbotConfig,ctx: &mut AimbotContext) {
    let absolute_delta = math::calculate_relative_angles(&gamedata.camera_pos, &target, &gamedata.camera_angles);

    // info!("Aiming at {}\t({}m)\t({}°)\t({})\t({:?})",
    //       player.name,
    //       units_to_m((target - gamedata.camera_pos).length()),
    //       absolute_delta.length(),
    //       player.health,
    //       player.stance
    // );

    let fov_multiplier = 120.0 / gamedata.get_fov();
    // let tickrate_multiplier = (crate::CHEAT_TICKRATE as f32) / 120.0;
    let tickrate_multiplier = 1.0;
    let speed_multiplier = config.speed;
    let scale = 1.0 / 2.5;

    let multiplier = fov_multiplier * tickrate_multiplier * speed_multiplier;

    let scaled_delta = absolute_delta * (multiplier * scale);

    let dx_f = -scaled_delta.yaw;
    let dy_f = scaled_delta.pitch;

    ctx.mouse_accum.0 += dx_f;
    ctx.mouse_accum.1 += dy_f;

    let dx;
    let dy;

    if ctx.mouse_accum.0 < 1.0 && ctx.mouse_accum.0 > -1.0 {
        dx = 0;
    } else {
        dx = ctx.mouse_accum.0 as _;
    }
    if ctx.mouse_accum.1 < 1.0 && ctx.mouse_accum.1 > -1.0 {
        dy = 0;
    } else {
        dy = ctx.mouse_accum.1 as _;
    }

    ctx.mouse_accum.0 -= dx as f32;
    ctx.mouse_accum.1 -= dy as f32;

    enigo::Enigo::new().mouse_move_relative(dx, dy);
}

/// Gets the position to aim at given a player.
/// This is where prediction should be implemented
fn get_aim_position(player: &Player, gamedata: &Gamedata, config: &AimbotConfig, ctx: &AimbotContext) -> Vector3 {
    let player_history = CHEAT.gamedata_history.iter()
        .filter(|(_, gamedata)| gamedata.player_by_id(player.id).is_some())
        .map(|(instant, gamedata)| (*instant, gamedata.player_by_id(player.id).unwrap().origin))
        .collect::<VecDeque<_>>();
    let target = Target::from_location_history(&player.origin, &player_history);

    let weapon = &gamedata.local_player().weapon;
    let projectile = Projectile{velocity: m_to_units(weapon.velocity), gravity: m_to_units(9.8), source_pos: gamedata.camera_pos};
    // let projectile = Projectile { velocity: 4000.0, gravity: m_to_units(9.8), source_pos: gamedata.camera_pos };

    let pred_pos = run_prediction(&target, &projectile);
    let pred_pos = run_bullet_drop(&pred_pos, &projectile);

    let pred_delta = pred_pos - player.origin;

    player.bones.get(&config.bone).copied().unwrap_or_else(|| match config.bone {
        Bone::Head => player.estimate_head_position(),
        _ => player.estimate_chest_position()
    }) + pred_delta
}


/// Returns the target player and the position to aim at
fn get_target<'a>(gamedata: &'a Gamedata, config: &AimbotConfig, ctx: &AimbotContext) -> Option<(&'a Player, Vector3)> {
    let local = gamedata.local_player();

    gamedata.players.iter().filter_map(|player| {
        if player.id == local.id {
            return None;
        }

        // Ignore downed
        if !config.aim_at_downed && player.stance == Stance::Downed {
            return None;
        }

        // Check team
        if !config.aim_at_teammates && player.is_teammate() {
            return None;
        }

        // Check distance
        let distance = units_to_m((player.origin - local.origin).length());
        if distance > config.max_distance {
            return None;
        }

        // first calculate fov to origin so we don't have to run prediction for every player
        let fov_to_origin = math::calculate_relative_angles(&gamedata.camera_pos, &player.origin, &gamedata.camera_angles).length();
        if fov_to_origin * 1.5 > config.fov {
            return None;
        }

        let aim_position = get_aim_position(&player, &gamedata, config, &ctx);
        let angle = math::calculate_relative_angles(&gamedata.camera_pos, &aim_position, &gamedata.camera_angles).length();
        if angle > config.fov {
            return None;
        }

        Some((player, aim_position, angle, distance))
    })
        .min_by_key(|(player, _, angle, distance)| {
            if player.stance == Stance::Downed {
                i32::MAX
            } else {
                // Combine fov and distance
                (angle + (distance / 100.0) * angle) as i32
            }
        })
        .map(|(player, aim_position, _, _)| (player, aim_position))
}

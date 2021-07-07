use std::mem;

use crate::decryption::DECRYPTION;
use crate::math::{Angles2, radians_to_deg, Vector2, Vector3};
use crate::sdk::{Player, RefDef, Stance};
use crate::sdk;
use crate::util::Global;

#[derive(Default)]
pub struct Gamedata {
    pub valid: bool,
    pub players: Vec<Player>,
    pub local_index: u32,
    pub camera_pos: Vector3,
    pub camera_angles: Angles2,
    pub local_team: i32,
    refdef: Option<&'static RefDef>,
}

pub static GAMEDATA: Global<Gamedata> = Global::new();

impl Gamedata {
    pub fn world_to_screen(&self, world_pos: Vector3) -> Option<Vector2> {
        let refdef = self.refdef.unwrap();
        sdk::world_to_screen_internal(
            world_pos,
            self.camera_pos,
            refdef.width,
            refdef.height,
            refdef.view.tan_half_fov,
            refdef.view.axis,
        )
    }

    pub fn get_fov(&self) -> f32 {
        radians_to_deg(f32::atan(self.refdef.unwrap().view.tan_half_fov.length()) * 2.0)
    }

    pub fn player_by_id(&self, id: u32) -> Option<&Player> {
        self.players.iter().find(|p| p.id == id)
    }

    pub fn local_player(&self) -> &Player {
        self.player_by_id(self.local_index).unwrap()
    }
}

// Should be ran every tick
impl Gamedata {
    pub unsafe fn update(&mut self) {
        self.valid = false;

        if !sdk::in_game() || !DECRYPTION.valid() {
            return;
        }

        sdk::get_players(&mut self.players);
        if self.players.is_empty() {
            return;
        }

        self.local_index = sdk::local_index();

        (self.camera_pos, self.camera_angles) = match sdk::get_camera() {
            Some(n) => n,
            None => {
                return;
            }
        };

        let refdef = match sdk::get_refdef() {
            Some(n) => n,
            None => {
                return;
            }
        };
        self.refdef = Some(refdef);

        self.local_team = self.local_player().team;

        self.valid = true;
    }
}

impl Player {
    pub fn is_local(&self) -> bool {
        self.id == GAMEDATA.local_index
    }

    pub fn is_teammate(&self) -> bool {
        self.team == GAMEDATA.local_team
    }

    pub fn is_enemy(&self) -> bool {
        !self.is_teammate()
    }

    pub fn get_bbox(&self) -> Option<(Vector2, Vector2)> {
        let head_pos = self.estimate_head_position();
        let head_pos = GAMEDATA.world_to_screen(head_pos + Vector3 { x: 0.0, y: 0.0, z: 10.0 })?;
        let feet_pos = GAMEDATA.world_to_screen(self.origin)?;

        let height = feet_pos.y - head_pos.y;
        let width = match self.stance {
            Stance::Standing => height / 4.0,
            Stance::Crouching => height / 2.5,
            Stance::Downed => height * 2.0,
            Stance::Crawling => height * 2.5,
        };

        let size = 1.0;

        let left_x = feet_pos.x - width - size;
        let right_x = feet_pos.x + width + size;
        let top_y = head_pos.y - size;
        let bottom_y = feet_pos.y + size;

        Some((
            Vector2 { x: left_x, y: bottom_y },
            Vector2 { x: right_x, y: top_y }
        ))
    }
}
use crate::sdk::*;
use crate::math::Vector3;
use crate::util::{try_read_memory, read_memory, is_bad_ptr, str_from_ptr};
use log::*;
use std::collections::HashMap;

#[derive(Debug, Clone)]
pub struct Player {
    pub name: &'static str,
    pub battle_tag: &'static str,
    pub origin: Vector3,
    pub team: i32,
    pub id: u32,
    pub stance: Stance,
    pub health: i32,
    pub base_address: u64,
    pub visible: bool,
    pub weapon_index: usize,
    // pub weapon: Weapon,
    pub bones: HashMap<Bone, Vector3>
}

impl Player {
    pub unsafe fn new(base_address: u64, index: u32) -> Option<Self> {
        use offsets::player;

        let valid: i32 = try_read_memory(base_address + player::VALID).unwrap_or_else(|| {
            error!("Could not read player address");
            0
        });
        if valid != 1 {
            return None;
        }

        let position_address: u64 = read_memory(base_address + player::POS);
        if is_bad_ptr(position_address) {
            return None;
        }

        let origin: Vector3 = read_memory(position_address + 0x40);
        if origin.is_zero() {
            return None;
        }

        let dead_1: i32 = read_memory(base_address + player::DEAD_1);
        if dead_1 != 0 {
            return None;
        }

        let dead_2: i32 = read_memory(base_address + player::DEAD_2);
        if dead_2 != 0 {
            return None;
        }

        let stance: Stance = read_memory(base_address + player::STANCE);
        let team: i32 = read_memory(base_address + player::TEAM);
        // let ads = read_memory::<i32>(base_address + player::ADS) == 1;
        // let reloading = read_memory::<i32>(base_address + player::RELOAD) == 121;

        let name_struct = get_name_struct(index as u32)?;
        if name_struct.health <= 0 {
            return None;
        }
        let name = str_from_ptr(name_struct.name.as_ptr()).unwrap_or_default();
        let battle_tag = str_from_ptr(name_struct.battle_tag.as_ptr()).unwrap_or_default();
        let health = name_struct.health;

        let weapon_index = read_memory(base_address + player::WEAPON_INDEX);
        // let weapon_index = 0;
        // let weapon = Weapon::from_index(weapon_index).unwrap_or_else(|| {
        //     error!("Could not get Weapon index {} for player {}", weapon_index, name);
        //     Weapon::from_index(0).unwrap()
        // });

        let bones = crate::sdk::get_bone_matrix(index)
            .unwrap_or_else(HashMap::new)
            .into_iter()
            .filter(|(_, pos)| (origin - pos).length() < m_to_units(3.0))
            .collect();

        Some(Self {
            origin,
            id: index,
            team,
            name,
            battle_tag,
            stance,
            health,
            base_address,
            // weapon,
            weapon_index,
            bones,
            visible: true,
        })
    }
}

impl Player {
    pub fn estimate_head_position(&self) -> Vector3 {
        let delta_z = match self.stance {
            Stance::Standing => 58.0,
            Stance::Crouching => 40.0,
            Stance::Crawling => 10.0,
            Stance::Downed => 20.0,
        };
        self.origin + Vector3 { x: 0.0, y: 0.0, z: delta_z }
    }

    pub fn estimate_chest_position(&self) -> Vector3 {
        let delta_z = match self.stance {
            Stance::Standing => 58.0,
            Stance::Crouching => 40.0,
            Stance::Crawling => 10.0,
            Stance::Downed => 20.0,
        };
        self.origin + Vector3 { x: 0.0, y: 0.0, z: delta_z * 0.7 }
    }
}
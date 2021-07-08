use std::collections::{HashMap, HashSet};

use Bone::*;

use crate::decryption::{DECRYPTION, Decryption};
use crate::math::Vector3;
use crate::memory::MEMORY;
use crate::offsets::bone;
use crate::util::{Global, read_memory};

#[repr(u32)]
#[derive(PartialEq, Debug, Clone, Copy, Hash, Eq)]
pub enum Bone {
    Head = 7,
    Neck = 6,
    Chest = 5,
    Mid = 4,
    Tummy = 3,

    RightFoot1 = 21,
    RightFoot2 = 22,
    RightFoot3 = 23,
    RightFoot4 = 24,

    LeftFoot1 = 17,
    LeftFoot2 = 18,
    LeftFoot3 = 19,
    LeftFoot4 = 20,

    LeftHand1 = 13,
    LeftHand2 = 14,
    LeftHand3 = 15,
    LeftHand4 = 16,

    RightHand1 = 9,
    RightHand2 = 10,
    RightHand3 = 11,
    RightHand4 = 12,
}

// Bone connections for a skeleton ESP
pub static BONE_CONNECTIONS: &[(Bone, Bone)] = &[
    (Head, Neck),
    (Neck, Chest),
    (Chest, Mid),
    (Mid, Tummy),
    (Tummy, LeftFoot1),
    (LeftFoot1, LeftFoot2),
    (LeftFoot2, LeftFoot3),
    (LeftFoot3, LeftFoot4),
    (Tummy, RightFoot1),
    (RightFoot1, RightFoot2),
    (RightFoot2, RightFoot3),
    (RightFoot3, RightFoot4),
    (Neck, LeftHand1),
    (LeftHand1, LeftHand2),
    (LeftHand2, LeftHand3),
    (LeftHand3, LeftHand4),
    (Neck, RightHand1),
    (RightHand1, RightHand2),
    (RightHand2, RightHand3),
    (RightHand3, RightHand4),
];

static ALL_BONES: Global<HashSet<Bone>> = Global::new();

pub unsafe fn get_bone_matrix(index: u32) -> Option<HashMap<Bone, Vector3>> {
    let mut bones = HashMap::new();

    let base_pos: Vector3 = read_memory(DECRYPTION.client_info? + bone::BASE_POS);
    let bone_base = DECRYPTION.bone_base?;

    let bone_ptr = {
        let bone_index = Decryption::bone_index(index as _);

        let bone_ptr: u64 = read_memory(bone_base + (bone_index * bone::INDEX_STRUCT_SIZE as u64) + 0xC0);

        bone_ptr
    };
    if bone_ptr == 0 {
        // log::trace!("bone_ptr was 0");
        return None;
    }

    for &bone in ALL_BONES.get_or_init(|| {
        BONE_CONNECTIONS.iter()
            .flat_map(|(a, b)| std::array::IntoIter::new([*a, *b]).collect::<Vec<_>>())
            .collect()
    }) {
        let bone_pos: Vector3 = read_memory(bone_ptr as u64 + (bone as u64 * 0x20) + 0x10);
        if bone_pos.is_zero() {
            continue;
        }
        bones.insert(bone, bone_pos + base_pos);
    }

    Some(bones)
}

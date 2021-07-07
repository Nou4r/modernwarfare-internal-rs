#![allow(non_camel_case_types, dead_code)]

use crate::math::{Vector2, Vector3};


#[repr(i32)]
#[derive(Copy, Clone, Debug, PartialEq)]
pub enum Stance {
    Standing = 0,
    Crouching = 1,
    Crawling = 2,
    Downed = 3,
}

impl ToString for Stance {
    fn to_string(&self) -> String {
        String::from(match self {
            Stance::Standing => "Standing",
            Stance::Crouching => "Crouching",
            Stance::Crawling => "Crawling",
            Stance::Downed => "Downed",
        })
    }
}

#[repr(C)]
pub struct NameInfo
{
    pub entity_index: u32,
    pub name: [u8; 0x24],
    pub battle_tag: [u8; 0x24],
    unk2: [u8; 0x40],
    pub health: i32,
}

#[repr(C)]
#[derive(Clone, Debug, Copy)]
pub struct RefdefView {
    pub tan_half_fov: Vector2,
    unk6: [u8; 0xC],
    pub axis: [Vector3; 3],
}

#[repr(C)]
#[derive(Clone, Debug, Copy)]
pub struct RefDef {
    pub x: i32,
    pub y: i32,
    pub width: i32,
    pub height: i32,
    pub view: RefdefView,
}

use crate::memory::MEMORY;
use crate::offsets;
use crate::util::Global;

/*
pub struct Funcs {
    pub dvar_setbool: extern "fastcall" fn(dvar_ptr: u64, value: bool),
}

pub static FUNCS: Global<Funcs> = Global::new();
*/

/*
impl Default for Funcs {
    fn default() -> Self {
        Self {
            dvar_setbool: unsafe { std::mem::transmute(MEMORY.image_base + offsets::funcs::DVAR_SETBOOL) }
        }
    }
}

impl Funcs {
    pub unsafe fn set_uav(&self, enabled: bool) {
        (self.dvar_setbool)(MEMORY.image_base + offsets::funcs::DVAR_UAV, enabled);
    }
}
*/


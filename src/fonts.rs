use std::collections::HashMap;

use imgui::*;
use imgui::internal::RawCast;

use crate::util::Global;

pub static FONTS: Global<HashMap<Font, FontId>> = Global::new();

pub unsafe fn init_fonts(ctx: &mut Context, font_scale: f32) {
    let mut fonts = HashMap::new();

    let mut atlas = ctx.fonts();

    // First font is default
    fonts.insert(
        Font::Default,
        atlas.add_font(&[FontSource::DefaultFontData {
                config: Some(FontConfig {
                    size_pixels: (13.0 * font_scale),
                    ..Default::default()
                })
            }]),
    );
    fonts.insert(
        Font::Pixel,
        atlas.add_font(&[FontSource::TtfData {
            data: include_bytes!("../fonts/smallest_pixel-7.ttf"),
            size_pixels: 10.0 * font_scale,
            config: None,
        }]),
    );
    fonts.insert(
        Font::Verdana,
        atlas.add_font(&[FontSource::TtfData {
            data: include_bytes!("../fonts/Verdana.ttf"),
            size_pixels: 13.0 * font_scale,
            config: None,
        }]),
    );
    fonts.insert(
        Font::Tahoma,
        atlas.add_font(&[FontSource::TtfData {
            data: include_bytes!("../fonts/Tahoma.ttf"),
            size_pixels: 14.0 * font_scale,
            config: None,
        }]),
    );
    fonts.insert(
        Font::Tahoma,
        atlas.add_font(&[FontSource::TtfData {
            data: include_bytes!("../fonts/undefined-medium.ttf"),
            size_pixels: 10.0 * font_scale,
            config: None,
        }]),
    );

    FONTS.init(fonts);
}

#[derive(Debug, Clone, Hash, Eq, PartialEq)]
pub enum Font {
    Default,
    Pixel,
    Tahoma,
    Verdana,
    Undefined,
}

use imgui::*;
use imgui::sys::ImColor;

use crate::fonts::FONTS;
use crate::util::read_memory;

/// Represents a frame that be can be drawn on
pub struct ImguiOverlay<'a, 'ui> {
    pub ui: &'a Ui<'ui>,
    style_tokens: Vec<StyleStackToken<'ui>>,
    color_token: ColorStackToken<'ui>,
    window_token: WindowToken<'ui>,
}

impl<'a: 'ui, 'ui> ImguiOverlay<'a, 'ui> {
    /// Creates a frame from a context
    pub fn begin(
        ui: &'a imgui::Ui<'ui>,
    ) -> Self {
        let mut style_tokens = Vec::new();
        style_tokens.push(ui.push_style_var(StyleVar::WindowBorderSize(0.0)));
        style_tokens.push(ui.push_style_var(StyleVar::WindowPadding([0.0, 0.0])));
        let color_token = ui.push_style_color(StyleColor::WindowBg, [0.0, 0.0, 0.0, 0.0]);
        let window_token = Window::new(im_str!("##overlay"))
            .flags(WindowFlags::NO_TITLE_BAR | WindowFlags::NO_INPUTS)
            .position([0.0, 0.0], Condition::Always)
            .size(ui.io().display_size, Condition::Always)
            .begin(&ui).unwrap();
        Self { ui, style_tokens, color_token, window_token }
    }

    pub fn build(
        ui: &'a imgui::Ui<'ui>,
        run: impl FnOnce(&ImguiOverlay),
    ) {
        let window = Self::begin(ui);
        run(&window);
        window.end();
    }

    pub fn end(self) {
        self.window_token.end();
        self.style_tokens.into_iter().for_each(|t| t.pop());
        self.color_token.pop();
    }
}

impl ImguiOverlay<'_, '_> {
    pub fn draw_list(&self) -> DrawListMut {
        self.ui.get_window_draw_list()
    }

    pub fn draw_text(&self, origin: impl Into<[f32; 2]>, text: &str, options: TextOptions) {
        let mut origin = origin.into();

        let font = *FONTS.get().get(&options.font).unwrap();

        // log::debug!("asd = {}", unsafe { read_memory::<u8>(font.unwrap() as *const _ as _) });

        // let font_token = self.ui.push_font(font);
        // font_token.pop();

        let text = unsafe { ImStr::from_ptr_unchecked(ImString::new(text).as_ptr()) };

        let x = match options.centered_horizontal {
            false => origin[0],
            true => origin[0] - (self.ui.calc_text_size(text)[0] / 2.0),
        };
        let y = match options.centered_vertical {
            false => origin[1],
            true => origin[1] - (self.ui.calc_text_size(text)[0] / 2.0),
        };

        let draw_list = self.draw_list();

        let draw = |color, offset: (f32, f32)| {
            draw_list.add_text([x + offset.0, y + offset.1], color, text);
        };

        let shadow_color = options.shadow_color;
        match options.style {
            TextStyle::Shadow => {
                draw(shadow_color, (1.0, 1.0));
            }
            TextStyle::Outlined => {
                draw(shadow_color, (1.0, 1.0));
                draw(shadow_color, (1.0, -1.0));
                draw(shadow_color, (-1.0, 1.0));
                draw(shadow_color, (-1.0, -1.0));
                draw(shadow_color, (0.0, 1.0));
                draw(shadow_color, (0.0, -1.0));
                draw(shadow_color, (1.0, 0.0));
                draw(shadow_color, (-1.0, 0.0));
            }
            TextStyle::None => {}
        }

        draw(options.color, (0.0, 0.0));

        // font_token.pop();
    }
}

#[derive(Debug, Clone)]
pub struct TextOptions {
    pub color: ImColor32,
    pub font: Font,
    pub centered_horizontal: bool,
    pub centered_vertical: bool,
    pub style: TextStyle,
    pub shadow_color: ImColor32,
}

impl Default for TextOptions {
    fn default() -> Self {
        Self {
            color: ImColor32::WHITE,
            font: Font::Verdana,
            centered_horizontal: false,
            centered_vertical: false,
            style: TextStyle::Shadow,
            shadow_color: ImColor32::from_rgba(20, 20, 20, 150),
        }
    }
}

macro_rules! generate_setter {
    ($member_name:ident: $setter_type:ty) => {
        pub fn $member_name(mut self, $member_name: $setter_type) -> Self {
            self.$member_name = $member_name.into();
            self
        }
    };
}

impl TextOptions {
    pub fn color(mut self, color: impl Into<ImColor32>) -> Self {
        self.color = color.into();
        self.shadow_color.a = self.color.a;
        self
    }
    generate_setter!(font: Font);
    generate_setter!(centered_horizontal: bool);
    generate_setter!(centered_vertical: bool);
    generate_setter!(style: TextStyle);
    generate_setter!(shadow_color: impl Into<ImColor32>);
}

#[derive(Debug, Clone)]
pub enum TextStyle {
    None,
    Shadow,
    Outlined,
}

#[derive(Debug, Clone, Hash, Eq, PartialEq)]
pub enum Font {
    Default,
    Pixel,
    Tahoma,
    Verdana,
    Undefined,
}
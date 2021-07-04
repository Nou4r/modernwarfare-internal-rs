//
// Created by draven on 7/3/2021.
//

#pragma once

#include "interop.h"
#include "Cheat.h"
#include "imgui.h"

extern "C" void on_load();
extern "C" void on_imgui_init(ImGuiContext*);
extern "C" void on_frame(ImGuiContext*);
extern "C" void on_input_event(std::int32_t input_type, std::uint32_t key);

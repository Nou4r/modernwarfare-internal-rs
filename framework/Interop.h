// ReSharper disable CppInconsistentNaming
#pragma once

#include <cstdint>
#include <imgui.h>

namespace interop {
	extern "C" void on_load();
	extern "C" void on_imgui_init(ImGuiContext*);
	extern "C" void on_frame(ImGuiContext*);
	extern "C" void on_input_event(int32_t input_type, uint32_t key);
}

// ReSharper disable CppInconsistentNaming
#pragma once

#include <cstdint>
#include <imgui.h>

namespace interop {
	extern "C" inline void on_load() {}
	extern "C" inline void on_imgui_init(ImGuiContext*) {}
	extern "C" inline void on_frame(ImGuiContext*) {}
	extern "C" inline void on_input_event(int32_t input_type, uint32_t key) {}

	extern "C" inline void unload_cheat()
	{
		framework->unload();
	}
}

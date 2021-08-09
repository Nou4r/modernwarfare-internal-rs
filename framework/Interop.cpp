#include "Framework.h"
#include "Syscall.h"

namespace interop {
	extern "C" void unload_cheat()
	{
		framework->unload();
	}

	extern "C" uint32_t move_mouse_relative(int32_t dx, int32_t dy)
	{
		INPUT input = {};

		input.type = INPUT_MOUSE;
		input.mi.dx = dx;
		input.mi.dy = dy;
		input.mi.dwFlags = MOUSEEVENTF_MOVE;
		return Syscall_SendInput(input);
	}
}

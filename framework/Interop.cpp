#include "Framework.h"

namespace interop {
	extern "C" void unload_cheat()
	{
		framework->unload();
	}

	extern "C" uint32_t move_mouse_relative(int32_t dx, int32_t dy)
	{
		// TODO
		return 0;
	}
}

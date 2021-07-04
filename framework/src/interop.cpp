#include "interop.h"

extern "C" void unload_cheat() {
    cheat->unload();
}

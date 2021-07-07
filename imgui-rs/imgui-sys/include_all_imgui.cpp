// This improves build speed by only compiling a single file, and performance by
// allowing the optimizer to inline across separate object files (note that even
// when rust is built with LTO, unless the steps are taken to allow cross-lang
// LTO (tricky), the C/C++ code won't be LTOed).
#include "../../imgui/imgui.cpp"
#include "../../imgui/imgui_demo.cpp"
#include "../../imgui/imgui_draw.cpp"
#include "../../imgui/imgui_widgets.cpp"
#include "../../imgui/imgui_tables.cpp"
#include "third-party/cimgui.cpp"



cmake_minimum_required(VERSION 3.19)
project(modernwarfare_internal)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/*.h"
#        "${CMAKE_SOURCE_DIR}/../imgui/*.cpp"
        )

include_directories(
        src
        ../imgui
)

add_library(framework STATIC ${SOURCES} ../imgui/imgui_impl_win32.cpp ../imgui/imgui_impl_dx12.cpp src/Gui.cpp src/Gui.h)

install(TARGETS framework DESTINATION .)
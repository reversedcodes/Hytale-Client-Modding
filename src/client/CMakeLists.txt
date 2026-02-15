project(client)

include(FetchContent)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking
)
FetchContent_MakeAvailable(imgui)

set(IMGUI_DIR ${imgui_SOURCE_DIR})

add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_win32.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/backends)

FetchContent_Declare(
    minhook
    GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
    GIT_TAG master
)

FetchContent_MakeAvailable(minhook)

add_library(client SHARED
    Dllmain.cc
    Runtime.cc

    common/utils/Terminal.cc
    common/utils/Memory.cc
    common/utils/ProcessHelper.cc

    sdk/abi/GDI32.cc

    core/Client.cc

    core/module/modules/visual/ImGuiModule.cc
    core/module/modules/dev/ConsoleModule.cc
    core/module/modules/settings/EjectModule.cc
)

target_include_directories(client PRIVATE ../)

target_link_libraries(client PRIVATE
    hytale::header
    psapi
    opengl32
    gdi32
    imgui
    minhook
)

target_include_directories(client PRIVATE ./)

target_compile_definitions(client PRIVATE NOMINMAX)
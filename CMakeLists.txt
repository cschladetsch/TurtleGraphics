cmake_minimum_required(VERSION 3.16)
set(proj_name turtle)
project(${proj_name})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

# these for MSVC
#add_compile_options(/DTURTLE_UNIT_TESTS)
#add_compile_options(/std:c++latest)

#add_compile_options(-std=c++17)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-std=c++20>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-stdlib=libc++>)


# Add SDL
set(SDL_ROOT "External/SDL2-2.0.12")
#set(BUILD_SHARED_LIBS OFF)
add_subdirectory(${SDL_ROOT})

# Add Boost
#set(BOOST_ROOT "c:\\Boost\\boost_1_73_0")
#set(Boost_USE_STATIC_LIBS ON)
#find_package(Boost 1.5 REQUIRED COMPONENTS filesystem)

include_directories("Include")

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "Source/*.cpp")
file(GLOB_RECURSE tests CONFIGURE_DEPENDS "Tests/*.cpp")

add_executable(${proj_name} ${sources} ${tests})
set(Win64_libs
    winmm.lib
    version.lib
    Imm32.lib
    Setupapi.lib
    kernel32.lib
    user32.lib
    gdi32.lib
    gdi32.lib
    winspool.lib
    shell32.lib
    ole32.lib
    oleaut32.lib
    uuid.lib
    comdlg32.lib
    advapi32.lib
)
#target_link_libraries(${proj_name} PUBLIC Boost::filesystem ${Win64_libs} SDL2)
target_link_libraries(${proj_name} PUBLIC ${Win64_libs} SDL2)


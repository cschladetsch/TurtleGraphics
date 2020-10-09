cmake_minimum_required(VERSION 3.17)
set(proj_name turtle)
project(${proj_name})

add_compile_options(/std:c++latest)

# SDL
set(SDL "External\\SDL2-2.0.12")
#set(SDL_Output ${PROJECT_SOURCE_DIR}\\${SDL}\\build\\Debug)
#set(SDL_Main ${SDL_Output}\\SDL2maind.lib)
#set(SDL_Static ${SDL_Output}\\SDL2-staticd.lib)
#message(STATUS ${SDL_Main})
#message(STATUS ${SDL_Static})
#set(SDL_Libs ${SDL_Main} ${SDL_Static})
add_subdirectory(${SDL})


set(BOOST_ROOT "c:\\Boost\\boost_1_73_0")
set(Boost_USE_STATIC_LIBS ON)

find_package(Boost 1.5 REQUIRED COMPONENTS filesystem)

include_directories(Include)
#include_directories(External/SDL2-2.0.12/include)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "Source/*.cpp")


add_executable(${proj_name} ${sources})

set(Win64_libs
        winmm.lib
        version.lib
        Imm32.lib
       	Setupapi.lib
        kernel32.lib
        user32.lib
        gdi32.lib
        winspool.lib
        comdlg32.lib
        advapi32.lib
        shell32.lib
        ole32.lib
        oleaut32.lib
        uuid.lib
        odbc32.lib
        odbccp32.lib
)

target_link_libraries(${proj_name} PUBLIC Boost::filesystem ${Win64_libs} SDL2)


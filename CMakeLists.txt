
cmake_minimum_required(VERSION 4.2)

project(jaminpp
    VERSION 0.98.9
    LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 90)
set(CMAKE_CXX_STANDARD 20)

option(JAMINPP_FFT_DOUBLE "Enable double precision fourier transform" OFF)

option(JAMINPP_OSC "Build with Open Sound Control interface" ON)

option(JAMINPP_LANG "Build with translations" ON)


option(JAMINPP_GTK4 "Build for Gtk4 (Default: Gtk3)" OFF)

option(JAMINPP_ADW "Link with libadwaita (requires JAMINPP_GTK4 on some hosts)" ${JAMINPP_GTK4})

option(BUILD_TESTING "Build tests" ON)

if(JAMINPP_GTK4)
    set(CACHE{JAMINPP_GTKMM_MODULE} TYPE INTERNAL VALUE gtkmm-4.0)
else()
    set(CACHE{JAMINPP_GTKMM_MODULE} TYPE INTERNAL VALUE gtkmm-3.0)
endif()

include(GNUInstallDirs)

if(JAMINPP_LANG)
    find_package(Gettext REQUIRED)
    find_program(GETTEXT_BIN xgettext)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/xlate.cmake)

## data files

set(CACHE{JAMINPP_SVG_FILES} TYPE INTERNAL VALUE)

function(jamin_add_icon svg_file)
    file(REAL_PATH ${svg_file} rl)
    list(APPEND JAMINPP_SVG_FILES ${rl})
endfunction()

add_subdirectory(data)


## compiled sources

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/module_chk.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/gresource.cmake)

set(CACHE{JAMINPP_RESOURCE_C} TYPE INTERNAL
  VALUE ${CMAKE_CURRENT_BINARY_DIR}/src/gen/${CMAKE_PROJECT_NAME}_resource.c)

add_resource_file(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}_resource
    ${JAMINPP_RESOURCE_C}
    src/jam.ui
    pixmaps/about_image.png
    pixmaps/brushed-steel.png
    pixmaps/JAMin_icon.xpm
    pixmaps/LED_green_off.xpm
    pixmaps/LED_green_on.xpm
    pixmaps/LED_red.xpm
    pixmaps/LED_yellow.xpm
    pixmaps/pause1.png
    pixmaps/play1.png
    pixmaps/thai-gold-knobs.png
    pixmaps/thai-gold.png
)

add_subdirectory(src)
add_subdirectory(controller)

## examples
add_subdirectory(examples)

## language files (gettext)
if(JAMINPP_LANG)
    add_subdirectory(po)
endif()

if(BUILD_TESTING)
    find_package(Catch2 3 CONFIG QUIET)
    if(NOT Catch2_FOUND)
        message(STATUS "BUILD_TESTING is defined but Catch2 version 3 was not found. Adding dependency with FetchContent")
        include(FetchContent)
        FetchContent_Declare(Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG        v3.15.2
        )
        FetchContent_MakeAvailable(Catch2)
    endif()
    include(Catch)

    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_catch_test.cmake)
    add_subdirectory(test/src)
endif()

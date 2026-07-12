
cmake_minimum_required(VERSION 4.2)

project(jaminpp
    VERSION 0.98.9
    LANGUAGES C CXX
)

set(C_STANDARD 90)
set(CXX_STANDARD 20)

option(JAMINPP_FFT_DOUBLE "Enable double precision fourier transform" OFF)

option(JAMINPP_OSC "Build with Open Sound Control interface" ON)

option(JAMINPP_LANG "Build with translations" ON)

option(JAMINPP_INSTALL "Build for Jamin++ installation" ON)

option(JAMINPP_GTK4 "Build for Gtk4 (else Gtk3)" OFF)

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

if(${JAMINPP_INSTALL})

    set(CACHE{JAMINPP_SVG_FILES} TYPE INTERNAL VALUE)

    function(jamin_add_icon svg_file)
        file(REAL_PATH ${svg_file} rl)
        list(APPEND JAMINPP_SVG_FILES ${rl})
    endfunction()

    add_subdirectory(data)
endif() # JAMINPP_INSTALL

## compiled sources

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/module_chk.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/gresource.cmake)

add_resource_file(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}_resource
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

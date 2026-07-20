
include(${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/cmake/gresource.cmake)


# build dependency (Fedora 44): one of
# - pipewire-jack-audio-connection-kit-devel
# - jack-audio-connection-kit-devel
module_chk(JACK jack>=0.124.0)

if(JAMINPP_FFT_DOUBLE)
    module_chk(FFTW fftw3>=3.0)
else()
    module_chk(FFTW fftw3f>=3.0)
    set(_FFT_EXECUTE fftwf_execute)
endif()
set(HAVE_FFTW_DOUBLE ${JAMINPP_FFT_DOUBLE})


module_chk(XML libxml-2.0>=2.0)

if(JAMNIN_OSC)
    # building jack-scene
    module_chk(OSC liblo>=0.5)
endif()

# using dependencies for glibmm, glib, gtk, ... via gtkmm
module_chk(GTKMM ${JAMINPP_GTKMM_MODULE})

if(JAMINPP_ADW)
    module_chk(ADW libadwaita-1)
endif()
# for config.h
set(HAVE_ADW ${JAMINPP_ADW})

set(FILTER_TUNING ${JAMINPP_FILTER_TUNING})
#
# set local variables for config.h
#

if(${JAMINPP_FFT_DOUBLE})
    set(JAMINPP_FFTW_TYPE double)
else()
    set(JAMINPP_FFTW_TYPE float)
endif()

set(HAVE_OSC ${JAMINPP_OSC})

# generate config.h
configure_file(config.h.in gen/config.h @ONLY)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/gen)

# using GNUInstallDirs
add_compile_definitions(
    PACKAGE_DATA_DIR="${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}"
    PACKAGE_LOCALE_DIR="${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/locale"
    PACKAGE_LIB_DIR="${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}"
    VERSION="${CMAKE_PROJECT_VERSION}"
    PACKAGE="${CMAKE_PROJECT_NAME}"
)

if(JAMINPP_LANG)
    add_compile_definitions(GETTEXT_PACKAGE=${CMAKE_PROJECT_NAME})
    # for config.h
    set(ENABLE_NLS ${JAMINPP_LANG})
endif()


#
# objects
#

add_library(jamui
    gtkmeter.c
    gtkmeterscale.c
   ${JAMINPP_RESOURCE_C}
    jamui.cpp
)
target_link_libraries(jamui PUBLIC
    PkgConfig::GTKMM
)

add_executable(jaminpp
    main.cpp
)
target_link_libraries(jaminpp
    PRIVATE PkgConfig::GTKMM jamui
)
if(JAMINPP_ADW)
    target_link_libraries(jaminpp PRIVATE PkgConfig::ADW)
endif()


add_library(hnopt STATIC
    ## from libnopt_a_SOURCES, Makefile.am
    interface.c # interface.h
)

target_link_libraries(hnopt PUBLIC PkgConfig::GTKMM)

add_executable(jamin
    ## from jamin_SOURCES, Makefile.am
    callbacks.c # callbacks.h callbacks_help.h
    # compressor.h
    compressor-ui.c # compressor-ui.h
    # constants.h
    # db.h
    # debug.h
    # ladspa.h
    geq.c # geq.h
    gtkmeter.c # gtkmeter.h
    hdeq.c # hdeq.h
    intrim.c # intrim.h
    io.c # io.h
    io-menu.c # io-menu.h
    # jackstatus.h
    # limiter.h
    limiter-ui.c # limiter-ui.h
    presets-ui.c # presets-ui.h
    main.c # main.h
    multiout-ui.c # multiout-ui.h
    plugin.c # plugin.h
    process.c # process.h
    resource.c # resource.h
    rms.c # rms.h
    spectrum.c # spectrum.h
    spline.c
    state.c # state.h
    status-ui.c # status-ui.h
    stereo.c # stereo.h
    support.c # support.h
    transport.c # transport.h
    scenes.c # scenes.h

    preferences.c # preferences.h
    help.c # help.h
    # denormal-kill.h
    # biquad.h
)

target_link_libraries(jamin PRIVATE
    hnopt
    jamui
    PkgConfig::JACK
    PkgConfig::FFTW
    PkgConfig::XML
    # PkgConfig::GTK
    PkgConfig::GTKMM
)

if(JAMINPP_ADW)
    target_link_libraries(jamin PRIVATE PkgConfig::ADW)
endif()

if(JAMINPP_OSC)
    module_chk(OSC liblo>=0.5)
    target_link_libraries(jamin PRIVATE PkgConfig::OSC)

    add_executable(jamin-scene
        jamin-scene.c
    )
    target_link_libraries(jamin-scene PRIVATE PkgConfig::OSC)
endif()

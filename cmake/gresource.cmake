
find_program(XMLLINT_BIN xmllint)

find_program(JSON_GLIB_FORMAT_BIN json-glib-format)

find_program(GLIB_COMPILE_RESOURCES_BIN glib-compile-resources)

include(GenerateExportHeader) # ?

macro(add_resource_file _name _tgt)
  if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_name}.gresource.xml)
    message(FATAL_ERROR "resource file not found: ${_name}.gresource.xml")
  endif()

  ## per glib-compile-resources(1)
  set(ENV{XMLLINT} ${XMLLINT_BIN})
  set(ENV{JSON_GLIB_FORMAT} ${JSON_GLIB_FORMAT_BIN})
  set(ENV{CC} ${CMAKE_C_COMPILER})

  add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${_tgt}.c"
    COMMAND ${GLIB_COMPILE_RESOURCES_BIN} ARGS
    --sourcedir="${CMAKE_CURRENT_SOURCE_DIR}"
    --target="${CMAKE_CURRENT_BINARY_DIR}/${_tgt}.c"
    --generate-source
    "${CMAKE_CURRENT_SOURCE_DIR}/${_name}.gresource.xml"
    MAIN_DEPENDENCY "${CMAKE_CURRENT_SOURCE_DIR}/${_name}.gresource.xml"
    ## Usage: list source files referred in the resource XML as args after 'tgt'
    DEPENDS ${ARGN}
    "${CMAKE_CURRENT_SOURCE_DIR}/${_name}.gresource.xml"
  )

  add_library(${_tgt} STATIC ${CMAKE_CURRENT_BINARY_DIR}/${_tgt}.c)

  target_link_libraries(${_tgt} PkgConfig::GTKMM)
endmacro()

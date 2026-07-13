
find_program(XMLLINT_BIN xmllint)

find_program(JSON_GLIB_FORMAT_BIN json-glib-format)

find_program(GLIB_COMPILE_RESOURCES_BIN glib-compile-resources)

function(add_resource_file _basename _tgt _dst)
  if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_basename}.gresource.xml)
    message(FATAL_ERROR "resource file not found: ${_basename}.gresource.xml")
  endif()

  ## environment variables for glib-compile-resources(1)
  set(ENV{XMLLINT} ${XMLLINT_BIN})
  set(ENV{JSON_GLIB_FORMAT} ${JSON_GLIB_FORMAT_BIN})
  # set(ENV{CC} ${CMAKE_C_COMPILER})

  add_custom_command(
    OUTPUT "${_dst}"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${GLIB_COMPILE_RESOURCES_BIN} ARGS
    --sourcedir="${CMAKE_CURRENT_SOURCE_DIR}"
    --target="${_dst}"
    --generate-source
    "${CMAKE_CURRENT_SOURCE_DIR}/${_basename}.gresource.xml"
    MAIN_DEPENDENCY "${CMAKE_CURRENT_SOURCE_DIR}/${_basename}.gresource.xml"
    ## Usage: list source files referred in the resource XML as args after 'tgt',
    ## to ensure that the resource file should be rebuilt after any of those
    ## files has been updated
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${_basename}.gresource.xml" ${ARGN}
    DEPENDS_EXPLICIT_ONLY
  )

  # by side effect, ensure that the _dst file is generated before building 
  # any tgts that would use _dst as a source file. 
  add_custom_target(${_tgt} DEPENDS ${_dst})

endfunction()

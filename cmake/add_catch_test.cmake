## add_catch_test.cmake

if(NOT TARGET ${CMAKE_PROJECT_NAME}_test_libs)
    add_library(${CMAKE_PROJECT_NAME}_test_libs INTERFACE)
endif()

function(add_catch_test test_name)
    set(_options CUSTOM_MAIN)
    set(_single_value)
    set(_multi_value SOURCES LIBRARIES INCLUDE SYSTEM_INCLUDE)
    cmake_parse_arguments(PARSE_ARGV 1 arg "${_options}" "${_single_value}" "${_multi_value}")

    if(arg_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "add_catch_test: Unrecognized options: ${arg_UNPARSED_ARGUMENTS}")
    endif()

    if(NOT DEFINED arg_SOURCES)
        set(arg_SOURCES ${test_name}.cpp)
    endif()

    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/_include)
        message(STATUS "test ${test_name} automatic includes: ${CMAKE_CURRENT_LIST_DIR}/_include")
        if(NOT DEFINED arg_INCLUDE)
            set(arg_INCLUDE)
        endif()
        list(PREPEND arg_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/_include)
    endif()

    if(NOT DEFINED arg_LIBRARIES)
        set(arg_LIBRARIES)
    endif()

    if(arg_CUSTOM_MAIN)
        list(APPEND arg_LIBRARIES Catch2::Catch2)
    else()
        list(APPEND arg_LIBRARIES Catch2::Catch2WithMain)
    endif()

    list(REMOVE_DUPLICATES arg_SOURCES)
    list(REMOVE_DUPLICATES arg_LIBRARIES)
    list(REMOVE_DUPLICATES arg_INCLUDE)
    list(REMOVE_DUPLICATES arg_SYSTEM_INCLUDE)

    add_executable(${test_name} ${arg_SOURCES})

    if(EXISTS ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/include)
        target_include_directories(${test_name} PRIVATE ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/include)
    elseif(EXISTS ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/src)
        target_include_directories(${test_name} PRIVATE ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/src)
    endif()

    if(EXISTS ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/include/test)
        target_include_directories(${test_name} PRIVATE ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/include/test)
    elseif(EXISTS ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/src/test)
        target_include_directories(${test_name} PRIVATE ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/src/test)
    endif()


    if(DEFINED arg_INCLUDE)
        message(STATUS "test ${test_name} includes: ${arg_INCLUDE}")
        target_include_directories(${test_name} PRIVATE ${arg_INCLUDE})
    endif()

    if(DEFINED arg_SYSTEM_INCLUDE)
        target_include_directories(${test_name} SYSTEM PRIVATE ${arg_SYSTEM_INCLUDE})
    endif()

    target_link_libraries(${test_name} PRIVATE ${arg_LIBRARIES})

    catch_discover_tests(${test_name})
endfunction()

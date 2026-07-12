
find_package(PkgConfig)

function(module_chk _name _spec)
    pkg_check_modules(${_name} REQUIRED ${_spec} IMPORTED_TARGET GLOBAL)
endfunction()

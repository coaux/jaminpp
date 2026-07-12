
function(jamin_translate)
    foreach(_tff ${ARGV})
        file(REAL_PATH  ${_tff} _tff_rl)
        list(APPEND JAMIN_TRANSLATE_FILES ${_tff_rl})
    endforeach()
endfunction()

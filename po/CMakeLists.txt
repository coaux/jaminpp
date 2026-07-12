
find_package(Gettext REQUIRED)

set(LANGUAGES cz fr ru)

foreach(LANG ${LANGUAGES})
    gettext_process_po_files(${LANG}
        PO_FILES ${LANG}.po
    )
endforeach()

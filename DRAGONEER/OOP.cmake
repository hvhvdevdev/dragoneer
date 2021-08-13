function(scanMethod inp)
    set(temp "${inp}")
    set(spaces "[ \\r\\t\\n]")
    set(anum "[A-Za-z0-9]")

    message(STATUS "Input: ${temp}")
    string(REGEX REPLACE "${anum}+${spaces}+DgnMethod${spaces}+" "" temp "${temp}")
    message(STATUS "Temp: ${temp}")
    string(REGEX MATCH "${anum}+" methname "${temp}")
    message(STATUS "Temp: ${methname}")


endfunction()

function(ScanInterface file_name)
    message(STATUS "Scanning ${file_name}")

    # Setting output files name
    set(out_file "${CMAKE_CURRENT_BINARY_DIR}/${DRAGONEER_LIBRARY_NAME}/Impl${file_name}")
    message("${out_file}")
    file(READ ${file_name} txt)

    # Does not make any sense but fix various stuffs.
    configure_file(
            "${file_name}"
            "${out_file}"
            @ONLY
    )

    # Scan for methods
    set(spaces "[ \\r\\t\\n]")
    set(anum "[A-Za-z0-9]")
    string(REGEX MATCHALL "${anum}+${spaces}+DgnMethod${spaces}+[^;]+;" matches "${txt}")

    foreach (f ${matches})
        scanMethod("${f}")
    endforeach ()

    # Write implementation helper
    file(WRITE
            "${out_file}"
            "//Generated\n${txt}")
endfunction()
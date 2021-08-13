function(scanMethod inp out_name out_param out_ret)
    set(temp "${inp}")
    set(spaces "[ \\r\\t\\n]")
    set(anum "[A-Za-z0-9]")

    string(REGEX MATCH "${anum}+" rettype "${temp}")

    message(STATUS "Input: ${temp}")
    string(REGEX REPLACE "${anum}+${spaces}+DgnMethod${spaces}+" "" temp "${temp}")
    message(STATUS "Temp: ${temp}")
    string(REGEX MATCH "${anum}+" methname "${temp}")
    message(STATUS "methname: ${methname}")

    string(REGEX REPLACE "\\(\\*[^\\)]*\\)" "" params "${temp}")
    message(STATUS "Params: ${params}")

    set(${out_name} "${methname}" PARENT_SCOPE)
    set(${out_param} "${params}" PARENT_SCOPE)
    set(${out_ret} "${rettype}" PARENT_SCOPE)
endfunction()

function(ScanInterface classname)
    message(STATUS "Scanning ${file_name}")
    set(file_name "${classname}.h")

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


    # Write implementation helper
    file(WRITE
            "${out_file}"
            "// Generated class ${classname}\n\n"
            "typedef struct {\n"
            "   ${classname}_Vft vft;\n"
            "   void *obj;\n"
            "} ${classname};\n\n"
            "typedef ${classname}* ${classname}Ptr;\n\n"
            )

    foreach (f ${matches})
        scanMethod("${f}" temname temparam temret)

        string(REGEX REPLACE "^${spaces}*\\(" "(${classname}Ptr self," temparam "${temparam}")
        string(REGEX REPLACE "${anum}+[${spaces}*]*(${anum}+)" "\\1" passed "${temparam}")

        message(STATUS "Scanned: ${temname} ${temparam} ${temret} ${passed}")
        file(APPEND
                "${out_file}"
                "${temret} ${classname}_${temname} ${temparam}"
                " {\n"
                "   self->vft->${temname}${passed};\n"
                "}\n\n"
                )
    endforeach ()

endfunction()
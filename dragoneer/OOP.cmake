function(scanMethod inp out_name out_param out_ret)
    set(temp "${inp}")
    set(spaces "[ \\r\\t\\n]")
    set(anum "[A-Za-z0-9]")

    string(REGEX MATCH "(${anum})+(${spaces}|[*])+" rettype "${temp}")
    #message(STATUS "return ${rettype}")

    #message(STATUS "Input: ${temp}")
    string(REGEX REPLACE "${anum}+(${spaces}|[*])+DgnMethod${spaces}+" "" temp "${temp}")
    #message(STATUS "Temp: ${temp}")
    string(REGEX MATCH "${anum}+" methname "${temp}")
    #message(STATUS "methname: ${methname}")

    string(REGEX REPLACE "\\(\\*[^\\)]*\\)" "" params "${temp}")
    string(REGEX REPLACE ".*DgnMethod" "" params "${params}")
    #message(STATUS "Params: ${params}")

    set(${out_name} "${methname}" PARENT_SCOPE)
    set(${out_param} "${params}" PARENT_SCOPE)
    set(${out_ret} "${rettype}" PARENT_SCOPE)
endfunction()

function(ScanInterface classname)
    message(STATUS "Scanning ${file_name}")
    set(file_name "${classname}.h")

    # Setting output files name
    set(out_file "${CMAKE_CURRENT_BINARY_DIR}/${DRAGONEER_LIBRARY_NAME}/OOP/Impl${file_name}")
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
    string(REGEX MATCHALL "(${anum}|[* ])+${spaces}*DgnMethod${spaces}+[^;]+;" matches "${txt}")

    # Scan for inheritance
    string(REGEX MATCHALL "DgnInherit${spaces}+${anum}+;" inherits "${txt}")
    message("${inherits}")

    # Write implementation helper
    file(WRITE
            "${out_file}"
            "// Generated class ${classname}\n"
            "struct ${classname}_Vft;\n\n"
            "typedef struct ${classname}_Vft* ${classname}_VftPtr;\n\n"
            "typedef struct {\n"
            "   ${classname}_VftPtr pVft;\n"
            "   TVoidPtr obj;\n"
            )
    #foreach (inh ${inherits})
    #    string(REGEX REPLACE "(DgnInherit)| " "" inh "${inh}")
    #    string(REGEX REPLACE "(DgnInherit)| " "" inh "${inh}")
    #
    #       file(APPEND
    #              "${out_file}"
    #             "  ${inh}_VftPtr p${inh}_Vft;\n"
    #            )
    #endforeach ()
    file(APPEND
            "${out_file}"
            "} ${classname};\n\n"
            "typedef ${classname}* ${classname}Ptr;\n\n"
            )


    # Impl

    file(APPEND
            "${out_file}"
            "#define Implement_${classname}(c) ;\\\n"
            )

    foreach (f ${matches})
        scanMethod("${f}" temname temparam temret)

        string(REGEX REPLACE "^${spaces}*\\(" "(TVoidPtr self," temparam "${temparam}")
        string(REGEX REPLACE "${anum}+[${spaces}*]*(${anum}+)" "\\1" passed "${temparam}")
        string(REGEX REPLACE "self" "self->obj" passed "${passed}")

        #message(STATUS "Scanned: ${temname} ${temparam} ${temret} ${passed}")
        file(APPEND
                "${out_file}"
                "${temret} c##_${temname} ${temparam};\\\n"
                )
    endforeach ()


    file(APPEND
            "${out_file}"
            "   struct ${classname}_Vft c##_##${classname}_Vft = { \\\n"
            )


    foreach (f ${matches})
        scanMethod("${f}" temname temparam temret)

        string(REGEX REPLACE "^${spaces}*\\(" "(TVoidPtr self," temparam "${temparam}")
        string(REGEX REPLACE "${anum}+[${spaces}*]*(${anum}+)" "\\1" passed "${temparam}")
        string(REGEX REPLACE "self" "self->obj" passed "${passed}")

        #message(STATUS "Scanned: ${temname} ${temparam} ${temret} ${passed}")
        file(APPEND
                "${out_file}"
                "   .${temname} = c##_${temname} ,\\\n"
                )
    endforeach ()

    file(APPEND
            "${out_file}"
            "    }\\\n"
            "\n"
            )

    # Virtual Function Table
    file(APPEND
            "${out_file}"
            "struct ${classname}_Vft {\n"
            )

    foreach (f ${matches})
        scanMethod("${f}" temname temparam temret)

        string(REGEX REPLACE "^${spaces}*\\(" "(TVoidPtr self," temparam "${temparam}")
        string(REGEX REPLACE "${anum}+[${spaces}*]*(${anum}+)" "\\1" passed "${temparam}")
        string(REGEX REPLACE "self" "self->obj" passed "${passed}")

        # message(STATUS "Scanned: ${temname} ${temparam} ${temret} ${passed}")
        file(APPEND
                "${out_file}"
                "   ${temret} (*${temname}) ${temparam};\n"
                )
    endforeach ()


    foreach (inh ${inherits})
        string(REGEX REPLACE "(DgnInherit)| " "" inh "${inh}")
        string(REGEX REPLACE "(DgnInherit)| " "" inh "${inh}")

        file(APPEND
                "${out_file}"
                "  ${inh}_VftPtr p${inh}_Vft;\n"
                )
    endforeach ()

    file(APPEND
            "${out_file}"
            "};\n\n"
            )

    # Functions to call method
    foreach (f ${matches})
        scanMethod("${f}" temname temparam temret)

        string(REGEX REPLACE "^${spaces}*\\(" "(${classname}Ptr self," temparam "${temparam}")
        string(REGEX REPLACE "const|\\[\\]" "" passed "${temparam}")
        #message(STATUS "DEBUG BEFORE: ${passed}")
        string(REGEX REPLACE "((${anum})+)${spaces}*(([*]+))" "\\1 " passed "${passed}")
        #message(STATUS "DEBUG: ${passed}")
        string(REGEX REPLACE "(${anum}|[*])+[${spaces}]*(${anum}+)" "\\2" passed "${passed}")
        #message(STATUS "DEBUG: ${passed}")
        string(REGEX REPLACE "self" "self->obj" passed "${passed}")

        #message(STATUS "Scanned: ${temname} ${temparam} ${temret} ${passed}")
        file(APPEND
                "${out_file}"
                "static ${temret} ${classname}_${temname} ${temparam}"
                " {\n"
                "   return self->pVft->${temname}${passed};\n"
                "}\n\n"
                )
    endforeach ()

    # Cast function

    foreach (inh ${inherits})
        string(REGEX REPLACE "(DgnInherit)| " "" inh "${inh}")
        string(REGEX REPLACE "(DgnInherit)| " "" inh "${inh}")

        file(APPEND
                "${out_file}"
                "static ${inh} ${classname}_As_${inh} (${classname} original) {\n"
                "   ${inh} temp;\n"
                "   temp.pVft = (original.pVft)->p${inh}_Vft;\n"
                "   temp.obj = original.obj;\n"
                "   return temp;\n"
                "}\n\n"
                )
    endforeach ()
endfunction()

function(EnableOOP target)
    target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${DRAGONEER_LIBRARY_NAME}/OOP)
endfunction()
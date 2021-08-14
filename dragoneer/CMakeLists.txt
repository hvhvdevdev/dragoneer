cmake_minimum_required(VERSION 3.17)

project(DRAGONEER
        VERSION 0.0.1)

set(DRAGONEER_LIBRARY_NAME "Dragoneer")

set(DRAGONEER_INPUTS LinkedList.h IElemList.h LinkedList.c)

set(DRAGONEER_INTERFACES IElemList)

set(DRAGONEER_CONCRETES LinkedList.h LinkedList.c)

set(Concrete_Path ${CMAKE_CURRENT_SOURCE_DIR})

function(EnableGeneric tgt)
    foreach (inter ${DRAGONEER_INTERFACES})
        ScanInterface(${inter})
        set(impath "${CMAKE_CURRENT_BINARY_DIR}/${DRAGONEER_LIBRARY_NAME}/OOP/Impl${inter}.h")
        file(READ ${impath} txt)
        file(WRITE ${impath} "// ${ARGN}\n\n")
        foreach (type ${ARGN})
            string(REPLACE "Elem" "${type}" cont "${txt}")
            file(APPEND ${impath} "${cont}")
        endforeach ()
    endforeach ()


    foreach (con ${DRAGONEER_CONCRETES})
        set(cpath "${CMAKE_CURRENT_BINARY_DIR}/${DRAGONEER_LIBRARY_NAME}/OOP/${con}")
        file(READ "${Concrete_Path}/${con}" txt)
        file(WRITE ${cpath} "// ${ARGN} \n\n")
        foreach (type ${ARGN})
            string(REGEX REPLACE "Elem" "${type}" cont "${txt}")
            string(REGEX REPLACE "/ImplI${type}" "/ImplIElem" cont "${cont}")
            file(APPEND ${cpath} "\n\n${cont}")
        endforeach ()
    endforeach ()

    configure_file(${Concrete_Path}/Utils.h ${CMAKE_CURRENT_BINARY_DIR}/${DRAGONEER_LIBRARY_NAME}/OOP/Utils.h)

    target_include_directories(${tgt} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${DRAGONEER_LIBRARY_NAME}/OOP)
    target_include_directories(${tgt} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${DRAGONEER_LIBRARY_NAME}/)

    set(srcs ${DRAGONEER_CONCRETES})

    list(TRANSFORM srcs PREPEND "${CMAKE_CURRENT_BINARY_DIR}/${DRAGONEER_LIBRARY_NAME}/OOP/")

    message("${srcs}")

    #    add_library("${tgt}__dragon" ${srcs})

    #    target_link_libraries(${tgt} ${tgt}__dragon)

    target_sources(${tgt} PRIVATE ${srcs})
endfunction()


foreach (inp ${DRAGONEER_INPUTS})
    configure_file(${inp} "${DRAGONEER_LIBRARY_NAME}/${inp}" @ONLY)
endforeach ()

add_library(
        ${DRAGONEER_LIBRARY_NAME}
        Dummy.c
        IElemList.h
        Utils.h
        ${DRAGONEER_INPUTS}
)

configure_file(Utils.h "${CMAKE_CURRENT_BINARY_DIR}/${DRAGONEER_LIBRARY_NAME}/Utils.h" @ONLY)

#set_target_properties(${DRAGONEER_LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE C)
set_target_properties(${DRAGONEER_LIBRARY_NAME} PROPERTIES C_EXTENSIONS OFF)
set_target_properties(${DRAGONEER_LIBRARY_NAME} PROPERTIES C_STANDARD 99)
set_target_properties(${DRAGONEER_LIBRARY_NAME} PROPERTIES C_STANDARD_REQUIRED TRUE)

target_include_directories(
        ${DRAGONEER_LIBRARY_NAME}
        PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}/${DRAGONEER_LIBRARY_NAME}/
)

target_compile_definitions(
        ${DRAGONEER_LIBRARY_NAME}
        PUBLIC
        DgnMethod=
        DgnInherit=//
)

# Object-oriented Programming

include(OOP.cmake)

EnableGeneric(${DRAGONEER_LIBRARY_NAME} TInt32 TFloat Elem)

# Add examples

add_subdirectory("examples")
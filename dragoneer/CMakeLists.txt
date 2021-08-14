cmake_minimum_required(VERSION 3.17)

project(DRAGONEER
        VERSION 0.0.1)

set(DRAGONEER_LIBRARY_NAME "Dragoneer")

set(DRAGONEER_INPUTS "LinkedList.h")

foreach (file ${DRAGONEER_INPUTS})
    message("${file}")
    configure_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/${file}"
            "${CMAKE_CURRENT_BINARY_DIR}/${DRAGONEER_LIBRARY_NAME}/${file}"
            @ONLY
    )
endforeach ()

add_library(
        ${DRAGONEER_LIBRARY_NAME}
        Dummy.c
        IList.h
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

ScanInterface(IList)

# Add examples

add_subdirectory("examples")
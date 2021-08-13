cmake_minimum_required(VERSION 3.17)

project(DRAGONEER
        VERSION 0.0.1)

set(DRAGONEER_LIBRARY_NAME "Dragoneer")

set(DRAGONEER_INPUTS
        "LinkedList.h"
        )

foreach (file ${DRAGONEER_INPUTS})
    message("${file}")
    configure_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/${file}"
            "${CMAKE_CURRENT_BINARY_DIR}/${DRAGONEER_LIBRARY_NAME}/${file}"
            @ONLY
    )
endforeach ()

add_library(${DRAGONEER_LIBRARY_NAME} INTERFACE)

target_include_directories(
        ${DRAGONEER_LIBRARY_NAME}
        INTERFACE
        ${CMAKE_CURRENT_BINARY_DIR}/${DRAGONEER_LIBRARY_NAME}/
)
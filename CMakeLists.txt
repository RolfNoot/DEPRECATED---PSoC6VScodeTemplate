cmake_minimum_required(VERSION 3.7.2)
######################################################################
#
#	Toolchain
#
######################################################################
#set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")

if (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
    set (CY_MODUS_DIR C:/ModusToolbox_1.1)
elseif (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
    set (CY_MODUS_DIR /opt/ModusToolbox_1.1)
elseif (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Darwin")
    set (CY_MODUS_DIR /Applications/ModusToolbox_1.1)
endif()

set (CONFIG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/config)
set (DESIGN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/design)
set (CY_PDL_DIR ${CY_MODUS_DIR}/libraries/psoc6sw-1.1/components/psoc6pdl)
set (CY_MW_DIR ${CY_MODUS_DIR}/libraries/psoc6sw-1.1/components/psoc6mw)
set (LINKER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/linker)
set (TOOLS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tools)
set (CYPRESS_ELF_TOOL_PATH ${CY_MODUS_DIR}/tools/cymcuelftool-1.0/bin)

set (CMAKE_TOOLCHAIN_FILE "${CONFIG_DIR}/cmake/arm-none-eabi-toolchain.cmake")
find_program(CYPRESS_ELF_TOOL cymcuelftool ${CYPRESS_ELF_TOOL_PATH} DOC "Cypress ELF tool executable")

######################################################################
#
#	Project
#
######################################################################
project(VStest4)
enable_language(ASM)

set(MAIN_PRJ_NAME "${PROJECT_NAME}")

# Use Cypress PDL
include(${CONFIG_DIR}/cmake/cypress_peripheral_drivers_library.cmake)

# Define PSoC63 chip used in the project
# CY8C6347BZI_BLD53 - Used on the Onethinx LoRaWAN Core board
set(CHIP "CY8C6347BZI_BLD53" CACHE STRING "Chip variant used on a board")
set_property(CACHE CHIP PROPERTY STRINGS CY8C6347BZI_BLD54 CY8C6347BZI_BLD53)

message("Chip variant: ${CHIP}")
add_definitions(-D${CHIP})

#Include common settings
include(${CONFIG_DIR}/cmake/common.cmake)

add_subdirectory(source/CortexM0)
add_subdirectory(source/CortexM4)

######################################################################
#
#	Sign and merge both elf files
#
######################################################################

add_custom_target(
    ${MAIN_PRJ_NAME} ALL
    COMMAND "${CYPRESS_ELF_TOOL}" --sign "source/CortexM0/${M0_PRJ_NAME}.elf" --output "source/CortexM0/${M0_PRJ_NAME}_signed.elf"
    COMMAND "${CYPRESS_ELF_TOOL}" --sign "source/CortexM4/${M4_PRJ_NAME}.elf" --output "source/CortexM4/${M4_PRJ_NAME}_signed.elf"

    COMMAND "${CYPRESS_ELF_TOOL}" --merge "source/CortexM4/${M4_PRJ_NAME}_signed.elf" "source/CortexM0/${M0_PRJ_NAME}_signed.elf" --output "${MAIN_PRJ_NAME}_M4debug.elf"
    COMMAND "${CYPRESS_ELF_TOOL}" --merge "source/CortexM0/${M0_PRJ_NAME}_signed.elf" "source/CortexM4/${M4_PRJ_NAME}_signed.elf" --output "${MAIN_PRJ_NAME}_M0debug.elf" --hex "${MAIN_PRJ_NAME}.hex"

    #POST_BUILD
    COMMAND echo "------- M0 memory usage -------"
    COMMAND "${CYPRESS_ELF_TOOL}" -A "source/CortexM0/${M0_PRJ_NAME}.elf"
    COMMAND echo "------- M4 memory usage -------"
    COMMAND "${CYPRESS_ELF_TOOL}" -A "source/CortexM4/${M4_PRJ_NAME}.elf"
    DEPENDS "source/CortexM0/${M0_PRJ_NAME}.elf" "source/CortexM4/${M4_PRJ_NAME}.elf"
)

add_custom_target(
    PreBuild ALL
    COMMAND "${TOOLS_DIR}/buildversion" "${CMAKE_CURRENT_SOURCE_DIR}/source/CortexM0/buildversion.h"
    COMMENT " Running the pre-build action..."
)
add_dependencies(${MAIN_PRJ_NAME} PreBuild)
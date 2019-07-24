cmake_minimum_required(VERSION 3.7.2)
######################################################################
#
#	Project
#
######################################################################

project(VStest4_CortexM4)
enable_language(ASM)

set(M4_PRJ_NAME "${PROJECT_NAME}")

# Use Cypress PDL
include(${CONFIG_DIR}/cmake/cypress_peripheral_drivers_library.cmake)

######################################################################
#
#	CPP Definitions
#
######################################################################

set(PROJECT_FLAGS_ARCH "\
-mthumb \
-mcpu=cortex-m4 \
-mfloat-abi=softfp \
-mfpu=fpv4-sp-d16 \
-DCYDEV_CLK_ALTHF__HZ=8000000UL"
)

set(PROJECT_LINKER_FLAGS "-Wl,-Map=${M4_PRJ_NAME}.map -TCortexM4.ld")

set(PROJECT_C_FLAGS_WARNINGS   "${COMMON_FLAGS_WARNINGS} ${C_FLAGS_WARNINGS_EXTRA}")
set(PROJECT_CXX_FLAGS_WARNINGS "${COMMON_FLAGS_WARNINGS}")

######################################################################
#
#	Sources
#
######################################################################

# Find Source includes folders
FIND_DIRECTORIES(SOURCE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/*.h)
include_directories (
    ${DESIGN_DIR}/CortexM4/GeneratedSource
    ${PDL_INCLUDE_DIRS}
    ${SOURCE_INCLUDE_DIRS}
)
#message(${SOURCE_INCLUDE_DIRS} )

FILE(GLOB_RECURSE SOURCE_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
FILE(GLOB_RECURSE DESIGN_SRCS ${DESIGN_DIR}/CortexM4/GeneratedSource/*.c)

set(PROJECT_SRCS
    ${SOURCE_SRCS}
    ${DESIGN_SRCS}
#Chip startup and core system
    ${CY_PDL_DIR}/devices/psoc6/startup/system_psoc6_cm4.c
    ${CY_PDL_DIR}/devices/psoc6/startup/gcc/startup_psoc6_02_cm4.S
)

######################################################################
#
#	TARGET
#
######################################################################

set (CMAKE_C_FLAGS   "${C_FLAGS} ${C_FLAGS_WARNINGS} ${FLAGS_OPTIMIZATION} ${PROJECT_FLAGS_ARCH}")
#TODO: Evaluate ASM FLAGS
set (CMAKE_ASM_FLAGS "${C_FLAGS} ${C_FLAGS_WARNINGS} ${FLAGS_OPTIMIZATION} ${PROJECT_FLAGS_ARCH}")
set (CMAKE_CXX_FLAGS "${CXX_FLAGS} ${CXX_FLAGS_WARNINGS} ${FLAGS_OPTIMIZATION} ${PROJECT_FLAGS_ARCH}")
set (CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS} ${PROJECT_LINKER_FLAGS}")

#Propagate name to upper scope
set(M4_PRJ_NAME "${M4_PRJ_NAME}" PARENT_SCOPE)

add_executable(${M4_PRJ_NAME}.elf ${PROJECT_SRCS} ${PDL_SRCS})
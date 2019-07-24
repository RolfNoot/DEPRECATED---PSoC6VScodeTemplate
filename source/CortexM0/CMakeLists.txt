cmake_minimum_required(VERSION 3.7.2)
######################################################################
#
#	Project
#
######################################################################

project(VStest4_CortexM0)
enable_language(ASM)

set(M0_PRJ_NAME "${PROJECT_NAME}")

# Use Cypress PDL
include(${CONFIG_DIR}/cmake/cypress_peripheral_drivers_library.cmake)

######################################################################
#
#	CPP Definitions
#
######################################################################
set(PROJECT_FLAGS_ARCH "\
-mcpu=cortex-m0plus \
-mthumb \
-DCYDEV_CLK_ALTHF__HZ=8000000UL"
)

set(PROJECT_LINKER_FLAGS "-Wl,-Map=${M0_PRJ_NAME}.map -TCortexM0.ld")

set(PROJECT_C_FLAGS_WARNINGS   "${COMMON_FLAGS_WARNINGS} ${C_FLAGS_WARNINGS_EXTRA}")
set(PROJECT_CXX_FLAGS_WARNINGS "${COMMON_FLAGS_WARNINGS}")

######################################################################
#
#	Sources
#
######################################################################

# Find Source includes folders
FIND_DIRECTORIES(SOURCE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/*.h)
include_directories ( ${PDL_INCLUDE_DIRS} ${SOURCE_INCLUDE_DIRS} )
#message(${SOURCE_INCLUDE_DIRS} )

FILE(GLOB_RECURSE SOURCE_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
FILE(GLOB_RECURSE SOURCE_ASMS ${CMAKE_CURRENT_SOURCE_DIR}/*.s)

set(PROJECT_SRCS 
  ${SOURCE_SRCS}
  ${DESIGN_SRCS}
#Chip startup and core system
  ${CY_PDL_DIR}/devices/psoc6/startup/system_psoc6_cm0plus.c
  ${CY_PDL_DIR}/devices/psoc6/startup/gcc/startup_psoc6_02_cm0plus.S
)
#message("${PROJECT_SRCS}")

######################################################################
#
#	TARGET
#
######################################################################

set (CMAKE_C_FLAGS            "${C_FLAGS} ${C_FLAGS_WARNINGS} ${FLAGS_OPTIMIZATION} ${PROJECT_FLAGS_ARCH}")
#TODO: Evaluate ASM FLAGS
set (CMAKE_ASM_FLAGS          "${C_FLAGS} ${C_FLAGS_WARNINGS} ${FLAGS_OPTIMIZATION} ${PROJECT_FLAGS_ARCH}")
set (CMAKE_CXX_FLAGS          "${CXX_FLAGS} ${CXX_FLAGS_WARNINGS} ${FLAGS_OPTIMIZATION} ${PROJECT_FLAGS_ARCH}")
set (CMAKE_EXE_LINKER_FLAGS   "${LINKER_FLAGS} ${PROJECT_LINKER_FLAGS} ${FLAGS_OPTIMIZATION} ${PROJECT_FLAGS_ARCH}")

#Propagate name to upper scope
set(M0_PRJ_NAME "${M0_PRJ_NAME}" PARENT_SCOPE)

add_executable(${M0_PRJ_NAME}.elf ${PROJECT_SRCS} ${PDL_SRCS})

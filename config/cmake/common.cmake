######################################################################
#
#	Warnings
#
######################################################################

set(COMMON_FLAGS_WARNINGS "\
-Wall \
-Wextra \
-Wcast-align \
-Wchar-subscripts \
-Wcomment \
-Werror-implicit-function-declaration \
-Wfloat-equal \
-Wformat \
-Wformat=2 \
-Wlong-long \
-Wmain \
-Wno-type-limits \
-Wno-unused-parameter \
-Wno-expansion-to-defined \
-Wno-implicit-fallthrough \
-Wparentheses \
-Wpointer-arith \
-Wreturn-type \
-Wsequence-point \
-Wsign-compare \
-Wswitch \
-Wtrigraphs \
-Wundef \
-Wuninitialized \
-Wunknown-pragmas \
-Wunreachable-code \
-Wunused \
-Wwrite-strings"
)

set(C_FLAGS_WARNINGS_EXTRA "\
-Waggregate-return \
-Wattributes \
-Wbad-function-cast \
-Wimplicit-int \
-Wmissing-declarations \
-Wmissing-format-attribute\
-Wmissing-prototypes \
-Wnested-externs \
-Wpacked \
-Wredundant-decls \
-Wshadow \
-Wstrict-prototypes"
)

######################################################################
#
#	Compiler options except warnings
#
######################################################################

IF(CMAKE_BUILD_TYPE MATCHES customDebug)
  message("Debug build.")
  set(FLAGS_OPTIMIZATION "\
-DDEBUG \
-ffunction-sections \
-ffat-lto-objects \
-Og \
-fno-exceptions \
-fmessage-length=0 \
-fsigned-char \
-fdata-sections \
-g3"
)
ELSE()
  message("Release build.")
  set(FLAGS_OPTIMIZATION "\
-DNDEBUG \
-ffunction-sections \
-ffat-lto-objects \
-Os \
-fno-exceptions \
-fmessage-length=0 \
-fsigned-char \
-fdata-sections \
-g"
)
ENDIF()

set(C_FLAGS "")

set(CXX_FLAGS "-std=gnu++11 -fdevirtualize-speculatively -fno-rtti")

######################################################################
#
#	Linker
#
######################################################################

IF(CMAKE_BUILD_TYPE MATCHES Debug)
  set(LINKER_FLAGS "\
-specs=nano.specs \
-L${LINKER_DIR} \
-Wl,--gc-sections \
-g \
-ffunction-sections \
-Og \
-ffat-lto-objects"
)
ELSE()
  set(LINKER_FLAGS "\
-specs=nano.specs \
-L${LINKER_DIR} \
-Wl,--gc-sections \
-g \
-ffunction-sections \
-Os \
-ffat-lto-objects"
)
ENDIF()
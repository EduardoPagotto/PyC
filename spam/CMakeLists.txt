# ref: https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
cmake_minimum_required(VERSION 3.16.0)
PROJECT(spammodule)

FIND_PACKAGE(PythonInterp)
FIND_PACKAGE(PythonLibs)

set (IncludeModule ${PYTHON_INCLUDE_PATH})
set (SourceModule spammodule.c)

add_library (spammodule SHARED ${SourceModule})
set_target_properties(spammodule PROPERTIES PREFIX "" 
                                 SOVERSION 0.1)
# # set_target_properties(spammodule PROPERTIES PUBLIC_HEADER include/mylib.h)

target_include_directories (spammodule PUBLIC ${IncludeModule})
# INSTALL(FILES ${spammodule_BINARY_DIR}/spammodule.a DESTINATION lib)

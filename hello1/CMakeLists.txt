cmake_minimum_required(VERSION 3.16.0)

PROJECT(helloworld)

FIND_PACKAGE(PythonInterp)
FIND_PACKAGE(PythonLibs)

set (IncludeModule ${CMAKE_CURRENT_SOURCE_DIR}/include
                   ${PYTHON_INCLUDE_PATH})

set (SourceModule src/bind.c
                  src/libHello1.c)

add_library (helloworld SHARED ${SourceModule})
set_target_properties(helloworld PROPERTIES PREFIX "" #) # remove prefix lib
                                 SOVERSION 0.1
                                 PUBLIC_HEADER libHello1.h)

target_include_directories (helloworld PRIVATE ${IncludeModule})

#INSTALL(FILES ${hello1_BINARY_DIR}/spammodule.a DESTINATION lib)

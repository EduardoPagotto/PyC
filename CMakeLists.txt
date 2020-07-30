# ref: https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
cmake_minimum_required(VERSION 3.10.2)

PROJECT(HybridTest)

# set (IncludeModule /usr/include/python3.8)

# set (SourceModule spammodule.c)

# add_library (spammodule SHARED ${SourceModule})

# set_target_properties(spammodule PROPERTIES SOVERSION 1)
# # set_target_properties(spammodule PROPERTIES PUBLIC_HEADER include/mylib.h)

# target_include_directories (spammodule PUBLIC ${IncludeModule})

# INSTALL(FILES ${spammodule_BINARY_DIR}/spammodule.a DESTINATION lib)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(hello1)

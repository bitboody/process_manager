cmake_minimum_required(VERSION 3.10)

# Project name and language
project(pmngr C)

# Add the executable
add_executable(pmngr pmngr.c util.c)

# Link against kernel32 library (only necessary for Windows)
if(WIN32)
    target_link_libraries(pmngr kernel32)
endif()

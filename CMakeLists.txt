cmake_minimum_required(VERSION 3.12)
project(Project_SWA)

set(CMAKE_CXX_STANDARD 14)

#------------------------------------------------------------------------------
# Required CPM Setup - no need to modify - See: https://github.com/iauns/cpm
#------------------------------------------------------------------------------
set(CPM_DIR "${CMAKE_CURRENT_BINARY_DIR}/cpm-packages" CACHE TYPE STRING)
find_package(Git)
if(NOT GIT_FOUND)
    message(FATAL_ERROR "CPM requires Git.")
endif()
if (NOT EXISTS ${CPM_DIR}/CPM.cmake)
    message(STATUS "Cloning repo (https://github.com/iauns/cpm)")
    execute_process(
            COMMAND "${GIT_EXECUTABLE}" clone https://github.com/iauns/cpm ${CPM_DIR}
            RESULT_VARIABLE error_code
            OUTPUT_QUIET ERROR_QUIET)
    if(error_code)
        message(FATAL_ERROR "CPM failed to get the hash for HEAD")
    endif()
endif()
include(${CPM_DIR}/CPM.cmake)
#------------------------------------------------------------------------------
# CPM Modules
#------------------------------------------------------------------------------

# TODO: Include any modules here...

#CPM_AddModule("SDL2"
#        GIT_REPOSITORY "https://github.com/davidsiaw/SDL2.git"
#        GIT_TAG "origin/master"
#        )

CPM_AddModule("Box2D"
        GIT_REPOSITORY "https://github.com/lb321/CPMBox2D.git"
        GIT_TAG "v2.3.1")

CPM_Finish()

include_directories(Headers)
include_directories(Sources)

set(SOURCE_FILES TonicEngine/HelloWorld.cpp)
add_executable(Project_SWA ${SOURCE_FILES})

target_link_libraries(Project_SWA ${CPM_LIBRARIES})

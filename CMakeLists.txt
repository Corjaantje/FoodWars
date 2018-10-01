cmake_minimum_required(VERSION 3.12)
project(Project_SWA)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH $(PROJECT_SOURCE_DIR)/CMake)
find_package(SDL2 REQUIRED)

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

CPM_AddModule("Box2D"
        GIT_REPOSITORY "https://github.com/lb321/CPMBox2D.git"
        GIT_TAG "v2.3.1")

CPM_Finish()

set(SOURCE_FILES main.cpp
        TonicEngine/Sources/Visual/Window.cpp
        TonicEngine/Headers/Visual/Window.h
        TonicEngine/Facades/Visual/VisualFacade.cpp
        TonicEngine/Headers/Visual/VisualFacade.h
        TonicEngine/Sources/Visual/WindowManager.cpp
        TonicEngine/Headers/Visual/WindowManager.h
        TonicEngine/Sources/Visual/ShapeRectangle.cpp
        TonicEngine/Headers/Visual/ShapeRectangle.h
        TonicEngine/Sources/Visual/Colour.cpp
        TonicEngine/Headers/Visual/Colour.h
        TonicEngine/Sources/Visual/ShapeSprite.cpp
        TonicEngine/Headers/Visual/ShapeSprite.h
        TonicEngine/Sources/Storage/XMLReader.cpp
        TonicEngine/Headers/Storage/XMLReader.h
        TonicEngine/Sources/Storage/XMLWriter.cpp
        TonicEngine/Headers/Storage/XMLWriter.h
        TonicEngine/Sources/Storage/MyNode.cpp
        TonicEngine/Headers/Storage/MyNode.h
        TonicEngine/Sources/Storage/MyDocument.cpp
        TonicEngine/Headers/Storage/MyDocument.h TonicEngine/Sources/Storage/tinyxml2.cpp TonicEngine/Headers/Storage/tinyxml2.h)

add_executable(Project_SWA ${SOURCE_FILES})

target_link_libraries(Project_SWA ${CPM_LIBRARIES} -lmingw32 -lSDL2main -lSDL2 -mwindows -static-libgcc -static-libstdc++)

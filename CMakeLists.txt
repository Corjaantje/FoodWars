cmake_minimum_required(VERSION 3.12)
project(Project_SWA)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH $(PROJECT_SOURCE_DIR)/CMake)
find_package(SDL2 REQUIRED)

set (LIB_DIR "${PROJECT_SOURCE_DIR}/TonicEngine/Libraries")
set (DEPENDENCIES "")
set (LIBRARIES "")

find_package(Git)
if(NOT GIT_FOUND)
    message(FATAL_ERROR "This program requires Git.")
endif()

macro(AddLib repo name)
    set (subdir "")
    set (extra_macro_args ${ARGN})

    # Did we get any optional args?
    list(LENGTH extra_macro_args num_extra_args)
    if (${num_extra_args} GREATER 0)
        list(GET extra_macro_args 0 tag)
        if (${num_extra_args} GREATER 1)
            list(GET extra_macro_args 1 tag)
        endif()
    endif()

    set(LIB_DIR_NAME "${LIB_DIR}/${name}")
    if (NOT EXISTS ${LIB_DIR_NAME})
        message(STATUS "Cloning repo (${repo})")
        if(DEFINED tag)
            message(STATUS "Using tag '${tag}'")
            execute_process(
                    COMMAND "${GIT_EXECUTABLE}" clone --branch ${tag} ${repo} ${LIB_DIR_NAME}
                    RESULT_VARIABLE error_code
                    OUTPUT_QUIET ERROR_QUIET)
        else()
            execute_process(
                    COMMAND "${GIT_EXECUTABLE}" clone ${repo} ${LIB_DIR_NAME}
                    RESULT_VARIABLE error_code
                    OUTPUT_QUIET ERROR_QUIET)
        endif()
        if(error_code)
            message(FATAL_ERROR "Failed to get the hash for HEAD. Error code: ${error_code}")
        endif()
    endif()
    include_directories(${LIB_DIR_NAME}${subdir})
    include_directories(${LIB_DIR_NAME}${subdir}/include)
    add_subdirectory(${LIB_DIR_NAME}${subdir})
    #link_libraries(${LIB_DIR_NAME}${subdir})
    set (DEPENDENCIES ${DEPENDENCIES} ${name})
    set (LIBRARIES ${LIBRARIES} ${LIB_DIR_NAME}${subdir})
    unset(tag)
    unset(subdir)
endmacro()

AddLib("https://github.com/lb321/CPMBox2D" Box2D '' "v2.3.1-nocpm")
AddLib("https://github.com/lsalzman/enet" enet)
AddLib("https://github.com/leethomason/tinyxml2" tinyxml2)

set(SOURCE_FILES_VISUAL
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
        TonicEngine/Headers/Visual/ShapeSprite.h)

set(SOURCE_FILES_INPUT
        TonicEngine/Sources/Input/InputFacade.cpp
        TonicEngine/Headers/Input/InputFacade.h
        TonicEngine/Headers/Input/IObservable.h
        TonicEngine/Headers/Input/IObserver.h)

set(SOURCE_FILES_STORAGE
        TonicEngine/Sources/Storage/XMLReader.cpp
        TonicEngine/Headers/Storage/XMLReader.h
        TonicEngine/Sources/Storage/XMLWriter.cpp
        TonicEngine/Headers/Storage/XMLWriter.h
        TonicEngine/Sources/Storage/MyNode.cpp
        TonicEngine/Headers/Storage/MyNode.h
        TonicEngine/Sources/Storage/MyDocument.cpp
        TonicEngine/Headers/Storage/MyDocument.h
        TonicEngine/Sources/Storage/tinyxml2.cpp
        TonicEngine/Headers/Storage/tinyxml2.h)

set(SOURCE_FILES_AUDIO
        TonicEngine/Headers/Audio/AudioDictionary.h
        TonicEngine/Sources/Audio/AudioDictionary.cpp
        TonicEngine/Headers/Audio/AudioPlayer.h
        TonicEngine/Sources/Audio/AudioPlayer.cpp
        TonicEngine/Facades/Audio/AudioFacade.cpp
        TonicEngine/Headers/Audio/AudioFacade.h)

set(SOURCE_FILES_COMMUNICATION
	    TonicEngine/Headers/Communication/CommunicationFacade.h
        TonicEngine/Headers/Communication/Server.h
        TonicEngine/Headers/Communication/Client.h
        TonicEngine/Headers/Communication/Packet.h
        TonicEngine/Sources/Communication/Server.cpp
        TonicEngine/Sources/Communication/Client.cpp
        TonicEngine/Sources/Communication/Packet.cpp
        TonicEngine/Facades/Communication/CommunicationFacade.cpp
        TonicEngine/Headers/Communication/IConnection.h)

set(SOURCE_FILES main.cpp TonicEngine/Headers/Events/IEvent.h TonicEngine/Sources/Events/KeyEvent.cpp TonicEngine/Headers/Events/KeyEvent.h TonicEngine/Headers/Events/WindowEvent.h TonicEngine/Sources/Input/KeyEventObservable.cpp TonicEngine/Headers/Input/KeyEventObservable.h TonicEngine/Sources/Input/PrintKeyInputObserver.cpp TonicEngine/Headers/Input/PrintKeyInputObserver.h TonicEngine/Sources/Events/MouseEvent.cpp TonicEngine/Headers/Events/MouseEvent.h TonicEngine/Sources/Input/MouseEventObservable.cpp TonicEngine/Headers/Input/MouseEventObservable.h TonicEngine/Sources/Input/PrintMouseInputObserver.cpp TonicEngine/Headers/Input/PrintMouseInputObserver.h)

add_executable(Project_SWA ${SOURCE_FILES} ${SOURCE_FILES_VISUAL} ${SOURCE_FILES_INPUT} ${SOURCE_FILES_STORAGE} ${SOURCE_FILES_COMMUNICATION} ${SOURCE_FILES_AUDIO})

target_link_libraries(Project_SWA ${DEPENDENCIES} -lmingw32 -lSDL2main -lSDL2 -mwindows -static-libgcc -static-libstdc++)

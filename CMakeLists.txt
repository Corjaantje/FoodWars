cmake_minimum_required(VERSION 3.12)
project(Project_SWA)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

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
                    COMMAND "${GIT_EXECUTABLE}" clone --recursive ${repo} ${LIB_DIR_NAME}
                    RESULT_VARIABLE error_code
                    OUTPUT_QUIET ERROR_QUIET)
        endif()
        if(error_code)
            message(FATAL_ERROR "Failed to get the hash for HEAD. Error code: ${error_code}")
        endif()
    endif()
    include_directories(${LIB_DIR_NAME}${subdir})
    include_directories(${LIB_DIR_NAME}${subdir}/include)
    include_directories(${LIB_DIR_NAME}${subdir}/include/nanogui)
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
        TonicEngine/Sources/Input/InputObservable.cpp
        TonicEngine/Headers/Input/InputObservable.h
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
        TonicEngine/Headers/Storage/tinyxml2.h
        TonicEngine/Facades/Storage/StorageFacade.cpp
        TonicEngine/Headers/Storage/StorageFacade.h)

set(SOURCE_FILES_AUDIO
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

set(SOURCE_FILES_COLLISION
        TonicEngine/Headers/Collision/Vector2D.h
        TonicEngine/Sources/Collision/Vector2D.cpp
        TonicEngine/Headers/Collision/Shape.h
        TonicEngine/Sources/Collision/Shape.cpp
        TonicEngine/Headers/Collision/Rectangle.h
        TonicEngine/Sources/Collision/Rectangle.cpp
        TonicEngine/Headers/Collision/Circle.h
        TonicEngine/Sources/Collision/Circle.cpp
        TonicEngine/Facades/Collision/CollisionFacade.cpp
        TonicEngine/Headers/Collision/CollisionFacade.h)

set(SOURCE_FILES main.cpp
        FoodWars/Headers/GameECS/Systems/IBaseSystem.h
        FoodWars/Sources/GameECS/Entities/EntityManager.cpp
        FoodWars/Headers/GameECS/Entities/EntityManager.h
        FoodWars/Sources/GameECS/Systems/DrawSystem.cpp
        FoodWars/Headers/GameECS/Systems/DrawSystem.h
        FoodWars/Sources/GameECS/Components/Component.cpp
        FoodWars/Headers/GameECS/Components/Component.h
        FoodWars/Sources/GameECS/Components/DrawableComponent.cpp
        FoodWars/Headers/GameECS/Components/DrawableComponent.h)

add_executable(Project_SWA ${SOURCE_FILES} ${SOURCE_FILES_VISUAL} ${SOURCE_FILES_INPUT} ${SOURCE_FILES_STORAGE} ${SOURCE_FILES_COMMUNICATION} ${SOURCE_FILES_AUDIO} ${SOURCE_FILES_COLLISION})

target_link_libraries(Project_SWA ${DEPENDENCIES}  -lmingw32 -lSDL2_mixer  -lSDL2main -lSDL2  -mwindows -static-libgcc -static-libstdc++)

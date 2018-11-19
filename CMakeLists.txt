cmake_minimum_required(VERSION 3.12)
project(Project_SWA)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

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

#AddLib("https://github.com/lb321/CPMBox2D" Box2D '' "v2.3.1-nocpm")
AddLib("https://github.com/lsalzman/enet" enet)
AddLib("https://github.com/leethomason/tinyxml2" tinyxml2)

file(GLOB_RECURSE SOURCES1 "Foodwars/*.cpp")
file(GLOB_RECURSE SOURCES2 "Foodwars/*.h")
file(GLOB_RECURSE SOURCES3 "TonicEngine/Sources/*.cpp")
file(GLOB_RECURSE SOURCES4 "TonicEngine/Facades/*.cpp")
file(GLOB_RECURSE SOURCES5 "TonicEngine/Headers/*.h")
set(SOURCE_FILES main.cpp)
add_executable(Project_SWA ${SOURCE_FILES} ${SOURCES1} ${SOURCES2} ${SOURCES3} ${SOURCES4} ${SOURCES5})

target_link_libraries(Project_SWA ${DEPENDENCIES} -lmingw32 -lSDL2_mixer -lSDL2_image -lSDL2main -lSDL2 -lSDL2_ttf  -mwindows -static-libgcc -static-libstdc++)
file(REMOVE_RECURSE ./cmake-build-debug/Assets/)
file(COPY Assets DESTINATION .)
file(COPY _INSTALLATION_/BUILDFILES/ DESTINATION .)

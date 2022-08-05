cmake_minimum_required(VERSION 3.5)
message("[INFO] CMake version: " ${CMAKE_VERSION})
project(tvdd LANGUAGES CXX)
message("[INFO] Turbo Vision C++ 2.0 Dialog Designer: " ${PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#use Russian (RUS) or English (ENG) resource string
add_definitions(-DRUS)

if (WIN32)
    message("[INFO] Build Windows revision")
endif(WIN32)

if (UNIX AND NOT APPLE)
    message("[INFO] Build Linux revision")
endif()

file(GLOB SOURCES tvdd/*.cpp tvdd/*.h)

set(PROJECT_SOURCES ${SOURCES})

include_directories(tvdd/include)
include_directories(tvdd/include/nlohmann)
include_directories(tvdd/include/tvision)

add_executable(tvdd ${PROJECT_SOURCES})
target_link_libraries(tvdd PUBLIC tvision)
#target_compile_options(${PROJECT_NAME} PRIVATE -fdata-sections -ffunction-sections)
#target_link_options(${PROJECT_NAME} PUBLIC -Wl,--gc-sections)

# if (WIN32)
    # #сборка под Windows
    # target_link_libraries(tvdd PUBLIC tvision)
# endif(WIN32)

# if (UNIX AND NOT APPLE)
    # #сборка под Linux (различие в библиотеках)
    # target_link_libraries(tvdd PUBLIC tvision)
# endif()


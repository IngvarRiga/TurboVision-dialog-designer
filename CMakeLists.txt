cmake_minimum_required(VERSION 3.5)
message("[INFO] CMake version: " ${CMAKE_VERSION})
project(tvdd LANGUAGES CXX)
message("[INFO] Turbo Vision C++ 2.0 Dialog Designer: " ${PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#use Russian (RUS) or English (ENG) resource string
if (RES STREQUAL "ENG")
	add_definitions(-DENG)
        message("[INFO] Use ENGLISH resources")
else()
	add_definitions(-DRUS)
        message("[INFO] Use RUSSIAN resources")
endif()

 message("[INFO] -- " ${CMAKE_BUILD_TYPE})


if (WIN32)
    message("[INFO] Build Windows revision")
endif(WIN32)

if (UNIX AND NOT APPLE)
    message("[INFO] Build Linux revision")
endif()

file(GLOB SOURCES tvdd/*.cpp tvdd/*.h)

set(PROJECT_SOURCES ${SOURCES})
message("--- " ${SOURCE_DIR})

include_directories(tvdd/include)
include_directories(tvdd/include/nlohmann)
include_directories(tvdd/include/tvision)
link_directories(tvdd)

add_executable(tvdd ${PROJECT_SOURCES})


if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PUBLIC
        /permissive-
        /Zc:__cplusplus
        /Zc:externConstexpr
        /Zc:inline
        /JMC 
        /MP
        /GS
        /W3
        /Zc:wchar_t
        /ZI
        /Gm-
        /Od
        /sdl
        /fp:precise
        /errorReport:prompt
        /WX-
        /Zc:forScope
        /RTC1
        /Gd
        /MDd
        /std:c++20
        /FC
        /EHsc
        /nologo
        /diagnostics:column 
        /wd4996 
	/wd4267 
    )
    target_link_libraries(tvdd PUBLIC tvision-debug)
    endif()
  if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(${PROJECT_NAME} PUBLIC

        /Zc:__cplusplus
        /Zc:externConstexpr
        /Zc:inline
        /GS
	/GL
	/W3
	/Gy
	/Zc:wchar_t
	/Zi
	/Gm-
	/O2
	/sdl
	/Zc:inline
	/fp:precise
        /std:c++20
	/errorReport:prompt
	/WX-
	/Zc:forScope
	/Gd
	/Oi
	/MD
	/FC
	/EHsc
	/nologo
	/diagnostics:column 
        /wd4996 
	/wd4267 
    )
    target_link_libraries(tvdd PUBLIC tvision)
    endif()

    if (TV_REDUCE_APP_SIZE) # Implies CMake >= 3.13.0
        target_compile_options(${PROJECT_NAME} PRIVATE
            /Gy
        )
        target_link_options(${PROJECT_NAME} PUBLIC
            /OPT:REF
        )
    endif()
endif()

if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC
        _CRT_NONSTDC_NO_WARNINGS
        _CRT_SECURE_NO_WARNINGS
    )
endif()




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


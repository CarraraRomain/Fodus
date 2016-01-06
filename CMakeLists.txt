cmake_minimum_required(VERSION 2.8)
project(Fodus)

cmake_policy(SET CMP0015 NEW)
# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Version Number
set(FODUS_VERSION_MAJOR 1)
set(FODUS_VERSION_MINOR 2)
set(PROJECT_SOURCE_DIR src/)

# Generate config.h file
configure_file(
        "${PROJECT_SOURCE_DIR}/config.h.in"
        "../${PROJECT_SOURCE_DIR}/config.h"
)
#include_directories("${PROJECT_BINARY_DIR}")
include_directories(lib/autobahn/autobahn)

include_directories(lib/easylogging)
include_directories(lib/rapidjson)
include_directories(lib/bonefish/third-party/msgpack-c/include)
#find_package(Boost REQUIRED COMPONENTS program_options system thread)
# Use C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated -std=c++11 -pthread")

# Sources files
file(
        GLOB_RECURSE
        SOURCE_FILES
        src/*

)
# Define sources and executable
set(EXECUTABLE_OUTPUT_PATH ../bin/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_NAME "Fodus")
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

######### BOOST
set(BOOST_ROOT lib/boost)
set(BOOST_NO_SYSTEM_PATHS ON)
set(BOOST_NO_BOOST_CMAKE ON)
find_package(Boost REQUIRED COMPONENTS system program_options thread)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${EXECUTABLE_NAME} ${Boost_LIBRARIES})
endif()
#include_directories(lib/boost)
#link_directories(${EXECUTABLE_NAME} lib/boost/stage/lib)

#############
# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
# Manual locate for Windows

set(SFML_ROOT /usr/lsa)
if(WIN32)
	file(GLOB SFML_DLL
	"${SFML_ROOT}/bin/*.dll"
	)	
# Copy DLLs to binary folder
file(COPY ${SFML_DLL} DESTINATION ../bin/Debug)
file(COPY ${SFML_DLL} DESTINATION ../bin/Release)
endif()
# Find SFML
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

## Next lines are useless for now
# Install target
# install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
# CPack packaging
# include(InstallRequiredSystemLibraries)
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
#set(CPACK_PACKAGE_VERSION_MAJOR "${SFML_Test_VERSION_MAJOR}")
#set(CPACK_PACKAGE_VERSION_MINOR "${SFML_Test_VERSION_MINOR}")
#include(CPack)

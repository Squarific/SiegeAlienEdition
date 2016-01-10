CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Siege_Alien_Edition)

# Extend the CMake module path to find the FindSFML.cmake
# file in {project root}/cmake/Modules
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

# Look for SFML >= 2.0, with the specific subcomponents listed below
FIND_PACKAGE(SFML 2 COMPONENTS system window graphics)

# Set the CMake flag for the c++ standard to std=c++11
SET(CMAKE_CXX_FLAGS "-Isrc/headers -Isrc/headers/controllers -Isrc/headers/model -Isrc/headers/view -Wall -std=c++11")

# The source files to compile
SET(SRC src/SiegeAlienEdition.cpp src/cpp/Entitys.cpp src/cpp/model/Game.cpp src/cpp/model/StopWatch.cpp src/cpp/view/Screen.cpp src/cpp/controllers/PlayerController.cpp src/cpp/controllers/Controller.cpp src/cpp/controllers/ControllerCollection.cpp)

# Add include dirs for SFML
# (The SFML_INCLUDE_DIR variable is defined by FindSFML.cmake, if SFML was found)
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})

# The program we're compiling with the sources set above
ADD_EXECUTABLE(SiegeAlienEdition ${SRC})

# Link target to SFML libs
# (The SFML_LIBRARIES variable is defined by FindSFML.cmake, if SFML was found)
TARGET_LINK_LIBRARIES(SiegeAlienEdition ${SFML_LIBRARIES})

INSTALL(TARGETS SiegeAlienEdition DESTINATION ./bin)

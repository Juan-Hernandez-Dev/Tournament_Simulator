cmake_minimum_required(VERSION 3.10)
project(TournamentSim)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/utils)

# Automatically collect all .cpp files from src/
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "utils/*.h")

# Create executable
add_executable(TournamentSim ${SOURCES} ${HEADERS})

# Copy jugadores.txt to build directory
configure_file(${CMAKE_SOURCE_DIR}/jugadores.txt
               ${CMAKE_BINARY_DIR}/jugadores.txt COPYONLY)

# Copy the sacred luck dog (DO NOT REMOVE OR MODIFY!)
configure_file(${CMAKE_SOURCE_DIR}/the_luck_dog.txt
               ${CMAKE_BINARY_DIR}/the_luck_dog.txt COPYONLY)

# Optional: Add compiler warnings
if(MSVC)
    target_compile_options(TournamentSim PRIVATE /W4)
else()
    target_compile_options(TournamentSim PRIVATE -Wall -Wextra)
endif()
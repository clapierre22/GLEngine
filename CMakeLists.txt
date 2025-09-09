cmake_minimum_required(VERSION 3.10)
project(GLEngine C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Add all .c files in src/
file(GLOB_RECURSE SRC_FILES src/*.c)

# Debug: Print all found source files
message(STATUS "Found source files:")
foreach(src_file ${SRC_FILES})
    message(STATUS "  ${src_file}")
endforeach()

add_executable(GLEngine ${SRC_FILES})

# Example: Link SDL2 (if installed via package manager)
find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(GLEngine ${SDL2_LIBRARIES})
endif()

# Working on linking libraries
target_link_libraries(GLEngine
    -lfreeglut
    -lglew32
    -lopengl32
    -lglu32
    -lSDL2
    -lSDL2main
    -lmingw32    
)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    # ${CMAKE_SOURCE_DIR}/src/base
    # ${CMAKE_SOURCE_DIR}/src/render
    # ${CMAKE_SOURCE_DIR}/src/logic
)

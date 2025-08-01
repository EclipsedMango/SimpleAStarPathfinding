cmake_minimum_required(VERSION 3.31)
project(SimplePathFinding)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git GIT_TAG 1.0.1)
FetchContent_MakeAvailable(glm)

set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCH CONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

add_executable(SimplePathFinding main.cpp
        Headers/Pathfinding.h
        Source/Pathfinding.cpp
        Headers/NodeMap.h
        Source/NodeMap.cpp
        Headers/PathAgent.h
        Source/PathAgent.cpp
        Headers/Agent.h
        Headers/Behaviour.h
        Source/Agent.cpp
        Headers/GotoPointBehaviour.h
        Source/GotoPointBehaviour.cpp
        Headers/WanderBehaviour.h
        Source/WanderBehaviour.cpp
        Headers/FollowBehaviour.h
        Source/FollowBehaviour.cpp
        Headers/SelectorBehaviour.h
        Source/SelectorBehaviour.cpp
)

target_link_libraries(SimplePathFinding PRIVATE raylib glm::glm)

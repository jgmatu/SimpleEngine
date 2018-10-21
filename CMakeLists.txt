cmake_minimum_required(VERSION 3.0)
project (SimpleEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11") # -Wpedantic -Wextra
set(GLAD_LIBRARIES dl)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(src/extras/glfw)

file(GLOB VENDORS_SOURCES src/extras/glad/src/glad.c)

include_directories(include
                    src/extras/glad/include/
                    src/extras/glfw/include/
                    src/extras/glm/
                    src/extras/stb/
)

file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

file(GLOB PROJECT_SOURCES
    src/Components/*cpp
    src/GameObjects/*cpp
    src/Mesh/*cpp
    src/Messages/*cpp
    src/Systems/*cpp
    src/Program/*cpp
    src/Engine.cpp
    src/main.cpp
)
source_group("src/extras" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                      ${PROJECT_CONFIGS} ${VENDORS_SOURCES})

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

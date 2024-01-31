cmake_minimum_required(VERSION 3.26)
project(Game2 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(OGRE_DIR $ENV{OGRE_HOME}/CMake)

find_package(OGRE REQUIRED)

file(GLOB_RECURSE SRC src/**.cpp)

add_executable(Game2
    ${SRC}
)

target_link_libraries(Game2 ${OGRE_LIBRARIES})

file(GLOB_RECURSE LIBS ${OGRE_PREFIX_DIR}/bin/*.dll)
file(COPY ${LIBS} DESTINATION ${CMAKE_BINARY_DIR}/Release)
file(COPY ${LIBS} DESTINATION ${CMAKE_BINARY_DIR}/Debug)

file(COPY Media DESTINATION ${CMAKE_BINARY_DIR}/Release/Media)
file(COPY Media DESTINATION ${CMAKE_BINARY_DIR}/Debug/Media)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

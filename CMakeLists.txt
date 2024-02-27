cmake_minimum_required(VERSION 3.26)
project(Game2 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OGRE_FOLDER "NOT_FOUND" CACHE STRING "Ogre SDK installation folder")
set(OGRE_DEPS_LIBS "NOT_FOUND" CACHE STRING "Ogre SDK dependencies libraries folder")
set(OGRE_DIR ${OGRE_FOLDER}/cmake)

find_package(OGRE REQUIRED)

file(GLOB_RECURSE SRC src/**.cpp)

add_executable(Game2
    ${SRC}
)

file(GLOB_RECURSE LIBS ${OGRE_DEPS_LIBS}/*.lib)

target_link_libraries(Game2 ${OGRE_LIBRARIES} ${LIBS})

file(GLOB_RECURSE LIBS ${OGRE_PREFIX_DIR}/bin/*.dll)
file(COPY ${LIBS} DESTINATION ${CMAKE_BINARY_DIR}/Release)
file(COPY ${LIBS} DESTINATION ${CMAKE_BINARY_DIR}/Debug)

file(COPY Media DESTINATION ${CMAKE_BINARY_DIR}/Release)
file(COPY Media DESTINATION ${CMAKE_BINARY_DIR}/Debug)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

cmake_minimum_required(VERSION 3.10)

project(RenaDataPack VERSION 2.0)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(include)

add_subdirectory(src)

add_library(minizipstatic      STATIC ${MINIZIP})
add_library(minizip            SHARED ${MINIZIP})

add_library(renadatapackstatic STATIC ${SRC_LIST})
add_library(renadatapack       SHARED ${MINIZIP} ${SRC_LIST})

set(MAIN main.cpp)

add_executable(test ${MINIZIP} ${SRC_LIST} ${MAIN})

target_link_libraries(minizip
    ${PROJECT_SOURCE_DIR}/src/lib/libzlibstatic.a
)

target_link_libraries(renadatapack
    ${PROJECT_SOURCE_DIR}/src/lib/libzlibstatic.a
)

target_link_libraries(test
    ${PROJECT_SOURCE_DIR}/src/lib/libzlibstatic.a
)

file(COPY ${PROJECT_SOURCE_DIR}/src/lib/libzlibstatic.a
     DESTINATION ${PROJECT_SOURCE_DIR}/lib)
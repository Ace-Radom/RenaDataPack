cmake_minimum_required(VERSION 3.10)

project(RenaDataPack VERSION 1.0)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(include)

add_subdirectory(src)

add_library(renadatapack_static STATIC ${SRC_LIST})
add_library(renadatapack        SHARED ${SRC_LIST})

#set(MAIN main.cpp)

#add_executable(test ${SRC_LIST} ${MAIN})
cmake_minimum_required(VERSION 3.10)

project(RenaDataPack VERSION 2.0)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib_renadatapack)

include_directories(include)
include_directories(${PROJECT_SOURCE_DIR}/lib/zlib/include)
include_directories(${PROJECT_SOURCE_DIR}/lib/minizip-ng/include)

add_subdirectory(src)

add_library(renadatapack_static STATIC ${SRC_LIST})
#add_library(renadatapack        SHARED ${SRC_LIST})

set(MAIN main.cpp)

add_executable(test ${SRC_LIST} ${MAIN})

target_link_libraries(renadatapack_static
    ${PROJECT_SOURCE_DIR}/lib/zlib/lib/libzlibstatic.a
    ${PROJECT_SOURCE_DIR}/lib/minizip-ng/lib/libbzip2.a
    ${PROJECT_SOURCE_DIR}/lib/minizip-ng/lib/liblzma.a
    ${PROJECT_SOURCE_DIR}/lib/minizip-ng/lib/libminizip.a
    ${PROJECT_SOURCE_DIR}/lib/minizip-ng/lib/libzstd.a
)

target_link_libraries(test
    ${PROJECT_SOURCE_DIR}/lib/zlib/lib/libzlibstatic.a
    ${PROJECT_SOURCE_DIR}/lib/minizip-ng/lib/libbzip2.a
    ${PROJECT_SOURCE_DIR}/lib/minizip-ng/lib/liblzma.a
    ${PROJECT_SOURCE_DIR}/lib/minizip-ng/lib/libminizip.a
    ${PROJECT_SOURCE_DIR}/lib/minizip-ng/lib/libzstd.a
)
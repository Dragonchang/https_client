cmake_minimum_required(VERSION 3.3)
project(https_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.c
    https.c
    https.h)

include_directories(.)
include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/mbedtls/include)

add_subdirectory(mbedtls)

add_executable(https_client ${SOURCE_FILES})

target_link_libraries(https_client mbedx509)
target_link_libraries(https_client mbedtls)
target_link_libraries(https_client mbedcrypto)
target_link_libraries(https_client pthread)

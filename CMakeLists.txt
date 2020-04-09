cmake_minimum_required(VERSION 3.7)
project(uvserver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if(UNIX AND NOT APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  set(CMAKE_EXE_LINKER_FLAGS "-lc++abi")
endif()

find_package(libuv REQUIRED)
find_package(boost REQUIRED)

file(GLOB_RECURSE USER_SOURCES
    src/*.cpp
    src/*.h
)

file(GLOB_RECURSE DTZONESPEC
    date_time_zonespec.csv
)

add_executable(${PROJECT_NAME}
    ${USER_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    ${UV_LIBRARY}
)

configure_file(${DTZONESPEC} . COPYONLY)

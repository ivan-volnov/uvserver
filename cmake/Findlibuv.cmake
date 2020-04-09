
find_path(UV_INCLUDE_DIR uv.h
  HINTS /usr/local/opt/libuv/include
  PATHS /usr/include
)

if(APPLE)
    set(UV_LIBRARY_NAMES libuv.a uv)
else()
    set(UV_LIBRARY_NAMES uv)
endif()

find_library(UV_LIBRARY
  NAMES ${UV_LIBRARY_NAMES}
  HINTS /usr/local/opt/libuv/lib
  PATHS /usr/lib /usr/local/lib
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(UV DEFAULT_MSG
  UV_INCLUDE_DIR
  UV_LIBRARY
)

include_directories(${UV_INCLUDE_DIR})

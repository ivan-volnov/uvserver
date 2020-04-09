
find_path(BOOST_INCLUDE_DIR boost/date_time.hpp
  HINTS /usr/local/opt/boost/include
  PATHS /usr/include
)

if(APPLE)
    set(BOOST_LIBRARY_NAMES libboost_date_time.a boost_date_time)
else()
    set(BOOST_LIBRARY_NAMES boost_date_time)
endif()

find_library(BOOST_LIBRARY
  NAMES ${BOOST_LIBRARY_NAMES}
  HINTS /usr/local/opt/boost/lib
  PATHS /usr/lib /usr/local/lib
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(BOOST DEFAULT_MSG
  BOOST_INCLUDE_DIR
  BOOST_LIBRARY
)

include_directories(${BOOST_INCLUDE_DIR})

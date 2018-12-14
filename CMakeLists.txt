CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(SignalBox)

# Detect Boost
set(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost REQUIRED COMPONENTS filesystem system program_options)
INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIRS} )

# Detect XercesC
FIND_PACKAGE(XercesC REQUIRED)
INCLUDE_DIRECTORIES(SYSTEM ${XercesC_INCLUDE_DIRS} )

# Detect PiGPIO
# Using Findpigpio.cmake
# https://github.com/joan2937/pigpio/blob/master/util/Findpigpio.cmake
FIND_PACKAGE(pigpio)
IF(pigpio_FOUND)
  # See http://abyz.me.uk/rpi/pigpio/pdif2.html
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_PIGPIO")
  INCLUDE_DIRECTORIES(SYSTEM ${pigpio_INCLUDE_DIR})
ENDIF()

# Sort out compiler flags
IF(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  SET(PLATFORM_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wthread-safety -Wpedantic -Wc++11-compat-pedantic -Weffc++")
ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  SET(PLATFORM_CXX_FLAGS "-std=c++11 -pthread -Wall -Wextra -Weffc++ -pedantic")
ENDIF()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ${PLATFORM_CXX_FLAGS}")

INCLUDE_DIRECTORIES( ./include )

ADD_SUBDIRECTORY( src )
ADD_SUBDIRECTORY( tst )
ADD_SUBDIRECTORY( app )

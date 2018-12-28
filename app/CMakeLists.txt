SET( srcs main.cpp )

LIST(APPEND srcs consoledigitaloutputpin.cpp)
LIST(APPEND srcs consolepinmanager.cpp)
LIST(APPEND srcs consoleloop.cpp)
LIST(APPEND srcs cmdlineopts.cpp)
LIST(APPEND srcs outputselector.cpp)
LIST(APPEND srcs consoleoutputselector.cpp)
LIST(APPEND srcs cppcmsloop.cpp)

IF( pigpio_FOUND )
  LIST(APPEND srcs pigpiodoutputselector.cpp)
ENDIF()

ADD_EXECUTABLE(Signalbox ${srcs})

TARGET_LINK_LIBRARIES( Signalbox signalbox ${Boost_LIBRARIES} ${XercesC_LIBRARIES} )
IF( pigpio_FOUND )
  TARGET_LINK_LIBRARIES( Signalbox ${pigpiod_if2_LIBRARY})
ENDIF()
TARGET_LINK_LIBRARIES( Signalbox ${CPPCMS_LIBRARIES} )

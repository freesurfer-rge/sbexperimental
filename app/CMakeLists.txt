SET( srcs main.cpp )

LIST(APPEND srcs consoledigitaloutputpin.cpp)
LIST(APPEND srcs consolepinmanager.cpp)
LIST(APPEND srcs cmdlineopts.cpp)

LIST(APPEND srcs outputselector.cpp)
LIST(APPEND srcs consoleoutputselector.cpp)

LIST(APPEND srcs driverselector.cpp)
LIST(APPEND srcs consoledriver.cpp)
LIST(APPEND srcs consoledriverselector.cpp)

IF( pigpio_FOUND )
  LIST(APPEND srcs pigpiodoutputselector.cpp)
ENDIF()

IF( CPPCMS_FOUND )
  LIST(APPEND srcs cppcms/cppcmsdriver.cpp)
  LIST(APPEND srcs cppcms/controlleditemservice.cpp)
  LIST(APPEND srcs cppcms/controlleditemservicefactory.cpp)
  LIST(APPEND srcs cppcms/itemidjson.cpp)
  LIST(APPEND srcs cppcms/signalheadjson.cpp)
  LIST(APPEND srcs cppcms/signalaspectjson.cpp)
  LIST(APPEND srcs cppcms/signalflashjson.cpp)
ENDIF()

INCLUDE_DIRECTORIES( ./ )

ADD_EXECUTABLE(Signalbox ${srcs})
CONFIGURE_FILE(config.js . COPYONLY)

TARGET_LINK_LIBRARIES( Signalbox signalbox ${Boost_LIBRARIES} ${XercesC_LIBRARIES} )
IF( pigpio_FOUND )
  TARGET_LINK_LIBRARIES( Signalbox ${pigpiod_if2_LIBRARY})
ENDIF()
TARGET_LINK_LIBRARIES( Signalbox ${CPPCMS_LIBRARIES} )

SET( srcs )

LIST(APPEND srcs configuration/xercesguard.cpp)
LIST(APPEND srcs configuration/xercesstringdeleter.cpp)
LIST(APPEND srcs configuration/utils.cpp)
LIST(APPEND srcs configuration/configreader.cpp)

LIST(APPEND srcs signalheadpins.cpp)
LIST(APPEND srcs signalaspect.cpp)
LIST(APPEND srcs signalflash.cpp)
LIST(APPEND srcs turnoutstate.cpp)

LIST(APPEND srcs itemid.cpp)
LIST(APPEND srcs signalheaddata.cpp)
LIST(APPEND srcs trackcircuitmonitordata.cpp)

LIST(APPEND srcs digitalinputpin.cpp)

LIST(APPEND srcs signalhead.cpp)
LIST(APPEND srcs trackcircuitmonitor.cpp)
LIST(APPEND srcs turnoutmotor.cpp)
LIST(APPEND srcs servoturnoutmotor.cpp)

LIST(APPEND srcs signalheadfactory.cpp)
LIST(APPEND srcs trackcircuitmonitorfactory.cpp)

LIST(APPEND srcs controlleditemmanager.cpp)

LIST(APPEND srcs mockpinmanager.cpp)
LIST(APPEND srcs mockdigitaloutputpin.cpp)
LIST(APPEND srcs mockdigitalinputpin.cpp)

LIST(APPEND srcs mockrailtrafficcontrolclient.cpp)

IF( pigpio_FOUND )
  LIST(APPEND srcs pigpioddigitaloutputpin.cpp)
  LIST(APPEND srcs pigpioddigitalinputpin.cpp)
  LIST(APPEND srcs pigpiodpinmanager.cpp)
ENDIF()

ADD_LIBRARY( signalbox ${srcs} )

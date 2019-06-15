SET( srcs test.cpp )

LIST(APPEND srcs xercesguardtest.cpp)
LIST(APPEND srcs configreadertest.cpp)

LIST(APPEND srcs signalaspecttest.cpp)
LIST(APPEND srcs signalflashtest.cpp)
LIST(APPEND srcs turnoutstatetest.cpp)

LIST(APPEND srcs signalheaddatatest.cpp)
LIST(APPEND srcs trackcircuitmonitordatatest.cpp)
LIST(APPEND srcs servoturnoutmotordatatest.cpp)

LIST(APPEND srcs signalheadtest.cpp)
LIST(APPEND srcs trackcircuitmonitortest.cpp)
LIST(APPEND srcs servoturnoutmotortest.cpp)

LIST(APPEND srcs signalheadfactorytest.cpp)
LIST(APPEND srcs trackcircuitmonitorfactorytest.cpp)
LIST(APPEND srcs servoturnoutmotorfactorytest.cpp)

LIST(APPEND srcs controlleditemmanagertest.cpp)
LIST(APPEND srcs hardwareproviderregistrartest.cpp)

LIST(APPEND srcs mockpinmanagertest.cpp)
LIST(APPEND srcs mockdigitalinputpintest.cpp)
LIST(APPEND srcs mockrailtrafficcontrolclienttest.cpp)

LIST(APPEND srcs mockpca9685test.cpp)
LIST(APPEND srcs mocki2cdevicefactorytest.cpp)

IF( pigpio_FOUND )
  LIST(APPEND srcs pigpiodpinmanagertest.cpp)
ENDIF()

ADD_EXECUTABLE(SignalboxTest ${srcs})

TARGET_LINK_LIBRARIES( SignalboxTest signalbox ${Boost_LIBRARIES} ${XercesC_LIBRARIES} )
IF( pigpio_FOUND )
  TARGET_LINK_LIBRARIES( SignalboxTest ${pigpiod_if2_LIBRARY})
ENDIF()

CONFIGURE_FILE(singlesignalhead.xml . COPYONLY)
CONFIGURE_FILE(twosignalheads.xml . COPYONLY)
CONFIGURE_FILE(singletrackcircuitmonitor.xml . COPYONLY)
CONFIGURE_FILE(singleturnout.xml . COPYONLY)

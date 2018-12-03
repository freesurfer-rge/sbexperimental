SET( srcs test.cpp )

LIST(APPEND srcs xercesguardtest.cpp)
LIST(APPEND srcs signalheaddatatest.cpp)
LIST(APPEND srcs configreadertest.cpp)
LIST(APPEND srcs mockpinmanagertest.cpp)
LIST(APPEND srcs signalheadtest.cpp)
LIST(APPEND srcs signalstatetest.cpp)
LIST(APPEND srcs signalflashtest.cpp)

LIST(APPEND srcs pigpiodpinmanagertest.cpp)

ADD_EXECUTABLE(SignalboxTest ${srcs})

TARGET_LINK_LIBRARIES( SignalboxTest signalbox ${Boost_LIBRARIES} ${XercesC_LIBRARIES} )

CONFIGURE_FILE(singlesignalhead.xml . COPYONLY)
CONFIGURE_FILE(twosignalheads.xml . COPYONLY)

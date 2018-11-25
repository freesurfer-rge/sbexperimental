SET( srcs main.cpp )

LIST(APPEND srcs consoleoutputpin.cpp)
LIST(APPEND srcs consoleloop.cpp)

ADD_EXECUTABLE(Signalbox ${srcs})

TARGET_LINK_LIBRARIES( Signalbox signalbox ${Boost_LIBRARIES} ${XercesC_LIBRARIES} )
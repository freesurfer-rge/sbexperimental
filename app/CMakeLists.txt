SET( srcs main.cpp )

LIST(APPEND srcs consoledigitaloutputpin.cpp)
LIST(APPEND srcs consolepinmanager.cpp)
LIST(APPEND srcs consoleloop.cpp)
LIST(APPEND srcs cmdlineopts.cpp)
LIST(APPEND srcs outputselector.cpp)
LIST(APPEND srcs consoleoutputselector.cpp)

LIST(APPEND srcs pigpiodoutputselector.cpp)

ADD_EXECUTABLE(Signalbox ${srcs})

TARGET_LINK_LIBRARIES( Signalbox signalbox ${Boost_LIBRARIES} ${XercesC_LIBRARIES} )

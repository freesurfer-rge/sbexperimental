SET( srcs main.cpp )

ADD_EXECUTABLE(Signalbox ${srcs})

TARGET_LINK_LIBRARIES( Signalbox signalbox ${Boost_LIBRARIES} ${XercesC_LIBRARIES} )

#include <iostream>

#define PIGPIOD_SAFE_CALL( call ) { \
    const int err = call;	    \
    if( err < 0 ) {				    \
      std::cerr << "PiGPIOd error on line " << __LINE__ \
		<< " of file " __FILE__			\
		<< std::endl				\
		<< "Returned value was " << err << std::endl;	\
      exit(1); } }

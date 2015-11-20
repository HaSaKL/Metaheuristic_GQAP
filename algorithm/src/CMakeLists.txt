include_directories(${PARADISEO_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)

set (GQAP_SOURCES
			GQAP.cpp
		)
				
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
add_library (lGQAP ${GQAP_SOURCES})
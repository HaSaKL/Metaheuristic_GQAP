include_directories(${PARADISEO_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)

set (GQAP_SOURCES
			GQAP.cpp
			
			GQAP_Eval.h
			
			GQAP_ElementFlip_Neighbor.cpp
		)
				
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
add_library (lGQAP ${GQAP_SOURCES})
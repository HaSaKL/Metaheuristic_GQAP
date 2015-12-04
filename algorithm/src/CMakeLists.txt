include_directories(${PARADISEO_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)

set (GQAP_SOURCES
			GQAP_Solution.h
			GQAP.cpp
			
			GQAP_Eval.h
			
			GQAP_ElementFlip_Neighbor.cpp
			GQAP_ElementFlip_IncrEval.cpp
			
			GRASP_Alpha.h
			GRASP_FixedAlpha.cpp
			GRASP_UniformRandomAlpha.cpp
			GRASP_ReactiveAlpha.cpp
			
			SolutionPool.cpp
			PathRelinking.cpp

		)
				
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
add_library (lGQAP ${GQAP_SOURCES})
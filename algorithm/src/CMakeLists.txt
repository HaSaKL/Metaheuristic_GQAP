include_directories(${PARADISEO_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)

set (GQAP_SOURCES
			GQAP_Solution.h
			GQAP.cpp
			
			GQAP_Eval.h
			GQAP_IncrEval_Base_ElementFlip.h
			
			GQAP_ElementFlip_Neighbor.cpp
			GQAP_ElementFlip_IncrEval.cpp
			
			GRASP_Alpha.h
			GRASP_FixedAlpha.cpp
			GRASP_UniformRandomAlpha.cpp
			GRASP_ReactiveAlpha.cpp
			
			SolutionPool.cpp
			PathRelinking.cpp
			PR_Neighbor.cpp
			PR_IncrEval.cpp
			
			GQAP_CLI.h
			GQAP_GRASP_Algo.cpp
		)
				
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
add_library (lGQAP ${GQAP_SOURCES})
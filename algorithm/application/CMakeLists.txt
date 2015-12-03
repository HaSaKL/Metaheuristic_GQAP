include_directories(${PARADISEO_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(TEST_READ test_ReadProblem.cpp)
target_link_libraries(TEST_READ ${PARADISEO_LIBRARIES})
target_link_libraries(TEST_READ lGQAP)

add_executable(TEST_EVAL test_Evaluation.cpp)
target_link_libraries(TEST_EVAL ${PARADISEO_LIBRARIES})
target_link_libraries(TEST_EVAL lGQAP)

add_executable(TEST_ELMFLIP test_ElementFlip_Neighborhood.cpp)
target_link_libraries(TEST_ELMFLIP ${PARADISEO_LIBRARIES})
target_link_libraries(TEST_ELMFLIP lGQAP)

add_executable(TEST_ELMFLIP_HC test_ElementFlip_NH_HillClimbing.cpp)
target_link_libraries(TEST_ELMFLIP_HC ${PARADISEO_LIBRARIES})
target_link_libraries(TEST_ELMFLIP_HC lGQAP)

add_executable(TEST_POOL test_Pool.cpp)
target_link_libraries(TEST_POOL ${PARADISEO_LIBRARIES})
target_link_libraries(TEST_POOL lGQAP)

add_executable(TEST_PR test_PathRelinking.cpp)
target_link_libraries(TEST_PR ${PARADISEO_LIBRARIES})
target_link_libraries(TEST_PR lGQAP)
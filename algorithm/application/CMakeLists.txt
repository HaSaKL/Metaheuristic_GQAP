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

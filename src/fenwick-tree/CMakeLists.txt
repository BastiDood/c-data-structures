add_library(${PROJECT_NAME}_FenwickTree STATIC fenwick.c)
target_link_libraries(${PROJECT_NAME}_FenwickTree ${PROJECT_NAME}_Slice)
target_include_directories(${PROJECT_NAME}_FenwickTree PUBLIC .)

if(BUILD_TESTING)
    add_executable(${PROJECT_NAME}_FenwickTree_Test test.c)
    target_link_libraries(${PROJECT_NAME}_FenwickTree_Test ${PROJECT_NAME}_FenwickTree unity)
    add_test(NAME ${PROJECT_NAME}_FenwickTree_Suite COMMAND $<TARGET_FILE:${PROJECT_NAME}_FenwickTree_Test>)
endif()

add_library(${PROJECT_NAME}_BinaryHeap STATIC heap.c)
target_link_libraries(${PROJECT_NAME}_BinaryHeap ${PROJECT_NAME}_Slice ${PROJECT_NAME}_Stack)
target_include_directories(${PROJECT_NAME}_BinaryHeap PUBLIC .)

if(BUILD_TESTING)
    add_executable(${PROJECT_NAME}_BinaryHeap_Test test.c)
    target_link_libraries(${PROJECT_NAME}_BinaryHeap_Test ${PROJECT_NAME}_BinaryHeap unity)
    add_test(NAME ${PROJECT_NAME}_BinaryHeap_Suite COMMAND $<TARGET_FILE:${PROJECT_NAME}_BinaryHeap_Test>)
endif()

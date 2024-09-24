add_library(${PROJECT_NAME}_Queue STATIC queue.c)
target_link_libraries(${PROJECT_NAME}_Queue ${PROJECT_NAME}_Slice)
target_include_directories(${PROJECT_NAME}_Queue PUBLIC .)

if(BUILD_TESTING)
    add_executable(${PROJECT_NAME}_Queue_Test test.c)
    target_link_libraries(${PROJECT_NAME}_Queue_Test ${PROJECT_NAME}_Queue unity)
    add_test(NAME ${PROJECT_NAME}_Queue_Suite COMMAND $<TARGET_FILE:${PROJECT_NAME}_Queue_Test>)
endif()

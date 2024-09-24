add_library(${PROJECT_NAME}_Stack STATIC stack.c)
target_link_libraries(${PROJECT_NAME}_Stack ${PROJECT_NAME}_Slice)
target_include_directories(${PROJECT_NAME}_Stack PUBLIC .)

if(BUILD_TESTING)
    add_executable(${PROJECT_NAME}_Stack_Test test.c)
    target_link_libraries(${PROJECT_NAME}_Stack_Test ${PROJECT_NAME}_Stack unity)
    add_test(NAME ${PROJECT_NAME}_Stack_Suite COMMAND $<TARGET_FILE:${PROJECT_NAME}_Stack_Test>)
endif()

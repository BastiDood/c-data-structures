add_library(${PROJECT_NAME}_Slice STATIC slice.c)
target_include_directories(${PROJECT_NAME}_Slice PUBLIC .)

if(BUILD_TESTING)
    add_executable(${PROJECT_NAME}_Slice_Test test.c)
    target_link_libraries(${PROJECT_NAME}_Slice_Test ${PROJECT_NAME}_Slice unity)
    add_test(NAME ${PROJECT_NAME}_Slice_Suite COMMAND $<TARGET_FILE:${PROJECT_NAME}_Slice_Test>)
endif()

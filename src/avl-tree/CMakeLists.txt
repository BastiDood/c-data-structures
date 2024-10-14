add_library(${PROJECT_NAME}_AVLTree STATIC avl.c node.c)
target_include_directories(${PROJECT_NAME}_AVLTree PUBLIC .)

if(BUILD_TESTING)
    add_executable(${PROJECT_NAME}_AVLTree_Test test.c)
    target_link_libraries(${PROJECT_NAME}_AVLTree_Test ${PROJECT_NAME}_AVLTree unity)
    add_test(NAME ${PROJECT_NAME}_AVLTree_Suite COMMAND $<TARGET_FILE:${PROJECT_NAME}_AVLTree_Test>)
endif()

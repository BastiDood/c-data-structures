add_library(${PROJECT_NAME}_SinglyLinkedList STATIC node.c list.c)
target_include_directories(${PROJECT_NAME}_SinglyLinkedList PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_TESTING)
    add_executable(${PROJECT_NAME}_SinglyLinkedList_Test test.c)
    target_link_libraries(${PROJECT_NAME}_SinglyLinkedList_Test ${PROJECT_NAME}_SinglyLinkedList unity)
    add_test(NAME ${PROJECT_NAME}_SinglyLinkedList_Suite COMMAND $<TARGET_FILE:${PROJECT_NAME}_SinglyLinkedList_Test>)
endif()

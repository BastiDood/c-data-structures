add_library(${PROJECT_NAME}_DoublyLinkedList STATIC node.c list.c)
target_include_directories(${PROJECT_NAME}_DoublyLinkedList PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_TESTING)
    add_executable(${PROJECT_NAME}_DoublyLinkedList_Test test.c)
    target_link_libraries(${PROJECT_NAME}_DoublyLinkedList_Test ${PROJECT_NAME}_DoublyLinkedList unity)
    add_test(NAME ${PROJECT_NAME}_DoublyLinkedList_Suite COMMAND $<TARGET_FILE:${PROJECT_NAME}_DoublyLinkedList_Test>)
endif()

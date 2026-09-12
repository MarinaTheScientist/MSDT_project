add_executable(test_rect_basic_methods test_rect_basic_methods.cpp)
target_link_libraries(test_rect_basic_methods PRIVATE lab1lib)
add_test(NAME rect_basic_methods COMMAND test_rect_basic_methods)

add_executable(test_rect_properties test_rect_properties.cpp)
target_link_libraries(test_rect_properties PRIVATE lab1lib)
add_test(NAME rect_properties COMMAND test_rect_properties)

add_executable(test_rect_operations test_rect_operations.cpp)
target_link_libraries(test_rect_operations PRIVATE lab1lib)
add_test(NAME rect_operations COMMAND test_rect_operations)

add_executable(test_bounding_rect test_bounding_rect.cpp)
target_link_libraries(test_bounding_rect PRIVATE lab1lib)
add_test(NAME bounding_rect COMMAND test_bounding_rect)
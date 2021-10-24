find_package (Boost COMPONENTS unit_test_framework)

add_executable (test "test_display.cpp")

target_include_directories(test PRIVATE ${BOOST_INCLUDE_DIRS})

add_test(NAME test COMMAND test)

target_link_libraries(test ${Boost_LIBRARIES} lcd_logic logging)
target_include_directories(test PUBLIC ${CMAKE_SOURCE_DIR}/include ${Boost_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../lcd_logic)
target_precompile_headers (test REUSE_FROM lcd_logic)

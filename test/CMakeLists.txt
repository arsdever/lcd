find_package (Boost COMPONENTS unit_test_framework REQUIRED)

include (BoostTestHelpers)

add_boost_test (lcd_logic_test_suite.cpp lcd_logic)
target_include_directories (lcd_logic_test_suite PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries (lcd_logic_test_suite ${Boost_LIBRARIES} logging)

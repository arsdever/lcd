find_package (Boost COMPONENTS unit_test_framework REQUIRED)

include (BoostTestHelpers)

add_boost_test (test_display.cpp lcd_logic)
target_include_directories (test_display PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries (test_display ${Boost_LIBRARIES} logging)

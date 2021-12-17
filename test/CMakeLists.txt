find_package (Boost COMPONENTS unit_test_framework REQUIRED)

include (BoostTestHelpers)

set (SOURCES "lcd_logic_test.cpp")
add_boost_test (TEST_EXECUTABLE_NAME lcd_logic_tests SOURCES ${SOURCES} DEPENDENCIES lcd_logic logging)
target_include_directories (lcd_logic_tests PUBLIC ${Boost_INCLUDE_DIRS})

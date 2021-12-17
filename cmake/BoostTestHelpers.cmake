# https://eb2.co/blog/2015/06/driving-boost.test-with-cmake/
# Copyright © 2017 Eric Scott Barr

function (add_boost_test TEST_EXECUTABLE_NAME SOURCES DEPENDENCIES)
# region Parse arguments

	set (single_value TEST_EXECUTABLE_NAME)
	set (multi_value SOURCES DEPENDENCIES)

	cmake_parse_arguments (PARSE_ARGV 0 boost_test "" "${single_value}" "${multi_value}")

# endregion

# region Generate main source file

	file (
		WRITE ${CMAKE_CURRENT_BINARY_DIR}/test_main.cpp
"#define BOOST_TEST_MODULE main
#include <boost/test/included/unit_test.hpp>"
	)

# endregion

	add_executable (
		${boost_test_TEST_EXECUTABLE_NAME}
		${CMAKE_CURRENT_BINARY_DIR}/test_main.cpp
		${boost_test_SOURCES}
	)
	target_link_libraries (
		${boost_test_TEST_EXECUTABLE_NAME}
		${boost_test_DEPENDENCIES}
	)

	foreach (SF ${boost_test_SOURCES})
		file (
			READ "${SF}"
			SOURCE_FILE_CONTENTS
		)
		#string (
		#	REGEX MATCHALL "BOOST_TEST_MODULE[\\t ]+([A-Za-z_0-9]+)"
		#	TEST_MODULE_NAME_REGEX "${SOURCE_FILE_CONTENTS}"
		#)
		#string (
		#	REGEX REPLACE "(BOOST_TEST_MODULE) ([A-Za-z_0-9]+)" "\\2"
		#	TEST_MODULE_NAME "${TEST_MODULE_NAME_REGEX}"
		#)
		string (
			REGEX MATCHALL "BOOST_AUTO_TEST_CASE\\( *([A-Za-z_0-9]+) *\\)" 
			FOUND_TESTS ${SOURCE_FILE_CONTENTS}
		)

		foreach (HIT ${FOUND_TESTS})
			string (
				REGEX REPLACE ".*\\( *([A-Za-z_0-9]+) *\\).*" "\\1"
				TEST_NAME ${HIT}
			)

			add_test (
				NAME "${boost_test_TEST_EXECUTABLE_NAME}.${TEST_NAME}" 
				COMMAND ${boost_test_TEST_EXECUTABLE_NAME} --run_test=${boost_test_TEST_EXECUTABLE_NAME}/${TEST_MODULE_NAME}/${TEST_NAME}
			)
		endforeach ()
	endforeach ()
endfunction ()

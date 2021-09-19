# CMake generated file
# The compiler generated pdb file needs to be written to disk
# by mspdbsrv. The foreach retry loop is needed to make sure
# the pdb file is ready to be copied.

foreach(retry RANGE 1 30)
  if (EXISTS "C:/lcd/build/x64-Debug/src/lcd_logic/lcd_logic.dir/${PDB_PREFIX}lcd_logic.pdb" AND "C:/lcd/build/x64-Debug/src/lcd_logic/lcd_logic.dir/${PDB_PREFIX}lcd_logic.pdb  " IS_NEWER_THAN "C:/lcd/build/x64-Debug/src/lcd_logic/lcd_logic_test.dir/${PDB_PREFIX}lcd_logic.pdb")
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy "C:/lcd/build/x64-Debug/src/lcd_logic/lcd_logic.dir/${PDB_PREFIX}lcd_logic.pdb" "C:/lcd/build/x64-Debug/src/lcd_logic/lcd_logic_test.dir/${PDB_PREFIX}" RESULT_VARIABLE result  ERROR_QUIET)
    if (NOT result EQUAL 0)
      execute_process(COMMAND ${CMAKE_COMMAND} -E sleep 1)
    else()
      break()
    endif()
  elseif(NOT EXISTS "C:/lcd/build/x64-Debug/src/lcd_logic/lcd_logic.dir/${PDB_PREFIX}lcd_logic.pdb")
    execute_process(COMMAND ${CMAKE_COMMAND} -E sleep 1)
  endif()
endforeach()

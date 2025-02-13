# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/PanddaInspectGtk4Window_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/PanddaInspectGtk4Window_autogen.dir/ParseCache.txt"
  "PanddaInspectGtk4Window_autogen"
  )
endif()

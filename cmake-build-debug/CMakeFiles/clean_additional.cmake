# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\OCCT_CAD_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\OCCT_CAD_autogen.dir\\ParseCache.txt"
  "OCCT_CAD_autogen"
  )
endif()

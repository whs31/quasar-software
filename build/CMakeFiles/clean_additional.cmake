# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Quasar_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Quasar_autogen.dir/ParseCache.txt"
  "Quasar_autogen"
  )
endif()

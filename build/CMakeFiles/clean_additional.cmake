# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/attach_bug_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/attach_bug_autogen.dir/ParseCache.txt"
  "attach_bug_autogen"
  )
endif()

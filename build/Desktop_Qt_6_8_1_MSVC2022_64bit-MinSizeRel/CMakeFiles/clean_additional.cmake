# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "MinSizeRel")
  file(REMOVE_RECURSE
  "CMakeFiles\\appuntitled1_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appuntitled1_autogen.dir\\ParseCache.txt"
  "appuntitled1_autogen"
  "serverlib\\CMakeFiles\\serverlib_autogen.dir\\AutogenUsed.txt"
  "serverlib\\CMakeFiles\\serverlib_autogen.dir\\ParseCache.txt"
  "serverlib\\serverlib_autogen"
  )
endif()

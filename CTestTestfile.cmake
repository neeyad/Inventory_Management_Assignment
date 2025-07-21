# CMake generated Testfile for 
# Source directory: C:/Users/Neerajy/Documents/AI Native Assignemnt 1
# Build directory: C:/Users/Neerajy/Documents/AI Native Assignemnt 1
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(UnitTests "C:/Users/Neerajy/Documents/AI Native Assignemnt 1/Debug/UnitTests.exe")
  set_tests_properties(UnitTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Neerajy/Documents/AI Native Assignemnt 1/CMakeLists.txt;61;add_test;C:/Users/Neerajy/Documents/AI Native Assignemnt 1/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(UnitTests "C:/Users/Neerajy/Documents/AI Native Assignemnt 1/Release/UnitTests.exe")
  set_tests_properties(UnitTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Neerajy/Documents/AI Native Assignemnt 1/CMakeLists.txt;61;add_test;C:/Users/Neerajy/Documents/AI Native Assignemnt 1/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(UnitTests "C:/Users/Neerajy/Documents/AI Native Assignemnt 1/MinSizeRel/UnitTests.exe")
  set_tests_properties(UnitTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Neerajy/Documents/AI Native Assignemnt 1/CMakeLists.txt;61;add_test;C:/Users/Neerajy/Documents/AI Native Assignemnt 1/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(UnitTests "C:/Users/Neerajy/Documents/AI Native Assignemnt 1/RelWithDebInfo/UnitTests.exe")
  set_tests_properties(UnitTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Neerajy/Documents/AI Native Assignemnt 1/CMakeLists.txt;61;add_test;C:/Users/Neerajy/Documents/AI Native Assignemnt 1/CMakeLists.txt;0;")
else()
  add_test(UnitTests NOT_AVAILABLE)
endif()

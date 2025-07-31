cmake_minimum_required(VERSION 3.12)

set( PROGRAM_NAME "test-sprintf-float")

project (${PROGRAM_NAME} DESCRIPTION "A test of printing float valuesing using sprintf" LANGUAGES CXX C)

############################################################
set(CMAKE_CXX_STANDARD 11)

if (MSVC)
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(
  -fexceptions 
  -Wall 
  -Wextra 
  -Wconversion 
  -Wunused-parameter
  )
endif()

include(GNUInstallDirs)

set(CMAKE_CXX_FLAGS_ASAN
  "-fsanitize=address -fno-optimize-sibling-calls -fsanitize-address-use-after-scope -fno-omit-frame-pointer -g -O1"
  CACHE STRING "Flags used by the C++ compiler during AddressSanitizer builds."
  FORCE)

if( NOT DEFINED CMAKE_BUILD_TYPE )
  MESSAGE( STATUS "To use Release mode, use \"cmake .. -DCMAKE_BUILD_TYPE=Release\"" )
  MESSAGE( STATUS "To use AddressSanitizer, use \"cmake .. -DCMAKE_BUILD_TYPE=asan\"" )
elseif( CMAKE_BUILD_TYPE STREQUAL "Release" )
  MESSAGE( STATUS "Using Release mode - CMAKE_BUILD_TYPE : \"${CMAKE_BUILD_TYPE}\"")
elseif( CMAKE_BUILD_TYPE STREQUAL "asan" )
  MESSAGE( STATUS "Using AddressSanitizer - CMAKE_BUILD_TYPE : \"${CMAKE_BUILD_TYPE}\"")
else()
  MESSAGE( STATUS "CMAKE_BUILD_TYPE : \"${CMAKE_BUILD_TYPE}\"")
  MESSAGE( STATUS "To use Release mode, use \"cmake .. -DCMAKE_BUILD_TYPE=Release\"" )
  MESSAGE( STATUS "To use AddressSanitizer, use \"cmake .. -DCMAKE_BUILD_TYPE=asan\"" )
endif()

# Set a default build type if none was specified
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

############################################################

file(GLOB SRC_FILES source/*)
add_executable(${PROGRAM_NAME} ${SRC_FILES})

############################################################
# add basic tests
enable_testing()

add_test(NAME "1-over-3--0-digits"  COMMAND ${PROGRAM_NAME} -numerator 1 -denominator 3 -digits 0  -expected_string 0 )
add_test(NAME "1-over-3--1-digits"  COMMAND ${PROGRAM_NAME} -numerator 1 -denominator 3 -digits 1  -expected_string 0.3 )
add_test(NAME "1-over-3--2-digits"  COMMAND ${PROGRAM_NAME} -numerator 1 -denominator 3 -digits 2  -expected_string 0.33 )
add_test(NAME "1-over-3--3-digits"  COMMAND ${PROGRAM_NAME} -numerator 1 -denominator 3 -digits 3  -expected_string 0.333 )
add_test(NAME "1-over-3--4-digits"  COMMAND ${PROGRAM_NAME} -numerator 1 -denominator 3 -digits 4  -expected_string 0.3333 )
add_test(NAME "1-over-3--5-digits"  COMMAND ${PROGRAM_NAME} -numerator 1 -denominator 3 -digits 5  -expected_string 0.33333 )
add_test(NAME "1-over-3--6-digits"  COMMAND ${PROGRAM_NAME} -numerator 1 -denominator 3 -digits 6  -expected_string 0.333333 )
add_test(NAME "1-over-3--7-digits"  COMMAND ${PROGRAM_NAME} -numerator 1 -denominator 3 -digits 7  -expected_string 0.3333333 )
add_test(NAME "1-over-3--8-digits"  COMMAND ${PROGRAM_NAME} -numerator 1 -denominator 3 -digits 8  -expected_string 0.33333333 )
add_test(NAME "1-over-3--9-digits"  COMMAND ${PROGRAM_NAME} -numerator 1 -denominator 3 -digits 9  -expected_string 0.333333333 )
add_test(NAME "1-over-3--10-digits" COMMAND ${PROGRAM_NAME} -numerator 1 -denominator 3 -digits 10 -expected_string 0.3333333333 )
add_test(NAME "1-over-3--11-digits" COMMAND ${PROGRAM_NAME} -numerator 1 -denominator 3 -digits 11 -expected_string 0.33333333333 )
add_test(NAME "1-over-3--12-digits" COMMAND ${PROGRAM_NAME} -numerator 1 -denominator 3 -digits 12 -expected_string 0.333333333333 )
set_tests_properties("1-over-3--8-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("1-over-3--9-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("1-over-3--10-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("1-over-3--11-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("1-over-3--12-digits" PROPERTIES WILL_FAIL TRUE)

add_test(NAME "4-over-3--0-digits"  COMMAND ${PROGRAM_NAME} -numerator 4 -denominator 3 -digits 0  -expected_string 1 )
add_test(NAME "4-over-3--1-digits"  COMMAND ${PROGRAM_NAME} -numerator 4 -denominator 3 -digits 1  -expected_string 1.3 )
add_test(NAME "4-over-3--2-digits"  COMMAND ${PROGRAM_NAME} -numerator 4 -denominator 3 -digits 2  -expected_string 1.33 )
add_test(NAME "4-over-3--3-digits"  COMMAND ${PROGRAM_NAME} -numerator 4 -denominator 3 -digits 3  -expected_string 1.333 )
add_test(NAME "4-over-3--4-digits"  COMMAND ${PROGRAM_NAME} -numerator 4 -denominator 3 -digits 4  -expected_string 1.3333 )
add_test(NAME "4-over-3--5-digits"  COMMAND ${PROGRAM_NAME} -numerator 4 -denominator 3 -digits 5  -expected_string 1.33333 )
add_test(NAME "4-over-3--6-digits"  COMMAND ${PROGRAM_NAME} -numerator 4 -denominator 3 -digits 6  -expected_string 1.333333 )
add_test(NAME "4-over-3--7-digits"  COMMAND ${PROGRAM_NAME} -numerator 4 -denominator 3 -digits 7  -expected_string 1.3333333 )
add_test(NAME "4-over-3--8-digits"  COMMAND ${PROGRAM_NAME} -numerator 4 -denominator 3 -digits 8  -expected_string 1.33333333 )
add_test(NAME "4-over-3--9-digits"  COMMAND ${PROGRAM_NAME} -numerator 4 -denominator 3 -digits 9  -expected_string 1.333333333 )
add_test(NAME "4-over-3--10-digits" COMMAND ${PROGRAM_NAME} -numerator 4 -denominator 3 -digits 10 -expected_string 1.3333333333 )
add_test(NAME "4-over-3--11-digits" COMMAND ${PROGRAM_NAME} -numerator 4 -denominator 3 -digits 11 -expected_string 1.33333333333 )
add_test(NAME "4-over-3--12-digits" COMMAND ${PROGRAM_NAME} -numerator 4 -denominator 3 -digits 12 -expected_string 1.333333333333 )
set_tests_properties("4-over-3--7-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("4-over-3--8-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("4-over-3--9-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("4-over-3--10-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("4-over-3--11-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("4-over-3--12-digits" PROPERTIES WILL_FAIL TRUE)

add_test(NAME "0.333333333333333--0-digits"  COMMAND ${PROGRAM_NAME} -float 0.333333333333333 -digits 0  -expected_string 0)
add_test(NAME "0.333333333333333--1-digits"  COMMAND ${PROGRAM_NAME} -float 0.333333333333333 -digits 1  -expected_string 0.3 )
add_test(NAME "0.333333333333333--2-digits"  COMMAND ${PROGRAM_NAME} -float 0.333333333333333 -digits 2  -expected_string 0.33 )
add_test(NAME "0.333333333333333--3-digits"  COMMAND ${PROGRAM_NAME} -float 0.333333333333333 -digits 3  -expected_string 0.333 )
add_test(NAME "0.333333333333333--4-digits"  COMMAND ${PROGRAM_NAME} -float 0.333333333333333 -digits 4  -expected_string 0.3333 )
add_test(NAME "0.333333333333333--5-digits"  COMMAND ${PROGRAM_NAME} -float 0.333333333333333 -digits 5  -expected_string 0.33333 )
add_test(NAME "0.333333333333333--6-digits"  COMMAND ${PROGRAM_NAME} -float 0.333333333333333 -digits 6  -expected_string 0.333333 )
add_test(NAME "0.333333333333333--7-digits"  COMMAND ${PROGRAM_NAME} -float 0.333333333333333 -digits 7  -expected_string 0.3333333 )
add_test(NAME "0.333333333333333--8-digits"  COMMAND ${PROGRAM_NAME} -float 0.333333333333333 -digits 8  -expected_string 0.33333333 )
add_test(NAME "0.333333333333333--9-digits"  COMMAND ${PROGRAM_NAME} -float 0.333333333333333 -digits 9  -expected_string 0.333333333 )
add_test(NAME "0.333333333333333--10-digits" COMMAND ${PROGRAM_NAME} -float 0.333333333333333 -digits 10 -expected_string 0.3333333333 )
add_test(NAME "0.333333333333333--11-digits" COMMAND ${PROGRAM_NAME} -float 0.333333333333333 -digits 11 -expected_string 0.33333333333 )
add_test(NAME "0.333333333333333--12-digits" COMMAND ${PROGRAM_NAME} -float 0.333333333333333 -digits 12 -expected_string 0.333333333333 )
set_tests_properties("0.333333333333333--8-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("0.333333333333333--9-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("0.333333333333333--10-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("0.333333333333333--11-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("0.333333333333333--12-digits" PROPERTIES WILL_FAIL TRUE)

add_test(NAME "42-over-1260--0-digits"  COMMAND ${PROGRAM_NAME} -numerator 42 -denominator 1260 -digits 0  -expected_string 0 )
add_test(NAME "42-over-1260--1-digits"  COMMAND ${PROGRAM_NAME} -numerator 42 -denominator 1260 -digits 1  -expected_string 0.0 )
add_test(NAME "42-over-1260--2-digits"  COMMAND ${PROGRAM_NAME} -numerator 42 -denominator 1260 -digits 2  -expected_string 0.03 )
add_test(NAME "42-over-1260--3-digits"  COMMAND ${PROGRAM_NAME} -numerator 42 -denominator 1260 -digits 3  -expected_string 0.033 )
add_test(NAME "42-over-1260--4-digits"  COMMAND ${PROGRAM_NAME} -numerator 42 -denominator 1260 -digits 4  -expected_string 0.0333 )
add_test(NAME "42-over-1260--5-digits"  COMMAND ${PROGRAM_NAME} -numerator 42 -denominator 1260 -digits 5  -expected_string 0.03333 )
add_test(NAME "42-over-1260--6-digits"  COMMAND ${PROGRAM_NAME} -numerator 42 -denominator 1260 -digits 6  -expected_string 0.033333 )
add_test(NAME "42-over-1260--7-digits"  COMMAND ${PROGRAM_NAME} -numerator 42 -denominator 1260 -digits 7  -expected_string 0.0333333 )
add_test(NAME "42-over-1260--8-digits"  COMMAND ${PROGRAM_NAME} -numerator 42 -denominator 1260 -digits 8  -expected_string 0.03333333 )
add_test(NAME "42-over-1260--9-digits"  COMMAND ${PROGRAM_NAME} -numerator 42 -denominator 1260 -digits 9  -expected_string 0.033333333 )
add_test(NAME "42-over-1260--10-digits" COMMAND ${PROGRAM_NAME} -numerator 42 -denominator 1260 -digits 10 -expected_string 0.0333333333 )
add_test(NAME "42-over-1260--11-digits" COMMAND ${PROGRAM_NAME} -numerator 42 -denominator 1260 -digits 11 -expected_string 0.03333333333 )
add_test(NAME "42-over-1260--12-digits" COMMAND ${PROGRAM_NAME} -numerator 42 -denominator 1260 -digits 12 -expected_string 0.033333333333 )
set_tests_properties("42-over-1260--8-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("42-over-1260--9-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("42-over-1260--10-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("42-over-1260--11-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("42-over-1260--12-digits" PROPERTIES WILL_FAIL TRUE)

add_test(NAME "preset_float_equation--0-digits"  COMMAND ${PROGRAM_NAME} -use_preset_float_equation -digits 0  -expected_string 0 )
add_test(NAME "preset_float_equation--1-digits"  COMMAND ${PROGRAM_NAME} -use_preset_float_equation -digits 1  -expected_string 0.0 )
add_test(NAME "preset_float_equation--2-digits"  COMMAND ${PROGRAM_NAME} -use_preset_float_equation -digits 2  -expected_string 0.03 )
add_test(NAME "preset_float_equation--3-digits"  COMMAND ${PROGRAM_NAME} -use_preset_float_equation -digits 3  -expected_string 0.033 )
add_test(NAME "preset_float_equation--4-digits"  COMMAND ${PROGRAM_NAME} -use_preset_float_equation -digits 4  -expected_string 0.0333 )
add_test(NAME "preset_float_equation--5-digits"  COMMAND ${PROGRAM_NAME} -use_preset_float_equation -digits 5  -expected_string 0.03333 )
add_test(NAME "preset_float_equation--6-digits"  COMMAND ${PROGRAM_NAME} -use_preset_float_equation -digits 6  -expected_string 0.033333 )
add_test(NAME "preset_float_equation--7-digits"  COMMAND ${PROGRAM_NAME} -use_preset_float_equation -digits 7  -expected_string 0.0333333 )
add_test(NAME "preset_float_equation--8-digits"  COMMAND ${PROGRAM_NAME} -use_preset_float_equation -digits 8  -expected_string 0.03333333 )
add_test(NAME "preset_float_equation--9-digits"  COMMAND ${PROGRAM_NAME} -use_preset_float_equation -digits 9  -expected_string 0.033333333 )
add_test(NAME "preset_float_equation--10-digits" COMMAND ${PROGRAM_NAME} -use_preset_float_equation -digits 10 -expected_string 0.0333333333 )
add_test(NAME "preset_float_equation--11-digits" COMMAND ${PROGRAM_NAME} -use_preset_float_equation -digits 11 -expected_string 0.03333333333 )
add_test(NAME "preset_float_equation--12-digits" COMMAND ${PROGRAM_NAME} -use_preset_float_equation -digits 12 -expected_string 0.033333333333 )
set_tests_properties("preset_float_equation--8-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("preset_float_equation--9-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("preset_float_equation--10-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("preset_float_equation--11-digits" PROPERTIES WILL_FAIL TRUE)
set_tests_properties("preset_float_equation--12-digits" PROPERTIES WILL_FAIL TRUE)
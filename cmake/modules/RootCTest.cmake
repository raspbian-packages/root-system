#---------------------------------------------------------------------------------------------------
#  RootCTest.cmake
#   - basic setup for testing ROOT using CTest
#---------------------------------------------------------------------------------------------------

#---Deduce the build name--------------------------------------------------------
set(BUILDNAME ${ROOT_ARCHTECTURE}-${CMAKE_BUILD_TYPE})

enable_testing()
include(CTest)

#---A number of operations to allow running the tests from the build directory-----------------------
set(ROOT_DIR ${CMAKE_BINARY_DIR})

execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/etc ${CMAKE_BINARY_DIR}/etc)
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/icons ${CMAKE_BINARY_DIR}/icons)
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/fonts ${CMAKE_BINARY_DIR}/fonts)
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/macros ${CMAKE_BINARY_DIR}/macros)

#---Install the headers which are needed to run the tests from the binary tree-----------------
add_custom_target(move_headers ALL ${CMAKE_COMMAND} -DPREFIX=${CMAKE_BINARY_DIR}
                                   -DCOMPONENTS="headers\;tutorials"
                                   -P ${CMAKE_SOURCE_DIR}/cmake/scripts/local_install.cmake )

execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/cint/reflex/python/genreflex ${CMAKE_BINARY_DIR}/lib/python/genreflex)

#--Add all subdirectories with tests-----------------------------------------------------------

get_property(test_dirs GLOBAL PROPERTY ROOT_TEST_SUBDIRS)
foreach(d ${test_dirs})
  add_subdirectory(${d})
endforeach()

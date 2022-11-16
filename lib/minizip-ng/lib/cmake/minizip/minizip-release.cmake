#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MINIZIP::minizip" for configuration "Release"
set_property(TARGET MINIZIP::minizip APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MINIZIP::minizip PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libminizip.a"
  )

list(APPEND _cmake_import_check_targets MINIZIP::minizip )
list(APPEND _cmake_import_check_files_for_MINIZIP::minizip "${_IMPORT_PREFIX}/lib/libminizip.a" )

# Import target "MINIZIP::bzip2" for configuration "Release"
set_property(TARGET MINIZIP::bzip2 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MINIZIP::bzip2 PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libbzip2.a"
  )

list(APPEND _cmake_import_check_targets MINIZIP::bzip2 )
list(APPEND _cmake_import_check_files_for_MINIZIP::bzip2 "${_IMPORT_PREFIX}/lib/libbzip2.a" )

# Import target "MINIZIP::liblzma" for configuration "Release"
set_property(TARGET MINIZIP::liblzma APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MINIZIP::liblzma PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/liblzma.a"
  )

list(APPEND _cmake_import_check_targets MINIZIP::liblzma )
list(APPEND _cmake_import_check_files_for_MINIZIP::liblzma "${_IMPORT_PREFIX}/lib/liblzma.a" )

# Import target "MINIZIP::libzstd_static" for configuration "Release"
set_property(TARGET MINIZIP::libzstd_static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MINIZIP::libzstd_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libzstd.a"
  )

list(APPEND _cmake_import_check_targets MINIZIP::libzstd_static )
list(APPEND _cmake_import_check_files_for_MINIZIP::libzstd_static "${_IMPORT_PREFIX}/lib/libzstd.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "quant_fin::quant_fin_lib" for configuration ""
set_property(TARGET quant_fin::quant_fin_lib APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(quant_fin::quant_fin_lib PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_NOCONFIG "spdlog::spdlog"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libquant_fin_lib.so.1.0"
  IMPORTED_SONAME_NOCONFIG "libquant_fin_lib.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS quant_fin::quant_fin_lib )
list(APPEND _IMPORT_CHECK_FILES_FOR_quant_fin::quant_fin_lib "${_IMPORT_PREFIX}/lib/libquant_fin_lib.so.1.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

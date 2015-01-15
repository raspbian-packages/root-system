# - Locate GFAL library
# Defines:
#
#  GFAL_FOUND
#  GFAL_INCLUDE_DIR
#  GFAL_INCLUDE_DIRS (not cached)
#  GFAL_LIBRARIES

find_path(GFAL_INCLUDE_DIR NAMES gfal_api.h HINTS ${GFAL_DIR}/include $ENV{GFAL_DIR}/inlcude)
find_library(GFAL_LIBRARIES NAMES gfal gfal2 HINTS ${GFAL_DIR}/lib $ENV{GFAL_DIR}/lib)
find_path(SRM_IFCE_INCLUDE_DIR  gfal_srm_ifce_types.h HINTS ${SRM_IFCE_DIR}/include $ENV{SRM_IFCE_DIR}/include) 

set(GFAL_INCLUDE_DIRS ${GFAL_INCLUDE_DIR} ${SRM_IFCE_INCLUDE_DIR})

# handle the QUIETLY and REQUIRED arguments and set GFAL_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GFAL DEFAULT_MSG GFAL_INCLUDE_DIR SRM_IFCE_INCLUDE_DIR GFAL_LIBRARIES)

mark_as_advanced(GFAL_FOUND GFAL_INCLUDE_DIR GFAL_LIBRARIES SRM_IFCE_INCLUDE_DIR)
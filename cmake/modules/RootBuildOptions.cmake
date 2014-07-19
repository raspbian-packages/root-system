set(root_build_options)

#---------------------------------------------------------------------------------------------------
#---ROOT_BUILD_OPTION( name defvalue [description] )
#---------------------------------------------------------------------------------------------------
function(ROOT_BUILD_OPTION name defvalue)
  if(ARGN)
    set(description ${ARGN})
  else()
    set(description " ")
  endif()    
  option(${name} "${description}" ${defvalue})
  set(root_build_options ${root_build_options} ${name} PARENT_SCOPE )
endfunction()

#---------------------------------------------------------------------------------------------------
#---ROOT_SHOW_OPTIONS([var] )
#---------------------------------------------------------------------------------------------------
function(ROOT_SHOW_OPTIONS)
  set(enabled)
  foreach(opt ${root_build_options})
    if(${opt})
      set(enabled "${enabled} ${opt}")
    endif()
  endforeach()
  if(NOT ARGN)
    message(STATUS "Enabled support for: ${enabled}")
  else()
    set(${ARGN} "${enabled}" PARENT_SCOPE)
  endif()
endfunction()

#---------------------------------------------------------------------------------------------------
#---ROOT_WRITE_OPTIONS(file )
#---------------------------------------------------------------------------------------------------
function(ROOT_WRITE_OPTIONS file)
  file(WRITE ${file} "#---Options enabled for the build of ROOT-----------------------------------------------\n")
  foreach(opt ${root_build_options})
    if(${opt})
      file(APPEND ${file} "set(${opt} ON)\n")
    else()
      file(APPEND ${file} "set(${opt} OFF)\n")
    endif()
  endforeach()
endfunction()

#---Define default values depending on platform before the options are defined----------------------
if(WIN32)
  set(x11_defvalue OFF)
  set(memstat_defvalue OFF)
  set(explicitlink_defvalue ON)
  set(cocoa_defvalue OFF)
  set(davix_defvalue OFF)
elseif(APPLE)
  execute_process(COMMAND sw_vers "-productVersion" COMMAND cut -d . -f 1-2
                  OUTPUT_VARIABLE MACOSX_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(memstat_defvalue ON)
  set(explicitlink_defvalue ON)
  if(MACOSX_VERSION VERSION_GREATER 10.7 AND ${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    set(x11_defvalue OFF)
    set(cocoa_defvalue ON)
  else()
    set(x11_defvalue ON)
    set(cocoa_defvalue OFF)
  endif()
  set(davix_defvalue OFF)
else()
  set(x11_defvalue ON)
  set(memstat_defvalue ON)
  set(explicitlink_defvalue ON)
  set(cocoa_defvalue OFF)
  set(davix_defvalue OFF)
endif()

if(all)
 set(gdml_defvalue ON)
 set(http_defvalue ON)
 set(qt_defvalue ON)
 set(qtgsi_defvalue ON)
 set(roofit_defvalue ON)
 set(minuit2_defvalue ON)
 set(table_defvalue ON)
 set(unuran_defvalue ON)
 set(vc_defvalue ON)
 set(vdt_defvalue ON)
else()
 set(gdml_defvalue OFF)
 set(http_defvalue OFF)
 set(qt_defvalue OFF)
 set(qtgsi_defvalue OFF)
 set(roofit_defvalue OFF)
 set(minuit2_defvalue OFF)
 set(table_defvalue OFF)
 set(unuran_defvalue OFF)
 set(vc_defvalue OFF)
 set(vdt_defvalue OFF)
endif()

ROOT_BUILD_OPTION(afdsmgrd OFF "Dataset manager for PROOF-based analysis facilities")
ROOT_BUILD_OPTION(afs OFF "AFS support, requires AFS libs and objects")
ROOT_BUILD_OPTION(alien ON "AliEn support, requires libgapiUI from ALICE")
ROOT_BUILD_OPTION(asimage ON "Image processing support, requires libAfterImage")
ROOT_BUILD_OPTION(astiff ON "Include tiff support in image processing")
ROOT_BUILD_OPTION(bonjour ON "Bonjour support, requires libdns_sd and/or Avahi")
ROOT_BUILD_OPTION(builtin_afterimage ON "Built included libAfterImage, or use system libAfterImage")
ROOT_BUILD_OPTION(builtin_ftgl ON "Built included libFTGL, or use system libftgl")
ROOT_BUILD_OPTION(builtin_freetype OFF "Built included libfreetype, or use system libfreetype")
ROOT_BUILD_OPTION(builtin_glew ON "Built included libGLEW, or use system libGLEW")
ROOT_BUILD_OPTION(builtin_pcre OFF "Built included libpcre, or use system libpcre")
ROOT_BUILD_OPTION(builtin_zlib OFF "Built included libz, or use system libz")
ROOT_BUILD_OPTION(builtin_lzma OFF "Built included liblzma, or use system liblzma")
ROOT_BUILD_OPTION(builtin_davix OFF "Built the Davix library internally (downloading tarfile from the Web)")
ROOT_BUILD_OPTION(builtin_gsl OFF "Built the GSL library internally (downloading tarfile from the Web)")
ROOT_BUILD_OPTION(builtin_cfitsio OFF "Built the FITSIO library internally (downloading tarfile from the Web)")
ROOT_BUILD_OPTION(builtin_xrootd OFF "Built the XROOTD internally (downloading tarfile from the Web)")
ROOT_BUILD_OPTION(cxx11 OFF "Build using C++11 compatible mode, requires gcc > 4.7.x or clang")
ROOT_BUILD_OPTION(libcxx OFF "Build using libc++, requires cxx11 option (MacOS X only, for the time being)")
ROOT_BUILD_OPTION(castor ON "CASTOR support, requires libshift from CASTOR >= 1.5.2")
ROOT_BUILD_OPTION(chirp ON "Chirp support (Condor remote I/O), requires libchirp_client")
ROOT_BUILD_OPTION(cintex ON "Build the libCintex Reflex interface library")
ROOT_BUILD_OPTION(clarens ON "Clarens RPC support, optionally used by PROOF")
ROOT_BUILD_OPTION(cling OFF "Enable new CLING C++ interpreter")
ROOT_BUILD_OPTION(cocoa ${cocoa_defvalue} "Use native Cocoa/Quartz graphics backend (MacOS X only)")
ROOT_BUILD_OPTION(davix ${davix_defvalue} "DavIx library for HTTP/WEBDAV access")
ROOT_BUILD_OPTION(dcache ON "dCache support, requires libdcap from DESY")
ROOT_BUILD_OPTION(exceptions ON "Turn on compiler exception handling capability")
ROOT_BUILD_OPTION(explicitlink ${explicitlink_defvalue} "Explicitly link with all dependent libraries")
ROOT_BUILD_OPTION(fftw3 ON "Fast Fourier Transform support, requires libfftw3")
ROOT_BUILD_OPTION(fitsio ON "Read images and data from FITS files, requires cfitsio")
ROOT_BUILD_OPTION(fortran ON "Enable the Fortran components of ROOT")
ROOT_BUILD_OPTION(gviz ON "Graphs visualization support, requires graphviz")
ROOT_BUILD_OPTION(gdml ${gdml_defvalue} "GDML writer and reader")
ROOT_BUILD_OPTION(genvector ON "Build the new libGenVector library")
ROOT_BUILD_OPTION(gfal ON "GFAL support, requires libgfal")
ROOT_BUILD_OPTION(glite ON "gLite support, requires libglite-api-wrapper v.3 from GSI (https://subversion.gsi.de/trac/dgrid/wiki)")
ROOT_BUILD_OPTION(globus OFF "Globus authentication support, requires Globus toolkit")
ROOT_BUILD_OPTION(gsl_shared OFF "Enable linking against shared libraries for GSL (default no)")
ROOT_BUILD_OPTION(hdfs ON "HDFS support; requires libhdfs from HDFS >= 0.19.1")
ROOT_BUILD_OPTION(http ${http_defvalue} "HTTP Server support")
ROOT_BUILD_OPTION(krb5 ON "Kerberos5 support, requires Kerberos libs")
ROOT_BUILD_OPTION(ldap ON "LDAP support, requires (Open)LDAP libs")
ROOT_BUILD_OPTION(mathmore ON "Build the new libMathMore extended math library, requires GSL (vers. >= 1.8)")
ROOT_BUILD_OPTION(memstat ${memstat_defvalue} "A memory statistics utility, helps to detect memory leaks")
ROOT_BUILD_OPTION(minuit2 ${minuit2_defvalue} "Build the new libMinuit2 minimizer library")
ROOT_BUILD_OPTION(monalisa ON "Monalisa monitoring support, requires libapmoncpp")
ROOT_BUILD_OPTION(mysql ON "MySQL support, requires libmysqlclient")
ROOT_BUILD_OPTION(odbc ON "ODBC support, requires libiodbc or libodbc")
ROOT_BUILD_OPTION(opengl ON "OpenGL support, requires libGL and libGLU")
ROOT_BUILD_OPTION(oracle ON "Oracle support, requires libocci")
ROOT_BUILD_OPTION(pch ON)
ROOT_BUILD_OPTION(peac ON "PEAC, PROOF Enabled Analysis Center, requires Clarens")
ROOT_BUILD_OPTION(pgsql ON "PostgreSQL support, requires libpq")
ROOT_BUILD_OPTION(pythia6 ON "Pythia6 EG support, requires libPythia6")
ROOT_BUILD_OPTION(pythia6_nolink OFF "Delayed linking of Pythia6 library")
ROOT_BUILD_OPTION(pythia8 ON "Pythia8 EG support, requires libPythia8")
ROOT_BUILD_OPTION(python ON "Python ROOT bindings, requires python >= 2.2")
ROOT_BUILD_OPTION(qt ${qt_defvalue} "Qt graphics backend, requires libqt >= 4.8")
ROOT_BUILD_OPTION(qtgsi ${qtgsi_defvalue} "GSI's Qt integration, requires libqt >= 4.8")
ROOT_BUILD_OPTION(reflex ON "Build the libReflex dictionary library")
ROOT_BUILD_OPTION(roofit ${roofit_defvalue} "Build the libRooFit advanced fitting package")
ROOT_BUILD_OPTION(ruby OFF "Ruby ROOT bindings, requires ruby >= 1.8")
ROOT_BUILD_OPTION(rfio ON "RFIO support, requires libshift from CASTOR >= 1.5.2")
ROOT_BUILD_OPTION(rpath OFF "Set run-time library load path on executables and shared libraries (at installation area)")
ROOT_BUILD_OPTION(sapdb ON "MaxDB/SapDB support, requires libsqlod and libsqlrte")
ROOT_BUILD_OPTION(shadowpw ON "Shadow password support")
ROOT_BUILD_OPTION(shared ON "Use shared 3rd party libraries if possible")
ROOT_BUILD_OPTION(soversion OFF "Set version number in sonames (recommended)")
ROOT_BUILD_OPTION(sqlite ON "SQLite support, requires libsqlite3")
ROOT_BUILD_OPTION(srp ON "SRP support, requires SRP source tree")
ROOT_BUILD_OPTION(ssl ON "SSL encryption support, requires openssl")
ROOT_BUILD_OPTION(gnuinstall OFF "Perform installation following the GNU guidelines")
ROOT_BUILD_OPTION(table ${table_defvalue} "Build libTable contrib library")
ROOT_BUILD_OPTION(tmva ON "Build TMVA multi variate analysis library")
ROOT_BUILD_OPTION(unuran ${unuran_defvalue} "UNURAN - package for generating non-uniform random numbers")
ROOT_BUILD_OPTION(vc ${vc_defvalue} "Vc adds a few new types for portable and intuitive SIMD programming")
ROOT_BUILD_OPTION(vdt ${vdt_defvalue} "VDT adds a set of fast and vectorisable mathematical functions")
ROOT_BUILD_OPTION(winrtdebug OFF "Link against the Windows debug runtime library")
ROOT_BUILD_OPTION(xft ON "Xft support (X11 antialiased fonts)")
ROOT_BUILD_OPTION(xml ON "XML parser interface")
ROOT_BUILD_OPTION(x11 ${x11_defvalue} "X11 support")
ROOT_BUILD_OPTION(xrootd ON "Build xrootd file server and its client (if supported)")
  
option(fail-on-missing "Fail the configure step if a required external package is missing" OFF)
option(minimal "Do not automatically search for support libraries" OFF)
option(gminimal "Do not automatically search for support libraries, but include X11" OFF)
option(all "Enable all optional components" OFF)
option(testing "Enable testing with CTest" OFF)


if(DEFINED c++11)   # For backward compatibility
  set(cxx11 ${c++11} CACHE BOOL "" FORCE)
endif()

#---General Build options----------------------------------------------------------------------
# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH  FALSE)
# when building, don't use the install RPATH already (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 
# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# the RPATH to be used when installing---------------------------------------------------------
if(rpath)
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
  set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE) 
endif()

#---Avoid creating dependencies to 'non-statndard' header files -------------------------------
include_regular_expression("^[^.]+$|[.]h$|[.]icc$|[.]hxx$|[.]hpp$")

#---Set all directories where to install parts of root up to now everything is installed ------
#---according to the setting of CMAKE_INSTALL_DIR

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT AND NOT gnuinstall)
  message(STATUS "Setting default installation prefix CMAKE_INSTALL_PREFIX to ${CMAKE_BINARY_DIR}/root")
  set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/root CACHE PATH "Default installation of ROOT" FORCE)
endif()

#---Add defines for CINT limits-----------------------------------------------------------------
if(DEFINED CINTMAXSTRUCT)
  add_definitions(-DG__MAXSTRUCT=${CINTMAXSTRUCT})
endif()
if(DEFINED CINTMAXTYPEDEF)
  add_definitions(-DG__MAXTYPEDEF=${CINTMAXTYPEDEF})
endif()
if(DEFINED CINTLONGLINE)
  add_definitions(-DG__LONGLINE=${CINTLONGLINE})
endif()

#---Add Installation Variables------------------------------------------------------------------
include(RootInstallDirs)





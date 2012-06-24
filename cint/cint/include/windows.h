/* -*- C++ -*- */
/*************************************************************************
 * Copyright(c) 1995~2005  Masaharu Goto (cint@pcroot.cern.ch)
 *
 * For the licensing terms see the file COPYING
 *
 ************************************************************************/
/****************************************************************
* windows.h
*****************************************************************/
#ifndef G__WINDOWS_H
#define G__WINDOWS_H

// #include <platform.h>

/* NOTE: win32api.dll is not generated by default. 
 * Goto %CINTSYSDIR%\lib\win32api directory and do 'setup' 
 * if you use Windows. */
#pragma include_noerr "win32api.dll"

#ifndef __MAKECINT__ /* ignore the error during dictionary generation */

#pragma ifndef G__WINFUNC_H /* G__WINFUNC_H is defined in win32api.dll */
#error win32api.dll is not ready. Run 'setup.bat' in %CINTSYSDIR%\lib\win32api directory if you use WinNT/95.
#pragma endif

#endif

#endif
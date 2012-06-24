/* -*- C++ -*- */

/************************************************************************
 *
 * Copyright(c) 1995~2006  Masaharu Goto (cint@pcroot.cern.ch)
 *
 * For the licensing terms see the file COPYING
 *
 ************************************************************************/

/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 */

#ifndef FLIST_H
#define FLIST_H

#ifdef LIST_H
#undef LIST_H
#define __LIST_WAS_DEFINED
#endif

#define Allocator far_allocator
#define list far_list
#include <faralloc.h>
#include <list.h>

#undef LIST_H

#ifdef __LIST_WAS_DEFINED
#define LIST_H
#undef  __LIST_WAS_DEFINED
#endif

#undef Allocator
#undef list

#endif
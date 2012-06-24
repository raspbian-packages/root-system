// @(#)root/graf2d:$Id: QuartzLine.h 43719 2012-04-12 23:00:08Z rdm $
// Author: Olivier Couet, 23/01/2012

/*************************************************************************
 * Copyright (C) 1995-2011, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_QuartzLine
#define ROOT_QuartzLine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// QuartzLine                                                           //
//                                                                      //
// Aux. functions to draw line.                                         //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <vector>

#include <Cocoa/Cocoa.h>

#ifndef ROOT_Rtypes
#include "Rtypes.h"
#endif

#ifndef ROOT_TPoint
#include "TPoint.h"
#endif

namespace ROOT {
namespace Quartz {
   
void DrawLine(CGContextRef ctx, Int_t x1, Int_t y1, Int_t x2, Int_t y2);
void DrawPolyLine(CGContextRef ctx, Int_t n, TPoint * xy);
void SetLineStyle(CGContextRef ctx, Int_t lstyle);
void SetLineType(CGContextRef ctx, Int_t n, Int_t *dash);
void SetLineWidth(CGContextRef ctx, Int_t width);

}
}

#endif
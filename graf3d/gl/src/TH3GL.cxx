// @(#)root/gl:$Id: TH3GL.cxx 40858 2011-09-13 06:45:50Z tpochep $
// Author: Matevz Tadel 2007

/*************************************************************************
 * Copyright (C) 1995-2007, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/
#include "TH3GL.h"
#include "TH3.h"
#include "TVirtualPad.h"
#include "TAxis.h"
#include "TMath.h"

#include "TGLSurfacePainter.h"
#include "TGLHistPainter.h"
#include "TGLLegoPainter.h"
#include "TGLBoxPainter.h"
#include "TGLTF3Painter.h"
#include "TGLAxisPainter.h"
#include "TGLPhysicalShape.h"
#include "TGLCamera.h"
#include "TPolyMarker3D.h"

#include "TGLRnrCtx.h"
#include "TGLIncludes.h"

//______________________________________________________________________________
// OpenGL renderer class for TH3.
//

ClassImp(TH3GL);

//______________________________________________________________________________
TH3GL::TH3GL() :
   TGLPlot3D(), fM(0)
{
   // Constructor.
}

//______________________________________________________________________________
TH3GL::TH3GL(TH3 *th3, TPolyMarker3D *pm) :
   TGLPlot3D(), fM(th3)
{
   // Constructor.
   SetPainter(new TGLBoxPainter(th3, pm, 0, &fCoord));
   fPlotPainter->InitGeometry();
}

//______________________________________________________________________________
TH3GL::~TH3GL()
{
   // Destructor.
}

/******************************************************************************/

//______________________________________________________________________________
Bool_t TH3GL::SetModel(TObject* obj, const Option_t* opt)
{
   // Set model object.

   TString option(opt);
   option.ToLower();

   fM = SetModelDynCast<TH3>(obj);

   if (option.Index("iso") != kNPOS)
      SetPainter( new TGLIsoPainter(fM, 0, &fCoord) );
   else if (option.Index("box") != kNPOS)
      SetPainter( new TGLBoxPainter(fM, 0, &fCoord) );
   else {
      Warning("SetModel", "Option '%s' not supported, assuming 'box'.", option.Data());
      SetPainter( new TGLBoxPainter(fM, 0, &fCoord) );
   }

   fPlotPainter->AddOption(option);

   Ssiz_t pos = option.Index("fb");
   if (pos != kNPOS) {
      option.Remove(pos, 2);
      fPlotPainter->SetDrawFrontBox(kFALSE);
   }

   pos = option.Index("bb");
   if (pos != kNPOS)
      fPlotPainter->SetDrawBackBox(kFALSE);

   pos = option.Index("a");
   if (pos != kNPOS)
      fPlotPainter->SetDrawAxes(kFALSE);


   fPlotPainter->InitGeometry();

   return kTRUE;
}

//______________________________________________________________________________
void TH3GL::SetBBox()
{
   // Set bounding box.

   fBoundingBox.Set(fPlotPainter->RefBackBox().Get3DBox());
}

/******************************************************************************/

//______________________________________________________________________________
void TH3GL::DirectDraw(TGLRnrCtx & rnrCtx) const
{
   // Render with OpenGL.
   if (fFirstPhysical)
      fPlotPainter->SetPhysicalShapeColor(fFirstPhysical->Color());

   fPlotPainter->RefBackBox().FindFrontPoint();

   glPushAttrib(GL_ENABLE_BIT | GL_LIGHTING_BIT);

   glEnable(GL_NORMALIZE);
   glDisable(GL_COLOR_MATERIAL);

   fPlotPainter->InitGL();
   fPlotPainter->DrawPlot();

   glDisable(GL_CULL_FACE);
   glPopAttrib();

   // Axes
   const Rgl::PlotTranslation trGuard(fPlotPainter);

   if (fPlotPainter->GetDrawAxes()) {
      TGLAxisPainterBox axe_painter;
      axe_painter.SetUseAxisColors(kFALSE);
      axe_painter.SetFontMode(TGLFont::kPixmap);
      axe_painter.PlotStandard(rnrCtx, fM, fBoundingBox);
   }
}
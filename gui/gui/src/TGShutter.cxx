// @(#)root/gui:$Id: TGShutter.cxx 42621 2012-01-13 13:26:34Z bellenot $
// Author: Fons Rademakers   18/9/2000

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGShutter, TGShutterItem                                             //
//                                                                      //
// A shutter widget contains a set of shutter items that can be         //
// open and closed like a shutter.                                      //
// This widget is usefull to group a large number of options in         //
// a number of categories.                                              //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "TGShutter.h"
#include "TGButton.h"
#include "TList.h"
#include "TTimer.h"
#include "Riostream.h"


ClassImp(TGShutterItem)
ClassImp(TGShutter)

//______________________________________________________________________________
TGShutter::TGShutter(const TGWindow *p, UInt_t options) :
   TGCompositeFrame(p, 10, 10, options)
{
   // Create shutter frame.

   fSelectedItem        = 0;
   fClosingItem         = 0;
   fHeightIncrement     = 1;
   fClosingHeight       = 0;
   fClosingHadScrollbar = kFALSE;
   fTimer               = 0;
   fTrash               = new TList;

   fDefWidth = fDefHeight = 0;

   // layout manager is not used
   delete fLayoutManager;
   fLayoutManager = 0;
}

//______________________________________________________________________________
TGShutter::~TGShutter()
{
   // Cleanup shutter widget.

   if (fTimer) delete fTimer;

   if (!MustCleanup()) {
      fTrash->Delete();
   }
   delete fTrash;
   fTrash = 0;
}

//______________________________________________________________________________
void TGShutter::AddItem(TGShutterItem *item)
{
   // Add shutter item to shutter frame.

   TGLayoutHints *hints = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY);
   AddFrame(item, hints);
   fTrash->Add(hints);
   if (!fSelectedItem) {
      fSelectedItem = item;
   }
}

//______________________________________________________________________________
void TGShutter::RemoveItem(const char *name)
{
   // Remove item from shutter

   TGShutterItem *item = GetItem(name);

   if (!item) {
      return;
   }

   if (fList->GetEntries() <= 1) {
      return;
   }

   if (item == fSelectedItem) {
      TGFrameElement *fe = (TGFrameElement*)fList->FindObject(item->GetFrameElement());
      if (fe) {
         TGFrameElement *sel = (TGFrameElement*)fList->Before(fe);
         if (!sel) {
            sel = (TGFrameElement*)fList->After(fe);
         }
         if (!sel) {
            return;
         }
         SetSelectedItem((TGShutterItem*)sel->fFrame);
      }
   }
   RemoveFrame(item);

   item->DestroyWindow();
   delete item;
   Layout();
}

//______________________________________________________________________________
void TGShutter::RemovePage()
{
   // Remove selected page

   if (!fSelectedItem) {
      return;
   }
   TGTextButton *btn = (TGTextButton*)fSelectedItem->GetButton();
   RemoveItem(btn->GetString().Data());
}

//______________________________________________________________________________
void TGShutter::RenamePage(const char *name)
{
   // Rename selected page

   if (!fSelectedItem) {
      return;
   }
   TGTextButton *btn = (TGTextButton*)fSelectedItem->GetButton();
   btn->SetText(name);
}

//______________________________________________________________________________
TGShutterItem *TGShutter::AddPage(const char *name)
{
   // Add new page (shutter item)

   static int id = 1000;
   TGShutterItem *item = new TGShutterItem(this, new TGHotString(name), id++);
   AddItem(item);
   MapSubwindows();
   Layout();
   return item;
}

//______________________________________________________________________________
Bool_t TGShutter::ProcessMessage(Long_t /*msg*/, Long_t parm1, Long_t /*parm2*/)
{
   // Handle shutter messages.

   if (!fList) return kFALSE;

   TGFrameElement *el;
   TGShutterItem  *child, *item = 0;

   TIter next(fList);
   while ((el = (TGFrameElement *) next())) {
      child = (TGShutterItem *) el->fFrame;
      if (parm1 == child->WidgetId()) {
         item = child;
         break;
      }
   }

   if (!item) return kFALSE;

   if (!fSelectedItem)
      fSelectedItem = (TGShutterItem*) ((TGFrameElement*)fList->First())->fFrame;
   if (fSelectedItem == item) return kTRUE;

   fHeightIncrement = 1;
   fClosingItem = fSelectedItem;
   fClosingHeight = fClosingItem->GetHeight();
   fClosingHeight -= fClosingItem->fButton->GetDefaultHeight();
   fSelectedItem = item;
   Selected(fSelectedItem);
   fSelectedItem->Selected();

   if (!fTimer) fTimer = new TTimer(this, 6); //10);
   fTimer->Reset();
   fTimer->TurnOn();

   return kTRUE;
}

//______________________________________________________________________________
Bool_t TGShutter::HandleTimer(TTimer *)
{
   // Shutter item animation.

   if (!fClosingItem) return kFALSE;
   fClosingHeight -= fHeightIncrement;
   fHeightIncrement += 5;
   if (fClosingHeight > 0) {
      fTimer->Reset();
   } else {
      fClosingItem   = 0;
      fClosingHeight = 0;
      fTimer->TurnOff();
   }
   Layout();

   return kTRUE;
}

//______________________________________________________________________________
void TGShutter::Layout()
{
   // Layout shutter items.

   TGFrameElement *el;
   TGShutterItem  *child;
   Int_t y, bh, exh;

   if (!fList) return;

   if (!fSelectedItem)
      fSelectedItem = (TGShutterItem*) ((TGFrameElement*)GetList()->First())->fFrame;

   exh = Int_t(fHeight - (fBorderWidth << 1));
   TIter next(fList);
   while ((el = (TGFrameElement *) next())) {
      child = (TGShutterItem *) el->fFrame;
      bh = child->fButton->GetDefaultHeight();
      exh -= bh;
   }

   y = fBorderWidth;
   next.Reset();
   while ((el = (TGFrameElement *) next())) {
      child = (TGShutterItem *) el->fFrame;
      bh = child->fButton->GetDefaultHeight();
      if (child == fSelectedItem) {
         if (fClosingItem)
            child->fCanvas->SetScrolling(TGCanvas::kCanvasNoScroll);
         else
            child->fCanvas->SetScrolling(TGCanvas::kCanvasScrollVertical);
         child->ShowFrame(child->fCanvas);
         child->MoveResize(fBorderWidth, y, fWidth - (fBorderWidth << 1),
                           exh - fClosingHeight + bh);
         y += exh - fClosingHeight + bh;
      } else if (child == fClosingItem) {
         child->fCanvas->SetScrolling(TGCanvas::kCanvasNoScroll);
         child->MoveResize(fBorderWidth, y, fWidth - (fBorderWidth << 1),
                           fClosingHeight + bh);
         y += fClosingHeight + bh;
      } else {
         child->MoveResize(fBorderWidth, y, fWidth - (fBorderWidth << 1), bh);
         child->HideFrame(child->fCanvas);
         y += bh;
      }
   }
}

//______________________________________________________________________________
void TGShutter::SetSelectedItem(TGShutterItem *item)
{
   // Set item to be the currently open shutter item.

   fSelectedItem = item;
   fSelectedItem->Selected(); // emit signal
   Layout();
}

//______________________________________________________________________________
void TGShutter::SetSelectedItem(const char *name)
{
   // Set item to be the currently open shutter item.

   TGShutterItem *item = GetItem(name);
   if (!item) {
      return;
   }
   SetSelectedItem(item);
}

//______________________________________________________________________________
void TGShutter::EnableItem(const char *name, Bool_t on)
{
   // Disable/enbale shutter item.

   TGShutterItem *item = GetItem(name);
   if (!item) {
      return;
   }

   item->GetButton()->SetEnabled(on);
}

//______________________________________________________________________________
TGShutterItem *TGShutter::GetItem(const char *name)
{
   // returns a shutter item by name (name is hot string of shutter item)

   TGFrameElement *el;
   TGShutterItem  *item = 0;

   TIter next(fList);

   while ((el = (TGFrameElement *) next())) {
      TGTextButton *btn;
      item = (TGShutterItem *)el->fFrame;
      btn = (TGTextButton*)item->GetButton();
      if (btn->GetString() == name) return item;
   }

   return item;
}

//______________________________________________________________________________
TGDimension TGShutter::GetDefaultSize() const
{
   // Return the default / minimal size of the widget.

   UInt_t w = (GetOptions() & kFixedWidth)  || (fDefWidth  == 0) ? fWidth  : fDefWidth;
   UInt_t h = (GetOptions() & kFixedHeight) || (fDefHeight == 0) ? fHeight : fDefHeight;
   return TGDimension(w, h);
}

//______________________________________________________________________________
void TGShutter::SetDefaultSize(UInt_t w, UInt_t h)
{
   // Set the default / minimal size of the widget.

   fDefWidth  = w;
   fDefHeight = h;
}


//______________________________________________________________________________
TGShutterItem::TGShutterItem(const TGWindow *p, TGHotString *s, Int_t id,
                             UInt_t options) :
   TGVerticalFrame (p, 10, 10, options), TGWidget (id)
{
   // Create a shutter item.

   if (!p && !s) {
      MakeZombie();
      // coverity [uninit_ctor]
      return;
   }
   fButton = new TGTextButton(this, s, id);
   fCanvas = new TGCanvas(this, 10, 10, kChildFrame);
   fContainer = new TGVerticalFrame(fCanvas->GetViewPort(), 10, 10, kOwnBackground);
   fCanvas->SetContainer(fContainer);
   fContainer->SetBackgroundColor(fClient->GetShadow(GetDefaultFrameBackground()));

   AddFrame(fButton, fL1 = new TGLayoutHints(kLHintsTop | kLHintsExpandX));
   AddFrame(fCanvas, fL2 = new TGLayoutHints(kLHintsExpandY | kLHintsExpandX));

   fButton->Associate((TGFrame *) p);

   fCanvas->SetEditDisabled(kEditDisableGrab | kEditDisableLayout);
   fButton->SetEditDisabled(kEditDisableGrab | kEditDisableBtnEnable);
   fContainer->SetEditDisabled(kEditDisableGrab);
   fEditDisabled = kEditDisableGrab | kEditDisableLayout;
}

//______________________________________________________________________________
TGShutterItem::~TGShutterItem()
{
   // Clan up shutter item.

   if (!IsZombie() && !MustCleanup()) {
      delete fL1;
      delete fL2;
      delete fButton;
      delete fContainer;
      delete fCanvas;
   }
}

//______________________________________________________________________________
void TGShutterItem::SavePrimitive(ostream &out, Option_t *option /*= ""*/)
{
   // Save a shutter item widget as a C++ statement(s) on output stream out

   char quote = '"';
   TGTextButton *b = (TGTextButton *)fButton;
   const char *text = b->GetText()->GetString();
   char hotpos = b->GetText()->GetHotPos();
   Int_t lentext = b->GetText()->GetLength();
   char *outext = new char[lentext+2];       // should be +2 because of \0
   Int_t i=0;

   while (lentext) {
      if (i == hotpos-1) {
         outext[i] = '&';
         i++;
      }
      outext[i] = *text;
      i++;
      text++;
      lentext--;
   }
   outext[i]=0;

   out << endl;
   out << "   // " << quote << outext << quote << " shutter item " << endl;
   out << "   TGShutterItem *";
   out << GetName() << " = new TGShutterItem(" << fParent->GetName()
       << ", new TGHotString(" << quote << outext << quote << "),"
       << fButton->WidgetId() << "," << GetOptionString() << ");" << endl;

   delete [] outext;
   if (option && strstr(option, "keep_names"))
      out << "   " << GetName() << "->SetName(\"" << GetName() << "\");" << endl;

   TList *list = ((TGCompositeFrame *)GetContainer())->GetList();

   if (!list) return;

   out << "   TGCompositeFrame *" << GetContainer()->GetName()
       << " = (TGCompositeFrame *)" << GetName() << "->GetContainer();" << endl;

   TGFrameElement *el;
   TIter next(list);

   while ((el = (TGFrameElement *) next())) {
      el->fFrame->SavePrimitive(out, option);
      out << "   " << GetContainer()->GetName() <<"->AddFrame(" << el->fFrame->GetName();
      el->fLayout->SavePrimitive(out, option);
      out << ");"<< endl;
   }
}

//______________________________________________________________________________
void TGShutter::SavePrimitive(ostream &out, Option_t *option /*= ""*/)
{
   // Save a shutter widget as a C++ statement(s) on output stream out.

   out << endl;
   out << "   // shutter" << endl;

   out << "   TGShutter *";
   out << GetName() << " = new TGShutter(" << fParent->GetName() << ","
       << GetOptionString() << ");" << endl;

   if ((fDefWidth > 0) || (fDefHeight > 0)) {
      out << "   " << GetName() << "->SetDefaultSize(";
      out << fDefWidth << "," << fDefHeight << ");" << endl;
   }
   if (option && strstr(option, "keep_names"))
      out << "   " << GetName() << "->SetName(\"" << GetName() << "\");" << endl;

   if (!fList) return;

   TGFrameElement *el;
   TIter next(fList);

   while ((el = (TGFrameElement *) next())) {
      el->fFrame->SavePrimitive(out, option);
      out << "   " << GetName() <<"->AddItem(" << el->fFrame->GetName();
      //el->fLayout->SavePrimitive(out, option);
      out << ");"<< endl;
   }

   out << "   " << GetName() << "->SetSelectedItem("
       << GetSelectedItem()->GetName() << ");" << endl;
   out << "   " <<GetName()<< "->Resize("<<GetWidth()<<","<<GetHeight()<<");"<<endl;
}


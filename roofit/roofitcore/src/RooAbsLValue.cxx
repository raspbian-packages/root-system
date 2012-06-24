/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitCore                                                       *
 * @(#)root/roofitcore:$Id: RooAbsLValue.cxx 24247 2008-06-12 14:54:32Z wouter $
 * Authors:                                                                  *
 *   WV, Wouter Verkerke, UC Santa Barbara, verkerke@slac.stanford.edu       *
 *   DK, David Kirkby,    UC Irvine,         dkirkby@uci.edu                 *
 *                                                                           *
 * Copyright (c) 2000-2005, Regents of the University of California          *
 *                          and Stanford University. All rights reserved.    *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// 
// BEGIN_HTML
//  Abstract base class for objects that are lvalues, i.e. objects
//  whose value can be modified directly. This class implements
//  abstract methods for binned fits that return the number of fit
//  bins and change the value of the object to the central value of a
//  given fit bin, regardless of the type of value.
// END_HTML
//

#include "RooFit.h"

#include "RooAbsLValue.h"
#include "RooAbsLValue.h"

ClassImp(RooAbsLValue)
;


//_____________________________________________________________________________
RooAbsLValue::RooAbsLValue() 
{
  // Constructor
}



//_____________________________________________________________________________
RooAbsLValue::~RooAbsLValue() 
{
  // Destructor
}
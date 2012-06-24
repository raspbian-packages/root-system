// @(#)root/mathcore:$Id: TDataPointN.cxx 41518 2011-10-20 16:19:03Z moneta $
// Authors: C. Gumpert    09/2011

/**********************************************************************
 *                                                                    *
 * Copyright (c) 2011 , LCG ROOT MathLib Team                         *
 *                                                                    *
 *                                                                    *
 **********************************************************************/

// Implementation file for TDataPointN class 
// 

#include "Math/TDataPointN.h"
namespace ROOT
{
   namespace Math
   {

      template<> UInt_t TDataPointN<Float_t>::kDimension = 0;
      template<> UInt_t TDataPointN<Double_t>::kDimension = 0;

   }//namespace Math
}//namespace ROOT

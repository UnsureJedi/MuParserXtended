/*
               __________                                 ____  ___
    _____  __ _\______   \_____ _______  ______ __________\   \/  /
   /     \|  |  \     ___/\__  \\_  __ \/  ___// __ \_  __ \     / 
  |  Y Y  \  |  /    |     / __ \|  | \/\___ \\  ___/|  | \/     \ 
  |__|_|  /____/|____|    (____  /__|  /____  >\___  >__| /___/\  \
        \/                     \/           \/     \/           \_/
                                       Copyright (C) 2016, Ingo Berg
                                       All rights reserved.

  Redistribution and use in source and binary forms, with or without 
  modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright notice, 
     this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright notice, 
     this list of conditions and the following disclaimer in the documentation 
     and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
  POSSIBILITY OF SUCH DAMAGE.
*/
#include "mpPackageCmplx.h"

#include "mpParserBase.h"
#include "mpFuncCmplx.h"
#include "mpOprtCmplx.h"
#include "mpOprtBinCommon.h"

MUP_NAMESPACE_START

//------------------------------------------------------------------------------
std::unique_ptr<PackageCmplx> PackageCmplx::s_pInstance;

//------------------------------------------------------------------------------
IPackage* PackageCmplx::Instance()
{
  if (s_pInstance.get()==nullptr)
  {
    s_pInstance.reset(new PackageCmplx);
  }

  return s_pInstance.get();
}

//------------------------------------------------------------------------------
void PackageCmplx::AddToParser(ParserXBase *pParser)
{
  // Constants
  pParser->DefineConst( _T("i"), cmplx_type(0.0, 1.0) );

  // Complex valued functions
  pParser->DefineFun(ptr_cal_type(new FunCmplxReal()));
  pParser->DefineFun(ptr_cal_type(new FunCmplxImag()));
  pParser->DefineFun(ptr_cal_type(new FunCmplxConj()));
  pParser->DefineFun(ptr_cal_type(new FunCmplxArg()));
  pParser->DefineFun(ptr_cal_type(new FunCmplxNorm()));
  pParser->DefineFun(ptr_cal_type(new FunCmplxSin()));
  pParser->DefineFun(ptr_cal_type(new FunCmplxCos()));
  pParser->DefineFun(ptr_cal_type(new FunCmplxTan()));
  pParser->DefineFun(ptr_cal_type(new FunCmplxSinH()));
  pParser->DefineFun(ptr_cal_type(new FunCmplxCosH()));
  pParser->DefineFun(ptr_cal_type(new FunCmplxTanH()));
  pParser->DefineFun(ptr_cal_type(new FunCmplxSqrt()));
  pParser->DefineFun(ptr_cal_type(new FunCmplxExp()));
  pParser->DefineFun(ptr_cal_type(new FunCmplxLn()));
  pParser->DefineFun(ptr_cal_type(new FunCmplxLog()));
  pParser->DefineFun(ptr_cal_type(new FunCmplxLog2()));
  pParser->DefineFun(ptr_cal_type(new FunCmplxLog10()));
  pParser->DefineFun(ptr_cal_type(new FunCmplxAbs()));
  pParser->DefineFun(ptr_cal_type(new FunCmplxPow()));

  // Complex valued operators
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtAddCmplx()));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtSubCmplx()));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtMulCmplx()));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtDivCmplx()));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtPowCmplx()));
  pParser->DefineInfixOprt(std::shared_ptr<IOprtInfix>(new OprtSignCmplx()));
}

//------------------------------------------------------------------------------
string_type PackageCmplx::GetDesc() const
{
  return _T("");
}

//------------------------------------------------------------------------------
string_type PackageCmplx::GetPrefix() const
{
  return _T("");
}

MUP_NAMESPACE_END

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
#include "mpPackageNonCmplx.h"

#include "mpParserBase.h"
#include "mpFuncNonCmplx.h"
#include "mpOprtNonCmplx.h"
#include "mpOprtBinCommon.h"


MUP_NAMESPACE_START

//------------------------------------------------------------------------------
std::unique_ptr<PackageNonCmplx> PackageNonCmplx::s_pInstance;

//------------------------------------------------------------------------------
IPackage* PackageNonCmplx::Instance()
{
  if (s_pInstance.get()==nullptr)
  {
    s_pInstance.reset(new PackageNonCmplx);
  }

  return s_pInstance.get();
}

//------------------------------------------------------------------------------
void PackageNonCmplx::AddToParser(ParserXBase *pParser)
{
  pParser->DefineFun(ptr_cal_type(new FunSin()));
  pParser->DefineFun(ptr_cal_type(new FunCos()));
  pParser->DefineFun(ptr_cal_type(new FunTan()));
  pParser->DefineFun(ptr_cal_type(new FunSinH()));
  pParser->DefineFun(ptr_cal_type(new FunCosH()));
  pParser->DefineFun(ptr_cal_type(new FunTanH()));
  pParser->DefineFun(ptr_cal_type(new FunASin()));
  pParser->DefineFun(ptr_cal_type(new FunACos()));
  pParser->DefineFun(ptr_cal_type(new FunATan()));
  pParser->DefineFun(ptr_cal_type(new FunASinH()));
  pParser->DefineFun(ptr_cal_type(new FunACosH()));
  pParser->DefineFun(ptr_cal_type(new FunATanH()));
  pParser->DefineFun(ptr_cal_type(new FunLog()));
  pParser->DefineFun(ptr_cal_type(new FunLog10()));
  pParser->DefineFun(ptr_cal_type(new FunLog2()));
  pParser->DefineFun(ptr_cal_type(new FunLn()));
  pParser->DefineFun(ptr_cal_type(new FunExp()));
  pParser->DefineFun(ptr_cal_type(new FunSqrt()));
  pParser->DefineFun(ptr_cal_type(new FunCbrt()));
  pParser->DefineFun(ptr_cal_type(new FunAbs()));

  // binary functions
  pParser->DefineFun(ptr_cal_type(new FunPow()));
  pParser->DefineFun(ptr_cal_type(new FunHypot()));
  pParser->DefineFun(ptr_cal_type(new FunAtan2()));
  pParser->DefineFun(ptr_cal_type(new FunFmod()));
  pParser->DefineFun(ptr_cal_type(new FunRemainder()));

  // Operator callbacks
  pParser->DefineInfixOprt(std::shared_ptr<IOprtInfix>(new OprtSign()));
  pParser->DefineInfixOprt(std::shared_ptr<IOprtInfix>(new OprtSignPos()));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtAdd()));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtSub()));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtMul()));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtDiv()));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtPow()));	// UnsureJedi note: OprtPow() was without ()
}

//------------------------------------------------------------------------------
string_type PackageNonCmplx::GetDesc() const
{
  return _T("");
}

//------------------------------------------------------------------------------
string_type PackageNonCmplx::GetPrefix() const
{
  return _T("");
}

MUP_NAMESPACE_END

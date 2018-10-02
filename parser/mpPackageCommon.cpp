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
#include "mpPackageCommon.h"

#include "mpParserBase.h"
#include "mpFuncNonCmplx.h"
#include "mpFuncCommon.h"
#include "mpFuncArray.h"
#include "mpOprtBinCommon.h"
#include "mpOprtBinAssign.h"
#include "mpOprtPostfixCommon.h"
#include "mpValReader.h"

/** \brief Pi (what else?). */
#define MUP_CONST_PI  3.141592653589793238462643
//#define MUP_CONST_PI    3.14159265358979323846264338327950288419716939937510L

/** \brief The eulerian number. */
#define MUP_CONST_E   2.718281828459045235360287


MUP_NAMESPACE_START

//------------------------------------------------------------------------------
std::unique_ptr<PackageCommon> PackageCommon::s_pInstance;

//------------------------------------------------------------------------------
IPackage* PackageCommon::Instance()
{
  if (s_pInstance.get()==nullptr)
  {
    s_pInstance.reset(new PackageCommon);
  }

  return s_pInstance.get();
}

//------------------------------------------------------------------------------
void PackageCommon::AddToParser(ParserXBase *pParser)
{
  // Readers that need fancy decorations on their values must
  // be added first (i.e. hex -> "0x...") Otherwise the
  // zero in 0x will be read as a value of zero!
  pParser->AddValueReader(new HexValReader);
  pParser->AddValueReader(new BinValReader);
  pParser->AddValueReader(new DblValReader);
  pParser->AddValueReader(new BoolValReader);

  // Constants
  pParser->DefineConst( _T("pi"), (float_type)MUP_CONST_PI );
  pParser->DefineConst( _T("e"),  (float_type)MUP_CONST_E );

  // Vector
  pParser->DefineFun(ptr_cal_type(new FunSizeOf()));

  // Array
  pParser->DefineFun(ptr_cal_type(new FunArray()));

  // Generic functions
  pParser->DefineFun(ptr_cal_type(new FunMax()));
  pParser->DefineFun(ptr_cal_type(new FunMin()));
  pParser->DefineFun(ptr_cal_type(new FunSum()));

  // misc
  pParser->DefineFun(ptr_cal_type(new FunParserID));

  // integer package
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtLAnd));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtLOr));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtAnd));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtOr));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtShr));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtShl));

  // booloean package
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtLE));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtGE));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtLT));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtGT));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtEQ));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtNEQ));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtLAnd(_T("and"))));  // add logic and with a different identifier
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtLOr(_T("or"))));    // add logic and with a different identifier
//  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtBXor));

  // assignement operators
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtAssign));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtAssignAdd));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtAssignSub));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtAssignMul));
  pParser->DefineOprt(std::shared_ptr<IOprtBin>(new OprtAssignDiv));

  // infix operators
  pParser->DefineInfixOprt(std::shared_ptr<IOprtInfix>(new OprtCastToFloat));
  pParser->DefineInfixOprt(std::shared_ptr<IOprtInfix>(new OprtCastToInt));

  // postfix operators
  pParser->DefinePostfixOprt(std::shared_ptr<IOprtPostfix>(new OprtFact));
// <ibg 20130708> commented: "%" is a reserved sign for either the 
//                modulo operator or comment lines. 
//  pParser->DefineFun(std::shared_ptr<IOprtPostfix>(new OprtPercentage);
// </ibg>
}

//------------------------------------------------------------------------------
string_type PackageCommon::GetDesc() const
{
  return _T("");
}

//------------------------------------------------------------------------------
string_type PackageCommon::GetPrefix() const
{
  return _T("");
}

MUP_NAMESPACE_END

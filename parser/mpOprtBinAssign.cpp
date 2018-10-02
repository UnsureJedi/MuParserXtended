/** \file
    \brief This file contains the implementation of binary assignment 
           operators used in muParser.

<pre>
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
</pre>
*/
#include "mpOprtBinAssign.h"


MUP_NAMESPACE_START

  //---------------------------------------------------------------------
  //
  //  class OprtAssign
  //
  //---------------------------------------------------------------------

  OprtAssign::OprtAssign() 
    :IOprtBin(_T("="), (int)prASSIGN, oaLEFT)
  {}

  //---------------------------------------------------------------------
  const char_type* OprtAssign::GetDesc() const 
  { 
    return _T("'=' assignement operator"); 
  }

  //---------------------------------------------------------------------
  ptr_tok_type OprtAssign::Clone() const
  { 
    return ptr_tok_type(new OprtAssign(*this)); 
  }
  
  //---------------------------------------------------------------------
  void OprtAssign::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int)
  {
    Variable *pVar = dynamic_cast<Variable*>(a_pArg[0].get());
	//ptr_val_type lol = a_pArg[1];
    // assigment to non variable type
    if (!pVar)
    {
      ErrorContext err;
      err.Arg   = 1;
      err.Ident = _T("=");
      err.Errc  = ecASSIGNEMENT_TO_VALUE;
      throw ParserError(err);
    }

	ret->Set_Array_Start_m_pVal(pVar->Get_Array_Start_m_pVal());

	if (a_pArg[1]->GetType() == 'f')
		*pVar = a_pArg[1]->GetFloat();
	else if (a_pArg[1]->GetType() == 'i')
		*pVar = a_pArg[1]->GetInteger();
	else if (a_pArg[1]->GetType() == 's')
		*pVar = a_pArg[1]->GetString();
	else if (a_pArg[1]->GetType() == 'A')
	{
		//const ptr_val_type* debug = &a_pArg[1];
		*pVar = *a_pArg[1];
		if (a_pArg[1]->AsValue())				// Redem: delete the Array_Value without deleting the containing Value, since it will be referenced later. Ugly, but for now I don't care as long as it works..
		{
			a_pArg[1]->Delete_Array();
		}
	}
	else // This last case takes much more time to assign because entire IValue object gets copied
		*pVar = *a_pArg[1]; //pVar->SetFloat(a_pArg[1]->GetFloat());
    *ret = *pVar;
	//pVar->Set_Array_std::shared_ptr(nullptr);
  }

  //---------------------------------------------------------------------
  //
  //  class OprtAssignAdd
  //
  //---------------------------------------------------------------------

  OprtAssignAdd::OprtAssignAdd() 
    :IOprtBin(_T("+="), (int)prASSIGN, oaLEFT) 
  {}

  //---------------------------------------------------------------------
  void OprtAssignAdd::Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int)   
  {
    Variable *pVar = dynamic_cast<Variable*>(a_pArg[0].get());

    // assigment to non variable type
    if (!pVar)
    {
      ErrorContext err;
      err.Arg   = 1;
      err.Ident = _T("+=");
      err.Errc  = ecASSIGNEMENT_TO_VALUE;
      throw ParserError(err);
    }

    *pVar = cmplx_type(a_pArg[0]->GetFloat() + a_pArg[1]->GetFloat(),
                       a_pArg[0]->GetImag() + a_pArg[1]->GetImag());
    *ret = *pVar;
  }

  //---------------------------------------------------------------------
  const char_type* OprtAssignAdd::GetDesc() const 
  { 
    return _T("assignement operator"); 
  }

  //---------------------------------------------------------------------
  ptr_tok_type OprtAssignAdd::Clone() const            
  { 
    return ptr_tok_type(new OprtAssignAdd(*this)); 
  }

  //---------------------------------------------------------------------
  //
  //  class OprtAssignAdd
  //
  //---------------------------------------------------------------------

  OprtAssignSub::OprtAssignSub() 
    :IOprtBin(_T("-="), (int)prASSIGN, oaLEFT) 
  {}

  //---------------------------------------------------------------------
  void OprtAssignSub::Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int)   
  {
    Variable *pVar = dynamic_cast<Variable*>(a_pArg[0].get());
    if (!pVar)
    {
      ErrorContext err;
      err.Arg   = 1;
      err.Ident = _T("-=");
      err.Errc  = ecASSIGNEMENT_TO_VALUE;
      throw ParserError(err);
    }

    *pVar = cmplx_type(a_pArg[0]->GetFloat() - a_pArg[1]->GetFloat(),
                       a_pArg[0]->GetImag() - a_pArg[1]->GetImag());
    *ret = *pVar; 
  }

  //---------------------------------------------------------------------
  const char_type* OprtAssignSub::GetDesc() const 
  { 
    return _T("assignement operator"); 
  }

  //---------------------------------------------------------------------
  ptr_tok_type OprtAssignSub::Clone() const            
  { 
     return ptr_tok_type(new OprtAssignSub(*this)); 
  }

  //---------------------------------------------------------------------
  //
  //  class OprtAssignAdd
  //
  //---------------------------------------------------------------------

  OprtAssignMul::OprtAssignMul() 
    :IOprtBin(_T("*="), (int)prASSIGN, oaLEFT) 
  {}

  //---------------------------------------------------------------------
  void OprtAssignMul::Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int)
  {
    Variable *pVar = dynamic_cast<Variable*>(a_pArg[0].get());
    if (!pVar)
    {
      ErrorContext err;
      err.Arg   = 1;
      err.Ident = _T("*=");
      err.Errc  = ecASSIGNEMENT_TO_VALUE;
      throw ParserError(err);
    }

    float_type a = a_pArg[0]->GetFloat(),
               b = a_pArg[0]->GetImag(),
               c = a_pArg[1]->GetFloat(),
               d = a_pArg[1]->GetImag();
    *pVar = cmplx_type(a*c-b*d, a*d-b*c); 
    *ret = *pVar;
  }

  //---------------------------------------------------------------------
  const char_type* OprtAssignMul::GetDesc() const 
  { 
    return _T("multiply and assign operator"); 
  }

  //---------------------------------------------------------------------
  ptr_tok_type OprtAssignMul::Clone() const
  {  
    return ptr_tok_type(new OprtAssignMul(*this)); 
  }

  //---------------------------------------------------------------------
  //
  //  class OprtAssignDiv
  //
  //---------------------------------------------------------------------

  OprtAssignDiv::OprtAssignDiv() : IOprtBin(_T("/="), (int)prASSIGN, oaLEFT) 
  {}

  //------------------------------------------------------------------------------
  void OprtAssignDiv::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int)
  {
    Variable *pVar = dynamic_cast<Variable*>(a_pArg[0].get());
    if (!pVar)
    {
      ErrorContext err;
      err.Arg   = 1;
      err.Ident = _T("/=");
      err.Errc  = ecASSIGNEMENT_TO_VALUE;
      throw ParserError(err);
    }

    float_type a = a_pArg[0]->GetFloat(),
               b = a_pArg[0]->GetImag(),
               c = a_pArg[1]->GetFloat(),
               d = a_pArg[1]->GetImag(),
               n = c*c + d*d;
    *pVar = cmplx_type((a*c+b*d)/n, (b*c-a*d)/n); 
    *ret = *pVar; 
  }

  //------------------------------------------------------------------------------
  const char_type* OprtAssignDiv::GetDesc() const 
  { 
     return _T("multiply and divide operator"); 
  }

  //------------------------------------------------------------------------------
  ptr_tok_type OprtAssignDiv::Clone() const
  {  
    return ptr_tok_type(new OprtAssignDiv(*this)); 
  }
MUP_NAMESPACE_END

/** \file
    \brief Implementation of the muParserX variable class.

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
#include "mpVariable.h"
#include "mpError.h"

#include "mpValue.h"


MUP_NAMESPACE_START
//-----------------------------------------------------------------------------------------------
// Default variable constructor, for use with "new" array allocation  
Variable::Variable()
	:IValue(cmVAL)
	, m_pVal(nullptr)
{
	AddFlags(IToken::flVOLATILE);
}
//-----------------------------------------------------------------------------------------------
  /** \brief Create a variable and bind a value to it.
      \param pVal Pointer of the value to bind to this variable.

    It is possible to create an empty variable object by setting pVal to nullptr.
    Such variable objects must be bound later in order to be of any use. The parser
    does NOT assume ownership over the pointer!
  */
Variable::Variable(IValue* pVal)
	:IValue(cmVAL)
{
	m_pVal = std::static_pointer_cast<IValue>(pVal->Clone());
	AddFlags(IToken::flVOLATILE);
}

  Variable::Variable(ptr_val_type pVal)
    :IValue(cmVAL)
  {
	m_pVal = pVal;
    AddFlags(IToken::flVOLATILE);
  }

  //-----------------------------------------------------------------------------------------------
  Variable::Variable(const Variable &obj)
    :IValue(cmVAL)
  {
    Assign(obj);
    AddFlags(IToken::flVOLATILE);
  }

  //-----------------------------------------------------------------------------------------------
  Variable& Variable::operator=(const Variable &obj)
  {
    Assign(obj);
    return *this;
  }

  //-----------------------------------------------------------------------------------------------
  /** \brief Assign a value to the variable. 
      \param ref Reference to the value to be assigned
  */
  IValue& Variable::operator=(const Value &ref)
  {
    assert(m_pVal);
    *m_pVal = ref;
    return *this;
  }

  //-----------------------------------------------------------------------------------------------
  IValue& Variable::operator=(int_type val)
  {
    assert(m_pVal);
    return m_pVal->operator=(val);
  }

  //-----------------------------------------------------------------------------------------------
  IValue& Variable::operator=(float_type val)
  {
    assert(m_pVal);
    return m_pVal->operator=(val);
  }

  //-----------------------------------------------------------------------------------------------
  IValue& Variable::operator=(string_type val)
  {
    assert(m_pVal);
    return m_pVal->operator=(val);
  }

  //-----------------------------------------------------------------------------------------------
  IValue& Variable::operator=(bool_type val)
  {
    assert(m_pVal);
    return m_pVal->operator=(val);
  }

  //-----------------------------------------------------------------------------------------------
  IValue& Variable::operator=(Value* val)
  {
	  assert(m_pVal);
	  return m_pVal->operator=(val);
  }

  //-----------------------------------------------------------------------------------------------
  IValue& Variable::operator=(const matrix_type &val)
  {
    assert(m_pVal);
    return m_pVal->operator=(val);
  }

  //-----------------------------------------------------------------------------------------------
  IValue& Variable::operator=(const cmplx_type &val)
  {
    assert(m_pVal);
    return m_pVal->operator=(val);
  }

  //-----------------------------------------------------------------------------------------------
  IValue& Variable::operator+=(const IValue &val)
  {
    assert(m_pVal);
    return m_pVal->operator+=(val);
  }

  //-----------------------------------------------------------------------------------------------
  IValue& Variable::operator-=(const IValue &val)
  {
    assert(m_pVal);
    return m_pVal->operator-=(val);
  }

  //-----------------------------------------------------------------------------------------------
  IValue& Variable::operator*=(const IValue &val)
  {
    assert(m_pVal);
    return m_pVal->operator*=(val);
  }

  //-----------------------------------------------------------------------------------------------
  IValue& Variable::At(int nRow, int nCol)
  {
    return m_pVal->At(nRow, nCol);
  }

  //-----------------------------------------------------------------------------------------------
  IValue& Variable::At(const IValue &row, const IValue &col)
  {
    try
    {
      return m_pVal->At(row, col);
    }
    catch(ParserError &exc)
    {
      // add the identifier to the error context
      exc.GetContext().Ident = GetIdent();
      throw exc;
    }
  }

  //-----------------------------------------------------------------------------------------------
  Variable::~Variable()
  {
	  ptr_val_type lol = m_pVal;	//debug
  }

  //-----------------------------------------------------------------------------------------------
  void Variable::Assign(const Variable &ref)
  {
    if (this==&ref)
      return;

    m_pVal = ref.m_pVal;
  }

  //-----------------------------------------------------------------------------------------------
  /** \brief Returns a character representing the type of the variable. 
      \throw nothrow  
  */
  char_type Variable::GetType() const
  {
    return (m_pVal) ? m_pVal->GetType() : 'v';
  }

    //-----------------------------------------------------------------------------------------------
    /** \brief Returns the Value pointer bound to this variable. 
        \throw nothrow
    */
    ptr_val_type Variable::GetPtr() const
    {
        return m_pVal;
    }

    //-----------------------------------------------------------------------------------------------
    int_type Variable::GetInteger() const
    {
        try
        {
            return m_pVal->GetInteger();
        }
        catch (ParserError &exc)
        {
            exc.GetContext().Ident = GetIdent();
            throw;
        }
    }

    //-----------------------------------------------------------------------------------------------
    float_type Variable::GetFloat() const
    {
        try
        {
            return m_pVal->GetFloat();
        }
        catch (ParserError &exc)
        {
            exc.GetContext().Ident = GetIdent();
            throw;
        }
    }

    //-----------------------------------------------------------------------------------------------
    float_type Variable::GetImag() const
    {
        try
        {
            return m_pVal->GetImag();
        }
        catch (ParserError &exc)
        {
            exc.GetContext().Ident = GetIdent();
            throw;
        }
    }

    //-----------------------------------------------------------------------------------------------
    const cmplx_type& Variable::GetComplex() const
    {
        try
        {
            return m_pVal->GetComplex();
        }
        catch (ParserError &exc)
        {
            exc.GetContext().Ident = GetIdent();
            throw;
        }
    }

    //-----------------------------------------------------------------------------------------------
    const string_type& Variable::GetString() const
    {
        try
        {
            return m_pVal->GetString();
        }
        catch (ParserError &exc)
        {
            exc.GetContext().Ident = GetIdent();
            throw;
        }
    }

    //-----------------------------------------------------------------------------------------------
    bool Variable::GetBool() const
    {
        try
        {
            return m_pVal->GetBool();
        }
        catch (ParserError &exc)
        {
            exc.GetContext().Ident = GetIdent();
            throw;
        }
    }

    //-----------------------------------------------------------------------------------------------
    const matrix_type& Variable::GetArray() const
    {
        try
        {
            return m_pVal->GetArray();
        }
        catch (ParserError &exc)
        {
            exc.GetContext().Ident = GetIdent();
            throw;
        }
    }

	//-----------------------------------------------------------------------------------------------
	std::shared_ptr<Variable[]> Variable::Get_Array() const
	{
		return m_pVal->Get_Array();
	}

	void Variable::Delete_Array()
	{
		m_pVal->Delete_Array();
	}

	//-----------------------------------------------------------------------------------------------
	void Variable::Index_Array(int* index, int dimension, ptr_val_type& ptr) const
	{
		try
		{
			return m_pVal->Index_Array(index, dimension, ptr);
		}
		catch (ParserError &exc)
		{
			exc.GetContext().Ident = GetIdent();
			throw;
		}
	}

	Variable& Variable::Get_Variable_At_Array_Index(int index) const
	{
		try
		{
			return m_pVal->Get_Variable_At_Array_Index(index);
		}
		catch (ParserError &exc)
		{
			exc.GetContext().Ident = GetIdent();
			throw;
		}
	}

	//-----------------------------------------------------------------------------------------------
	ptr_val_type Variable::Get_Array_Start_m_pVal()
	{
		return m_pVal->Get_Array_Start_m_pVal();
	}

	//-----------------------------------------------------------------------------------------------
	void Variable::Set_Array_Start_m_pVal(ptr_val_type p)
	{
		m_pVal->Set_Array_Start_m_pVal(p);
	}

	void Variable::Set_Index_In_Array(int index)
	{
		m_pVal->Set_Index_In_Array(index);
	}

	//-----------------------------------------------------------------------------------------------
	void Variable::Set_m_pVal(ptr_val_type p)
	{
		m_pVal = p;
	}

	ptr_val_type Variable::Get_m_pVal()
	{
		return m_pVal;
	}

	//-----------------------------------------------------------------------------------------------
	Value* Variable::Get_Value() const
	{
		try
		{
			return m_pVal->Get_Value();
		}
		catch (ParserError &exc)
		{
			exc.GetContext().Ident = GetIdent();
			throw;
		}
	}

	//-----------------------------------------------------------------------------------------------
	void Variable::Delete_Value()
	{
//		if (m_pVal->Decrease_Reference_Number() == 0)	// Check that no other Variable references this array
			m_pVal->Delete_Value();
		/*else if (Reference_Number < 0)
			throw;*/
	}

	//-----------------------------------------------------------------------------------------------
	int Variable::Get_Array_Size() const
	{
		try
		{
			return m_pVal->Get_Array_Size();
		}
		catch (ParserError &exc)
		{
			exc.GetContext().Ident = GetIdent();
			throw;
		}
	}



	//-----------------------------------------------------------------------------------------------
	IValue& Variable::Initialize_Array(ptr_val_type Array_Start_Ptr, int Size)
	{
		m_pVal -> Initialize_Array(Array_Start_Ptr, Size);
		return *this;
	}

    //-----------------------------------------------------------------------------------------------
    int Variable::GetRows() const
    {
        try
        {
            return m_pVal->GetRows();
        }
        catch (ParserError &exc)
        {
            exc.GetContext().Ident = GetIdent();
            throw;
        }
    }

    //-----------------------------------------------------------------------------------------------
    int Variable::GetCols() const
    {
        try
        {
            return m_pVal->GetCols();
        }
        catch (ParserError &exc)
        {
            exc.GetContext().Ident = GetIdent();
            throw;
        }
    }

  //-----------------------------------------------------------------------------------------------
  void Variable::SetFloat(float_type a_fVal)
  {
    assert(m_pVal);
    *m_pVal = a_fVal;
  }

  //-----------------------------------------------------------------------------------------------
  void Variable::SetString(const string_type &a_sVal)
  {
    assert(m_pVal);
    *m_pVal = a_sVal;
  }

  //-----------------------------------------------------------------------------------------------
  void Variable::SetBool(bool a_bVal)
  {
    assert(m_pVal);
    *m_pVal = a_bVal;
  }

  //-----------------------------------------------------------------------------------------------
  void Variable::Bind(ptr_val_type pValue)
  {
    m_pVal = pValue;
  }

  //---------------------------------------------------------------------------
  bool Variable::IsVariable() const
  {
    return true;
  }

  //-----------------------------------------------------------------------------------------------
  ptr_tok_type Variable::Clone() const
  {
    return ptr_tok_type(new Variable(*this));
  }

  //-----------------------------------------------------------------------------------------------
  Value* Variable::AsValue()
  {
    return nullptr;
  }

  //-----------------------------------------------------------------------------------------------
  string_type Variable::AsciiDump() const
  {
    stringstream_type ss;

    ss << g_sCmdCode[ GetCode() ];
    ss << _T(" [addr=0x") << std::hex << this << std::dec;
    ss << _T("; pos=") << GetExprPos();
    ss << _T("; id=\"") << GetIdent() << _T("\"");
    ss << _T("; type=\"") << GetType() << _T("\"");
    ss << _T("; val=");

    switch(GetType())
    {
    case 'i': ss << (int_type)GetFloat(); break;
    case 'f': ss << GetFloat(); break;
    case 'm': ss << _T("(array)"); break;
    case 's': ss << _T("\"") << GetString() << _T("\""); break;
    }

    ss << ((IsFlagSet(IToken::flVOLATILE)) ? _T("; ") : _T("; not ")) << _T("vol");
    ss << _T("]");

    return ss.str();
  }
MUP_NAMESPACE_END

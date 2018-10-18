/** \file
    \brief Definition of basic types used by muParserX

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
#ifndef MUP_VALUE_H
#define MUP_VALUE_H

//--- Standard includes ------------------------------------------------------------
#include <complex>
#include <list>

//--- Parser framework -------------------------------------------------------------
#include "mpIValue.h"
#include "mpTypes.h"


MUP_NAMESPACE_START

  //------------------------------------------------------------------------------
  /** \brief Value class of muParserX
  
    This class represents a value to be used with muParserX. It's a Variant like
    class able to store a variety of types.
  */
  class Value : public IValue
  {
  public:
	Value();
    explicit Value(char_type cType);

    Value(int_type val);
    Value(bool_type val);
    Value(float_type val);
    Value(string_type val);
    Value(const char_type *val);
    Value(const cmplx_type &v);
    Value(const matrix_type &val);

    // Array and Matrix constructors
    Value(int_type m, float_type v);
    Value(int_type m, int_type n, float_type v);

    Value(const Value &a_Val );
    Value(const IValue &a_Val);
    Value& operator=(const Value &a_Val);

    virtual ~Value();
 
    virtual IValue& At(int nRow, int nCol = 0);
    virtual IValue& At(const IValue &row, const IValue &col);

    virtual IValue& operator=(int_type a_iVal);
    virtual IValue& operator=(float_type a_fVal);
    virtual IValue& operator=(string_type a_sVal);
    virtual IValue& operator=(bool val);
	virtual IValue& operator=(Value* val);
    virtual IValue& operator=(const matrix_type &a_vVal);
    virtual IValue& operator=(const cmplx_type &val);
    virtual IValue& operator=(const char_type *a_szVal);
    virtual IValue& operator+=(const IValue &val);
    virtual IValue& operator-=(const IValue &val);
    virtual IValue& operator*=(const IValue &val);

    virtual char_type GetType() const override;
    virtual int_type GetInteger() const override;
    virtual float_type GetFloat() const override;
    virtual float_type GetImag() const override;
    virtual bool GetBool() const override;
    virtual const cmplx_type& GetComplex() const override;
    virtual const string_type& GetString() const override;
    virtual const matrix_type& GetArray() const override;
	virtual void Delete_Array() override;
	virtual std::shared_ptr<std::shared_ptr<Variable>[]> Get_Array() const override;	// Redem note: function for getting the 1D array of Values (not vector- or map-based).
	virtual void Index_Array(int* index, int dimension, ptr_val_type& ptr) const override;	// Get the array Variable at specified index or indices
	virtual Variable& Get_Variable_At_Array_Index(int index) const override;
	virtual void Set_Index_In_Array(int index);
	virtual void Set_m_pVal(ptr_val_type p);
	virtual ptr_val_type Get_m_pVal();
	virtual int Get_Array_Size() const;
	virtual Value* Get_Value() const;
	virtual void Delete_Value();
    virtual int GetRows() const override;
    virtual int GetCols() const override;

    virtual bool IsVariable() const;

    virtual ptr_tok_type Clone() const;
    virtual Value* AsValue() override;

    virtual string_type AsciiDump() const;
    void BindToCache(ValueCache *pCache);
	
    // Conversion operators
    operator cmplx_type();
    operator int ();
    operator string_type();
    operator float_type();
    operator bool();

	
  private:

    cmplx_type   m_val;    ///< Member variable for storing the value of complex, float, int and boolean values
    string_type *m_psVal;  ///< Variable for storing a string value
    matrix_type *m_pvVal;  ///< A Vector for storing array variable content
	std::shared_ptr<std::shared_ptr<Variable>[]> Array_Value;	// A pointer for array of Values
	int Array_Size = 0;
	int Index_In_Array;	// if this Value is an Array element, this variable is an index of this element in Array_Value, containing it. -1 means that this Value is not an Array member
    char_type    m_cType;  ///< A byte indicating the type of the represented value
    EFlags       m_iFlags; ///< Additional flags
    ValueCache  *m_pCache; ///< Pointer to the Value Cache

    void CheckType(char_type a_cType) const;
    void Assign(const Value &a_Val);
	virtual IValue & Initialize_Array(ptr_val_type Array_Start_Ptr, int Size);
    void reset();

    virtual void Release();
  }; // class Value


MUP_NAMESPACE_END

#endif



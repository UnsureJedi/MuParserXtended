/*
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
#include "mpValue.h"
#include "mpVariable.h"
#include "mpError.h"
#include "mpValueCache.h"


MUP_NAMESPACE_START

//------------------------------------------------------------------------------
// Default constructor
Value::Value()
	:IValue(cmVAL)
	, m_val(0, 0)
	, m_psVal(nullptr)
	, m_pvVal(nullptr)
	, Array_Value(nullptr)
	, Array_Size(0)
	, m_cType('v')
	, m_iFlags(flNONE)
	, m_pCache(nullptr)
	, Index_In_Array(-1)
{}

//------------------------------------------------------------------------------
/** \brief Construct an empty value object of a given type.
    \param cType The type of the value to construct (default='v').
    */
    Value::Value(char_type cType)
    :IValue(cmVAL)
    , m_val(0, 0)
    , m_psVal(nullptr)
    , m_pvVal(nullptr)
	, Array_Value(nullptr)
	, Array_Size(0)
    , m_cType(cType)
    , m_iFlags(flNONE)
    , m_pCache(nullptr)
	, Index_In_Array(-1)
{
    // strings and arrays must allocate their memory
    switch (cType)
    {
    case 's': m_psVal = new string_type(); break;
    case 'm': m_pvVal = new matrix_type(0, Value(0.0)); break;
    }
}

//---------------------------------------------------------------------------
Value::Value(int_type a_iVal)
  :IValue(cmVAL)
  ,m_val((float_type)a_iVal, 0)
  ,m_psVal(nullptr)
  ,m_pvVal(nullptr)
  ,Array_Value(nullptr)
  ,Array_Size(0)
  ,m_cType('i')
  ,m_iFlags(flNONE)
  ,m_pCache(nullptr)
  ,Index_In_Array(-1)
{}

//---------------------------------------------------------------------------
Value::Value(bool_type a_bVal)
    :IValue(cmVAL)
    , m_val((float_type)a_bVal, 0)
    , m_psVal(nullptr)
    , m_pvVal(nullptr)
	, Array_Value(nullptr)
	, Array_Size(0)
    , m_cType('b')
    , m_iFlags(flNONE)
    , m_pCache(nullptr)
{}

//---------------------------------------------------------------------------
Value::Value(string_type a_sVal)
    :IValue(cmVAL)
    , m_val()
    , m_psVal(new string_type(a_sVal))
    , m_pvVal(nullptr)
	, Array_Value(nullptr)
	, Array_Size(0)
    , m_cType('s')
    , m_iFlags(flNONE)
    , m_pCache(nullptr)
	, Index_In_Array(-1)
{}

//---------------------------------------------------------------------------
Value::Value(int_type array_size, float_type v)
    :IValue(cmVAL)
    , m_val()
    , m_psVal(nullptr)
    , m_pvVal(new matrix_type(array_size, Value(v)))
	, Array_Value(nullptr)
	, Array_Size(0)
    , m_cType('m')
    , m_iFlags(flNONE)
    , m_pCache(nullptr)
	, Index_In_Array(-1)
{}

//---------------------------------------------------------------------------
/** \brief Create a m x n matrix
*/
Value::Value(int_type m, int_type n, float_type v)
    :IValue(cmVAL)
    , m_val()
    , m_psVal(nullptr)
    , m_pvVal(new matrix_type(m, n, Value(v)))
	, Array_Value(nullptr)
	, Array_Size(0)
    , m_cType('m')
    , m_iFlags(flNONE)
    , m_pCache(nullptr)
	, Index_In_Array(-1)
{}

//---------------------------------------------------------------------------
Value::Value(const char_type *a_szVal)
    :IValue(cmVAL)
    , m_val()
    , m_psVal(new string_type(a_szVal))
    , m_pvVal(nullptr)
	, Array_Value(nullptr)
	, Array_Size(0)
    , m_cType('s')
    , m_iFlags(flNONE)
    , m_pCache(nullptr)
	, Index_In_Array(-1)
{}

//---------------------------------------------------------------------------
Value::Value(const cmplx_type &v)
    :IValue(cmVAL)
    , m_val(v)
    , m_psVal(nullptr)
    , m_pvVal(nullptr)
	, Array_Value(nullptr)
	, Array_Size(0)
    , m_cType('c')
    , m_iFlags(flNONE)
    , m_pCache(nullptr)
	, Index_In_Array(-1)
{
    if ((m_val.real() == (int_type)m_val.real()) && (m_val.imag() == 0))
        m_cType = 'i';
    else
        m_cType = (m_val.imag() == 0) ? 'f' : 'c';
}

//---------------------------------------------------------------------------
Value::Value(float_type val)
    :IValue(cmVAL)
    , m_val(val, 0)
    , m_psVal(nullptr)
    , m_pvVal(nullptr)
	, Array_Value(nullptr)
	, Array_Size(0)
    , m_cType((val == (int_type)val) ? 'i' : 'f')
    , m_iFlags(flNONE)
    , m_pCache(nullptr)
	, Index_In_Array(-1)
{}

//---------------------------------------------------------------------------
Value::Value(const matrix_type &val)
    :IValue(cmVAL)
    , m_val()
    , m_psVal(nullptr)
    , m_pvVal(new matrix_type(val))
	, Array_Value(nullptr)
	, Array_Size(0)
    , m_cType('m')
    , m_iFlags(flNONE)
    , m_pCache(nullptr)
	, Index_In_Array(-1)
{}

//---------------------------------------------------------------------------
Value::Value(const Value &a_Val)
    :IValue(cmVAL)
    , m_psVal(nullptr)
    , m_pvVal(nullptr)
	, Array_Value(nullptr)
	, Array_Size(0)
    , m_pCache(nullptr)
	, Index_In_Array(-1)
{
    Assign(a_Val);
}

//---------------------------------------------------------------------------
Value::Value(const IValue &a_Val)
    :IValue(cmVAL)
    , m_psVal(nullptr)
    , m_pvVal(nullptr)
	, Array_Value(nullptr)
	, Array_Size(0)
    , m_pCache(nullptr)
	, Index_In_Array(-1)
{
    Reset();

    switch (a_Val.GetType())
    {
    case 'i':
    case 'f':
    case 'b': m_val = cmplx_type(a_Val.GetFloat(), 0);
        break;


    case 'c': m_val = cmplx_type(a_Val.GetFloat(), a_Val.GetImag());
        break;

    case 's': if (!m_psVal)
        m_psVal = new string_type(a_Val.GetString());
              else
                  *m_psVal = a_Val.GetString();
        break;

    case 'm': if (!m_pvVal)
        m_pvVal = new matrix_type(a_Val.GetArray());
              else
                  *m_pvVal = a_Val.GetArray();
        break;

	case 'A': 
		Array_Size = a_Val.Get_Array_Size();
		Array_Value = a_Val.Get_Array();

		break;

    case 'v': break;
    default:  MUP_FAIL(INVALID_TYPE_CODE);
    }

    m_cType = a_Val.GetType();
}

//---------------------------------------------------------------------------
Value& Value::operator=(const Value &a_Val)
{
    Assign(a_Val);
    return *this;
}

//---------------------------------------------------------------------------
/** \brief Return the matrix element at row col.

  Row and col are the indices of the matrix. If this element does not
  represent a matrix row and col must be 0 otherwise an index out of bound error
  is thrown.
  */
IValue& Value::At(const IValue &row, const IValue &col)
{
    if (!row.IsInteger() || !col.IsInteger())
    {
        ErrorContext errc(ecTYPE_CONFLICT_IDX, GetExprPos());
        errc.Type1 = (!row.IsInteger()) ? row.GetType() : col.GetType();
        errc.Type2 = 'i';
        throw ParserError(errc);
    }

    int nRow = row.GetInteger(),
        nCol = col.GetInteger();
    return At(nRow, nCol);
}

//---------------------------------------------------------------------------
IValue& Value::At(int nRow, int nCol)
{
    if (IsMatrix())
    {
        if (nRow >= m_pvVal->GetRows() || nCol >= m_pvVal->GetCols() || nRow < 0 || nCol < 0)
            throw ParserError(ErrorContext(ecINDEX_OUT_OF_BOUNDS, -1, GetIdent()));

        return m_pvVal->At(nRow, nCol);
    }
    else if (nRow == 0 && nCol == 0)
    {
        return *this;
    }
    else
        throw ParserError(ErrorContext(ecINDEX_OUT_OF_BOUNDS));
}

//---------------------------------------------------------------------------
Value::~Value()
{
    delete m_psVal;
    delete m_pvVal;
}

//---------------------------------------------------------------------------
IToken* Value::Clone() const
{
    return new Value(*this);
}

//---------------------------------------------------------------------------
Value* Value::AsValue()
{
    return this;
}

//---------------------------------------------------------------------------
/** \brief Copy constructor. */
void Value::Assign(const Value &ref)
{
    if (this == &ref)
        return;

    m_val = ref.m_val;
    m_cType = ref.m_cType;
    m_iFlags = ref.m_iFlags;

	if (ref.GetType() == 'A')
	{
		Array_Size = ref.Get_Array_Size();
		Array_Value = ref.Get_Array();

		return;
	}

    // allocate room for a string
    if (ref.m_psVal)
    {
        if (!m_psVal)
            m_psVal = new string_type(*ref.m_psVal);
        else
            *m_psVal = *ref.m_psVal;
    }
    else
    {
        delete m_psVal;
        m_psVal = nullptr;
    }

    // allocate room for a vector
    if (ref.m_pvVal)
    {
        if (m_pvVal == nullptr)
            m_pvVal = new matrix_type(*ref.m_pvVal);
        else
            *m_pvVal = *ref.m_pvVal;
    }
    else
    {
        delete m_pvVal;
        m_pvVal = nullptr;
    }

    // Do NOT access ref beyound this point! If you do, "unboxing" of
    // a 1 x 1 matrix using:
    //
    // this->Assign(m_pvVal->At(0,0));
    // 
    // will blow up in your face since ref will become invalid at them very
    // moment you delete m_pvVal!
}

IValue& Value::Initialize_Array(ptr_val_type Array_Start_Ptr, int Size)
{
	Array_Size = Size;
	Array_Value = std::shared_ptr<Variable[]>(new Variable[Size]);	// Allocating array of values
	//ptr_val_type * val_ptr_buf;	// this pointer will be deleted at every loop iteration, unlike the data it points to, so that data will persist after loop
	for (int i = 0; i < Size; i++)
	{
		//val_ptr_buf = new ptr_val_type(new Value((char_type)'A'));  // Create new value token for variable in array, use 'A' type as default
		Array_Value[i].~Variable();
		Array_Value[i].Variable::Variable((*(new ptr_val_type(new Value((char_type)'A')))).Get());	// Manually calling the constructor because "new" does not support them	
		Array_Value[i].Set_Array_Start_m_pVal(this);	// Connect element of the Array to Start Variable
		Array_Value[i].Set_Index_In_Array(i);
	}
	m_cType = 'A';
	m_iFlags = flNONE;

	return *this;
}

//---------------------------------------------------------------------------
void Value::Reset()
{
    m_val = cmplx_type(0, 0);

    delete m_psVal;
    m_psVal = nullptr;

    delete m_pvVal;
    m_pvVal = nullptr;

    m_cType = 'f';
    m_iFlags = flNONE;
}

//---------------------------------------------------------------------------
IValue& Value::operator=(Value* val)
{
	if (val->GetType() == 'A')
	{
		Array_Size = val->Get_Array_Size();
		Array_Value = val->Get_Array();

		m_cType = 'A';
		m_iFlags = flNONE;
		return *this;
	}
	
	m_val = val->m_val;

	// allocate room for a string
	if (val->m_psVal)
	{
		if (!m_psVal)
			m_psVal = new string_type(*val->m_psVal);
		else
			*m_psVal = *val->m_psVal;
	}
	else
	{
		delete m_psVal;
		m_psVal = nullptr;
	}

	// allocate room for a vector
	if (val->m_pvVal)
	{
		if (m_pvVal == nullptr)
			m_pvVal = new matrix_type(*val->m_pvVal);
		else
			*m_pvVal = *val->m_pvVal;
	}
	else
	{
		delete m_pvVal;
		m_pvVal = nullptr;
	}

	Array_Value = nullptr;
	Array_Size = 0;

	m_cType = val->GetType();
	m_iFlags = flNONE;
	return *this;
}

//---------------------------------------------------------------------------
IValue& Value::operator=(bool val)
{
    m_val = cmplx_type((float_type)val, 0);

    delete m_psVal;
    m_psVal = nullptr;

    delete m_pvVal;
    m_pvVal = nullptr;

	Array_Value = nullptr;
	Array_Size = 0;

    m_cType = 'b';
    m_iFlags = flNONE;
    return *this;
}

//---------------------------------------------------------------------------
IValue& Value::operator=(int_type a_iVal)
{
  m_val = cmplx_type(a_iVal,0);

  delete m_psVal;
  m_psVal = nullptr;

  delete m_pvVal;
  m_pvVal = nullptr;

  Array_Value = nullptr;
  Array_Size = 0;

  m_cType = 'i';
  m_iFlags = flNONE;
  return *this;
}

//---------------------------------------------------------------------------
IValue& Value::operator=(float_type val)
{
    m_val = cmplx_type(val, 0);

    delete m_psVal;
    m_psVal = nullptr;

    delete m_pvVal;
    m_pvVal = nullptr;

	Array_Value = nullptr;
	Array_Size = 0;

    m_cType = (val == (int_type)val) ? 'i' : 'f';
    m_iFlags = flNONE;
    return *this;
}

//---------------------------------------------------------------------------
IValue& Value::operator=(string_type a_sVal)
{
    m_val = cmplx_type();

    if (!m_psVal)
        m_psVal = new string_type(a_sVal);
    else
        *m_psVal = a_sVal;

    delete m_pvVal;
    m_pvVal = nullptr;

	Array_Value = nullptr;
	Array_Size = 0;

    m_cType = 's';
    m_iFlags = flNONE;
    return *this;
}

//---------------------------------------------------------------------------
IValue& Value::operator=(const char_type *a_szVal)
{
    m_val = cmplx_type();

    if (!m_psVal)
        m_psVal = new string_type(a_szVal);
    else
        *m_psVal = a_szVal;

    delete m_pvVal;
    m_pvVal = nullptr;

	Array_Value = nullptr;
	Array_Size = 0;

    m_cType = 's';
    m_iFlags = flNONE;
    return *this;
}

//---------------------------------------------------------------------------
IValue& Value::operator=(const matrix_type &a_vVal)
{
    m_val = cmplx_type(0, 0);

    delete m_psVal;
    m_psVal = nullptr;

    if (m_pvVal == nullptr)
        m_pvVal = new matrix_type(a_vVal);
    else
        *m_pvVal = a_vVal;

	Array_Value = nullptr;
	Array_Size = 0;

    m_cType = 'm';
    m_iFlags = flNONE;

    return *this;
}

//---------------------------------------------------------------------------
IValue& Value::operator=(const cmplx_type &val)
{
    m_val = val;

    delete m_psVal;
    m_psVal = nullptr;

    delete m_pvVal;
    m_pvVal = nullptr;

	Array_Value = nullptr;
	Array_Size = 0;

    m_cType = (m_val.imag() == 0) ? ((m_val.real() == (int)m_val.real()) ? 'i' : 'f') : 'c';
    m_iFlags = flNONE;

    return *this;
}

//---------------------------------------------------------------------------
IValue& Value::operator+=(const IValue &val)
{
    if (IsScalar() && val.IsScalar())
    {
        // Scalar/Scalar addition
        m_val += val.GetComplex();
        m_cType = (m_val.imag() == 0) ? ((m_val.real() == (int)m_val.real()) ? 'i' : 'f') : 'c';
    }
    else if (IsMatrix() && val.IsMatrix())
    {
        // Matrix/Matrix addition
        assert(m_pvVal);
        *m_pvVal += val.GetArray();
    }
    else if (IsString() && val.IsString())
    {
        // string/string addition
        assert(m_psVal);
        *m_psVal += val.GetString();
    }
    else
    {
        // Type conflict
        throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, _T("+"), GetType(), val.GetType(), 2));
    }

    return *this;
}

//---------------------------------------------------------------------------
IValue& Value::operator-=(const IValue &val)
{
    if (IsScalar() && val.IsScalar())
    {
        // Scalar/Scalar addition
        m_val -= val.GetComplex();
        m_cType = (m_val.imag() == 0) ? ((m_val.real() == (int)m_val.real()) ? 'i' : 'f') : 'c';
    }
    else if (IsMatrix() && val.IsMatrix())
    {
        // Matrix/Matrix addition
        assert(m_pvVal);
        *m_pvVal -= val.GetArray();
    }
    else
    {
        // There is a typeconflict:
        throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, _T("-"), GetType(), val.GetType(), 2));
    }

    return *this;
}

//---------------------------------------------------------------------------
/** \brief Assign a value with multiplication
    \param val The value to multiply to this

    When multiplying to values with each value representing a matrix type
    the result is checked whether it is a 1 x 1 matrix. If so the value is
    "unboxed" and stored directly in this value object. It is no longer
    treated as a matrix internally.
    */
IValue& Value::operator*=(const IValue &val)
{
    if (IsScalar() && val.IsScalar())
    {
        // Scalar/Scalar multiplication
        m_val *= val.GetComplex();
        m_cType = (m_val.imag() == 0) ? ((m_val.real() == (int)m_val.real()) ? 'i' : 'f') : 'c';
    }
    else if (IsMatrix() && val.IsMatrix())
    {
        // Matrix/Matrix addition
        assert(m_pvVal);
        *m_pvVal *= val.GetArray();

        // The result may actually be a scalar value, i.e. the scalar product of
        // two vectors.
        if (m_pvVal->GetCols() == 1 && m_pvVal->GetRows() == 1)
        {
            Assign(m_pvVal->At(0, 0));
        }
    }
    else if (IsMatrix() && val.IsScalar())
    {
        *m_pvVal *= val;
    }
    else if (IsScalar() * val.IsMatrix())
    {
        // transform this into a matrix and multiply with rhs
        Value prod = val * (*this);
        Assign(prod);
    }
    else
    {
        // Type conflict
        ErrorContext errc(ecTYPE_CONFLICT_FUN, -1, _T("*"));
        errc.Type1 = GetType();
        errc.Type2 = 'm'; //val.GetType();
        errc.Arg = 2;
        throw ParserError(errc);
    }

    return *this;
}

//---------------------------------------------------------------------------
/** \brief Returns a character representing the type of this value instance.
    \return m_cType Either one of 'c' for comlex, 'i' for integer,
    'f' for floating point, 'b' for boolean, 's' for string or
    'm' for matrix values.
    */
char_type Value::GetType() const
{
    return m_cType;
}

//---------------------------------------------------------------------------
/** \brief Return the value as an integer.

  This function should only be called if you really need an integer value and
  want to make sure your either get one or throw an exception if the value
  can not be implicitely converted into an integer.
  */
int_type Value::GetInteger() const
{
    float_type v = m_val.real();

    if (m_cType != 'i')
    {
        ErrorContext err;
        err.Errc = ecTYPE_CONFLICT;
        err.Type1 = m_cType;
        err.Type2 = 'i';

        if (GetIdent().length())
        {
            err.Ident = GetIdent();
        }
        else
        {
            stringstream_type ss;
            ss << *this;
            err.Ident = ss.str();
        }

        throw ParserError(err);
    }

    return (int_type)v;
}

//---------------------------------------------------------------------------
float_type Value::GetFloat() const
{
    return m_val.real();
}

//---------------------------------------------------------------------------
/** \brief Get the imaginary part of the value.
    \throw ParserError in case this value represents a string or a matrix
    */
float_type Value::GetImag() const
{
    if (!IsScalar())
    {
        ErrorContext err;
        err.Errc = ecTYPE_CONFLICT;
        err.Type1 = m_cType;
        err.Type2 = 'c';

        if (GetIdent().length())
        {
            err.Ident = GetIdent();
        }
        else
        {
            stringstream_type ss;
            ss << *this;
            err.Ident = ss.str();
        }

        throw ParserError(err);
    }

    return m_val.imag();
}

//---------------------------------------------------------------------------
/** \brief Returns this value as a complex number.
    \throw nothrow

    If the value instance does not represent a complex value the returned value
    is undefined. No exception is triggered. If you are unsure about the type
    use IsComplex() or GetType() to verify the type.
    */
const cmplx_type& Value::GetComplex() const
{
    return m_val;
}

//---------------------------------------------------------------------------
const string_type& Value::GetString() const
{
    CheckType('s');
    assert(m_psVal != nullptr);
    return *m_psVal;
}

//---------------------------------------------------------------------------
bool Value::GetBool() const
{
    CheckType('b');
    return m_val.real() == 1;
}

//---------------------------------------------------------------------------
const matrix_type& Value::GetArray() const
{
    CheckType('m');
    assert(m_pvVal != nullptr);
    return *m_pvVal;
}

void Value::Delete_Array()
{
	bool Delete_Array = 0;
	for (int i = 0; i < Array_Size; i++)
	{
		/*if (!Array_Value_Deleted[i])
			Array_Value[i].Delete_Value();*/
		Delete_Array = 1;
	}
	if (Delete_Array)
	{
		Array_Size = 0;
		//delete[] Array_Value;
	}
}

//---------------------------------------------------------------------------
std::shared_ptr<Variable[]> Value::Get_Array() const
{
	return Array_Value;
}

//---------------------------------------------------------------------------
void Value::Index_Array(int* index, int dimension, ptr_val_type& ptr) const
{
	int i;
	
	Variable * temp;
	temp = &Array_Value[index[0]];
	// Because every element in an array is a Variable, we can use temp pointer to
	// descend to target dimension, one index at a time
	for (i = 1; i < dimension; i++)
	{
		temp = &temp->Get_Variable_At_Array_Index(index[i]);
	}
	// Setting the Array_Start_Ptr to address of Variable being indexed (that is, its m_pVal pointer)
	temp->Set_Array_Start_m_pVal(ptr.Get()->Get_m_pVal());
	//Array_Start_Ptr.operator=(ptr);
	ptr = temp;
}

//---------------------------------------------------------------------------
Variable& Value::Get_Variable_At_Array_Index(int index) const
{
	return Array_Value[index];
}

//---------------------------------------------------------------------------
void Value::Set_Array_Start_m_pVal(IValue* ptr)
{
	Array_Start_Ptr = ptr;
}

//---------------------------------------------------------------------------
IValue* Value::Get_Array_Start_m_pVal()
{
	return Array_Start_Ptr;
}

void Value::Set_Index_In_Array(int index)
{
	Index_In_Array = index;
}

//---------------------------------------------------------------------------
void Value::Set_m_pVal(IValue * p)
{}

IValue* Value::Get_m_pVal()
{
	return nullptr;
}

//---------------------------------------------------------------------------
Value* Value::Get_Value() const
{
	return (Value*)this;
}

void Value::Delete_Value()
{
	delete this;
}

//---------------------------------------------------------------------------
int Value::Get_Array_Size() const
{
	return Array_Size;
}

//---------------------------------------------------------------------------
int Value::GetRows() const
{
    return (GetType() != 'm') ? 1 : GetArray().GetRows();
}

//---------------------------------------------------------------------------
int Value::GetCols() const
{
    return (GetType() != 'm') ? 1 : GetArray().GetCols();
}

//---------------------------------------------------------------------------
void Value::CheckType(char_type a_cType) const
{
    if (m_cType != a_cType)
    {
        ErrorContext err;
        err.Errc = ecTYPE_CONFLICT;
        err.Type1 = m_cType;
        err.Type2 = a_cType;

        if (GetIdent().length())
        {
            err.Ident = GetIdent();
        }
        else
        {
            stringstream_type ss;
            ss << *this;
            err.Ident = ss.str();
        }

        throw ParserError(err);
    }
}

//---------------------------------------------------------------------------
bool Value::IsVariable() const
{
    return false;
}

//---------------------------------------------------------------------------
string_type Value::AsciiDump() const
{
    stringstream_type ss;

    ss << g_sCmdCode[GetCode()];
    ss << _T(" [addr=0x") << std::hex << this << std::dec;
    ss << _T("; pos=") << GetExprPos();
    ss << _T("; type=\"") << GetType() << _T("\"");
    ss << _T("; val=");

    switch (m_cType)
    {
    case 'i': ss << (int_type)m_val.real(); break;
    case 'f': ss << m_val.real(); break;
    case 'm': ss << _T("(matrix)"); break;
    case 's':
        assert(m_psVal != nullptr);
        ss << _T("\"") << m_psVal << _T("\""); break;
    }

    ss << ((IsFlagSet(IToken::flVOLATILE)) ? _T("; ") : _T("; not ")) << _T("vol");
    ss << _T("]");

    return ss.str();
}

//-----------------------------------------------------------------------------------------------
void Value::Release()
{
	// Redem note: "&&" here is for safety, either of these should mean this Value is an Array
	if (Array_Value && Array_Size)
	{
		// Delete array members
		for (int i = 0; i < Array_Size; i++)
		{	
			Array_Value[i].Delete_Value();
		}
		Array_Value.~shared_ptr();
		Array_Size = 0;
		delete this;
	}
	else if (m_pCache)
        m_pCache->ReleaseToCache(this);
    else
        delete this;
}

//-----------------------------------------------------------------------------------------------
void Value::BindToCache(ValueCache *pCache)
{
    m_pCache = pCache;
}

//-----------------------------------------------------------------------------------------------
Value::operator cmplx_type ()
{
    return GetComplex();
}

//-----------------------------------------------------------------------------------------------
Value::operator int()
{
    return GetInteger();
}

//-----------------------------------------------------------------------------------------------
Value::operator string_type()
{
    return GetString();
}

//-----------------------------------------------------------------------------------------------
Value::operator float_type()
{
    return GetFloat();
}

//-----------------------------------------------------------------------------------------------
Value::operator bool()
{
    return GetBool();
}
}  // namespace mu

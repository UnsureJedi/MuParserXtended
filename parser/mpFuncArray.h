/*
Function for creating the Value object that contains an array of Value objects by allocating
space in Value's "Array_Value" field.

*/

#include "mpICallback.h"

//--- Parser framework -----------------------------------------------------
#include "mpValue.h"
#include "mpError.h"


MUP_NAMESPACE_START

class FunArray : public ICallback
{
public:
	FunArray();
	virtual ~FunArray();
	virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc) override;
	virtual const char_type* GetDesc() const override;
	virtual ptr_tok_type Clone() const override;
};

FunArray::FunArray()
	:ICallback(cmFUNC, _T("Array"), -1)
{}

//-----------------------------------------------------------------------
FunArray::~FunArray()
{}

//-----------------------------------------------------------------------
void FunArray::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int argc)
{
	// Redem note: for now, only initialization of 1D array is allowed per function call.
	if (argc != 1)
	{
		ErrorContext err;
		err.Errc = ecINVALID_NUMBER_OF_PARAMETERS;
		err.Arg = argc;
		err.Ident = GetIdent();
		throw ParserError(err);
	}

	ret->Initialize_Array(ret, a_pArg[0]->GetInteger());	// Assigning the array to IValue pointer
}

//-----------------------------------------------------------------------
const char_type* FunArray::GetDesc() const
{
	return _T("Array(n) - Creates an array with n number of elements, without initializing the elements");
}

//-----------------------------------------------------------------------
ptr_tok_type FunArray::Clone() const
{
	return ptr_tok_type(new FunArray(*this));
}

MUP_NAMESPACE_END
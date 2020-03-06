#include "FpUtils.h"
#include "MipsJitter.h"

#include <xmmintrin.h>
#include <pmmintrin.h>

#define EXC_FP_MAX 0x7F7FFFFF

void FpUtils::SetDenormalHandlingMode()
{
	_MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
	_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
}

void FpUtils::IsZero(CMipsJitter* codeGen, size_t offset)
{
	//Check wether an FP number is +/-0
	//BeginIf(CONDITION_EQ) to verify result
	codeGen->PushRel(offset);
	codeGen->PushCst(0x7FFFFFFF);
	codeGen->And();
	codeGen->PushCst(0);
}

void FpUtils::ComputeDivisionByZero(CMipsJitter* codeGen, size_t dividend, size_t divisor)
{
	//Return either +/-FP_MAX
	codeGen->PushCst(EXC_FP_MAX);
	codeGen->PushRel(dividend);
	codeGen->PushRel(divisor);
	codeGen->Xor();
	codeGen->PushCst(0x80000000);
	codeGen->And();
	codeGen->Or();
}

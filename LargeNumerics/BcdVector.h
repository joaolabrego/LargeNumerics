/******************************************************************************/
/*** File-Name: BcdVector.h  	                                            ***/
/*** Author...: João da Rocha Labrego                                       ***/
/*** E-Mail...: joaolabrego@gmail.com                                       ***/
/*** Purpose..: BcdVector implementation.                                   ***/
/******************************************************************************/

#ifndef BcdVector_H
#define BcdVector_H

#include "NumericString.h"

static const VECTOR NULL = {};
static const VECTOR ZERO = { 0 };
static const VECTOR ONE = { 1 };

struct BcdVector
{
public:
	/* Assignment Operations */
	static VECTOR& ToNull(VECTOR& target) { target.clear(); return target; }
	static VECTOR& ToZero(VECTOR& target) { target = ZERO; return target; }
	static VECTOR& ToOne(VECTOR& target) { target = ONE; return target; }
	static VECTOR& ToValue(VECTOR& target, DOUBLE_DIGIT value);
	static VECTOR& ToValue(VECTOR& target, const string& value);
	static VECTOR& ToValue(VECTOR& target, const char value[]) { return ToValue(target, string(value)); }
	static VECTOR& ToValue(VECTOR& target, const VECTOR& value) { return target = value; }

	/* String Conversion Operations */
	static string AsString(const VECTOR& value, const bool grouped);

	/* Subvector Operations */
	static VECTOR SubVector(const VECTOR& value, const size_t start, size_t length = string::npos);

	/* Boolean Attributes */
	static bool IsNull(const VECTOR& value) { return value.empty(); }
	static bool IsZero(const VECTOR& value) { return value.size() == 1 && !value.front(); }
	static bool IsNullOrZero(const VECTOR& value) { return value.empty() || (value.size() == 1 && !value.front()); }
	static bool IsOne(const VECTOR& value) { return value.size() == 1 && value.front() == 1; }
	static bool IsOdd(const VECTOR& value) { return value.size() && (value.front() & 0x1); }
	static bool IsEven(const VECTOR& value) { return value.size() && !(value.front() & 0x1); }
	static bool IsBase(const VECTOR& value) { return value.size() == 2 && !value.front() && value.back() == 1; }

	/* Arithmetic Operations */
	static COMPARISON Compare(const VECTOR& leftComparand, DIGIT rightComparand);
	static COMPARISON Compare(const VECTOR& leftComparand, const VECTOR& rightComparand);
	static void Normalize(VECTOR& value);
	static VECTOR Add(const VECTOR& augend, const VECTOR& addend);
	static VECTOR& Increment(VECTOR& augend);
	static VECTOR Subtract(const VECTOR& minuend, const VECTOR& subtrahend);
	static VECTOR Subtract1(const VECTOR& minuend, VECTOR subtrahend);
	static VECTOR& Decrement(VECTOR& minuend);
	static VECTOR Multiply(VECTOR multiplicand, const DIGIT multiplier);
	static VECTOR Multiply(const VECTOR& multiplicand, const VECTOR& multiplier);
	static VECTOR Divide(VECTOR dividend, const DIGIT divisor, DIGIT& remainder);
	static VECTOR Divide(const VECTOR& dividend, const DIGIT divisor) { DIGIT remainder; return Divide(dividend, divisor, remainder); }
	static VECTOR Divide(VECTOR dividend, VECTOR divisor, VECTOR& remainder);
	static VECTOR Divide(const VECTOR& dividend, const VECTOR& divisor) { VECTOR remainder; return Divide(dividend, divisor, remainder); }
	static DIGIT Module(const VECTOR& dividend, DIGIT divisor) { DIGIT remainder; return (Divide(dividend, divisor, remainder), remainder); }
	static VECTOR Module(const VECTOR& dividend, const VECTOR& divisor) { VECTOR remainder; return (Divide(dividend, divisor, remainder), remainder); }
	static void ShiftLeft(VECTOR& value, size_t decimalDigits);
	static VECTOR ShiftRight(VECTOR& value, size_t count);
	static VECTOR Power(VECTOR base, size_t exponent);
	static VECTOR Root(const VECTOR& radicand, size_t degree, VECTOR& remainder);
	static VECTOR GCD(const VECTOR& leftValue, const VECTOR& rightValue);
	static VECTOR LCM(const VECTOR& leftValue, const VECTOR& rightValue);
	static VECTOR Factorial(VECTOR value);
	static VECTOR Complement(const VECTOR& value);
protected:
	static void CalculateDigit(const VECTOR& radicand, size_t degree, VECTOR& root, VECTOR& remainder);
	static void CalculateDigit1(const VECTOR& radicand, size_t degree, VECTOR& root, VECTOR& remainder);
	static VECTOR CalculateSum(const VECTOR& augend, const VECTOR& addend, bool ignoreLastCarry = false);
	static VECTOR CalculateGCD(VECTOR leftValue, VECTOR rightValue);
};
#endif // BcdVector_H
/***********/
/*** EOF ***/
/***********/

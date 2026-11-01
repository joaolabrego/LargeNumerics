/******************************************************************************/
/*** File-Name: NumericVector.h  	                                        ***/
/*** Author...: João da Rocha Labrego                                       ***/
/*** E-Mail...: joaolabrego@gmail.com                                       ***/
/*** Purpose..: NumericVector implementation.                               ***/
/******************************************************************************/

#ifndef NumericVector_H
#define NumericVector_H

#include "Config.h"

static const VECTOR NULL = {};
static const VECTOR ZERO = { 0 };
static const VECTOR ONE = { 1 };

class NumericVector
{
	static VECTOR SubVector(const VECTOR& value, const size_t start, size_t length = string::npos);
	static VECTOR& Assign(VECTOR& target, const VECTOR& value);
	static VECTOR& Insert(VECTOR& target, const DIGIT value);
	static VECTOR& Insert(VECTOR& target, const size_t count, const DIGIT value);
	static VECTOR& Insert(VECTOR& target, const VECTOR& value);
	static VECTOR& Append(VECTOR& target, const DIGIT value);
	static VECTOR& Append(VECTOR& target, const size_t count, const DIGIT value);
	static VECTOR& Append(VECTOR& target, const VECTOR& value);
	static VECTOR& ToNull(VECTOR& target);
	static VECTOR& ToZero(VECTOR& target);
	static VECTOR& ToOne(VECTOR& target);

	static bool IsNull(const VECTOR& value);
	static bool IsZero(const VECTOR& value);
	static bool IsNullOrZero(const VECTOR& value);
	static bool IsOne(const VECTOR& value);
	static bool IsOdd(const VECTOR& value);
	static bool IsEven(const VECTOR& value);

	static COMPARISON Compare(const VECTOR& leftComparand, DIGIT rightComparand);
	static COMPARISON Compare(const VECTOR& leftComparand, const VECTOR& rightComparand);
	static void Normalize(VECTOR& value);
	static VECTOR Add(const VECTOR& augend, const VECTOR& addend);
	static VECTOR& Increment(VECTOR& augend);
	static VECTOR Subtract(const VECTOR& minuend, const VECTOR& subtrahend);
	static VECTOR& Decrement(VECTOR& minuend);
	static VECTOR Multiply(VECTOR multiplicand, const DIGIT multiplier);
	static VECTOR Multiply(const VECTOR& multiplicand, const VECTOR& multiplier);
	static VECTOR Divide(VECTOR dividend, const DIGIT divisor, DIGIT& remainder);
	static VECTOR Divide(const VECTOR& dividend, const DIGIT divisor) { DIGIT remainder; return Divide(dividend, divisor, remainder); }
	static VECTOR Divide(VECTOR dividend, VECTOR divisor, VECTOR& remainder);
	static VECTOR Divide(const VECTOR& dividend, const VECTOR& divisor) { VECTOR remainder; return Divide(dividend, divisor, remainder); }
	static DIGIT Module(const VECTOR& dividend, DOUBLE_DIGIT divisor) { DIGIT remainder; return (Divide(dividend, divisor, remainder), remainder); }
	static VECTOR Module(const VECTOR& dividend, const VECTOR& divisor) { VECTOR remainder; return (Divide(dividend, divisor, remainder), remainder); }
	static void ShiftLeft(VECTOR& value, size_t decimalDigits);
	static VECTOR ShiftRight(VECTOR& value, size_t count);
	static VECTOR Power(VECTOR base, size_t exponent);
	static VECTOR Root(const VECTOR& radicand, size_t degree, VECTOR& remainder);
	static VECTOR GCD(const VECTOR& leftValue, const VECTOR& rightValue);
	static VECTOR LCM(const VECTOR& leftValue, const VECTOR& rightValue);
	static VECTOR Factorial(VECTOR value);
protected:
	static void CalculateDigit(const VECTOR& radicand, size_t degree, VECTOR& root, VECTOR& remainder);
	static VECTOR CalculateSum(const VECTOR& augend, const VECTOR& addend);
	static VECTOR CalculateGCD(VECTOR leftValue, VECTOR rightValue);
};
#endif // NumericVector_H
/***********/
/*** EOF ***/
/***********/

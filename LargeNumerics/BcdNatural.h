/******************************************************************************/
/*** File-Name: BcdNatural.h                                                ***/
/*** Author...: João da Rocha Labrego                                       ***/
/*** E-Mail...: joaolabrego@gmail.com                                       ***/
/*** Purpose..: BcdNatural header.                                          ***/
/******************************************************************************/

#ifndef BcdNatural_H
#define BcdNatural_H

#include "BcdNumericVector.h"

struct BcdNatural
{
public:
	/* Constructors and Destructor */
	BcdNatural() {}
	BcdNatural(const DIGIT value) { *this = value; }
	BcdNatural(const char value[]) { *this = string(value); }
	BcdNatural(const string& value) { *this = value; }
	BcdNatural(const VECTOR& value) { *this = value; }
	BcdNatural(const BcdNatural& value) { *this = value; }
	~BcdNatural() {}

	/* Assignment Operations */
	BcdNatural& ToNull() { return (BcdNumericVector::ToNull(data), *this); }
	BcdNatural& ToZero() { return (BcdNumericVector::ToZero(data), *this); }
	BcdNatural& ToOne() { return (BcdNumericVector::ToOne(data), *this); }

	/* Conversion Operations */
	VECTOR AsVector() const { return data; }
	string ToString(const bool grouped = Config->SHOW_GROUPED) const { return BcdNumericVector::ToString(data, grouped); }

	/* Assignment Operators */
	BcdNatural& operator =(DIGIT value) { return (BcdNumericVector::ToValue(data, value), *this); }
	BcdNatural& operator =(const char value[]) { return (BcdNumericVector::ToValue(data, string(value)), *this); }
	BcdNatural& operator =(const string& value) { return (BcdNumericVector::ToValue(data, value), *this); }
	BcdNatural& operator =(const VECTOR& value) { return (BcdNumericVector::ToValue(data, value), *this); }
	BcdNatural& operator =(const BcdNatural& value) { return (BcdNumericVector::ToValue(data, value.data), *this); }

	/* Boolean Attributes */
	bool IsNull() const { return BcdNumericVector::IsNull(data); }
	bool IsZero() const { return BcdNumericVector::IsZero(data); }
	bool IsNullOrZero() const { return BcdNumericVector::IsNullOrZero(data); }
	bool IsOne() const { return BcdNumericVector::IsOne(data); }
	bool IsOdd() const { return BcdNumericVector::IsOdd(data); }
	bool IsEven() const { return BcdNumericVector::IsEven(data); }
	COMPARISON Compare(const DIGIT rightComparand) const { return BcdNumericVector::Compare(data, rightComparand); }
	COMPARISON Compare(const BcdNatural& rightComparand) const { return BcdNumericVector::Compare(data, rightComparand.data); }

	/* Arithmetic Operations */
	BcdNatural Divide(const DIGIT divisor, DIGIT& remainder) const { return BcdNumericVector::Divide(data, divisor, remainder); }
	BcdNatural Divide(const BcdNatural& divisor, BcdNatural& remainder) const { return BcdNumericVector::Divide(data, divisor.data, remainder.data); }
	BcdNatural Power(DIGIT exponent) const { return BcdNumericVector::Power(data, exponent); }
	BcdNatural Root(const DIGIT degree, BcdNatural& remainder) const { return BcdNumericVector::Root(data, degree, remainder.data); }
	BcdNatural GCD(const BcdNatural& rightValue) const { return BcdNumericVector::GCD(data, rightValue.data); }
	BcdNatural LCM(const BcdNatural& rightValue) const { return BcdNumericVector::LCM(data, rightValue.data); }
	BcdNatural Factorial() const { return BcdNumericVector::Factorial(data); }

	/* Comparison Operators */
	bool operator <(const DIGIT rightComparand) const { return BcdNumericVector::Compare(data, rightComparand) == COMPARISON::MINOR; }
	bool operator <=(const DIGIT rightComparand) const { return BcdNumericVector::Compare(data, rightComparand) != COMPARISON::MAJOR; }
	bool operator ==(const DIGIT rightComparand) const { return BcdNumericVector::Compare(data, rightComparand) == COMPARISON::EQUAL; }
	bool operator !=(const DIGIT rightComparand) const { return BcdNumericVector::Compare(data, rightComparand) != COMPARISON::EQUAL; }
	bool operator >(const DIGIT rightComparand) const { return BcdNumericVector::Compare(data, rightComparand) == COMPARISON::MAJOR; }
	bool operator >=(const DIGIT rightComparand) const { return BcdNumericVector::Compare(data, rightComparand) != COMPARISON::MINOR; }

	bool operator <(const BcdNatural& rightComparand) const { return BcdNumericVector::Compare(data, rightComparand.data) == COMPARISON::MINOR; }
	bool operator <=(const BcdNatural& rightComparand) const { return BcdNumericVector::Compare(data, rightComparand.data) != COMPARISON::MAJOR; }
	bool operator ==(const BcdNatural& rightComparand) const { return BcdNumericVector::Compare(data, rightComparand.data) == COMPARISON::EQUAL; }
	bool operator !=(const BcdNatural& rightComparand) const { return BcdNumericVector::Compare(data, rightComparand.data) != COMPARISON::EQUAL; }
	bool operator >(const BcdNatural& rightComparand) const { return BcdNumericVector::Compare(data, rightComparand.data) == COMPARISON::MAJOR; }
	bool operator >=(const BcdNatural& rightComparand) const { return BcdNumericVector::Compare(data, rightComparand.data) != COMPARISON::MINOR; }

	/* Arithmetic Operators */
	BcdNatural operator +(const BcdNatural& addend) const { return BcdNumericVector::Add(data, addend.data); }
	BcdNatural& operator ++() { return (BcdNumericVector::Increment(data), *this); }
	BcdNatural operator ++(int) { BcdNatural last = *this; BcdNumericVector::Increment(data); return last; }
	BcdNatural operator -(const BcdNatural& subtrahend) const { return BcdNumericVector::Subtract(data, subtrahend.data); }
	BcdNatural& operator --() { return (BcdNumericVector::Decrement(data), *this); }
	BcdNatural operator --(int) { BcdNatural last = *this; BcdNumericVector::Decrement(data); return last; }
	BcdNatural operator *(DIGIT multiplier) const { return BcdNumericVector::Multiply(data, multiplier); }
	BcdNatural operator *(const BcdNatural& multiplier) const { return BcdNumericVector::Multiply(data, multiplier.data); }
	BcdNatural operator /(DIGIT divisor) const { return BcdNumericVector::Divide(data, divisor); }
	BcdNatural operator /(const BcdNatural& divisor) const { return BcdNumericVector::Divide(data, divisor.data); }
	DIGIT operator %(DIGIT divisor) const { return BcdNumericVector::Module(data, divisor); }
	BcdNatural operator %(const BcdNatural& divisor) const { return BcdNumericVector::Module(data, divisor.data); }

	BcdNatural& operator +=(const BcdNatural& addend) { return *this = *this + addend; }
	BcdNatural& operator -=(const BcdNatural& subtrahend) { return *this = *this - subtrahend; }
	BcdNatural& operator *=(const DIGIT multiplier) { return *this = *this * multiplier; }
	BcdNatural& operator *=(const BcdNatural& multiplier) { return *this = *this * multiplier; }
	BcdNatural& operator /=(const DIGIT divisor) { return *this = *this / divisor; }
	BcdNatural& operator /=(const BcdNatural& divisor) { return *this = *this / divisor; }
	BcdNatural& operator %=(const DIGIT divisor) { return *this = *this % divisor; }
	BcdNatural& operator %=(const BcdNatural& divisor) { return *this = *this % divisor; }
private:
	VECTOR data;
};

inline BcdNatural operator""_BcdN(const char* text, size_t length) { return BcdNatural(string(text, length)); }

#endif // BcdNatural_H
/***********/
/*** EOF ***/
/***********/
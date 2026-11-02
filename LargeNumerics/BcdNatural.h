/******************************************************************************/
/*** File-Name: BcdNatural.h                                                ***/
/*** Author...: João da Rocha Labrego                                       ***/
/*** E-Mail...: joaolabrego@gmail.com                                       ***/
/*** Purpose..: BcdNatural header.                                          ***/
/******************************************************************************/

#ifndef BcdNatural_H
#define BcdNatural_H

#include "NumericVector.h"

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
	BcdNatural& ToNull() { return (NumericVector::ToNull(data), *this); }
	BcdNatural& ToZero() { return (NumericVector::ToZero(data), *this); }
	BcdNatural& ToOne() { return (NumericVector::ToOne(data), *this); }

	/* Conversion Operations */
	VECTOR AsVector() const { return data; }
	string ToString(const bool grouped = SHOW_GROUPED) const { return NumericVector::ToString(data, grouped); }

	/* Assignment Operators */
	BcdNatural& operator =(DIGIT value) { return (NumericVector::ToValue(data, value), *this); }
	BcdNatural& operator =(const char value[]) { return (NumericVector::ToValue(data, string(value)), *this); }
	BcdNatural& operator =(const string& value) { return (NumericVector::ToValue(data, value), *this); }
	BcdNatural& operator =(const VECTOR& value) { return (NumericVector::ToValue(data, value), *this); }
	BcdNatural& operator =(const BcdNatural& value) { return (NumericVector::ToValue(data, value.data), *this); }

	/* Boolean Attributes */
	bool IsNull() const { return NumericVector::IsNull(data); }
	bool IsZero() const { return NumericVector::IsZero(data); }
	bool IsNullOrZero() const { return NumericVector::IsNullOrZero(data); }
	bool IsOne() const { return NumericVector::IsOne(data); }
	bool IsOdd() const { return NumericVector::IsOdd(data); }
	bool IsEven() const { return NumericVector::IsEven(data); }
	COMPARISON Compare(const DIGIT rightComparand) const { return NumericVector::Compare(data, rightComparand); }
	COMPARISON Compare(const BcdNatural& rightComparand) const { return NumericVector::Compare(data, rightComparand.data); }

	/* Arithmetic Operations */
	BcdNatural Divide(const DIGIT divisor, DIGIT& remainder) const { return NumericVector::Divide(data, divisor, remainder); }
	BcdNatural Divide(const BcdNatural& divisor, BcdNatural& remainder) const { return NumericVector::Divide(data, divisor.data, remainder.data); }
	BcdNatural Power(DIGIT exponent) const { return NumericVector::Power(data, exponent); }
	BcdNatural Root(const DIGIT degree, BcdNatural& remainder) const { return NumericVector::Root(data, degree, remainder.data); }
	BcdNatural GCD(const BcdNatural& rightValue) const { return NumericVector::GCD(data, rightValue.data); }
	BcdNatural LCM(const BcdNatural& rightValue) const { return NumericVector::LCM(data, rightValue.data); }
	BcdNatural Factorial() const { return NumericVector::Factorial(data); }

	/* Comparison Operators */
	bool operator <(const DIGIT rightComparand) const { return NumericVector::Compare(data, rightComparand) == COMPARISON::MINOR; }
	bool operator <=(const DIGIT rightComparand) const { return NumericVector::Compare(data, rightComparand) != COMPARISON::MAJOR; }
	bool operator ==(const DIGIT rightComparand) const { return NumericVector::Compare(data, rightComparand) == COMPARISON::EQUAL; }
	bool operator !=(const DIGIT rightComparand) const { return NumericVector::Compare(data, rightComparand) != COMPARISON::EQUAL; }
	bool operator >(const DIGIT rightComparand) const { return NumericVector::Compare(data, rightComparand) == COMPARISON::MAJOR; }
	bool operator >=(const DIGIT rightComparand) const { return NumericVector::Compare(data, rightComparand) != COMPARISON::MINOR; }

	bool operator <(const BcdNatural& rightComparand) const { return NumericVector::Compare(data, rightComparand.data) == COMPARISON::MINOR; }
	bool operator <=(const BcdNatural& rightComparand) const { return NumericVector::Compare(data, rightComparand.data) != COMPARISON::MAJOR; }
	bool operator ==(const BcdNatural& rightComparand) const { return NumericVector::Compare(data, rightComparand.data) == COMPARISON::EQUAL; }
	bool operator !=(const BcdNatural& rightComparand) const { return NumericVector::Compare(data, rightComparand.data) != COMPARISON::EQUAL; }
	bool operator >(const BcdNatural& rightComparand) const { return NumericVector::Compare(data, rightComparand.data) == COMPARISON::MAJOR; }
	bool operator >=(const BcdNatural& rightComparand) const { return NumericVector::Compare(data, rightComparand.data) != COMPARISON::MINOR; }

	/* Arithmetic Operators */
	BcdNatural operator +(const BcdNatural& addend) const { return NumericVector::Add(data, addend.data); }
	BcdNatural& operator ++() { return (NumericVector::Increment(data), *this); }
	BcdNatural operator ++(int) { BcdNatural last = *this; NumericVector::Increment(data); return last; }
	BcdNatural operator -(const BcdNatural& subtrahend) const { return NumericVector::Subtract(data, subtrahend.data); }
	BcdNatural& operator --() { return (NumericVector::Decrement(data), *this); }
	BcdNatural operator --(int) { BcdNatural last = *this; NumericVector::Decrement(data); return last; }
	BcdNatural operator *(DIGIT multiplier) const { return NumericVector::Multiply(data, multiplier); }
	BcdNatural operator *(const BcdNatural& multiplier) const { return NumericVector::Multiply(data, multiplier.data); }
	BcdNatural operator /(DIGIT divisor) const { return NumericVector::Divide(data, divisor); }
	BcdNatural operator /(const BcdNatural& divisor) const { return NumericVector::Divide(data, divisor.data); }
	DIGIT operator %(DIGIT divisor) const { return NumericVector::Module(data, divisor); }
	BcdNatural operator %(const BcdNatural& divisor) const { return NumericVector::Module(data, divisor.data); }

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

#endif // BcdNatural_H
/***********/
/*** EOF ***/
/***********/
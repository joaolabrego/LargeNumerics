/******************************************************************************/
/*** File-Name: BcdNatural.h                                                ***/
/*** Author...: João da Rocha Labrego                                       ***/
/*** E-Mail...: joaolabrego@gmail.com                                       ***/
/*** Purpose..: BcdNatural header.                                          ***/
/******************************************************************************/

#ifndef BcdNatural_H
#define BcdNatural_H

#include "BcdVector.h"

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
	BcdNatural& ToNull() { return (BcdVector::ToNull(data), *this); }
	BcdNatural& ToZero() { return (BcdVector::ToZero(data), *this); }
	BcdNatural& ToOne() { return (BcdVector::ToOne(data), *this); }

	/* Conversion Operations */
	VECTOR AsVector() const { return data; }
	string AsString(const bool grouped = Config->SHOW_GROUPED) const { return BcdVector::AsString(data, grouped); }

	/* Assignment Operators */
	BcdNatural& operator =(DOUBLE_DIGIT value) { return (BcdVector::ToValue(data, value), *this); }
	BcdNatural& operator =(const char value[]) { return (BcdVector::ToValue(data, string(value)), *this); }
	BcdNatural& operator =(const string& value) { return (BcdVector::ToValue(data, value), *this); }
	BcdNatural& operator =(const VECTOR& value) { return (BcdVector::ToValue(data, value), *this); }
	BcdNatural& operator =(const BcdNatural& value) { return (BcdVector::ToValue(data, value.data), *this); }

	/* Boolean Attributes */
	bool IsNull() const { return BcdVector::IsNull(data); }
	bool IsZero() const { return BcdVector::IsZero(data); }
	bool IsNullOrZero() const { return BcdVector::IsNullOrZero(data); }
	bool IsOne() const { return BcdVector::IsOne(data); }
	bool IsOdd() const { return BcdVector::IsOdd(data); }
	bool IsEven() const { return BcdVector::IsEven(data); }
	COMPARISON Compare(const DIGIT rightComparand) const { return BcdVector::Compare(data, rightComparand); }
	COMPARISON Compare(const BcdNatural& rightComparand) const { return BcdVector::Compare(data, rightComparand.data); }

	/* Arithmetic Operations */
	BcdNatural Divide(const DIGIT divisor, DIGIT& remainder) const { return BcdVector::Divide(data, divisor, remainder); }
	BcdNatural Divide(const BcdNatural& divisor, BcdNatural& remainder) const { return BcdVector::Divide(data, divisor.data, remainder.data); }
	BcdNatural Power(DIGIT exponent) const { return BcdVector::Power(data, exponent); }
	BcdNatural Root(const DIGIT degree, BcdNatural& remainder) const { return BcdVector::Root(data, degree, remainder.data); }
	BcdNatural GCD(const BcdNatural& rightValue) const { return BcdVector::GCD(data, rightValue.data); }
	BcdNatural LCM(const BcdNatural& rightValue) const { return BcdVector::LCM(data, rightValue.data); }
	BcdNatural Factorial() const { return BcdVector::Factorial(data); }
	BcdNatural Complement() { return (BcdVector::Complement(data), BcdVector::Increment(data), *this); }

	/* Comparison Operators */
	bool operator <(const DIGIT rightComparand) const { return BcdVector::Compare(data, rightComparand) == COMPARISON::MINOR; }
	bool operator <=(const DIGIT rightComparand) const { return BcdVector::Compare(data, rightComparand) != COMPARISON::MAJOR; }
	bool operator ==(const DIGIT rightComparand) const { return BcdVector::Compare(data, rightComparand) == COMPARISON::EQUAL; }
	bool operator !=(const DIGIT rightComparand) const { return BcdVector::Compare(data, rightComparand) != COMPARISON::EQUAL; }
	bool operator >(const DIGIT rightComparand) const { return BcdVector::Compare(data, rightComparand) == COMPARISON::MAJOR; }
	bool operator >=(const DIGIT rightComparand) const { return BcdVector::Compare(data, rightComparand) != COMPARISON::MINOR; }

	bool operator <(const BcdNatural& rightComparand) const { return BcdVector::Compare(data, rightComparand.data) == COMPARISON::MINOR; }
	bool operator <=(const BcdNatural& rightComparand) const { return BcdVector::Compare(data, rightComparand.data) != COMPARISON::MAJOR; }
	bool operator ==(const BcdNatural& rightComparand) const { return BcdVector::Compare(data, rightComparand.data) == COMPARISON::EQUAL; }
	bool operator !=(const BcdNatural& rightComparand) const { return BcdVector::Compare(data, rightComparand.data) != COMPARISON::EQUAL; }
	bool operator >(const BcdNatural& rightComparand) const { return BcdVector::Compare(data, rightComparand.data) == COMPARISON::MAJOR; }
	bool operator >=(const BcdNatural& rightComparand) const { return BcdVector::Compare(data, rightComparand.data) != COMPARISON::MINOR; }

	/* Arithmetic Operators */
	BcdNatural operator +(const BcdNatural& addend) const { return BcdVector::Add(data, addend.data); }
	BcdNatural& operator ++() { return (BcdVector::Increment(data), *this); }
	BcdNatural operator ++(int) { BcdNatural last = *this; BcdVector::Increment(data); return last; }
	BcdNatural operator -(const BcdNatural& subtrahend) const { return BcdVector::Subtract(data, subtrahend.data); }
	BcdNatural& operator --() { return (BcdVector::Decrement(data), *this); }
	BcdNatural operator --(int) { BcdNatural last = *this; BcdVector::Decrement(data); return last; }
	BcdNatural operator *(DIGIT multiplier) const { return BcdVector::Multiply(data, multiplier); }
	BcdNatural operator *(const BcdNatural& multiplier) const { return BcdVector::Multiply(data, multiplier.data); }
	BcdNatural operator /(DIGIT divisor) const { return BcdVector::Divide(data, divisor); }
	BcdNatural operator /(const BcdNatural& divisor) const { return BcdVector::Divide(data, divisor.data); }
	DIGIT operator %(DIGIT divisor) const { return BcdVector::Module(data, divisor); }
	BcdNatural operator %(const BcdNatural& divisor) const { return BcdVector::Module(data, divisor.data); }
	BcdNatural operator <<(size_t count) { return (BcdVector::ShiftLeft(data, count), *this); }
	BcdNatural operator >>(size_t count) { return (BcdVector::ShiftRight(data, count), *this); }
	BcdNatural operator ~() { return (BcdVector::Complement(data), *this); }

	BcdNatural& operator +=(const BcdNatural& addend) { return *this = *this + addend; }
	BcdNatural& operator -=(const BcdNatural& subtrahend) { return *this = *this - subtrahend; }
	BcdNatural& operator *=(const DIGIT multiplier) { return *this = *this * multiplier; }
	BcdNatural& operator *=(const BcdNatural& multiplier) { return *this = *this * multiplier; }
	BcdNatural& operator /=(const DIGIT divisor) { return *this = *this / divisor; }
	BcdNatural& operator /=(const BcdNatural& divisor) { return *this = *this / divisor; }
	BcdNatural& operator %=(const DIGIT divisor) { return *this = *this % divisor; }
	BcdNatural& operator %=(const BcdNatural& divisor) { return *this = *this % divisor; }
	BcdNatural& operator <<=(size_t count) { return *this = *this << count; }
	BcdNatural& operator >>=(size_t count) { return *this = *this >> count; }
private:
	VECTOR data;
};

inline BcdNatural operator""_BcdN(const char* text, size_t length) { return BcdNatural(string(text, length)); }

#endif // BcdNatural_H
/***********/
/*** EOF ***/
/***********/
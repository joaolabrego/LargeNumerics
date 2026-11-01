/******************************************************************************/
/*** File-Name: BcdNatural.h                                                ***/
/*** Author...: João da Rocha Labrego                                       ***/
/*** E-Mail...: joaolabrego@gmail.com                                       ***/
/*** Purpose..: BcdNatural header.                                          ***/
/******************************************************************************/

#ifndef BcdNatural_H
#define BcdNatural_H

#include "NumericString.h"

struct BcdNatural: private VECTOR
{
public:
	BcdNatural() {}
	BcdNatural(const DIGIT value) { ToValue(value); }
	BcdNatural(const char value[]) { *this = string(value); }
	BcdNatural(const string& value) { *this = value; }
	BcdNatural(const VECTOR& value) { *this = value; }
	~BcdNatural() {}

	BcdNatural& ToNull() { return (clear(), *this); }
	BcdNatural& ToZero() { return (assign(ZERO.begin(), ZERO.end()), *this); }
	BcdNatural& ToOne() { return (assign(ONE.begin(), ONE.end()), *this); }
	BcdNatural& ToValue(DIGIT value) { ToNull(); push_back(value); return *this; }
	string ToString(const bool grouped = SHOW_GROUPED) const;

	BcdNatural& operator =(DIGIT value) { return ToValue(value); }
	BcdNatural& operator =(const char value[]) { return *this = string(value); }
	BcdNatural& operator =(const string& value);
	BcdNatural& operator =(const VECTOR& value) { return (assign(value.begin(), value.end()), *this); }
	BcdNatural& operator =(const BcdNatural& value) { return (assign(value.begin(), value.end()), *this); }

	bool IsNull() const { return empty(); }
	bool IsZero() const { return size() == 1 && !front(); }
	bool IsNullOrZero() const { return empty() || (size() == 1 && !front()); }
	bool IsOne() const { return size() == 1 && front() == 1; }
	bool IsOdd() const { return size() && (front() & 0x1); }
	bool IsEven() const { return size() && !(front() & 0x1); }
	COMPARISON Compare(const DIGIT rightComparand) const;
	COMPARISON Compare(const BcdNatural& rightComparand) const;

	BcdNatural Divide(const DIGIT divisor, DIGIT& remainder) const;
	DIGIT BinarySearchDigit(const BcdNatural& divisor, BcdNatural& remainder) const;
	BcdNatural Divide(const BcdNatural& divisor, BcdNatural& remainder) const;
	BcdNatural Power(DIGIT exponent) const;
	void BinarySearchDigit(DIGIT degree, BcdNatural& root, BcdNatural& remainder) const;
	BcdNatural Root(const DIGIT degree, BcdNatural& remainder) const;
	BcdNatural GCD(const BcdNatural& rightValue) const;
	BcdNatural LCM(const BcdNatural& rightValue) const;
	BcdNatural Factorial() const;

	bool operator <(const DIGIT rightComparand) const { return Compare(rightComparand) == COMPARISON::MINOR; }
	bool operator <=(const DIGIT rightComparand) const { return Compare(rightComparand) != COMPARISON::MAJOR; }
	bool operator ==(const DIGIT rightComparand) const { return Compare(rightComparand) == COMPARISON::EQUAL; }
	bool operator !=(const DIGIT rightComparand) const { return Compare(rightComparand) != COMPARISON::EQUAL; }
	bool operator >(const DIGIT rightComparand) const { return Compare(rightComparand) == COMPARISON::MAJOR; }
	bool operator >=(const DIGIT rightComparand) const { return Compare(rightComparand) != COMPARISON::MINOR; }

	bool operator <(const BcdNatural& rightComparand) const { return Compare(rightComparand) == COMPARISON::MINOR; }
	bool operator <=(const BcdNatural& rightComparand) const { return Compare(rightComparand) != COMPARISON::MAJOR; }
	bool operator ==(const BcdNatural& rightComparand) const { return Compare(rightComparand) == COMPARISON::EQUAL; }
	bool operator !=(const BcdNatural& rightComparand) const { return Compare(rightComparand) != COMPARISON::EQUAL; }
	bool operator >(const BcdNatural& rightComparand) const { return Compare(rightComparand) == COMPARISON::MAJOR; }
	bool operator >=(const BcdNatural& rightComparand) const { return Compare(rightComparand) != COMPARISON::MINOR; }

	BcdNatural operator +(const BcdNatural& addend) const;
	BcdNatural& operator ++();
	BcdNatural operator ++(int) { BcdNatural last = *this; ++*this; return last; }
	BcdNatural operator -(const BcdNatural& subtrahend) const;
	BcdNatural& operator --();
	BcdNatural operator --(int) { BcdNatural last = *this; --*this; return last; }
	BcdNatural operator *(DIGIT multiplier) const;
	BcdNatural operator *(const BcdNatural& multiplier) const;
	BcdNatural operator /(DIGIT divisor) const { DIGIT remainder; return Divide(divisor, remainder); }
	BcdNatural operator /(const BcdNatural& divisor) const { BcdNatural remainder; return Divide(divisor, remainder); }
	DIGIT operator %(DIGIT divisor) const { DIGIT remainder; BcdNatural quotient = Divide(divisor, remainder); return remainder; }
	BcdNatural operator %(const BcdNatural& divisor) const { BcdNatural remainder, quotient = Divide(divisor, remainder); return remainder; }

	BcdNatural& operator +=(const BcdNatural& addend) { return *this = *this + addend; }
	BcdNatural& operator -=(const BcdNatural& subtrahend) { return *this = *this - subtrahend; }
	BcdNatural& operator *=(const DIGIT multiplier) { return *this = *this * multiplier; }
	BcdNatural& operator *=(const BcdNatural& multiplier) { return *this = *this * multiplier; }
	BcdNatural& operator /=(const DIGIT divisor) { return *this = *this / divisor; }
	BcdNatural& operator /=(const BcdNatural& divisor) { return *this = *this / divisor; }
	BcdNatural& operator %=(const DIGIT divisor) { return *this = *this % divisor; }
	BcdNatural& operator %=(const BcdNatural& divisor) { return *this = *this % divisor; }
protected:
	BcdNatural Add(const BcdNatural& addend) const;
	static BcdNatural CalculateGCD(BcdNatural leftValue, BcdNatural rightValue);
};

#endif // BcdNatural_H
/***********/
/*** EOF ***/
/***********/
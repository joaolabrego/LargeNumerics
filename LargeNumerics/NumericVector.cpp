/******************************************************************************/
/*** File-Name: NumericVector.cpp  	                                        ***/
/*** Author...: João da Rocha Labrego                                       ***/
/*** E-Mail...: joaolabrego@gmail.com                                       ***/
/*** Purpose..: NumericVector implementation.                               ***/
/******************************************************************************/

#include "NumericVector.h"

/**********************************************************************************/
COMPARISON NumericVector::Compare(const VECTOR& leftComparand, DIGIT rightComparand)
/**********************************************************************************/
{
	size_t length = leftComparand.size();
	DOUBLE_DIGIT value;

	if (!length)
		return COMPARISON::MINOR;
	if (length > 1)
		return COMPARISON::MAJOR;
	value = leftComparand.front();
	if (value < rightComparand)
		return COMPARISON::MINOR;
	if (value > rightComparand)
		return COMPARISON::MAJOR;

	return COMPARISON::EQUAL;
}
/******************************************************************************************/
COMPARISON NumericVector::Compare(const VECTOR& leftComparand, const VECTOR& rightComparand)
/******************************************************************************************/
{
	size_t leftLength = leftComparand.size(),
		rightLength = rightComparand.size();
	DIGIT left,
		right;

	if (leftLength < rightLength)
		return COMPARISON::MINOR;
	if (leftLength > rightLength)
		return COMPARISON::MAJOR;
	for (size_t i = leftLength; i;)
	{
		left = leftComparand.at(--i);
		right = rightComparand.at(i);
		if (left < right)
			return COMPARISON::MINOR;
		if (left > right)
			return COMPARISON::MAJOR;
	}

	return COMPARISON::EQUAL;
}
/******************************************/
void NumericVector::Normalize(VECTOR& value)
/******************************************/
{
	size_t length = value.size(),
		i;

	if (length)
	{
		for (i = length; i && !value.at(i - 1); --i);
		if (i)
		{
			if (i < length)
				value.erase(value.begin() + i, value.end());
		}
		else
			value = ZERO;
	}
}
/*************************************************************************************/
VECTOR NumericVector::SubVector(const VECTOR& value, const size_t start, size_t length)
/*************************************************************************************/
{
	size_t lengthValue = value.size(),
		end;
	VECTOR result;

	if (lengthValue && start < lengthValue)
	{
		if (length == string::npos)
			length = value.size();
		if ((end = start + length) > lengthValue)
			result.assign(value.begin() + start, value.end());
		else
			result.assign(value.begin() + start, value.begin() + end);
	}

	return result;
}
/****************************************************************/
VECTOR& NumericVector::Assign(VECTOR& target, const VECTOR& value)
/****************************************************************/
{
	return (target.assign(value.begin(), value.end()), target);
}
/**************************************************************/
VECTOR& NumericVector::Insert(VECTOR& target, const DIGIT value)
/**************************************************************/
{
	return (target.insert(target.begin(), value), target);
}
/**********************************************************************************/
VECTOR& NumericVector::Insert(VECTOR& target, const size_t count, const DIGIT value)
/**********************************************************************************/
{
	return (target.insert(target.begin(), count, value), target);
}
/****************************************************************/
VECTOR& NumericVector::Insert(VECTOR& target, const VECTOR& value)
/****************************************************************/
{
	return (target.insert(target.begin(), value.begin(), value.end()), target);
}
/**************************************************************/
VECTOR& NumericVector::Append(VECTOR& target, const DIGIT value)
/**************************************************************/
{
	return (target.push_back(value), target);
}
/**********************************************************************************/
VECTOR& NumericVector::Append(VECTOR& target, const size_t count, const DIGIT value)
/*******************************************************************************/
{
	return (target.insert(target.end(), count, value), target);
}
/****************************************************************/
VECTOR& NumericVector::Append(VECTOR& target, const VECTOR& value)
/****************************************************************/
{
	return (target.insert(target.end(), value.begin(), value.end()), target);
}
/*******************************************/
VECTOR& NumericVector::ToNull(VECTOR& target)
/*******************************************/
{
	return (target = NULL, target);
}
/*******************************************/
VECTOR& NumericVector::ToZero(VECTOR& target)
/*******************************************/
{
	return (target = ZERO, target);
}
/******************************************/
VECTOR& NumericVector::ToOne(VECTOR& target)
/******************************************/
{
	return (target = ONE, target);
}
/*********************************************/
bool NumericVector::IsNull(const VECTOR& value)
/********************************************/
{
	return value.empty();
}
/*********************************************/
bool NumericVector::IsZero(const VECTOR& value)
/********************************************/
{
	return value.size() == 1 && !value.front();
}
/***************************************************/
bool NumericVector::IsNullOrZero(const VECTOR& value)
/***************************************************/
{
	return value.empty() || (value.size() == 1 && !value.front());
}
/********************************************/
bool NumericVector::IsOne(const VECTOR& value)
/********************************************/
{
	return value.size() == 1 && value.front() == 1;
}
/********************************************/
bool NumericVector::IsOdd(const VECTOR& value)
/********************************************/
{
	return value.size() && (value.front() & 0x1);
}
/*********************************************/
bool NumericVector::IsEven(const VECTOR& value)
/*********************************************/
{
	return value.size() && !(value.front() & 0x1);
}
/****************************************************************************/
VECTOR NumericVector::CalculateSum(const VECTOR& augend, const VECTOR& addend)
/****************************************************************************/
{
	VECTOR sum;
	size_t leftLength = augend.size(),
		rightLength = addend.size(),
		i;
	DIGIT carry = 0;

	sum.resize(leftLength, 0);
	for (i = 0; i < rightLength; ++i)
	{
		carry += (augend.at(i) + addend.at(i));
		sum.at(i) = carry % DEC::BASE;
		carry /= DEC::BASE;
	}
	for (; i < leftLength; ++i)
	{
		carry += augend.at(i);
		sum.at(i) = carry % DEC::BASE;
		carry /= DEC::BASE;
	}
	if (carry)
		sum.push_back(carry);

	return sum;
}
/*******************************************************************/
VECTOR NumericVector::Add(const VECTOR& augend, const VECTOR& addend)
/*******************************************************************/
{
	size_t leftLength = augend.size(),
		rightLength = addend.size();

	if (leftLength && rightLength)
	{
		if (IsZero(augend))
			return addend;
		if (IsZero(addend))
			return augend;
		if (leftLength < rightLength)
			return VECTOR(CalculateSum(addend, augend));
		return VECTOR(CalculateSum(augend, addend));
	}

	return NULL;
}
/**********************************************/
VECTOR& NumericVector::Increment(VECTOR& augend)
/**********************************************/
{
	size_t length = augend.size(),
		i;

	if (length)
	{
		for (i = 0; i < length && augend.at(i) == DEC::MAXIMUM_VALUE; ++i)
			augend.at(i) = 0;
		if (i == length)
			augend.push_back(1);
		else
			++augend.at(i);
	}

	return augend;
}
/*****************************************************************************/
VECTOR NumericVector::Subtract(const VECTOR& minuend, const VECTOR& subtrahend)
/*****************************************************************************/
{
	VECTOR difference;
	size_t leftLength = minuend.size(),
		rightLength = subtrahend.size(),
		i;
	DIGIT borrow;
	COMPARISON comparison;

	if (leftLength && rightLength && (comparison = Compare(minuend, subtrahend)) != COMPARISON::MINOR)
	{
		if (comparison == COMPARISON::EQUAL)
			return ZERO;
		if (IsZero(subtrahend))
			return minuend;
		borrow = 0;
		difference.resize(leftLength, 0);
		for (i = 0; i < rightLength; ++i)
		{
			borrow = DEC::BASE + minuend.at(i) - subtrahend.at(i) - borrow;
			difference.at(i) = borrow % DEC::BASE;
			borrow = borrow < DEC::BASE;
		}
		for (; i < leftLength; ++i)
		{
			borrow = DEC::BASE + minuend.at(i) - borrow;
			difference.at(i) = borrow % DEC::BASE;
			borrow = borrow < DEC::BASE;
		}
		Normalize(difference);
	}

	return difference;
}
/***********************************************/
VECTOR& NumericVector::Decrement(VECTOR& minuend)
/***********************************************/
{
	size_t length = minuend.size(),
		i;

	if (length)
	{
		if (IsZero(minuend))
			minuend = NULL;
		else
		{
			for (i = 0; i < length && !minuend.at(i); ++i)
				minuend.at(i) = DEC::MAXIMUM_VALUE;
			Normalize(minuend);
		}
	}

	return minuend;
}
/********************************************************************************/
VECTOR NumericVector::Multiply(VECTOR multiplicand, const DIGIT multiplier)
/********************************************************************************/
{
	size_t length = multiplicand.size();
	VECTOR product;
	DOUBLE_DIGIT carry;

	if (length && multiplier <= DEC::BASE)
	{
		if (IsZero(multiplicand) || !multiplier)
			return ZERO;
		if (IsOne(multiplicand))
			return VECTOR(multiplier);
		if (multiplier == 1)
			return multiplicand;
		if (multiplier == DEC::BASE)
			return (multiplicand.insert(multiplicand.begin(), 0), multiplicand);
		carry = 0;
		product.resize(length, 0);
		for (size_t i = 0; i < length; ++i)
		{
			carry += DOUBLE_DIGIT(multiplicand.at(i)) * DOUBLE_DIGIT(multiplier);
			product.at(i) = DIGIT(carry % DEC::BASE);
			carry /= DEC::BASE;
		}
		if (carry)
			product.push_back(DIGIT(carry));
	}

	return product;
}
/**********************************************************************************/
VECTOR NumericVector::Multiply(const VECTOR& multiplicand, const VECTOR& multiplier)
/**********************************************************************************/
{
	size_t leftLength = multiplicand.size(),
		rightLength = multiplier.size();
	VECTOR product;
	DOUBLE_DIGIT carry;

	if (leftLength && rightLength)
	{
		if (IsZero(multiplicand) || IsZero(multiplier))
			return ZERO;
		if (IsOne(multiplicand))
			return multiplier;
		if (IsOne(multiplier))
			return multiplicand;
		if (rightLength == 1)
			return Multiply(multiplicand, multiplier.front());
		carry = 0;
		product.resize(leftLength + rightLength, 0);
		for (size_t i = 0, k; i < leftLength; ++i)
		{
			k = i;
			carry = 0;
			for (size_t j = 0; j < rightLength; ++j)
			{
				carry = DOUBLE_DIGIT(multiplicand.at(i)) * DOUBLE_DIGIT(multiplier.at(j)) + DOUBLE_DIGIT(product.at(k)) + carry;
				product.at(k++) = DIGIT(carry % DEC::BASE);
				carry /= DEC::BASE;
			}
			while (carry)
			{
				carry += product.at(k);
				product.at(k++) = DIGIT(carry % DEC::BASE);
				carry /= DEC::BASE;
			}
		}
		Normalize(product);
	}

	return product;
}
/**********************************************************************************/
VECTOR NumericVector::Divide(VECTOR dividend, const DIGIT divisor, DIGIT& remainder)
/**********************************************************************************/
{
	size_t length = dividend.size();
	DOUBLE_DIGIT partialDividend = 0;
	VECTOR quotient = NULL,
		comparand;
	COMPARISON comparison;

	remainder = 0;
	if (length && divisor && divisor <= DEC::BASE)
	{
		if (IsZero(dividend) || divisor == 1)
			return dividend;
		if ((comparison = Compare(dividend, divisor)) == COMPARISON::MINOR)
			return (remainder = dividend.front(), ZERO);
		if (comparison == COMPARISON::EQUAL)
			return ONE;
		if (divisor == DEC::BASE)
			return (remainder = dividend.front(), dividend.erase(dividend.begin()), dividend);
		for (size_t i = length; i;)
		{
			partialDividend = partialDividend * DEC::BASE + dividend.at(--i);
			if (partialDividend < divisor)
			{
				if (!quotient.empty())
					quotient.insert(quotient.begin(), 0);
				remainder = DIGIT(partialDividend);
			}
			else
			{
				quotient.insert(quotient.begin(), DIGIT(partialDividend / divisor));
				remainder = DIGIT(partialDividend %= divisor);
			}
		}
		Normalize(quotient);
	}

	return quotient;
}
/******************************************************************************/
VECTOR NumericVector::Divide(VECTOR dividend, VECTOR divisor, VECTOR& remainder)
/******************************************************************************/
{
	const size_t dividendLength = dividend.size(), 
		divisorLength = divisor.size();
	VECTOR partialDividend,
		quotient,
		product;
	COMPARISON comparison;
	DIGIT factor,
		digit,
		high;

	if (!dividendLength || !divisorLength || IsZero(divisor))
		return (remainder = NULL, NULL);
	if (IsZero(dividend) || IsOne(divisor))
		return (remainder = ZERO, dividend);
	if ((comparison = Compare(dividend, divisor)) == COMPARISON::MINOR)
		return (remainder = dividend, ZERO);
	if (comparison == COMPARISON::EQUAL)
		return (remainder = ZERO, ONE);
	factor = DIGIT(DEC::BASE / (DOUBLE_DIGIT(divisor.back()) + 1));
	dividend = Multiply(dividend, factor);
	divisor = Multiply(divisor, factor);
	for (size_t i = dividend.size(); i > 0;)
	{
		digit = 0;
		partialDividend.insert(partialDividend.begin(), dividend.at(--i));
		Normalize(partialDividend);
		comparison = Compare(partialDividend, divisor);
		if (comparison == COMPARISON::EQUAL)
		{
			partialDividend = ZERO;
			quotient.insert(quotient.begin(), 1);
		}
		else if (comparison == COMPARISON::MAJOR)
		{
			high = partialDividend.size() > divisorLength ? partialDividend[divisorLength] : 0;
			digit = min(((DOUBLE_DIGIT)high * (DOUBLE_DIGIT)DEC::BASE + (DOUBLE_DIGIT)partialDividend[divisorLength - 1]) / divisor.back(), DEC::BASE - 1);
			for(;;)
			{
				product = Multiply(divisor, digit);
				if (Compare(partialDividend, product) != COMPARISON::MINOR)
					break;
				--digit;
			}
			partialDividend = Subtract(partialDividend, product);
			quotient.insert(quotient.begin(), digit);
		}
		else if(!quotient.empty())
			quotient.insert(quotient.begin(), 0);
	}
	remainder = Divide(partialDividend, factor);

	return quotient;
}
/********************************************************/
void NumericVector::ShiftLeft(VECTOR& value, size_t count)
/********************************************************/
{
	size_t wholeShift,
		digitShift;
	DIGIT factor = 1;
	DOUBLE_DIGIT carry = 0,
		digit;

	if (!count || IsNullOrZero(value))
		return;

	wholeShift = count / DEC::DIGIT_LENGTH;
	digitShift = count % DEC::DIGIT_LENGTH;
	if (wholeShift)
		value.insert(value.begin(), wholeShift, 0);
	if (digitShift)
	{
		for (size_t i = 0; i < digitShift; ++i)
			factor *= 10;
		for (size_t i = 0; i < value.size(); ++i)
		{
			digit = DOUBLE_DIGIT(value[i]) * factor + carry;
			value[i] = DIGIT(digit % DEC::BASE);
			carry = digit / DEC::BASE;
		}
		if (carry)
			value.push_back(DIGIT(carry));
	}
}

/***********************************************************/
VECTOR NumericVector::ShiftRight(VECTOR& value, size_t count)
/***********************************************************/
{
	VECTOR discarded;
	size_t wholeShift, 
		digitShift;
	DIGIT factor = 1;
	DOUBLE_DIGIT carry = 0,
		digit;

	if (!count || IsNullOrZero(value))
		return ZERO;

	wholeShift = count / DEC::DIGIT_LENGTH;
	digitShift = count % DEC::DIGIT_LENGTH;
	if (wholeShift >= value.size())
		return (discarded = value, ToZero(value), discarded);
	if (wholeShift)
	{
		discarded.assign(value.begin(), value.begin() + wholeShift);
		value.erase(value.begin(), value.begin() + wholeShift);
	}
	if (digitShift)
	{
		for (size_t i = 0; i < digitShift; ++i)
			factor *= 10;
		for (size_t i = value.size(); i > 0;)
		{
			digit = carry * DEC::BASE + value[--i];
			value[i] = DIGIT(digit / factor);
			carry = digit % factor;
		}
		if (carry)
			discarded.push_back(DIGIT(carry));
	}
	Normalize(value);
	if (discarded.empty())
		ToZero(discarded);
	else
		Normalize(discarded);

	return discarded;
}
/*******************************************************/
VECTOR NumericVector::Power(VECTOR base, size_t exponent)
/*******************************************************/
{
	VECTOR potency;
	bool isBaseZero = IsZero(base);

	if (!base.empty() && (exponent || !isBaseZero))
	{
		if (!exponent)
			return ONE;
		if (exponent == 1 || isBaseZero || IsOne(base))
			return base;
		potency = ONE;
		for (;;)
		{
			if (exponent & 0x1)
			{
				potency = Multiply(potency, base);
				if (exponent == 1)
					break;
			}
			base = Multiply(base, base);
			exponent >>= 1;
		}
	}

	return potency;
}
/********************************************************************************************************/
void NumericVector::CalculateDigit(const VECTOR& radicand, size_t degree, VECTOR& root, VECTOR& remainder)
/********************************************************************************************************/
{
	VECTOR potency;
	DIGIT minimum = 0,
		maximum = DEC::BASE,
		digit;
	COMPARISON comparison;

	root.insert(root.begin(), DEC::BASE - 1);
	if (Compare(Power(root,degree), radicand) == COMPARISON::MINOR)
		ToZero(remainder);
	else
	{
		root.front() = 0;
		do
		{
			digit = DIGIT((DOUBLE_DIGIT(minimum) + maximum) >> 1);
			root.front() = digit;
			potency = Power(root, degree);
			comparison = Compare(potency, radicand);
			if (comparison == COMPARISON::MINOR)
				minimum = digit + 1;
			else if (comparison == COMPARISON::EQUAL)
			{
				maximum = digit;
				break;
			}
			else
				maximum = digit - 1;
		} while (minimum <= maximum);
		if (digit != maximum)
		{
			root.front() = maximum;
			potency = Power(root, degree);
		}
		remainder = Subtract(radicand, potency);
	}
}
/**********************************************************************************/
VECTOR NumericVector::Root(const VECTOR& radicand, size_t degree, VECTOR& remainder)
/**********************************************************************************/
{
	VECTOR root,
		potency,
		partialRadicand;
	size_t length = radicand.size(),
		lengthGroup;

	if (length && degree > 0)
	{
		if (degree == 1 || IsZero(radicand) || IsOne(radicand))
			return (ToZero(remainder), radicand);
		if (!(lengthGroup = length % degree))
			lengthGroup = degree;
		for (size_t i = length; i > 0;)
		{
			i -= lengthGroup;
			partialRadicand.insert(partialRadicand.begin(), radicand.begin() + i, radicand.begin() + i + lengthGroup);
			lengthGroup = degree;
			CalculateDigit(partialRadicand, degree, root, remainder);
		}
	}

	return root;
}
/*********************************************************************/
VECTOR NumericVector::CalculateGCD(VECTOR leftValue, VECTOR rightValue)
/*********************************************************************/
{
	VECTOR quotient,
		remainder;
	while (quotient = Divide(leftValue, rightValue, remainder), !IsZero(remainder))
	{
		leftValue = rightValue;
		rightValue = remainder;
	}

	return rightValue;
}
/**************************************************************************/
VECTOR NumericVector::GCD(const VECTOR& leftValue, const VECTOR& rightValue)
/**************************************************************************/
{
	COMPARISON comparison;

	if (leftValue.size() && rightValue.size())
	{
		if (IsZero(leftValue))
			return rightValue;
		if (IsZero(rightValue) || (comparison = Compare(leftValue, rightValue)) == COMPARISON::EQUAL)
			return leftValue;
		if (comparison == COMPARISON::MINOR)
			return CalculateGCD(rightValue, leftValue);
		return CalculateGCD(leftValue, rightValue);
	}
	return NULL;
}
/**************************************************************************/
VECTOR NumericVector::LCM(const VECTOR& leftValue, const VECTOR& rightValue)
/**************************************************************************/
{
	VECTOR result,
		remainder,
		gcd;

	if (leftValue.size() && rightValue.size())
	{
		if (IsZero(leftValue) || IsZero(rightValue))
			return ZERO;
		if (Compare(leftValue, rightValue) == COMPARISON::MINOR)
			gcd = CalculateGCD(rightValue, leftValue);
		else
			gcd = CalculateGCD(leftValue, rightValue);
		return Divide((Multiply(leftValue, rightValue)), gcd, remainder);
	}

	return NULL;
}
/*******************************************/
VECTOR NumericVector::Factorial(VECTOR value)
/*******************************************/
{
	VECTOR result;

	if (value.size())
	{
		result = ONE;
		if (!IsZero(value))
			while (!IsOne(value)) {
				result = Multiply(result, value);
				Decrement(value);
			}
		return result;
	}

	return NULL;
}

/***********/
/*** EOF ***/
/***********/
/******************************************************************************/
/*** File-Name: BcdNatural.cpp	                                            ***/
/*** Author...: João da Rocha Labrego                                       ***/
/*** E-Mail...: joaolabrego@gmail.com                                       ***/
/*** Purpose..: BcdNatural implementation.                                  ***/
/******************************************************************************/

#include "BcdNatural.h"

/********************************************************/
COMPARISON BcdNatural::Compare(DIGIT rightComparand) const
/********************************************************/
{
	size_t length = size();
	DIGIT value;

	if (!length)
		return COMPARISON::MINOR;
	if (length > 1)
		return COMPARISON::MAJOR;
	value = front();
	if (value < rightComparand)
		return COMPARISON::MINOR;
	if (value > rightComparand)
		return COMPARISON::MAJOR;

	return COMPARISON::EQUAL;
}
/********************************************************************/
COMPARISON BcdNatural::Compare(const BcdNatural& rightComparand) const
/********************************************************************/
{
	BcdNatural leftComparand = *this;
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
/*****************************************************/
BcdNatural& BcdNatural::operator =(const string& value)
/*****************************************************/
{
	char signal;
	string wholePart,
		decimalPart;

	ToNull();
	if (NumericString::Parse(value, signal, wholePart, decimalPart))
	{
		wholePart = General::PadLeft(wholePart);
		for (size_t i = wholePart.size(); i;)
			data.push_back(stoul(wholePart.substr(i -= DEC::DIGIT_LENGTH, DEC::DIGIT_LENGTH)));
		if (decimalPart.size() && decimalPart.front() >= '5') // to round.
			++*this;
	}

	return *this;
}
/***************************************************/
string BcdNatural::ToString(const bool grouped) const
/***************************************************/
{
	string result;

	if (IsNull())
		return UNDEFINED;
	if (IsZero())
		return "0";
	for (size_t i = size(); i;)
		result.append(PadLeft(to_string(at(--i))));
	result = General::LeftTrim(result);
	if (grouped)
		return General::Agroup(result);

	return result;
}
/*************************************************/
BcdNatural& BcdNatural::ToValue(DIGIT value)
/*************************************************/
{
	ToNull();
	do
		data.push_back(value % DEC::BASE);
	while (value /= DEC::BASE);

	return *this;
}
/**************************************************/
BcdNatural BcdNatural::Add(const BcdNatural& addend)
/**************************************************/
{
	VECTOR sum;
	size_t leftLength = data.size(),
		rightLength = addend.data.size(),
		i;
	DIGIT carry = 0;

	sum.resize(leftLength, 0);
	for (i = 0; i < rightLength; ++i)
	{
		carry += (data.at(i) + addend.data.at(i));
		sum.at(i) = carry % DEC::BASE;
		carry /= DEC::BASE;
	}
	for (; i < leftLength; ++i)
	{
		carry += data.at(i);
		sum.at(i) = carry % DEC::BASE;
		carry /= DEC::BASE;
	}
	if (carry)
		sum.push_back(carry);

	return sum;
}
/***************************************************************/
BcdNatural BcdNatural::operator +(const BcdNatural& addend) const
/***************************************************************/
{
	BcdNatural sum;
	size_t leftLength = data.size(),
		rightLength = addend.data.size();

	if (leftLength && rightLength)
	{
		if (IsZero())
			return addend;
		if (addend.IsZero())
			return *this;
		if (leftLength < rightLength)
			return BcdNatural(addend.Add(data).data);
		sum = BcdNatural(Add(addend.data).data);
	}

	return sum;
}
/***********************************/
BcdNatural& BcdNatural::operator ++()
/***********************************/
{
	size_t length = data.size(),
		i;

	if (length)
	{
		for (i = 0; i < length && data.at(i) == DEC::MAXIMUM_VALUE; ++i)
			data.at(i) = 0;
		if (i == length)
			data.push_back(1);
		else
			++data.at(i);
	}

	return *this;
}
/*******************************************************************/
BcdNatural BcdNatural::operator -(const BcdNatural& subtrahend) const
/*******************************************************************/
{
	BcdNatural difference;
	size_t leftLength = data.size(),
		rightLength = subtrahend.data.size(),
		i;
	DIGIT borrow;
	COMPARISON comparison;

	if (leftLength && rightLength && (comparison = Compare(subtrahend)) != COMPARISON::MINOR)
	{
		if (comparison == COMPARISON::EQUAL)
			return difference.ToZero();
		if (subtrahend.IsZero())
			return *this;
		borrow = 0;
		difference.data.resize(leftLength, 0);
		for (i = 0; i < rightLength; ++i)
		{
			borrow = DEC::BASE + data.at(i) - subtrahend.data.at(i) - borrow;
			difference.data.at(i) = borrow % DEC::BASE;
			borrow = borrow < DEC::BASE;
		}
		for (; i < leftLength; ++i)
		{
			borrow = DEC::BASE + data.at(i) - borrow;
			difference.data.at(i) = borrow % DEC::BASE;
			borrow = borrow < DEC::BASE;
		}
		General::Normalize(difference.data);
	}

	return difference;
}
/***********************************/
BcdNatural& BcdNatural::operator --()
/***********************************/
{
	size_t length = data.size(),
		i;

	if (length)
	{
		if (IsZero())
			ToNull();
		else
		{
			for (i = 0; i < length && !data.at(i); ++i)
				data.at(i) = DEC::MAXIMUM_VALUE;
			General::Normalize(data);
		}
	}

	return *this;
}
/**************************************************************/
BcdNatural BcdNatural::operator *(DIGIT multiplier) const
/**************************************************************/
{
	size_t length = data.size();
	BcdNatural product;
	DIGIT carry;

	if (length && multiplier <= BIN::BASE)
	{
		if (IsZero() || !multiplier)
			return product.ToZero();
		if (IsOne())
			return BcdNatural(multiplier);
		if (multiplier == 1)
			return *this;
		carry = 0;
		product.data.resize(length, 0);
		for (size_t i = 0; i < length; ++i)
		{
			carry += data.at(i) * multiplier;
			product.data.at(i) = DIGIT(carry % DEC::BASE);
			carry /= DEC::BASE;
		}
		if (carry)
			product.data.push_back(DIGIT(carry));
	}

	return product;
}
/*******************************************************************/
BcdNatural BcdNatural::operator *(const BcdNatural& multiplier) const
/*******************************************************************/
{
	size_t leftLength = data.size(),
		rightLength = multiplier.data.size();
	BcdNatural product;
	DIGIT carry;

	if (leftLength && rightLength)
	{
		if (IsZero() || multiplier.IsZero())
			return product.ToZero();
		if (IsOne())
			return multiplier;
		if (multiplier.IsOne())
			return *this;
		carry = 0;
		product.data.resize(leftLength + rightLength, 0);
		for (size_t i = 0, k; i < leftLength; ++i)
		{
			k = i;
			carry = 0;
			for (size_t j = 0; j < rightLength; ++j)
			{
				carry = DIGIT(data.at(i)) * multiplier.data.at(j) + product.data.at(k) + carry;
				product.data.at(k++) = carry % DEC::BASE;
				carry /= DEC::BASE;
			}
			while (carry)
			{
				carry += product.data.at(k);
				product.data.at(k++) = carry % DEC::BASE;
				carry /= DEC::BASE;
			}
		}
		General::Normalize(product.data);
	}

	return product;
}

/*******************************************************************************/
BcdNatural BcdNatural::Divide(const DIGIT divisor, DIGIT& remainder) const
/*******************************************************************************/
{
	size_t length = data.size();
	DIGIT partialDividend;
	BcdNatural quotient,
		comparand;
	COMPARISON comparison;

	if (length && divisor && divisor <= BIN::BASE)
	{
		if (IsZero() || divisor == 1)
			return (remainder = 0, *this);
		if ((comparison = Compare(divisor)) == COMPARISON::MINOR)
			return (remainder = data.front(), quotient.ToZero());
		if (comparison == COMPARISON::EQUAL)
			return (remainder = 0, quotient.ToOne());
		partialDividend = 0;
		for (size_t i = length; i;)
		{
			partialDividend = partialDividend * DEC::BASE + data.at(--i);
			if (partialDividend < divisor)
			{
				if (!quotient.IsNull())
					quotient.data.insert(quotient.data.begin(), 0);
				remainder = DIGIT(partialDividend);
			}
			else
			{
				quotient.data.insert(quotient.data.begin(), DIGIT(partialDividend / divisor));
				remainder = DIGIT(partialDividend %= divisor);
			}
		}
		General::Normalize(quotient.data);
	}

	return quotient;
}
/*****************************************************************************************/
DIGIT BcdNatural::BinarySearchDigit(const BcdNatural& divisor, BcdNatural& remainder) const
/*****************************************************************************************/
{
	COMPARISON comparison;
	BcdNatural product;
	DIGIT digit,
		minimumDigit = 0,
		maximumDigit = DEC::MAXIMUM_VALUE;

	do
	{
		digit = (minimumDigit + maximumDigit) >> 0x1;
		product = divisor * digit;
		comparison = product.Compare(*this);
		if (comparison == COMPARISON::MINOR)
			minimumDigit = digit + 1;
		else if (comparison == COMPARISON::EQUAL)
		{
			maximumDigit = digit;
			break;
		}
		else
			maximumDigit = digit - 1;
	} while (minimumDigit <= maximumDigit);
	if (digit != maximumDigit)
	{
		digit = maximumDigit;
		product = divisor * digit;
	}
	remainder = *this - product;

	return digit;
}
///***********************************************************************************/
//BcdNatural BcdNatural::Divide(const BcdNatural& divisor, BcdNatural& remainder) const
///***********************************************************************************/
//{
//	size_t length = data.size();
//	BcdNatural partialDividend,
//		quotient;
//	COMPARISON comparison;
//
//	if (length && divisor.data.size() && !divisor.IsZero())
//	{
//		if (IsZero() || divisor.IsOne())
//			return (remainder.ToZero(), *this);
//		if ((comparison = Compare(divisor)) == COMPARISON::MINOR)
//			return (remainder = *this, quotient.ToZero());
//		if (comparison == COMPARISON::EQUAL)
//			return (remainder.ToZero(), quotient.ToOne());
//		for (size_t i = length; i;)
//		{
//			partialDividend.data.insert(partialDividend.data.begin(), data.at(--i));
//			comparison = partialDividend.Compare(divisor);
//			if (comparison == COMPARISON::MINOR)
//			{
//				if (quotient.data.size())
//					quotient.data.insert(quotient.data.begin(), 0);
//				remainder = partialDividend;
//			}
//			else if (comparison == COMPARISON::EQUAL)
//			{
//				partialDividend.ToNull();
//				quotient.data.insert(quotient.data.begin(), 1);
//				remainder.ToZero();
//			}
//			else
//			{
//				quotient.data.insert(quotient.data.begin(), partialDividend.BinarySearchDigit(divisor, remainder));
//				partialDividend = remainder;
//			}
//		}
//		General::Normalize(quotient.data);
//	}
//
//	return quotient;
//}

/***********************************************************************************/
BcdNatural BcdNatural::Divide(const BcdNatural& divisor, BcdNatural& remainder) const
/***********************************************************************************/
{
	BcdNatural quotient;
	const size_t dividendLength = data.size();
	size_t divisorLength = divisor.data.size();

	if (!dividendLength || !divisorLength || divisor.IsZero())
		return quotient;

	if (IsZero())
	{
		remainder.ToZero();
		return *this;
	}

	COMPARISON comparison = Compare(divisor);

	if (comparison == COMPARISON::MINOR)
	{
		remainder = *this;
		return quotient.ToZero();
	}

	if (comparison == COMPARISON::EQUAL)
	{
		remainder.ToZero();
		return quotient.ToOne();
	}

	const DIGIT base = DEC::BASE;

	// Divisão por um único dígito BCD.
	if (divisorLength == 1)
	{
		const DIGIT singleDivisor = divisor.data[0];
		DIGIT carry = 0;

		quotient.data.resize(dividendLength, 0);

		for (size_t i = dividendLength; i > 0;)
		{
			--i;
			const DIGIT partial =
				carry * base + DIGIT(data[i]);

			quotient.data[i] = DIGIT(partial / singleDivisor);
			carry = partial % singleDivisor;
		}

		General::Normalize(quotient.data);
		remainder = BcdNatural(carry);
		return quotient;
	}

	/*
	 * Normaliza o divisor para que seu dígito mais significativo
	 * fique próximo da metade da base.
	 */
	const DIGIT factor = DIGIT(
		base / (DIGIT(divisor.data[divisorLength - 1]) + 1)
	);

	VECTOR normalizedDivisor(divisorLength, 0);
	VECTOR normalizedDividend(dividendLength + 1, 0);

	DIGIT carry = 0;
	for (size_t i = 0; i < divisorLength; ++i)
	{
		const DIGIT current =
			DIGIT(divisor.data[i]) * factor + carry;

		normalizedDivisor[i] = DIGIT(current % base);
		carry = current / base;
	}
	// O fator foi escolhido para que não haja carry além do divisor.

	carry = 0;
	for (size_t i = 0; i < dividendLength; ++i)
	{
		const DIGIT current =
			DIGIT(data[i]) * factor + carry;

		normalizedDividend[i] = DIGIT(current % base);
		carry = current / base;
	}
	normalizedDividend[dividendLength] = DIGIT(carry);

	quotient.data.resize(dividendLength - divisorLength + 1, 0);

	// Produz os dígitos do quociente, do mais significativo para o menos.
	for (size_t j = dividendLength - divisorLength + 1; j > 0;)
	{
		--j;

		const DIGIT numerator =
			DIGIT(normalizedDividend[j + divisorLength]) * base
			+ normalizedDividend[j + divisorLength - 1];

		DIGIT quotientDigit =
			numerator / normalizedDivisor[divisorLength - 1];

		DIGIT estimateRemainder =
			numerator % normalizedDivisor[divisorLength - 1];

		// Corrige uma estimativa excessiva usando o segundo dígito do divisor.
		while (
			quotientDigit >= base ||
			quotientDigit * normalizedDivisor[divisorLength - 2] >
			estimateRemainder * base
			+ normalizedDividend[j + divisorLength - 2]
			)
		{
			--quotientDigit;
			estimateRemainder += normalizedDivisor[divisorLength - 1];

			if (estimateRemainder >= base)
				break;
		}

		// Multiplica o divisor pelo dígito estimado e subtrai.
		carry = 0;
		for (size_t i = 0; i < divisorLength; ++i)
		{
			const DIGIT product =
				quotientDigit * normalizedDivisor[i] + carry;

			const DIGIT lowDigit = DIGIT(product % base);
			carry = product / base;

			if (normalizedDividend[j + i] < lowDigit)
			{
				normalizedDividend[j + i] = DIGIT(
					DIGIT(normalizedDividend[j + i])
					+ base - lowDigit
				);
				++carry;
			}
			else
			{
				normalizedDividend[j + i] -= lowDigit;
			}
		}

		const bool borrowed =
			DIGIT(normalizedDividend[j + divisorLength]) < carry;

		if (borrowed)
		{
			normalizedDividend[j + divisorLength] = DIGIT(
				DIGIT(normalizedDividend[j + divisorLength])
				+ base - carry
			);
		}
		else
		{
			normalizedDividend[j + divisorLength] =
				DIGIT(DIGIT(normalizedDividend[j + divisorLength]) - carry);
		}

		// Se a estimativa foi uma unidade alta, soma o divisor de volta.
		if (borrowed)
		{
			--quotientDigit;
			carry = 0;

			for (size_t i = 0; i < divisorLength; ++i)
			{
				const DIGIT sum =
					DIGIT(normalizedDividend[j + i])
					+ normalizedDivisor[i]
					+ carry;

				normalizedDividend[j + i] = DIGIT(sum % base);
				carry = sum / base;
			}

			normalizedDividend[j + divisorLength] = DIGIT(
				(DIGIT(normalizedDividend[j + divisorLength]) + carry) % base
			);
		}

		quotient.data[j] = DIGIT(quotientDigit);
	}

	General::Normalize(quotient.data);

	// Copia os n dígitos do resto normalizado.
	remainder.data.resize(divisorLength);
	for (size_t i = 0; i < divisorLength; ++i)
		remainder.data[i] = normalizedDividend[i];

	// Desnormaliza o resto dividindo-o pelo fator usado no início.
	carry = 0;
	for (size_t i = divisorLength; i > 0;)
	{
		--i;

		const DIGIT current =
			carry * base + remainder.data[i];

		remainder.data[i] = DIGIT(current / factor);
		carry = current % factor;
	}

	General::Normalize(remainder.data);
	return quotient;
}
/*******************************************************/
BcdNatural BcdNatural::Power(DIGIT exponent) const
/*******************************************************/
{
	BcdNatural base = *this,
		potency;

	if (base.data.size() && (exponent || !base.IsZero()))
	{
		if (!exponent)
			return potency.ToOne();
		if (exponent == 1 || base.IsZero() || base.IsOne())
			return base;
		potency.ToOne();
		for (;;)
		{
			if (exponent & 0x1)
			{
				potency *= base;
				if (exponent == 1)
					break;
			}
			base *= base;
			exponent >>= 1;
		}
	}

	return potency;
}
/****************************************************************************************************/
void BcdNatural::BinarySearchDigit(DIGIT degree, BcdNatural& root, BcdNatural& remainder) const
/****************************************************************************************************/
{
	BcdNatural potency;
	DIGIT minimum = 0,
		maximum = DEC::BASE,
		digit;
	COMPARISON comparison;

	root.data.insert(root.data.begin(), DEC::BASE - 1);
	if (root.Power(degree) < *this)
		remainder.ToZero();
	else
	{
		root.data.front() = 0;
		do
		{
			digit = DIGIT((DIGIT(minimum) + maximum) >> 1);
			root.data.front() = digit;
			potency = root.Power(degree);
			comparison = potency.Compare(*this);
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
			root.data.front() = maximum;
			potency = root.Power(degree);
		}
		remainder = *this - potency;
	}
}
/***************************************************************************/
BcdNatural BcdNatural::Root(DIGIT degree, BcdNatural& remainder) const
/***************************************************************************/
{
	BcdNatural root,
		potency,
		partialRadicand;
	size_t length = data.size(),
		lengthGroup;

	if (degree > 0 && data.size())
	{
		if (degree == 1 || IsZero() || IsOne())
			return (remainder.ToZero(), *this);
		if (!(lengthGroup = length % degree))
			lengthGroup = degree;
		for (size_t i = length; i > 0;)
		{
			i -= lengthGroup;
			partialRadicand.data.insert(partialRadicand.data.begin(), data.begin() + i, data.begin() + i + lengthGroup);
			lengthGroup = degree;
			partialRadicand.BinarySearchDigit(degree, root, remainder);
		}
	}

	return root;
}
/******************************************************************************/
BcdNatural BcdNatural::CalculateGCD(BcdNatural leftValue, BcdNatural rightValue)
/******************************************************************************/
{
	BcdNatural quotient,
		remainder;
	while (quotient = leftValue.Divide(rightValue, remainder), !remainder.IsZero())
	{
		leftValue = rightValue;
		rightValue = remainder;
	}

	return rightValue;
}
/************************************************************/
BcdNatural BcdNatural::GCD(const BcdNatural& rightValue) const
/************************************************************/
{
	BcdNatural result;
	COMPARISON comparison;

	if (data.size() && rightValue.data.size())
	{
		if (IsZero())
			return rightValue;
		if (rightValue.IsZero() || (comparison = Compare(rightValue)) == COMPARISON::EQUAL)
			return *this;
		if (comparison == COMPARISON::MINOR)
			result = CalculateGCD(rightValue, *this);
		else
			result = CalculateGCD(*this, rightValue);
	}

	return result;
}
/************************************************************/
BcdNatural BcdNatural::LCM(const BcdNatural& rightValue) const
/************************************************************/
{
	BcdNatural result,
		remainder,
		gcd;

	if (data.size() && rightValue.data.size())
	{
		if (IsZero() || rightValue.IsZero())
			return result.ToZero();
		if (Compare(rightValue) == COMPARISON::MINOR)
			gcd = CalculateGCD(rightValue, *this);
		else
			gcd = CalculateGCD(*this, rightValue);
		result = (*this * rightValue).Divide(gcd, remainder);
	}

	return result;
}
/**************************************/
BcdNatural BcdNatural::Factorial() const
/**************************************/
{
	BcdNatural value = *this,
		result;

	if (value.data.size())
	{
		result.ToOne();
		if (!value.IsZero())
			while (!value.IsOne())
				result *= value--;
	}

	return result;
}
/***********/
/*** EOF ***/
/***********/
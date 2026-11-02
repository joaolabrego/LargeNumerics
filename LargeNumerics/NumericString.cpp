/******************************************************************************/
/*** File-Name: NumericString.cpp	                                        ***/
/*** Author...: João da Rocha Labrego                                       ***/
/*** E-Mail...: joaolabrego@gmail.com                                       ***/
/*** Purpose..: NumericString implementation.                               ***/
/******************************************************************************/

#include "NumericString.h"

/*************************************************************************************/
string NumericString::PadLeft(const string& value, size_t length, const string& filler)
/*************************************************************************************/
{
	size_t missingZeroes = length - value.size() % length;

	if (missingZeroes < length)
		return Replicate(filler, missingZeroes).append(value);

	return value;
}
/**************************************************************************************/
string NumericString::PadRight(const string& value, size_t length, const string& filler)
/**************************************************************************************/
{
	size_t missingZeroes = length - value.size() % length;
	if (missingZeroes < length)
		return Replicate(filler, missingZeroes).insert(0, value);

	return value;
}
/*************************************************/
string NumericString::LeftTrim(const string& value)
/*************************************************/
{
	size_t length = value.size(),
		i;

	for (i = 0; i < length && value.at(i) == '0'; i++);
	if (i == length)
		return "0";
	else if (i)
		return value.substr(i);

	return value;
}
/**************************************************/
string NumericString::RightTrim(const string& value)
/**************************************************/
{
	size_t length = value.size(),
		i;

	for (i = length; i && value.at(i - 1) == '0'; i--);
	if (!i)
		return "";
	else if (i < length)
		return value.substr(0, i);

	return value;
}
/***********************************************/
string NumericString::Agroup(const string& value)
/***********************************************/
{
	string result;
	size_t i = value.size();

	while (i > Config->THOUSANDS_LENGTH)
		result.insert(0, string(1, Config->THOUSANDS_SEPARATOR).append(value.substr(i -= Config->THOUSANDS_LENGTH, Config->THOUSANDS_LENGTH)));

	return result.insert(0, value.substr(0, i));
}
/************************************************************************************************/
string NumericString::Replace(const string& value, const string& oldValue, const string& newValue)
/************************************************************************************************/
{
	size_t length = value.size(),
		oldLength = oldValue.size();
	string result;

	if (length && oldLength && oldLength <= length)
	{
		for (size_t i = 0; i < length;)
		{
			if (value.substr(i, oldLength) == oldValue)
			{
				result.append(newValue);
				i += oldLength;
			}
			else
				result.push_back(value.at(i++));
		}
	}
	else
		result = value;

	return result;
}
/**********************************************************************/
string NumericString::Replicate(const string& value, const size_t count)
/**********************************************************************/
{
	size_t lengthvalue = value.size(),
		limit;
	string result;

	if (lengthvalue && count)
	{
		limit = count / lengthvalue;
		for (size_t i = 0; i < limit; ++i) result.append(value);
		result.append(value.substr(0, count % lengthvalue));
	}

	return result;
}
/************************************************/
bool NumericString::IsNumeric(const string& value)
/************************************************/
{
	size_t length = value.size(),
		i;

	for (i = 0; i < length && isdigit(value.at(i)); ++i);

	return i == length;
}
/******************************************/
void NumericString::Decrement(string& value)
/******************************************/
{
	size_t i;

	for (i = value.size(); i && value.at(i - 1) == '0'; i--)
		value.at(i - 1) = '9';
	--value.at(i - 1);
}
/*************************************************************************************************************************************
The complete format of a numeric string is "-999,999,999,999...".
The '-' character can also be '+' and, if it is '+', it is optional.
The character ',' is optional and separates thousands.
The character '.' it is also optional and separates the decimal places.
Finally, the 3 consecutive points, also optional, inform that the expression represents a periodic tithe.
For the expression to be considered a periodic tithe, it is necessary to repeat at least 3 times its period, followed by the ellipsis.
*************************************************************************************************************************************/
/*******************************************************************************************/
bool NumericString::Parse(string value, char& signal, string& wholePart, string& decimalPart)
/*******************************************************************************************/
{
	size_t decimalPosition,
		lengthDecimals,
		precision;
	bool ellipsed;
	string repetend;

	if (value.empty())
		return false;
	signal = value.front();
	if (Config->IsSignal(signal))
		value.erase(0, 1);
	else if (isdigit(signal))
		signal = char(SIGNAL::POSITIVE);
	else
		return false;
	decimalPosition = value.find(Config->DECIMAL_SEPARATOR);
	if (decimalPosition == string::npos)
	{
		wholePart = LeftTrim(Replace(value, string(1, Config->THOUSANDS_SEPARATOR), ""));
		decimalPart.clear();
	}
	else if (decimalPosition && decimalPosition < value.size() - 1)
	{
		wholePart = LeftTrim(Replace(value.substr(0, decimalPosition), string(1, Config->THOUSANDS_SEPARATOR), ""));
		lengthDecimals = (decimalPart = Replace(RightTrim(value.substr(decimalPosition + 1)), ELLIPSIS, "#")).size();
		if ((ellipsed = decimalPart.back() == '#'))
		{
			decimalPart.pop_back();
			--lengthDecimals;
		}
		if (!IsNumeric(decimalPart))
			return false;
		precision = Config->GetPrecision() * DEC::DIGIT_LENGTH;
		if (ellipsed || lengthDecimals > DECIMAL_PLACES * DEC::DIGIT_LENGTH)
		{
			if ((repetend = Repetend(decimalPart)).empty())
			{
				if (lengthDecimals < precision)
				{
					Decrement(decimalPart);
					decimalPart = PadRight(decimalPart, precision, "9");
				}
			}
			else
				decimalPart = PadRight(decimalPart, precision, repetend);
		}
		else if (lengthDecimals < precision)
			decimalPart = PadRight(decimalPart, DEC::DIGIT_LENGTH, "0");
		decimalPart = decimalPart.substr(0, precision);
	}
	else
		return false;

	return IsNumeric(wholePart);
}
/************************************************************************/
size_t NumericString::CountDigits(const string& value, const string digit)
/************************************************************************/
{
	size_t lengthDigit = digit.size(),
		counter = 0;

	for (size_t i = value.size(); i >= lengthDigit && value.substr(i - lengthDigit, lengthDigit) == digit; i -= lengthDigit)
		++counter;
	return counter;
}
/*************************************************/
string NumericString::Repetend(const string& value)
/*************************************************/
{
	string digit,
		result;
	size_t lastcounter = 0,
		counter,
		length = value.size();

	if (length)
	{
		for (size_t i = length - 1; i > 0; i--)
		{
			counter = CountDigits(value, digit = value.substr(i, length - i));
			if (counter >= Config->THOUSANDS_LENGTH && counter >= lastcounter)
			{
				lastcounter = counter;
				result = digit;
			}
		}
	}
	return result;
}
/*********************************************************************/
VECTOR NumericString::Repetend(const string& value, const size_t times)
/*********************************************************************/
{
	string repetend = Repetend(value);
	VECTOR result;

	if (repetend.empty())
		return VECTOR(Config->GetPrecision() * times, 0);
	repetend = NumericString::PadRight(repetend, Config->GetPrecision() * DEC::DIGIT_LENGTH * times, repetend);
	for (size_t i = repetend.size(); i;)
		result.push_back(stoul(repetend.substr(i -= DEC::DIGIT_LENGTH, DEC::DIGIT_LENGTH)));

	return result;
}
/*****************************************************/
DIGIT NumericString::StringToDigit(const string& value)
/*****************************************************/
{
	DIGIT result = 0;
	DIGIT maximum,
		digit;

	if (!IsNumeric(value))
		return 0;
	maximum = (std::numeric_limits<DIGIT>::max)();
	for (char character : value)
	{
		digit = DIGIT(character - '0');
		if (result > (maximum - digit) / 10)
			throw out_of_range("Valor excede o limite de DIGIT");

		result = result * 10 + digit;
	}

	return result;
}
/***********/
/*** EOF ***/
/***********/
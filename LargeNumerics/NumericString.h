/******************************************************************************/
/*** File-Name: NumericString.h                                             ***/
/*** Author...: João da Rocha Labrego                                       ***/
/*** E-Mail...: joaolabrego@gmail.com                                       ***/
/*** Purpose..: NumericString header.                                       ***/
/******************************************************************************/

#ifndef NumericString_H
#define NumericString_H

#include "Config.h"

struct NumericString: private string
{
public:
	static string PadLeft(const string& value, size_t length = DEC::DIGIT_LENGTH, const string& filler = "0");
	static string PadRight(const string& value, size_t length = DEC::DIGIT_LENGTH, const string& filler = "0");
	static string LeftTrim(const string& value);
	static string RightTrim(const string& value);
	static string Agroup(const string& value);
	static string Replace(const string& value, const string& oldValue, const string& newValue);
	static string Replicate(const string& value, const size_t count);
	static string Repetend(const string& value);
	static VECTOR Repetend(const string& value, const size_t times);
	static size_t CountDigits(const string& value, const string digit);
	static void Decrement(string& value);
	static bool IsNumeric(const string& value);
	static bool Parse(string value, char& signal, string& wholePart, string& decimalPart);
	static DIGIT StringToDigit(const string& value);
};

#endif // NumericString_H
/***********/
/*** EOF ***/
/***********/
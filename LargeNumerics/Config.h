/******************************************************************************/
/*** File-Name: Config.h                                                    ***/
/*** Author...: João da Rocha Labrego                                       ***/
/*** E-Mail...: joaolabrego@gmail.com                                       ***/
/*** Purpose..: Config header.                                              ***/
/******************************************************************************/

#ifndef Config_H
#define Config_H

#include <windows.h>
#include <vector>
#include <string>
#include <locale>
#include <math.h>
#include <cstring>
#undef NULL

using namespace std;

// Changeable definitions.
static const size_t DECIMAL_PLACES = 6; // Change with even values ​​greater than zero.
static const string UNDEFINED = "NULL";
static const string ELLIPSIS = "...";
static const locale LOCALE = locale("");

// Unchangeable definitions.
typedef INT32 SIGNED_DIGIT; // Change the type to INT64 if type INT128 is available.
typedef UINT32 DIGIT; // Change the type to UINT64 if type UINT128 is available.
typedef INT64 SIGNED_DOUBLE_DIGIT; // Change the type to INT128 if type INT128 is available.
typedef UINT64 DOUBLE_DIGIT; // Change the type to UINT128 if type UINT128 is available.
typedef vector<DIGIT> VECTOR;

namespace BIN
{
	static const DIGIT RADIX = 2;
	static const size_t DIGIT_LENGTH = sizeof(DIGIT) * CHAR_BIT;
	static const DIGIT BASE = DIGIT(pow(RADIX, DIGIT_LENGTH));
	static const DIGIT MAXIMUM_VALUE = DIGIT(BASE - 1);
}
namespace DEC
{
	static const DIGIT RADIX = 10;
	static const size_t DIGIT_LENGTH = size_t(log10(double(BIN::BASE / 2)));
	static const DIGIT BASE = DIGIT(pow(RADIX, double(DIGIT_LENGTH)));
	static const DIGIT MAXIMUM_VALUE = DIGIT(BASE - 1);
}

static enum class COMPARISON : INT8 { MINOR = -1, EQUAL = 0, MAJOR = 1 };
static enum class SIGN : INT8 { NEGATIVE = -1, POSITIVE = 1 };
static enum class SIGNAL : char { NEGATIVE = '-', POSITIVE = '+' };

static enum class ANGLE_UNIT : char { DEGREE = 'D', GRADIAN = 'G', RADIAN = 'R' };
static enum class ANGLE_QUADRANT : UINT8 { FIRST = 0, SECOND = 1, THIRD = 2, FOURTH = 3 };
static enum class ANGLE_TYPE : UINT8 { ANGLE = 0, SIN = 1, COS = 2, TAN = 3, COT = 4, SEC = 5, CSC = 6, SINH = 7, COSH = 8, TANH = 9, COTH = 10, SECH = 11, CSCH = 12 };

static const char DECIMAL_SEPARATOR = DecimalSeparator().front();
static const char THOUSANDS_SEPARATOR = GroupingSeparator().front();
static const size_t THOUSANDS_LENGTH = GroupingLength();
static const bool SHOW_POSITIVE = ShowPositiveSignal();
static const bool SHOW_GROUPED = ShowGrouped();
static const char NEGATIVE_SIGNAL = NegativeSignal().front();
static const char POSITIVE_SIGNAL = PositiveSignal().front();

namespace
{
	/****************************/
	static string NegativeSignal()
	/****************************/
	{
		string result = std::use_facet<std::moneypunct<char>>(LOCALE).negative_sign();

		return result.empty() ? "-" : result;
	}
	/****************************/
	static string PositiveSignal()
	/****************************/
	{
		string result = std::use_facet<std::moneypunct<char>>(LOCALE).positive_sign();

		return result.empty() ? "+" : result;
	}
	/******************************/
	static string DecimalSeparator()
	/******************************/
	{
		string result = string(1, std::use_facet< std::numpunct<char> >(LOCALE).decimal_point());

		return result.empty() ? "," : result;
	}
	/*******************************/
	static string GroupingSeparator()
	/*******************************/
	{
		string result = string(1, std::use_facet<std::numpunct<char>>(LOCALE).thousands_sep());

		return result.empty() ? "." : result;
	}
	/****************************/
	static size_t GroupingLength()
	/****************************/
	{
		size_t result = std::use_facet<std::numpunct<char>>(LOCALE).grouping().front();

		return result;
	}
	/******************************/
	static bool ShowPositiveSignal()
	/******************************/
	{
		return std::use_facet<std::moneypunct<char>>(LOCALE).positive_sign().size();
	}
	/***********************/
	static bool ShowGrouped()
	/***********************/
	{
		return string(1, std::use_facet<std::numpunct<char>>(LOCALE).thousands_sep()).size();
	}
}
#endif // Config_H
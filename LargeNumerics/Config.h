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
	static DOUBLE_DIGIT BASE = DOUBLE_DIGIT(pow(RADIX, DIGIT_LENGTH));
	static DIGIT MAXIMUM_VALUE = DIGIT(BASE - 1);
};
namespace DEC
{
	static DIGIT RADIX = 10;
	static size_t DIGIT_LENGTH = size_t(log10(double(BIN::BASE / 2)));
	static DIGIT BASE = DIGIT(pow(RADIX, double(DIGIT_LENGTH)));
	static DIGIT MAXIMUM_VALUE = DIGIT(BASE - 1);
};

enum class COMPARISON : INT8 { MINOR = -1, EQUAL = 0, MAJOR = 1 };
enum class SIGN : INT8 { NEGATIVE = -1, POSITIVE = 1 };
enum class SIGNAL : char { NEGATIVE = '-', POSITIVE = '+' };

enum class ANGLE_UNIT : char { DEGREE = 'D', GRADIAN = 'G', RADIAN = 'R' };
enum class ANGLE_QUADRANT : UINT8 { FIRST = 1, SECOND = 2, THIRD = 3, FOURTH = 4 };
enum class ANGLE_TYPE : UINT8 { ANGLE = 0, SIN = 1, COS = 2, TAN = 3, COT = 4, SEC = 5, CSC = 6, SINH = 7, COSH = 8, TANH = 9, COTH = 10, SECH = 11, CSCH = 12 };

static size_t counterPrecision = 0;

class Configuration {
public:
	Configuration() {}
	~Configuration() {}
	static SIGN Sign(const char signal);
	static SIGN Sign(const SIGNAL signal);
	static SIGNAL Signal(const char signal);
	static SIGNAL Signal(const SIGN sign);
	static SIGN NotSign(const SIGN sign);
	static SIGNAL NotSignal(const SIGNAL signal);
	static bool IsSignal(const char signal);
	static COMPARISON NotComparison(const COMPARISON comparison);
	static size_t GetPrecision(bool ignoreExtra = false);
	static void UpPrecision();
	static void DownPrecision();

	const char DECIMAL_SEPARATOR = DecimalSeparator().front();
	const char THOUSANDS_SEPARATOR = GroupingSeparator().front();
	const size_t THOUSANDS_LENGTH = GroupingLength();
	const bool SHOW_POSITIVE = ShowPositiveSignal();
	const bool SHOW_GROUPED = ShowGrouped();
	const char NEGATIVE_SIGNAL = NegativeSignal().front();
	const char POSITIVE_SIGNAL = PositiveSignal().front();

private:
	static string NegativeSignal();
	static string PositiveSignal();
	static string DecimalSeparator();
	static string GroupingSeparator();
	static size_t GroupingLength();
	static bool ShowPositiveSignal();
	static bool ShowGrouped();
};

extern Configuration* Config;

/**************************************************/
template <class T> SIGN ToAbsolute(T& value)
/**************************************************/
{
	if (value < 0)
	{
		value = -value;
		return SIGN::NEGATIVE;
	}

	return SIGN::POSITIVE;
}



#endif // Config_H
/***********/
/*** EOF ***/
/***********/
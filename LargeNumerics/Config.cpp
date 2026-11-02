/******************************************************************************/
/*** File-Name: Config.cpp	                                                ***/
/*** Author...: João da Rocha Labrego                                       ***/
/*** E-Mail...: joaolabrego@gmail.com                                       ***/
/*** Purpose..: Config implementation.                                      ***/
/******************************************************************************/

#include "Config.h"

/****************************/
string Configuration::NegativeSignal()
/****************************/
{
	string result = std::use_facet<std::moneypunct<char>>(LOCALE).negative_sign();

	return result.empty() ? "-" : result;
}
/****************************/
string Configuration::PositiveSignal()
/****************************/
{
	string result = std::use_facet<std::moneypunct<char>>(LOCALE).positive_sign();

	return result.empty() ? "+" : result;
}
/******************************/
string Configuration::DecimalSeparator()
/******************************/
{
	string result = string(1, std::use_facet< std::numpunct<char> >(LOCALE).decimal_point());

	return result.empty() ? "," : result;
}
/*******************************/
string Configuration::GroupingSeparator()
/*******************************/
{
	string result = string(1, std::use_facet<std::numpunct<char>>(LOCALE).thousands_sep());

	return result.empty() ? "." : result;
}
/****************************/
size_t Configuration::GroupingLength()
/****************************/
{
	size_t result = std::use_facet<std::numpunct<char>>(LOCALE).grouping().front();

	return result;
}
/******************************/
bool Configuration::ShowPositiveSignal()
/******************************/
{
	return std::use_facet<std::moneypunct<char>>(LOCALE).positive_sign().size();
}
/***********************/
bool Configuration::ShowGrouped()
/***********************/
{
	return string(1, std::use_facet<std::numpunct<char>>(LOCALE).thousands_sep()).size();
}
/***********************************/
SIGN Configuration::Sign(const char signal)
/***********************************/
{
	return signal == char(SIGNAL::NEGATIVE) ? SIGN::NEGATIVE : SIGN::POSITIVE;
}
/*************************************/
SIGN Configuration::Sign(const SIGNAL signal)
/*************************************/
{
	return signal == SIGNAL::NEGATIVE ? SIGN::NEGATIVE : SIGN::POSITIVE;
}
/***************************************/
SIGNAL Configuration::Signal(const char signal)
/***************************************/
{
	return signal == char(SIGNAL::NEGATIVE) ? SIGNAL::NEGATIVE : SIGNAL::POSITIVE;
}
/*************************************/
SIGNAL Configuration::Signal(const SIGN sign)
/*************************************/
{
	return sign == SIGN::NEGATIVE ? SIGNAL::NEGATIVE : SIGNAL::POSITIVE;
}
/************************************/
SIGN Configuration::NotSign(const SIGN sign)
/************************************/
{
	return sign == SIGN::NEGATIVE ? SIGN::POSITIVE : SIGN::NEGATIVE;
}
/********************************************/
SIGNAL Configuration::NotSignal(const SIGNAL signal)
/********************************************/
{
	return signal == SIGNAL::NEGATIVE ? SIGNAL::POSITIVE : SIGNAL::NEGATIVE;
}
/***************************************/
bool Configuration::IsSignal(const char signal)
/***************************************/
{
	return signal == char(SIGNAL::NEGATIVE) || signal == char(SIGNAL::POSITIVE);
}
/************************************************************/
COMPARISON Configuration::NotComparison(const COMPARISON comparison)
/************************************************************/
{
	return comparison == COMPARISON::MINOR ? COMPARISON::MAJOR : comparison == COMPARISON::MAJOR ? COMPARISON::MINOR : COMPARISON::EQUAL;
}

auto Config = new Configuration();

/********************************************/
size_t Configuration::GetPrecision(bool ignoreExtra)
/********************************************/
{
	return DECIMAL_PLACES + (counterPrecision && !ignoreExtra ? DECIMAL_PLACES * 2 : 0);
}
/*************************/
void Configuration::UpPrecision()
/*************************/
{
	++counterPrecision;
}
/***************************/
void Configuration::DownPrecision()
/***************************/
{
	if (counterPrecision)
		--counterPrecision;
	else
		throw logic_error("Unbalanced precision");
}
/***********/
/*** EOF ***/
/***********/
/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"

#include <algorithm>

#include <cme/tables.hpp>
#include <cme/details/unary_math_function.hpp>
#include <cme/details/map_key_iterator.hpp>

#include <boost/xpressive/xpressive_static.hpp>
#include <boost/bind.hpp>

namespace cme {

	constant_table::constant_table()
		: details::constant_table_t()
	{
		add("PI", "3.14159265358979323846");
		add("ROOT_PI", "1.772453850905516027");
		add("ROOT_HALF_PI", "1.253314137315500251");
		add("ROOT_TWO_PI", "2.506628274631000502");
		add("ROOT_LN_FOUR", "1.17741002251547469");
		add("E", "2.71828182845904523536");
		add("HALF", "0.5");
		add("EULER", "0.577215664901532860606");
		add("ROOT_TWO", "1.4142135623730950488");
		add("LN_TWO", "0.6931471805599453094");
		add("LN_LN_TWO", "-0.3665129205816643");
		add("THIRD", "0.333333333333333333");
		add("TWOTHIRD", "0.666666666666666666");
		add("PI_MINUS_THREE", "0.14159265358979323846");
		add("FOUR_MINUS_PI", "0.85840734641020676153735");
		add("GOLDEN_RATIO", "1.61803398874989484820458683436563811");
		add("C", "2.99792458e8"); /// Light Speed
		add("PLANK_CONST", "6.6260693e-34");
		/// etc...
	}

	constant_table::constant_table(constant_table&& other)
		: details::constant_table_t(std::forward<details::constant_table_t>(static_cast<details::constant_table_t&&>(other)))
	{
	}

	constant_table& constant_table::operator=(constant_table&& other)
	{
		details::constant_table_t::operator =(std::forward<details::constant_table_t>(static_cast<details::constant_table_t&&>(other)));
		return *this;
	}
	
	unary_math_function_table::unary_math_function_table()
		: details::unary_math_function_table_t()
	{
		add("tg", &details::tg);
		add("ctg", &details::ctg);
		add("sin", &details::sin);
		add("cos", &details::cos);

		add("atg", &details::atg);
		add("actg", &details::actg);
		add("asinh", &details::asinh);
		add("acosh", &details::acosh);
		add("cosh", &details::cosh);
		add("sinh", &details::sinh);

		add("tgh", &details::tgh);
		add("ctgh", &details::ctgh);
		add("atgh", &details::atgh);
		add("actgh", &details::actgh);

		add("sec", &details::sec);
		add("cosec", &details::cosec);
		add("sech", &details::sech);
		add("cosech", &details::cosech);
		add("asech", &details::asech);
		add("acosech", &details::acosech);

		add("exp", &details::exp);
		add("ln", &details::ln);
		add("lg", &details::lg);
		add("modul", &details::modul);
		add("fact", &details::fact);
		add("dfact", &details::dfact);
		add("sqrt", &details::sqrt);
	}

	unary_math_function_table::unary_math_function_table(unary_math_function_table&& other)
		: details::unary_math_function_table_t(std::forward<details::unary_math_function_table_t>(static_cast<details::unary_math_function_table_t&&>(other)))
	{
	}

	unary_math_function_table& unary_math_function_table::operator=(unary_math_function_table&& other)
	{
		details::unary_math_function_table_t::operator =(std::forward<details::unary_math_function_table_t>(static_cast<details::unary_math_function_table_t&&>(other)));
		return *this;
	}

	variable_table::variable_table()
		: details::variable_table_t()
	{
	}

	variable_table::variable_table(variable_table&& other)
		: details::variable_table_t(std::forward<details::variable_table_t>(static_cast<details::variable_table_t&&>(other)))
	{
	}

	variable_table& variable_table::operator=(variable_table&& other)
	{
		details::variable_table_t::operator =(std::forward<details::variable_table_t>(static_cast<details::variable_table_t&&>(other)));
		return *this;
	}

	namespace {
	
		bool _is_name(std::string const& str)
		{
			using namespace boost::xpressive;

			static sregex const name = ('_' | alpha) >> *_w;

			return regex_match(str, name);
		}

		bool _is_number(std::string const& str)
		{
			using namespace boost::xpressive;

			static sregex const number = []()->sregex
			{
				sregex const fractional_constant_ = (*digit >> '.' >> +digit) | (+digit >> '.');
				sregex const exponent_part_ = (set = 'e', 'E') >> ~(set = '+', '-') >> +digit;
				sregex const fp_ = fractional_constant_ >> !exponent_part_ | +digit >> exponent_part_;
				sregex const number_ = !(as_xpr('+') | '-') >> (fp_ | +digit);

				return number_;
			}();

			return regex_match(str, number);
		}
		
	} /// end unnamed namespace

	bool verify_table(constant_table const& tlb)
	{
		auto const end = tlb.end();
		return std::find_if(tlb.begin(), end
			, [](constant_table::const_reference node) {
				return !_is_name(node.first) || !_is_number(node.second);
		}) == end;
	}

	bool verify_table(unary_math_function_table const& tlb)
	{
		auto const end = tlb.end();
		return std::find_if(tlb.begin(), end
			, [](unary_math_function_table::const_reference node) { 
				return !_is_name(node.first) || !node.second; 
		}) == end;
	}

	bool verify_table(variable_table const& tlb)
	{
		auto const end = details::make_map_key_iterator(tlb.end());
		return std::find_if(details::make_map_key_iterator(tlb.begin()), end, boost::bind(&_is_name, _1) == false) == end;
	}
	
} /// end namespace cme



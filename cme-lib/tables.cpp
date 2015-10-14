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

	constant_table constant_table::make_by_default()
	{
		constant_table ctlb;

		ctlb.add("PI", "3.14159265358979323846");
		ctlb.add("ROOT_PI", "1.772453850905516027");
		ctlb.add("ROOT_HALF_PI", "1.253314137315500251");
		ctlb.add("ROOT_TWO_PI", "2.506628274631000502");
		ctlb.add("ROOT_LN_FOUR", "1.17741002251547469");
		ctlb.add("E", "2.71828182845904523536");
		ctlb.add("HALF", "0.5");
		ctlb.add("EULER", "0.577215664901532860606");
		ctlb.add("ROOT_TWO", "1.4142135623730950488");
		ctlb.add("LN_TWO", "0.6931471805599453094");
		ctlb.add("LN_LN_TWO", "-0.3665129205816643");
		ctlb.add("THIRD", "0.333333333333333333");
		ctlb.add("TWOTHIRD", "0.666666666666666666");
		ctlb.add("PI_MINUS_THREE", "0.14159265358979323846");
		ctlb.add("FOUR_MINUS_PI", "0.85840734641020676153735");
		ctlb.add("GOLDEN_RATIO", "1.61803398874989484820458683436563811");
		ctlb.add("C", "2.99792458e8"); /// Light Speed
		ctlb.add("PLANK_CONST", "6.6260693e-34");
		/// etc...

		return ctlb;
	}
	
	unary_math_function_table::unary_math_function_table()
		: details::unary_math_function_table_t()
	{
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

	unary_math_function_table unary_math_function_table::make_by_default()
	{
		unary_math_function_table umftlb;

		umftlb.add("tg", &details::tg);
		umftlb.add("ctg", &details::ctg);
		umftlb.add("sin", &details::sin);
		umftlb.add("cos", &details::cos);

		umftlb.add("atg", &details::atg);
		umftlb.add("actg", &details::actg);
		umftlb.add("asinh", &details::asinh);
		umftlb.add("acosh", &details::acosh);
		umftlb.add("cosh", &details::cosh);
		umftlb.add("sinh", &details::sinh);

		umftlb.add("tgh", &details::tgh);
		umftlb.add("ctgh", &details::ctgh);
		umftlb.add("atgh", &details::atgh);
		umftlb.add("actgh", &details::actgh);

		umftlb.add("sec", &details::sec);
		umftlb.add("cosec", &details::cosec);
		umftlb.add("sech", &details::sech);
		umftlb.add("cosech", &details::cosech);
		umftlb.add("asech", &details::asech);
		umftlb.add("acosech", &details::acosech);

		umftlb.add("exp", &details::exp);
		umftlb.add("ln", &details::ln);
		umftlb.add("lg", &details::lg);
		umftlb.add("modul", &details::modul);
		umftlb.add("fact", &details::fact);
		umftlb.add("dfact", &details::dfact);
		umftlb.add("sqrt", &details::sqrt);

		return umftlb;
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
				sregex const fractional_constant = (*digit >> '.' >> +digit) | (+digit >> '.');
				sregex const exponent_part = (set = 'e', 'E') >> ~(set = '+', '-') >> +digit;
				sregex const floating_point_literal = fractional_constant >> !exponent_part | +digit >> exponent_part;
				return !(as_xpr('+') | '-') >> (floating_point_literal | +digit);
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



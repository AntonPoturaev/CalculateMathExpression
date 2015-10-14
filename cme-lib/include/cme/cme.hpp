/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#if !defined(CME_LIB_INCLUDE)
#	define CME_LIB_INCLUDE

#include <cme/tables.hpp>

namespace cme {

	real_t calculate_math_expression(string_t const& exprStr
		, variable_table&& vtlb = variable_table()
		, constant_table&& ctlb = constant_table()
		, unary_math_function_table&& umftlb = unary_math_function_table()
		);

} /// end namespace cme

#endif /// !CME_LIB_INCLUDE

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
		, variable_table_ptr_t vtlb = std::make_shared<variable_table>()
		, constant_table_ptr_t ctlb = std::make_shared<constant_table>(constant_table::make_by_default())
		, unary_math_function_table_ptr_t umftlb = std::make_shared<unary_math_function_table>(unary_math_function_table::make_by_default())
		);

} /// end namespace cme

#endif /// !CME_LIB_INCLUDE

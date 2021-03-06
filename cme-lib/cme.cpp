/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"

#include <cme/cme.hpp>
#include <cme/reverse_polish_notation.hpp>
#include <cme/calculator.hpp>

#include <stdexcept>

#include <boost/algorithm/string/trim.hpp>

namespace cme {

	namespace {

		void _check_empty_input(string_t const& input)
		{
			if (input.empty())
				throw std::invalid_argument("Failed to calculate math expression. Reason: empty expression string.");
		}
			
		real_t _calculate_math_expression(string_t&& exprStr, variable_table_ptr_t const& vtlb, constant_table_ptr_t const& ctlb, unary_math_function_table_ptr_t const& umftlb)
		{
			_check_empty_input(exprStr);

			if (vtlb && !verify_table(*vtlb))
				throw std::invalid_argument("Failed to calculate math expression. Reason: bad variable table.");

			if (ctlb && !verify_table(*ctlb))
				throw std::invalid_argument("Failed to calculate math expression. Reason: bad constant table.");

			if (umftlb && !verify_table(*umftlb))
				throw std::invalid_argument("Failed to calculate math expression. Reason: bad unary math function table.");

			reverse_polish_notation const rpn(vtlb, ctlb, umftlb);
			expression const expr = rpn.build(exprStr);
			calculator const calc(vtlb, ctlb, umftlb);

			return calc.calculate(expr);
		}

	} /// end unnamed namespace

	real_t calculate_math_expression(string_t const& exprStr, variable_table_ptr_t vtlb, constant_table_ptr_t ctlb, unary_math_function_table_ptr_t umftlb)
	{
		_check_empty_input(exprStr);
		return _calculate_math_expression(boost::algorithm::trim_copy(exprStr), vtlb, ctlb, umftlb);
	}

} /// end namespace cme

/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#if !defined(CME_CALCULATOR_HPP)
#	define CME_CALCULATOR_HPP

#include <cme/tables.hpp>
#include <cme/expression.hpp>

#include <boost/noncopyable.hpp>

namespace cme {

class calculator
	: public boost::noncopyable
{
	class _impl;
public:
	calculator(variable_table_ptr_t const& vtlb, constant_table_ptr_t const& ctlb, unary_math_function_table_ptr_t const& umftlb);
	~calculator();
	
	real_t calculate(expression const& expr) const;

private:
	_impl* impl_;
};

} /// end namespace cme

#endif /// !CME_CALCULATOR_HPP

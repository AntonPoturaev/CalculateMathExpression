/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#if !defined(CME_REVERSE_POLISH_NOTATION_HPP)
#	define CME_REVERSE_POLISH_NOTATION_HPP

#include <cme/tables.hpp>
#include <cme/expression.hpp>

#include <boost/noncopyable.hpp>

namespace cme {

class reverse_polish_notation
	: public boost::noncopyable
{
	class _impl;
public:
	reverse_polish_notation(variable_table_ptr_t const& vtlb, constant_table_ptr_t const& ctlb, unary_math_function_table_ptr_t const& umftlb);
	~reverse_polish_notation();
	
	expression build(string_t const& str) const;

private:
	_impl* impl_;
};

} /// end namespace cme

#endif /// !CME_REVERSE_POLISH_NOTATION_HPP

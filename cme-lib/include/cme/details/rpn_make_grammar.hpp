/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#if !defined(CME_RPN_MAKE_GRAMMAR_HPP)
#	define CME_RPN_MAKE_GRAMMAR_HPP

#include <cme/tables.hpp>
#include <cme/details/create_rpn_algorithm.hpp>

#include <boost/spirit/include/qi.hpp>

namespace cme { namespace details {

	typedef boost::spirit::qi::symbols<char_t, string_t> symbol_table_t;

	class rpn_make_grammar
		: public boost::spirit::qi::grammar<string_t::const_iterator, expression>
	{
		typedef boost::spirit::qi::rule<iterator_type, string_t()> rule_t;
	public:
		rpn_make_grammar(variable_table_ptr_t const& vtlb, constant_table_ptr_t const& ctlb, unary_math_function_table_ptr_t const& umftlb);

	private:
		details::create_rpn_algorithm const alg_;

		symbol_table_t variable_;
		symbol_table_t constant_;
		symbol_table_t um_function_name_;
				
		rule_t floating_literal_;
		rule_t number_literal_;
		rule_t fractional_constant_;
		rule_t exponent_part_;
		rule_t um_function_;
		rule_t unary_plus_or_minus_;
		rule_t expression_is_in_brackets_;
		rule_t expression_;
		rule_t term_;
		rule_t factor_;
		rule_t binary_function_;
		rule_t power_rule_;

		start_type start_;
	};

}} /// end namespace cme::details

#endif /// !CME_RPN_MAKE_GRAMMAR_HPP

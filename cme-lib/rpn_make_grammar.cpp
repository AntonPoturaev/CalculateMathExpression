/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"

#include <cme/details/rpn_make_grammar.hpp>
#include <cme/details/map_key_iterator.hpp>

#include <boost/spirit/include/phoenix.hpp>

namespace cme { namespace details {

	namespace {
				
		class fill_symbols_table
		{
		public:
			template<typename TlbPtr>
			static void call(symbol_table_t& symbols, std::string const& name, TlbPtr const& tlbPtr)
			{
				fill_symbols_table self(symbols, name);
				if (tlbPtr)
					self._fill(*tlbPtr);
			}

		private:
			fill_symbols_table(symbol_table_t& symbols, std::string const& name)
				: symbols_(symbols)
			{
				symbols_.name(name);
			}

			template<typename Tlb>
			void _fill(Tlb const& tlb)
			{
				std::for_each(make_map_key_iterator(tlb.begin()), make_map_key_iterator(tlb.end())
					, std::bind(&fill_symbols_table::_add_node, this, std::placeholders::_1)
				);
			}

			void _add_node(string_t const& str) {
				_add(str, str);
			}

			void _add(string_t const& key, string_t const& value) {
				symbols_.add(key, value);
			}

		private:
			symbol_table_t& symbols_;
		};
		
	} /// end unnamed namespace
	
	rpn_make_grammar::rpn_make_grammar(variable_table_ptr_t const& vtlb, constant_table_ptr_t const& ctlb, unary_math_function_table_ptr_t const& umftlb)
		: base_type(start_)
	{
		fill_symbols_table::call(variable_, "variable_table", vtlb);
		fill_symbols_table::call(constant_, "constant_table", ctlb);
		fill_symbols_table::call(um_function_name_, "unary_math_function_table", umftlb);

		using boost::spirit::qi::digit;
		using boost::spirit::qi::char_;
		using boost::spirit::qi::string;
		using boost::spirit::qi::eps;
		using boost::spirit::qi::_val;
		using boost::spirit::qi::_1;
		using boost::phoenix::bind;
		using boost::phoenix::construct;

		start_ =	
			eps[bind(&details::create_rpn_algorithm::start_processing, alg_, _val)]
			>> expression_
			>> eps[bind(&details::create_rpn_algorithm::end_processing, alg_)]
		;

		fractional_constant_ = (*digit >> char_('.') >> +digit) | (+digit >> char_('.'));

		//exponent_part_ = (char_('e') | char_('E')) >> !(char_('+') | char_('-')) >> +digit;
		exponent_part_ = char_("eE") >> !char_("+-") >> +digit;

		floating_literal_ = fractional_constant_ >> !exponent_part_ | +digit >> exponent_part_;

		number_literal_ = floating_literal_ | +digit;

#define PUSH_TOKEN_BY_ID(id_value) bind(&details::create_rpn_algorithm::push_token, alg_, construct<token>(_1, token::id::id_value))

		expression_is_in_brackets_ =
			char_('(')[PUSH_TOKEN_BY_ID(open_bracket)]
			>> expression_
			>> char_(')')[PUSH_TOKEN_BY_ID(closed_bracket)]
		;

		unary_plus_or_minus_ = (char_('-')[PUSH_TOKEN_BY_ID(unary_minus)] | char_('+')) >> factor_;
		
		factor_ =
			number_literal_[PUSH_TOKEN_BY_ID(number)]
			| variable_[PUSH_TOKEN_BY_ID(variable)]
			| constant_[PUSH_TOKEN_BY_ID(constant)]
			| um_function_
			| binary_function_
			| expression_is_in_brackets_
			| unary_plus_or_minus_
		;
		
		power_rule_ = factor_ >> *(char_('^')[PUSH_TOKEN_BY_ID(power)] >> factor_);

		term_ =
			power_rule_
			>> *(
				(char_('*')[PUSH_TOKEN_BY_ID(mul)] >> power_rule_) 
				| (char_('/')[PUSH_TOKEN_BY_ID(div)] >> power_rule_)
			)
		;

		expression_ =
			term_
			>> *(
				(char_('+')[PUSH_TOKEN_BY_ID(plus)] >> term_)
				| (char_('-')[PUSH_TOKEN_BY_ID(minus)] >> term_)
			)
		;

		um_function_ = um_function_name_[PUSH_TOKEN_BY_ID(function_name)] >> expression_is_in_brackets_;

		binary_function_ =
			(string("pow")[PUSH_TOKEN_BY_ID(power_function)] | string("root")[PUSH_TOKEN_BY_ID(root_function)])
			>> char_('(')[PUSH_TOKEN_BY_ID(open_bracket)]
			>> expression_
			>> char_(',')[PUSH_TOKEN_BY_ID(coma)]
			>> expression_
			>> char_(')')[PUSH_TOKEN_BY_ID(closed_bracket)]
		;

#undef PUSH_TOKEN_BY_ID
	}
	
}} /// end namespace cme::details

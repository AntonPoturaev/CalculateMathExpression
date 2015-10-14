/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"

#include <cme/reverse_polish_notation.hpp>
#include <cme/details/rpn_make_grammar.hpp>

#include <stdexcept>

#include <boost/format.hpp>

namespace cme {

	class reverse_polish_notation::_impl
	{
	public:
		_impl(variable_table const& vtlb, constant_table const& ctlb, unary_math_function_table const& umftlb)
			: vtlb_(vtlb)
			, ctlb_(ctlb)
			, umftlb_(umftlb)
		{
		}

		expression build(string_t const& str) const
		{
			expression expr;
			details::rpn_make_grammar const parser(vtlb_, ctlb_, umftlb_);

			using namespace  boost::spirit::qi;
			if (!phrase_parse(str.begin(), str.end(), parser, ascii::space, expr))
				throw std::runtime_error(boost::str(boost::format("Failed to build RPN for input:[%1%].") % str));

			return expr;
		}

	private:
		variable_table const& vtlb_;
		constant_table const& ctlb_;
		unary_math_function_table const& umftlb_;
	};

	reverse_polish_notation::reverse_polish_notation(variable_table const& vtlb, constant_table const& ctlb, unary_math_function_table const& umftlb)
		: impl_(new _impl(vtlb, ctlb, umftlb))
	{
	}

	reverse_polish_notation::~reverse_polish_notation()
	{
		delete impl_;
		impl_ = nullptr;
	}

	expression reverse_polish_notation::build(string_t const& str) const {
		return impl_->build(str);
	}

} /// end namespace cme

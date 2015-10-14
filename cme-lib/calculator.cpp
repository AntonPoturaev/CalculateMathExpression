/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"

#include <cme/calculator.hpp>
#include <cme/details/string_to_real_cast.hpp>

#include <stack>
#include <functional>
#include <cassert>
#include <cmath>
#include <stdexcept>

#include <boost/format.hpp>

namespace cme {

	namespace {
	
		template<typename RealTy>
		struct power;

		template<>
		struct power<float>
		{
			float operator()(float x, float y) const {
				return std::powf(x, y);
			}
		};

		template<>
		struct power<double>
		{
			double operator()(double x, double y) const {
				return std::pow(x, y);
			}
		};

		template<>
		struct power<long double>
		{
			long double operator()(long double x, long double y) const {
				return std::powl(x, y);
			}
		};

		power<real_t> const power_;
		
	} /// end unnamed namespace

	class calculator::_impl
	{
		typedef std::stack<real_t> stack_t;

		typedef std::function<real_t(real_t, real_t)> operation_proc_t;

	public:
		_impl(variable_table const& vtlb, constant_table const& ctlb, unary_math_function_table const& umftlb)
			: vtlb_(vtlb)
			, ctlb_(ctlb)
			, umftlb_(umftlb_)
			, tmvalue_(0.)
		{
		}

		real_t calculate(expression const& expr)
		{
			for (auto const& tok : expr)
				do_calculate(tok);

			if (stack_.size() == 1)
				return stack_.top();

			throw std::logic_error("Failed to calculate math expression. Reason: unknown logic error.");
		}

	private:
		void build_operation(operation_proc_t&& operation)
		{
			assert(operation && "Bad param!");

			tmvalue_ = stack_.top();
			stack_.pop();
			stack_.top() = operation(stack_.top(), tmvalue_);
		};

		void do_calculate(token const& tok)
		{
			switch (token::id const id = tok.get_id())
			{
			case token::id::number:
				stack_.push(details::string_to_real_cast(tok.get_name()));
				break;
			case token::id::variable:
				stack_.push(vtlb_.at(tok.get_name()));
				break;
			case token::id::constant:
				stack_.push(details::string_to_real_cast(ctlb_.at(tok.get_name())));
				break;
			case token::id::plus:
				build_operation(std::plus<real_t>());
				break;
			case token::id::minus:
				build_operation(std::minus<real_t>());
				break;
			case token::id::mul:
				build_operation(std::multiplies<real_t>());
				break;
			case token::id::div:
				build_operation(std::divides<real_t>());
				break;
			case token::id::unary_minus:
				stack_.top() = -stack_.top();
				break;
			case token::id::power: case token::id::power_function:
				build_operation(power_);
				break;
			case token::id::root_function:
				build_operation([](real_t x, real_t y) { return power_(x, real_t(1.) / y); });
				break;
			case token::id::function_name:
				stack_.top() = umftlb_.at(tok.get_name()) (stack_.top());
				break;
			default:
				throw std::invalid_argument(boost::str(boost::format("Failed to calculate math expression. Reason: unknown token id:[%1%]") % static_cast<int>(id)));
			}
		}
		
	private:
		variable_table const& vtlb_;
		constant_table const& ctlb_;
		unary_math_function_table const& umftlb_;
		real_t tmvalue_;
		stack_t stack_;
	};

	calculator::calculator(variable_table const& vtlb, constant_table const& ctlb, unary_math_function_table const& umftlb)
		: impl_(new _impl(vtlb, ctlb, umftlb))
	{
	}

	calculator::~calculator()
	{
		delete impl_;
		impl_ = nullptr;
	}

	real_t calculator::calculate(expression const& expr) const {
		return impl_->calculate(expr);
	}

} /// end namespace cme

/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"

#include <cme/details/create_rpn_algorithm.hpp>

#include <stack>
#include <cassert>
#include <stdexcept>

#include <boost/format.hpp>

namespace cme { namespace details {

	namespace {
	
		enum class priority
		{
			opening_bracket
			, plus_minus
			, mul_div
			, power
			, unary_minus
			, function_name
		};

		priority to_priority(token::id id)
		{
			switch (id)
			{
			case token::id::open_bracket: return priority::opening_bracket;
			case token::id::plus: case token::id::minus: return priority::plus_minus;
			case token::id::mul: case token::id::div: return priority::mul_div;
			case token::id::unary_minus: return priority::unary_minus;
			case token::id::function_name: case token::id::power_function: case token::id::root_function: return priority::function_name;
			case token::id::power: return priority::power;
			default: throw std::invalid_argument(boost::str(boost::format("Failed to get priority for token id. Reason: unknown token id:[%1%]") % static_cast<int>(id)));
			}
		}
		
	} /// end unnamed namespace

	class create_rpn_algorithm::_impl
	{
		typedef std::stack<token> stack_t;
	public:
		_impl()
			: expr_(nullptr)
		{
		}

		~_impl() {
			_release();
		}

		void start_processing(expression& expr) 
		{
			if (!_is_released())
				throw std::logic_error("Failed to start \"Create RPN algorithm\". Reason: algorithm is started.");

			expr_ = std::addressof(expr);
		}

		void push_token(token const& tok)
		{
			if (_is_released())
				throw std::logic_error("Failed to push token to \"Create RPN algorithm\". Reason: algorithm is released.");

			switch (tok.get_id())
			{
			case token::id::coma:
				_unload_expr();
				break;
			case token::id::open_bracket:
				stack_.push(tok);
				break;
			case token::id::closed_bracket:
			{
				_unload_expr();
				stack_.pop();
				break;
			}
			case token::id::number: case token::id::variable: case token::id::constant:
				expr_->push_back(tok);
				break;
			case token::id::power:
			{
				while (_cond(_top_priority() > priority::power))
					_add_tok();
				stack_.push(tok);
				break;
			}
			default:
				_alg_execute(tok);
				break;
			}
		}

		void end_processing()
		{
			assert(!_is_released() && "Bad logic!");

			while (!stack_.empty())
				_add_tok();

			_release();
		}

	private:
		bool _is_released() const {
			return expr_ == nullptr && stack_.empty();
		}

		void _release() 
		{
			expr_ = nullptr;
			stack_ = stack_t();
		}

		priority _top_priority() const {
			return to_priority(stack_.top().get_id());
		}

		void _add_tok()
		{
			expr_->push_back(stack_.top());
			stack_.pop();
		}

		void _unload_expr()
		{
			while (_top_priority() != priority::opening_bracket)
				_add_tok();
		}

		bool _cond(bool value) const {
			return (!stack_.empty() && value);
		}

		bool _cond(priority value) const {
			return _cond(_top_priority() >= value);
		}

		void _alg_execute(token const& tok)
		{
			priority const priorityValue = to_priority(tok.get_id());

ALG_EP:		if (stack_.empty() || _top_priority() < priorityValue)
			{
				stack_.push(tok);
				return;
			}

			if (_cond(priorityValue))
			{
				_add_tok();

				while (_cond(priorityValue))
					_add_tok();

				goto ALG_EP;
			}
		}

	private:
		expression* expr_;
		stack_t stack_;
	};

	create_rpn_algorithm::create_rpn_algorithm()
		: impl_(new _impl)
	{
	}

	create_rpn_algorithm::~create_rpn_algorithm()
	{
		delete impl_;
		impl_ = nullptr;
	}

	void create_rpn_algorithm::start_processing(expression& expr) const {
		impl_->start_processing(expr);
	}

	void create_rpn_algorithm::push_token(token const& tok) const {
		impl_->push_token(tok);
	}

	void create_rpn_algorithm::end_processing() const {
		impl_->end_processing();
	}

}} /// end namespace cme::details

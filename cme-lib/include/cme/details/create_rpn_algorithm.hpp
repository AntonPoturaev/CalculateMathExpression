/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#if !defined(CME_CREATE_RPN_ALGORITHM_HPP)
#	define CME_CREATE_RPN_ALGORITHM_HPP

#include <cme/token.hpp>
#include <cme/expression.hpp>

namespace cme { namespace details {

	class create_rpn_algorithm
	{
		class _impl;
	public:
		create_rpn_algorithm();
		~create_rpn_algorithm();

		void start_processing(expression& expr) const;
		void push_token(token const& tok) const;
		void end_processing() const;

	private:
		_impl* impl_;
	};

}} /// end namespace cme::details

#endif /// !CME_CREATE_RPN_ALGORITHM_HPP

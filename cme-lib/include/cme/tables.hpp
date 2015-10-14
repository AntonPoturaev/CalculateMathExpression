/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#if !defined(CME_TABLES_HPP)
#	define CME_TABLES_HPP

#include <cme/details/base_types.hpp>
#include <cme/details/table_base.hpp>

#include <functional>
#include <memory>

namespace cme {

	namespace details 
	{
		typedef details::table_base<std::string> constant_table_t;

		typedef std::function<real_t(real_t)> unary_math_function_t;
		typedef details::table_base<unary_math_function_t> unary_math_function_table_t;

		typedef details::table_base<real_t> variable_table_t;
	} /// end namespace details

	struct constant_table
		: public details::constant_table_t
	{
		constant_table();
		constant_table(constant_table&& other);
		constant_table& operator=(constant_table&& other);

		static constant_table make_by_default();
	};

	typedef std::shared_ptr<constant_table const> constant_table_ptr_t;

	struct unary_math_function_table
		: public details::unary_math_function_table_t
	{
		unary_math_function_table();
		unary_math_function_table(unary_math_function_table&& other);
		unary_math_function_table& operator=(unary_math_function_table&& other);

		static unary_math_function_table make_by_default();
	};

	typedef std::shared_ptr<unary_math_function_table const> unary_math_function_table_ptr_t;

	struct variable_table
		: public details::variable_table_t
	{
		variable_table();
		variable_table(variable_table&& other);
		variable_table& operator=(variable_table&& other);
	};

	typedef std::shared_ptr<variable_table const> variable_table_ptr_t;

	bool verify_table(constant_table const& tlb);
	bool verify_table(unary_math_function_table const& tlb);
	bool verify_table(variable_table const& tlb);

} /// end namespace cme

#endif /// !CME_TABLES_HPP

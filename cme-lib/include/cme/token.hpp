/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/


#if !defined(CME_TOKEN_HPP)
#	define CME_TOKEN_HPP

#include <cme/details/base_types.hpp>

#include <boost/serialization/nvp.hpp>

namespace cme {
	
	class token
	{
		friend class boost::serialization::access;
	public:
		enum class id
		{
			coma
			, open_bracket
			, closed_bracket
			, number
			, variable
			, constant
			, plus
			, minus
			, mul
			, div
			, power
			, unary_minus
			, function_name
			, power_function
			, root_function
		};

	public:
		token();
		token(string_t const& tok_name, id _id);
		token(char_t tok_name, id _id);
		token(token const& right);
		token(token&& other);

		token& operator=(token const& other);
		token& operator=(token&& other);

		void set_id(id id_);
		id get_id() const;
		void set_name(string_t const& name);
		void set_name(char_t op);
		string_t const& get_name() const;

	private:
		template<typename XMLArchiveTy>
		void serialize(XMLArchiveTy& archive, unsigned int version)
		{
			using namespace boost::serialization;

			archive & make_nvp("token_name", name_);
			archive & make_nvp("token_id", id_);
		}

	private:
		id id_;
		string_t name_;
	};

} /// end namespace cme

#endif /// !CME_TOKEN_HPP

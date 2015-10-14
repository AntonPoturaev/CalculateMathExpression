/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"

#include <cme/token.hpp>

namespace cme {
	
	token::token()
		: id_()
		, name_()
	{
	}

	token::token(string_t const& tok_name, id _id)
		: id_(_id)
		, name_(tok_name)
	{
	}

	token::token(char_t tok_name, id _id)
		: id_(_id)
		, name_(1, tok_name)
	{
	}

	token::token(token const& right)
		: id_(right.id_)
		, name_(right.name_)
	{
	}

	token::token(token&& other)
		: id_(std::forward<id>(other.id_))
		, name_(std::forward<string_t>(other.name_))
	{
	}

	token& token::operator=(token const& other)
	{
		if (this != &other)
		{
			id_ = other.id_;
			name_ = other.name_;
		}

		return *this;
	}

	token& token::operator=(token&& other)
	{
		id_ = std::forward<id>(other.id_);
		name_ = std::forward<string_t>(other.name_);

		return *this;
	}

	void token::set_id(id id_) {
		id_ = id_;
	}

	token::id token::get_id() const {
		return id_;
	}
	
	void token::set_name(string_t const& name) {
		name_ = name;
	}

	void token::set_name(char_t op) {
		name_ = string_t(1, op);
	}

	string_t const& token::get_name() const {
		return name_;
	}

} /// end namespace cme

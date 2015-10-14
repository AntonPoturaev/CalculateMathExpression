/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"

#include <cme/details/string_to_real_cast.hpp>

#include <stdexcept>
#include <typeinfo>

#include <boost/spirit/include/qi.hpp>
#include <boost/format.hpp>

namespace cme { namespace details {

	namespace {
		void _cast_is_failed(string_t const& str) {
			throw std::runtime_error(boost::str(boost::format("Failed to convert string:[\"%1%\"] to type:[%2%]") % str % typeid(real_t).name()));
		}
	} /// end unnamed namespace

	real_t string_to_real_cast(string_t const& str)
	{
		typedef boost::spirit::qi::real_parser<real_t, boost::spirit::qi::real_policies<real_t>> real_parser_t;

		real_t value(0.);

		if (!boost::spirit::qi::parse(str.begin(), str.end(), real_parser_t(), value))
			_cast_is_failed(str);

		return value;
	}

}} /// end namespace cme::details

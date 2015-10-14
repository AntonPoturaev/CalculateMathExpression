/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#if !defined(CME_STRING_TO_REAL_CAST_HPP)
#	define CME_STRING_TO_REAL_CAST_HPP

#include <cme/details/base_types.hpp>

namespace cme { namespace details {
	real_t string_to_real_cast(string_t const& str);
}} /// end namespace cme::details

#endif /// !CME_STRING_TO_REAL_CAST_HPP

/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#if !defined(CME_REAL_TYPE)
#	pragma message("Macro CME_REAL_TYPE is't defined. Set to default value: double")
#	define CME_REAL_TYPE double
#endif /// !CME_REAL_TYPE

#if !defined(CME_BASE_TYPES_HPP)
#	define CME_BASE_TYPES_HPP

#include <string>
#include <type_traits>

namespace cme {

	typedef char char_t;
	typedef std::basic_string<char_t> string_t;
	typedef CME_REAL_TYPE real_t;

	static_assert(std::is_floating_point<real_t>::value, "Type cme::real_t - isn't floating point!");

} /// end namespace cme::details

#endif /// !CME_BASE_TYPES_HPP

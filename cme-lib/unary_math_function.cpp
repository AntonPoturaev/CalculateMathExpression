/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"

#include <cme/details/unary_math_function.hpp>

#include <cmath>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include <boost/math/special_functions/asinh.hpp>
#include <boost/math/special_functions/acosh.hpp>
#include <boost/math/special_functions/atanh.hpp>

namespace cme { namespace details {

namespace {
	
	template<typename RealTy>
	struct _umf_spec
	{
	public:
		typedef RealTy real_type;

	public:
		static real_type tg(real_type value) {
			return std::tan(value);
		}

		static real_type tgh(real_type value) {
			return std::tanh(value);
		}

		static real_type atg(real_type value) {
			return std::atan(value);
		}

		static real_type ln(real_type value) {
			return std::log(value);
		}

		static real_type exp(real_type value) {
			return std::exp(value);
		}

		static real_type lg(real_type value) {
			return std::log10(value);
		}
	};

	template <>
	struct _umf_spec<long double>
	{
	public:
		typedef long double real_type;

	public:
		static real_type tg(real_type value) {
			return ::tanl(value);
		}

		static real_type tgh(real_type value) {
			return ::tanhl(value);
		}

		static real_type atg(real_type value) {
			return ::atanl(value);
		}

		static real_type ln(real_type value) {
			return ::logl(value);
		}

		static real_type exp(real_type value) {
			return ::expl(value);
		}

		static real_type lg(real_type value) {
			return ::log10l(value);
		}
	};

	typedef _umf_spec<real_t> umf_spec;

	unsigned to_unsigned(real_t value)
	{
		try {
			return boost::numeric_cast<unsigned>(value);
		} catch (boost::bad_numeric_cast const&) {
			return static_cast<unsigned>(value);
		}
	}

	real_t acosech_helper(real_t value1, real_t value2) {
		return ((real_t(1.) + value1) / value2);
	}

} /// end unnamed namespace

/// @short �����
real_t sin(real_t value) {
	return std::sin(value);
}

/// @short �������
real_t cos(real_t value) {
	return std::cos(value);
}

/// @short ����� ���������������
real_t sinh(real_t value) {
	return std::sinh(value);
}

/// @short ������� ���������������
real_t cosh(real_t value) {
	return std::cosh(value);
}

/// @short �������
real_t tg(real_t value) {
	return umf_spec::tg(value);
}

/// @short ���������
real_t ctg(real_t value) {
	return(real_t(1.) / tg(value)); 
}

/// @short ��������������� �������
real_t tgh(real_t value) {
	return umf_spec::tgh(value);
}

/// @short ��������������� ���������
real_t ctgh(real_t value) { 
	return(real_t(1.) / tgh(value)); 
}

/// @short ����������
real_t atg(real_t value) {
	return umf_spec::atg(value);
}

/// @short ������������
real_t actg(real_t value) {
	return(atg(real_t(1.) / value));
}

/// @short ��������������� ��������
real_t asinh(real_t value) { 
	return boost::math::asinh<real_t>(value); 
}

/// @short ��������������� ����������
real_t acosh(real_t value) {
	return boost::math::acosh<real_t>(value);
}

/// @short ��������������� ����������
real_t atgh(real_t value) { 
	return boost::math::atanh<real_t>(value); 
}

/// @short ��������������� ������������
real_t actgh(real_t value) { 
	return(real_t(.5) * ln((value + real_t(1.)) / (value - real_t(1.))));
}

/// @short ������
real_t sec(real_t value) { 
	return(real_t(1.) / cos(value));
}

/// @short ��������
real_t cosec(real_t value) { 
	return(real_t(1.) / sinh(value));
}

/// @short ��������������� ������
real_t sech(real_t value) { 
	return(real_t(1.) / cosh(value));
}

/// @short ��������������� ��������
real_t cosech(real_t value) { 
	return(real_t(1.) / sinh(value));
}

/// @short �������� ��������������� ������
real_t asech(real_t value) { 
	return ln((real_t(1.) +(std::sqrt(real_t(1.) - value * value))) / value);
}

/// @short �������� ��������������� ��������
real_t acosech(real_t value) {
	real_t const internal_value = std::sqrt(real_t(1.) + value * value);
	return (value < real_t(0.)) ? acosech_helper(-internal_value, value) : acosech_helper(internal_value, value);
}

/// @short ����������� ��������
real_t ln(real_t value) { 
	return umf_spec::ln(value); 
}

/// @short ����������
real_t exp(real_t value) { 
	return umf_spec::exp(value); 
}

/// @short ���������� ��������
real_t lg(real_t value) { 
	return umf_spec::lg(value); 
}

/// @short ������
real_t modul(real_t value) {
	return(value > 0 ? value : - value);
}

/// @short ���������
real_t fact(real_t value) {
	return boost::math::factorial<real_t>(to_unsigned(value));
}

/// @short ������� ���������
real_t dfact(real_t value) {
	return boost::math::double_factorial<real_t>(to_unsigned(value));
}

/// @short ���������� ������
real_t sqrt(real_t value) {
	return std::sqrt(value);
}

}} /// end namespace cme::details

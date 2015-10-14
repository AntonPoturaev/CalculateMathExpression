/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#if !defined(CME_UNARY_MATH_FUNCTION_HPP)
#	define CME_UNARY_MATH_FUNCTION_HPP

#include <cme/details/base_types.hpp>

namespace cme { namespace details {

/// @short Синус
real_t sin(real_t value);

/// @short Косинус
real_t cos(real_t value);

/// @short Синус гипербалический
real_t sinh(real_t value);

/// @short Косинус гипербалический
real_t cosh(real_t value);

/// @short Тангенс
real_t tg(real_t value);

/// @short Катангенс
real_t ctg(real_t value);

/// @short Гиперболический тангенс
real_t tgh(real_t value);

/// @short Гиперболический катангенс
real_t ctgh(real_t value);

/// @short Арктангенс
real_t atg(real_t value);

/// @short Арккатангенс
real_t actg(real_t value);

/// @short Гиперболический арксинус
real_t asinh(real_t value);

/// @short Гиперболический арккосинус
real_t acosh(real_t value);

/// @short Гиперболический арктангенс
real_t atgh(real_t value);

/// @short Гиперболический арккатангенс
real_t actgh(real_t value);

/// @short Секанс
real_t sec(real_t value);

/// @short Косеканс
real_t cosec(real_t value);

/// @short Гиперболический секанс
real_t sech(real_t value);

/// @short Гиперболический косеканс
real_t cosech(real_t value);

/// @short Обратный гиперболический секанс
real_t asech(real_t value);

/// @short Обратный гиперболический косеканс
real_t acosech(real_t value);

/// @short Натуральный логарифм
real_t ln(real_t value);

/// @short Експанента
real_t exp(real_t value);

/// @short Десятичный логарифм
real_t lg(real_t value);

/// @short Модуль
real_t modul(real_t value);

/// @short Факториал
real_t fact(real_t value);

/// @short двойной факториал
real_t dfact(real_t value);

/// @short квадратный корень
real_t sqrt(real_t value);

}} /// end namespace cme::details

#endif /// !CME_UNARY_MATH_FUNCTION_HPP

/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#if defined(_WIN32)

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows

#endif /// _WIN32

#include <cme/details/base_types.hpp>

#include <stdexcept>
#include <string>

#include <boost/spirit/include/qi.hpp>
#include <boost/format.hpp>
#include <boost/unordered_map.hpp>
#include <boost/format.hpp>
#include <boost/filesystem/path.hpp>

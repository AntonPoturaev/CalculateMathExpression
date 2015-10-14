/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/


#if !defined(CME_EXPRESSION_HPP)
#	define CME_EXPRESSION_HPP

#include <cme/token.hpp>

#include <vector>

#include <boost/filesystem/path.hpp>

namespace cme {

class expression
	: public std::vector<token>
{
	typedef std::vector<token> super_t;
public:
	expression();
	expression(expression const& other);
	expression(expression&& other);

	expression& operator=(expression const& other);
	expression& operator=(expression&& other);

	string_t to_string(char_t tok_delim = char_t('|'), char_t unary_minus_substitute = char_t('!')) const;

	void save_to_file(boost::filesystem::path const& path, std::string const& headerName = "cmelib_cme_expression_file") const;
	void load_from_file(boost::filesystem::path const& path, std::string const& headerName = "cmelib_cme_expression_file");
};

} /// end namespace cme

#endif /// !CME_EXPRESSION_HPP

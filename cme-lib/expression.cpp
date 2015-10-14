/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"

#include <cme/expression.hpp>

#include <stdexcept>

#include <boost/format.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>

namespace cme {

	namespace {

		class _collector
		{
		public:
			_collector(string_t& result, char_t tok_delim, char_t unary_minus_substitute)
				: result_(result)
				, tok_delim_(tok_delim)
				, unary_minus_substitute_(unary_minus_substitute)
			{
			}

			void operator()(token const& tok)
			{
				_add(tok);
				result_ += tok_delim_;
			}

			void complete(token const& tok) {
				_add(tok);
			}

		private:
			void _add(token const& tok)
			{
				if (tok.get_id() == token::id::unary_minus)
					result_ += unary_minus_substitute_;
				else
					result_ += tok.get_name();
			}

		private:
			string_t& result_;
			char_t const tok_delim_;
			char_t const unary_minus_substitute_;
		};

		bool _file_is_empty(boost::filesystem::path const& path) {
			return path.empty() || boost::filesystem::is_empty(path);
		}

	} /// end unnamed namespace 


	expression::expression()
		: super_t()
	{
	}

	expression::expression(expression const& other)
		: super_t(other)
	{
	}

	expression::expression(expression&& other)
		: super_t(std::forward<super_t>(static_cast<super_t&&>(other)))
	{
	}

	expression& expression::operator=(expression const& other)
	{
		if (this != &other)
			super_t::operator=(other);

		return *this;
	}

	expression& expression::operator=(expression&& other)
	{
		super_t::operator=(std::forward<super_t>(static_cast<super_t&&>(other)));
		return *this;
	}

	string_t expression::to_string(char_t tok_delim, char_t unary_minus_substitute) const
	{
		string_t result;

		_collector collector(result, tok_delim, unary_minus_substitute);
		std::for_each(begin(), std::prev(end()), collector);
		collector.complete(back());

		return result;
	}

	void expression::save_to_file(boost::filesystem::path const& path, std::string const& headerName) const
	{
		if (_file_is_empty(path))
			throw std::invalid_argument("Failed to save RPN expression to file. Reason: path is empty.");

		if (boost::filesystem::exists(path))
			if (!boost::filesystem::is_regular_file(path))
				throw std::invalid_argument(boost::str(boost::format("Failed to save RPN expression to file. Reason: path:[\"%1%\"] isn't regular file.") % path.string()));

		boost::filesystem::ofstream ofs(path, std::ios::out);

		if (!ofs)
			throw std::invalid_argument(boost::str(boost::format("Failed to save RPN expression to file. Reason: failed to create output stream for file:[\"%1%\"].") % path.string()));

		boost::archive::xml_oarchive oa(ofs);

		oa << boost::serialization::make_nvp(headerName.c_str(), static_cast<super_t const&>(*this));
	};

	void expression::load_from_file(boost::filesystem::path const& path, std::string const& headerName)
	{
		if (_file_is_empty(path))
			throw std::invalid_argument("Failed to load RPN expression from file. Reason: path is empty.");
			
		if (!boost::filesystem::exists(path))
			throw std::invalid_argument(boost::str(boost::format("Failed to load RPN expression from file. Reason: path:[\"%1%\"] isn't exists.") % path.string()));

		if (!boost::filesystem::is_regular_file(path))
			throw std::invalid_argument(boost::str(boost::format("Failed to load RPN expression from file. Reason: path:[\"%1%\"] isn't regular file.") % path.string()));

		boost::filesystem::ifstream ifs(path, std::ios::in);

		if (!ifs)
			throw std::invalid_argument(boost::str(boost::format("Failed to load RPN expression from file. Reason: failed to create input stream for file:[\"%1%\"].") % path.string()));

		boost::archive::xml_iarchive ia(ifs);

		if (!empty())
			clear();

		ia >> boost::serialization::make_nvp(headerName.c_str(), static_cast<super_t&>(*this));
	};

} /// end namespace cme


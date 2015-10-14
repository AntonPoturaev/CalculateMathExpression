/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#if !defined(CME_TABLE_BASE_IMPL_HPP)
#	define CME_TABLE_BASE_IMPL_HPP

#include <string>
#include <stdexcept>

#include <boost/unordered_map.hpp>

namespace cme { namespace details {

	namespace {
		void _insert_is_failed() {
			throw std::runtime_error("Insert node to table is failed.");
		}
	} /// end unnamed namespace

	template<typename ValueT>
	class table_base
		: public boost::unordered_map<std::string, ValueT>
	{
		typedef boost::unordered_map<std::string, ValueT> super_t;
	protected:
		table_base()
			: super_t()
		{
		}

		table_base(table_base&& other)
			: super_t(std::forward<super_t>(static_cast<super_t&&>(other)))
		{
		}

		table_base& operator=(table_base&& other)
		{
			super_t::operator =(std::forward<super_t>(static_cast<super_t&&>(other)));
			return *this;
		}

	public:
		bool const contained_here(std::string const& name) const {
			return find(name) != end();
		}

		void add(value_type&& rec)
		{
			if (insert(std::forward<value_type>(rec)).second == false)
				_insert_is_failed();
		}

		void add(const_reference rec)
		{
			if (insert(rec).second == false)
				_insert_is_failed();
		}

		void add(std::string&& name, mapped_type&& val = mapped_type()) {
			add(std::make_pair(std::forward<std::string>(name), std::forward<mapped_type>(val)));
		}
	};

}} /// end namespace cme::details

#endif /// !CME_TABLE_BASE_IMPL_HPP

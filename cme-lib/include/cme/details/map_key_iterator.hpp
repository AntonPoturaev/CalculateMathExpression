/**
	Project - Calculate Math Expression
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#if !defined(CME_MAP_KEY_ITERATOR_HPP)
#	define CME_MAP_KEY_ITERATOR_HPP

#include <boost/iterator/iterator_facade.hpp>

namespace cme { namespace details {

	template<typename MapIteratorTy>
	class map_key_iterator
		: public boost::iterator_facade<
			map_key_iterator<MapIteratorTy>
			, typename std::iterator_traits<MapIteratorTy>::value_type::first_type
			, typename std::iterator_traits<MapIteratorTy>::iterator_category
		>
	{
		friend class boost::iterator_core_access;
	public:
		typedef MapIteratorTy map_iterator_t;
		typedef typename std::iterator_traits<map_iterator_t>::value_type::first_type key_t;

	public:
		map_key_iterator(map_iterator_t const& iter)
			: iter_(iter)
		{
		}

		map_key_iterator(map_key_iterator const& other)
			: iter_(other.iter_)
		{
		}

		key_t& dereference() const {
			return iter_->first;
		}

		void increment() {
			++iter_;
		}

		void decrement() {
			--iter_;
		}

		bool equal(map_key_iterator const& other) const {
			return iter_ == other.iter_;
		}

	private:
		map_iterator_t iter_;
	};

	template<typename MapIteratorTy>
	map_key_iterator<MapIteratorTy> make_map_key_iterator(MapIteratorTy const& iter) {
		return map_key_iterator<MapIteratorTy>(iter);
	}
}} /// end namespace cme::details

#endif /// !CME_MAP_KEY_ITERATOR_HPP

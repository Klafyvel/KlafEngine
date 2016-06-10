#ifndef H_KLFUTILS
#define H_KLFUTILS
/**
 * @file Utils.hpp
 * @brief Utilities for KlafEngine.
 * @author klafyvel
 */

#include <assert.h>

namespace klf
{
class range {
public:
	class iterator {
	friend class range;
	public:
		long int operator *() const { return m_i; }
		const iterator &operator ++() { ++m_i; return *this; }
		iterator operator ++(int) { iterator copy(*this); ++m_i; return copy; }

		bool operator ==(const iterator &other) const { return m_i == other.m_i; }
		bool operator !=(const iterator &other) const { return m_i != other.m_i; }

	protected:
		iterator(long int start) : m_i (start) { }

	private:
		unsigned long m_i;
	};

	iterator begin() const { return m_begin; }
	iterator end() const { return m_end; }
	range(long int  begin, long int end) : m_begin(begin), m_end(end) {}
private:
	iterator m_begin;
	iterator m_end;
};

float intersect(float begin1, float end1, float begin2, float end2);


}

#endif // H_KLFUTILS

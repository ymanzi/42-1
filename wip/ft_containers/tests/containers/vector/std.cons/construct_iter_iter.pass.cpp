/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_iter_iter.pass.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:20:42 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 18:20:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Vector.hpp>
#include <test_macros.hpp>

template<class C, class Iterator>
	void
	test(Iterator first, Iterator last)
	{
		C c(first, last);
		ASSERT(c.size() == static_cast<std::size_t>(ft::distance(first, last)));

		for (typename C::const_iterator i = c.begin(), e = c.end(); i != e; ++i, ++first)
			ASSERT(*i == *first);
	}

static void
basic_test_cases()
{
	Aware<int> a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 1, 0 };
	Aware<int> *an = a + sizeof(a) / sizeof(a[0]);

	test<ft::Vector<Aware<int> > >(SimpleIterator<const Aware<int> >(a), SimpleIterator<const Aware<int> >(an));
	test<ft::Vector<Aware<int> > >(ft::Vector<Aware<int> >::iterator(a), ft::Vector<Aware<int> >::iterator(an));
	test<ft::Vector<Aware<int> > >(ft::Vector<Aware<int> >::const_iterator(a), ft::Vector<Aware<int> >::const_iterator(an));
	test<ft::Vector<Aware<int> > >(a, an);
}

struct B1
{
		int x;
};

struct B2
{
		int y;
};

struct Der :
		B1,
		B2
{
		int z;
};

void
test_ctor_with_different_value_type() // Initialize a vector with a different value type.
{
	float array[3] = { 0.0f, 1.0f, 2.0f };

	{ // Make sure initialization is performed with each element value, not with a memory blob.
		ft::Vector<int> v(array, array + 3);
		assert(v[0] == 0);
		assert(v[1] == 1);assert(v[2] == 2);
	}

	{ // Though the types Der* and B2* are very similar, initialization still cannot be done with `memcpy`.
		Der z;
		Der *array[1] = { &z };

		ft::Vector<B2*> v(array, array + 1);
		ASSERT(v[0] == &z);
	}

	{ // Though the types are different, initialization can be done with `memcpy`.
		int32_t array[1] = { -1 };
		ft::Vector<uint32_t> v(array, array + 1);
		ASSERT(v[0] == 4294967295);
	}
}

int
main(void)
{
	TEST_AWARE_BLOCK({
		basic_test_cases();
	});

	test_ctor_with_different_value_type();

	return (0);
}

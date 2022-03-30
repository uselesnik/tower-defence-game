#pragma once
# include <iostream>
template <class T>
class test
{
public:
	void sus(T d);
};

template<class T>
inline void test<T>::sus(T d)
{
	std::cout << d;
}

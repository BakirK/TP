#include <iostream>
#include <set>

template<typename someType>
std::set<someType> Presjek (std::set<someType> a, std::set<someType> b)
{
	std::set<someType> c;
	for(someType i: a) {
		for(someType j: b) {
			if (i == j) {
				c.insert(i);
			}
		}
	}
	return c;
}

template<typename someType>
std::set<someType> Unija (std::set<someType> a, std::set<someType> b)
{
	std::set<someType> c;
	for(someType i: a) {
		c.insert(i);
	}
	for(someType i: b) {
		c.insert(i);
	}
	return c;
}


int main ()
{
	std::set<std::string> s1{"A", "B", "C", "C", "C"}, s2{"B", "B", "D"};
	for(auto x: Unija(s1, s2)) std::cout << x << " ";
	std::cout << std::endl;
	for(auto x: Presjek(s1, s2)) std::cout << x << " ";
	std::cout << std::endl;

	return 0;
}

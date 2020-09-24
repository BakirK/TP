#include <iostream>
#include <set>
#include <utility>

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

template<typename someType>
std::set<someType> operator+(const std::set<someType> &s1, const std::set<someType> &s2)
{
	return Unija(s1, s2);
}

template<typename someType>
std::set<someType> operator*(const std::set<someType> &s1, const std::set<someType> &s2)
{
	return Presjek(s1, s2);
}


template<typename someType>
std::ostream &operator<<(std::ostream &tok, std::set<someType> s)
{
	tok << '{';
	int i(0);
	auto it = s.begin();
	while(it != s. end()) {
		if (i == s.size() - 1) {
			tok << *it;
		} else {
			tok << *it << ",";
		}
		it++;
		i++;
	}

	tok << "}";
	return tok;
}

template<typename someType>
std::set<someType> &operator+=(std::set<someType> &s1, const std::set<someType> &s2) {
	s1 = operator+(s1, s2);
	return s1;
}

template<typename someType>
std::set<someType> &operator*=(std::set<someType> &s1, const std::set<someType> &s2) {
	s1 = operator*(s1, s2);
	return s1;
}


template<typename someType1, typename someType2>
std::set<std::pair<someType1, someType2>> operator%(const std::set<someType1> &s1, const std::set<someType2> &s2) {
	std::set<std::pair<someType1, someType2>> s3;
	auto it1 (s1.begin());
	while(it1 != s1.end()) {
		auto it2 (s2.begin());
		while(it2 != s2.end()) {
			std::pair<someType1, someType2> temp (*it1, *it2);
			s3.insert(temp);
			it2++;
		}
		it1++;
	}
	return s3;
}


template<typename someType1, typename someType2>
std::ostream &operator<<(std::ostream &tok, std::set<std::pair<someType1, someType2>> p)
{
	auto it (p.begin());
	int i(0);
	tok <<"{";
	while(it != p.end()) {
		if (i == p.size() - 1) {
			tok << "(" << it->first << "," << it->second <<")";
		} else {
				tok << "(" << it->first << "," << it->second <<")" << ",";
		}
		i++;
		it++;
	}
	tok << "}";
	return tok;
}




int main ()
{
std::set<char> s3{'A', 'B'};
std::set<int> s4{1, 2, 3};
std::cout << s3 % s4 << std::endl;
	return 0;
}

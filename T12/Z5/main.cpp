#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>


int main ()
{
	std::cout << "Koliko zelite elemenata: ";
	int n;
	std::cin >> n;
	std::cout << "Unesite elemente: ";
	std::vector<double> v;
	double d;
	int i(0);
	while (i < n) {
		std::cin >> d;
		v.push_back(d);
		i++;
	}
	std::transform(v.begin(), v.end(), v.begin(), std::bind1st(std::divides<double>(), 1));
	std::cout << "Transformirani elementi: ";
	for(double d: v) {
		std::cout << d << " ";
	}
	return 0;
}
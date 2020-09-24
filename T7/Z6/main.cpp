#include <iostream>
#include <list>


template<typename someType>
std::list<someType> SortirajListu(std::list<someType> &lista)
{
	std::list<someType> povratna;
	for(int i(0); i < lista.size() ; i++) {
		auto it1 (lista.begin());
		auto it2 (it1);
		it2++;
		for (int j = 0; j < lista.size() - 1; j++) {
			if (*it1 > *it2) {
				auto temp = *it1;
				*it1 = *it2;
				*it2 = temp;
			}
			it1++;
			it2++;
		}
	}
	return lista;
}

int main ()
{
	std::cout << "Koliko ima elemenata: ";
	int n;
	std::cin >> n;
	int i(0);
	std::list<int> pocetna;
	std::cout << "Unesite elemente: ";
	while (i < n) {
		int temp;
		std::cin >> temp;
		pocetna.push_back(temp);
		i++;
	}
	std::list<int> povratna = SortirajListu(pocetna);
	std::cout << "Sortirana lista: ";
	for(int i: povratna) {
		std::cout << i << " ";
	}
	return 0;
}

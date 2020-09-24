/* 
    TP 2018/2019: Tutorijal 5, Zadatak 3
	
	Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
	mozete slati na mail nslamnik1@etf.unsa.ba.
	
	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.
			  
			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <iostream>
#include <algorithm>
#include <cmath>
#include <deque>

int i(0);
std::deque<int> brojevi;

int main ()
{
	
	std::cout << "Unesite broj elemenata: ";
	int n;
	std::cin >> n;
	if (n < 0 || n > 1000) {
		std::cout << "penal" << std::endl;;
		return 0;
	}
	std::cout << "Unesite elemente: ";
	brojevi.resize(n);
	
	std::for_each(brojevi.begin(), brojevi.end(), [] (int p) {
		int temp;
		std::cin >> temp;
		brojevi.at(i) = temp;
		i++;
	});
	
	
	std::deque<int>::iterator kraj = brojevi.end();
	int max = *(std::max_element(brojevi.begin(), kraj));
	std::cout << "Najveci element deka je " << max << std::endl;
	
	std::deque<int> trocifreniBrojevi;
	trocifreniBrojevi.resize(n);
	auto kraj2 = std::remove_copy_if(brojevi.begin(), kraj, trocifreniBrojevi.begin(), [] (int a) -> bool {
		int broj = std::log10(std::abs(a)) + 1;
		if (broj != 3) {
			return false;
		}
		return true;
	});
	
	int min = *(std::min_element(brojevi.begin(), kraj));
	int broj_min = std::count(brojevi.begin(), kraj, min);
	std::cout << "Najmanji element deka se pojavljuje " << broj_min <<" puta u deku" << std::endl;
	int broj_kvadrata = std::count_if(brojevi.begin(), kraj, [] (int broj) {
		double temp = std::sqrt(static_cast<double>(broj));
		return (std::ceil(temp) == std::floor(temp));
	});
	std::cout << "U deku ima "<< broj_kvadrata << " brojeva koji su potpuni kvadrati" << std::endl;
	
	
	std::stable_sort(brojevi.begin(), kraj, [] (int a, int b) -> bool {
		int suma1 = std::log10(std::abs(a)) + 1;
		int suma2 = std::log10(std::abs(b)) + 1;
		return (suma1 < suma2);
	});
	std::cout << "Prvi element sa najmanjim brojem cifara je " << brojevi.at(0) << std::endl;
	
	std::cout << "Elementi koji nisu trocifreni su: ";
	std::for_each (trocifreniBrojevi.begin(), kraj2, [] (int a) {
		std::cout << a << " ";
	});
	
	return 0;
}
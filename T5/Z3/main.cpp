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


bool jeVeci (int a, int b) {
	int suma1 = std::log10(std::abs(a)) + 1;
	int suma2 = std::log10(std::abs(b)) + 1;
	return (suma1 < suma2);
}

bool jeTrocifren (int a) {
	int broj = std::log10(std::abs(a)) + 1;
	if (broj != 3) {
		return false;
	}
	return true;
}



int cifre(int broj) {
	return std::log10(std::abs(broj)) + 1;
}





int i (0);
int brojevi [1000];

void unos (int p) {
	int temp;
	std::cin >> temp;
	brojevi[i] = temp;
	i++;
}

int main ()
{
	std::cout << cifre(555);
	std::cout << "Unesite broj elemenata (max. 1000): ";
	int n;
	std::cin >> n;
	if (n < 0 || n > 1000) {
		std::cout << "penal" << std::endl;;
		return 0;
	}
	std::cout << "Unesite elemente: ";
	
	std::for_each(brojevi, brojevi + n, unos);
	
	
	int *kraj = &brojevi[i];
	int max = *(std::max_element(brojevi, kraj));
	std::cout << "Najveci element niza je " << max << std::endl;
	
	int trocifreniBrojevi[1000];
	int *kraj2 = std::remove_copy_if(brojevi, kraj, trocifreniBrojevi, jeTrocifren);
	
	int min = *(std::min_element(brojevi, kraj));
	int broj_min = std::count(brojevi, kraj, min);
	std::cout << "Najmanji element niza se pojavljuje " << broj_min <<" puta u nizu" << std::endl;
	int broj_kvadrata = std::count_if(brojevi, kraj, [] (int broj) {
		double temp = std::sqrt(static_cast<double>(broj));
		return (std::ceil(temp) == std::floor(temp));
	});
	std::cout << "U nizu ima "<< broj_kvadrata << " brojeva koji su potpuni kvadrati" << std::endl;
	std::sort(brojevi, kraj, jeVeci);
	std::cout << "Prvi element sa najmanjim brojem cifara je " << brojevi[0] << std::endl;
	
	std::cout << "Elementi koji nisu trocifreni su: ";
	std::for_each (trocifreniBrojevi, kraj2, [] (int a) {
		std::cout << a << " ";
	});
	
	return 0;
}















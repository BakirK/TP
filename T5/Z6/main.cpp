/* 
    TP 2018/2019: Tutorijal 5, Zadatak 6
	
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
#include <vector>
#include <algorithm>

int sumaCifara (int broj) {
	if (broj == 0) {
    	return broj;
    }
    else
    {
       return (broj % 10 + sumaCifara(broj / 10));
    }
}



bool jeVeci (int a, int b) {
	int suma1 = sumaCifara(std::abs(a));
	int suma2 = sumaCifara(std::abs(b));
	if (suma1 == suma2) {
		return a < b;
	}
	return suma1 < suma2;
}

int i (0);
std::vector<int> brojevi;

int main ()
{
	std::cout << "Unesite broj elemenata: ";
	int n;
	std::cin >> n;
	std::cout << "Unesite elemente: ";
	brojevi.resize(n);
	std::for_each(brojevi.begin(), brojevi.end(), [] (int p) {
		int temp;
		std::cin >> temp;
		brojevi.at(i) = temp;
		i++;
	});
	std::sort(brojevi.begin(), brojevi.end(), jeVeci);
	std::cout << "Niz sortiran po sumi cifara glasi: ";
	std::for_each(brojevi.begin(), brojevi.end(), [](int a) {
		std::cout << a << " ";
	});
	std::cout << std::endl << "Unesite broj koji trazite: ";
	int trazeniBroj;
	std::cin >> trazeniBroj;
	bool temp = std::binary_search(brojevi.begin(), brojevi.end(), trazeniBroj, jeVeci);
	if (!temp) {
		std::cout << "Trazeni broj ne nalazi se u nizu!";
	}
	else {
		auto pozicija = std::lower_bound(brojevi.begin(), brojevi.end(), trazeniBroj, jeVeci);
		std::cout << "Trazeni broj nalazi se na poziciji " <<  pozicija - brojevi.begin();
	}
	return 0;
}
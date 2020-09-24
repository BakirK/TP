/* 
    TP 2018/2019: Tutorijal 5, Zadatak 1
	
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

int main ()
{
	std::cout << "Unesite recenicu: ";
	int i (0);
	char recenica[1000];
	char *p = recenica;
	while (i < 999 && std::cin.peek() != '\n') {
		char c = static_cast<char> (std::cin.get());
		*p = c;
		p++;
		i++;
	}
	//dodaj \0 na unesenu recenicu
	*p = '\0';
	//recenica[15000] = 'a';
	char *p2 = p; //p2 pokazuje na \0
	
	p = recenica;
	
	//ako rijec predznace razmaci, pomjeri p na pocetak rijeci
	if (*p == ' ') {
		while (*p == ' ' && *p != '\0') {
			p++;
		}
	}
	
	//pomjeri p na prvi razmak iza rijeci
	while (*p != ' ' && *p != '\0') {
		p++;
	}
	
	//pomjeri p na pocetak druge rijeci
	while (*p == ' ' && *p != '\0') {
		p++;
	}
	//ako recenica ima samo jednu rijec
	if (*p == '\0' || *p == ' ') {
		char *p3 = recenica;
		*p3 = '\0';
	} 
	else {
		char *temp = std::copy(p, p2, recenica);
		*temp = '\0';
	}
	
	//ispis
	p = recenica;
	std::cout << "Recenica bez prve rijeci glasi: ";
	while (*p != '\0') {
		std::cout << *p;
		p++;
	}
	std::cout<< std::endl;
	return 0;
}
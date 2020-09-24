/* 
    TP 2018/2019: Tutorijal 5, Zadatak 2
	
	Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
	mozete slati na mail nslamnik1@etf.unsa.ba.
	
	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.
			  
			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/

#include <vector>
#include <deque>
#include <iostream>

template <typename iter1, typename iter2>
iter2 RazmijeniBlokove(iter1 pocetak, iter1 iza, iter2 odrediste) {
	while (pocetak != iza) {
		auto temp = *pocetak;
		*pocetak = *odrediste;
		*odrediste = temp;
		pocetak++;
		odrediste++;
	}
	return odrediste;
}

int main ()
{
	return 0;
}
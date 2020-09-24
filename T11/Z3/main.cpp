#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>

class Tim
{
	char ime_tima[20];
	int broj_odigranih, broj_pobjeda, broj_nerijesenih, broj_poraza, broj_datih, broj_primljenih, broj_poena;

public:
	Tim(const char ime[])
	{

		if (std::strlen(ime) > 19) {
			throw std::range_error("Predugacko ime tima");
		}
		std::copy(ime, ime + std::strlen(ime), ime_tima);
		ime_tima[std::strlen(ime)] = '\0';
		broj_odigranih = 0;
		broj_pobjeda = 0;
		broj_nerijesenih = 0;
		broj_poraza = 0;
		broj_datih = 0;
		broj_primljenih = 0;
		broj_poena = 0;
	}
	void ObradiUtakmicu(int broj_datih, int broj_primljenih)
	{
		if (broj_datih < 0 || broj_primljenih < 0) {
			throw std::range_error("Neispravan broj golova");
		}
		broj_odigranih++;
		this->broj_datih += broj_datih;
		this->broj_primljenih += broj_primljenih;
		if (broj_datih > broj_primljenih) {
			broj_pobjeda++;
			broj_poena += 3;
		} else if (broj_datih < broj_primljenih) {
			broj_poraza++;
		} else {
			broj_nerijesenih++;
			broj_poena++;
		}

	}
	const char *DajImeTima() const
	{
		return ime_tima;
	}
	int DajBrojPoena() const
	{
		return broj_poena;
	}
	int DajGolRazliku() const
	{
		return broj_datih - broj_primljenih;
	}
	void IspisiPodatke() const
	{
		int i(0);
		while(i < std::strlen(ime_tima)) {
			std::cout<< ime_tima[i];
			i++;
		}
		for(; i < 20; i++) {
			std::cout<< " ";
		}
		std::cout <<  std::right << std::setw(4) << broj_odigranih <<
		          std::right << std::setw(4) << broj_pobjeda <<
		          std::right << std::setw(4) << broj_nerijesenih <<
		          std::right << std::setw(4) << broj_poraza <<
		          std::right << std::setw(4) << broj_datih <<
		          std::right << std::setw(4) << broj_primljenih <<
		          std::right << std::setw(4) << broj_poena << std::endl;
	}
};

int main ()
{
	//Konstruktor koji pravi novi tim sa imenom FK Zeljeznicar 
	//i postavlja sve podatke na nula
	Tim t1("NK Zeljeznicar");
	Tim t2("FK Sarajevo");
	Tim t3("HSK Zrinjski");
	//zeljeznicar je dao 1 gol i primio 1 gol
	//broj utakmica ce se uvecati za 1
	t1.ObradiUtakmicu(1, 0);
	t1.ObradiUtakmicu(3, 0);
	t1.ObradiUtakmicu(2, 1);
	t2.ObradiUtakmicu(1, 1);
	t2.ObradiUtakmicu(1, 0);
	t2.ObradiUtakmicu(0, 5);
	t3.ObradiUtakmicu(0, 1);
	t3.ObradiUtakmicu(0, 2);
	t3.ObradiUtakmicu(1, 1);
	//ispisujemo podatke o fk zeljeznicaru
	t1.IspisiPodatke();
	t2.IspisiPodatke();
	t3.IspisiPodatke();

	return 0;
}

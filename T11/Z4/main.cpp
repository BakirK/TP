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
//kopirajuci konstruktor
	Tim(const Tim &tim)
	{
		std::copy(tim.ime_tima, tim.ime_tima + std::strlen(tim.ime_tima), this->ime_tima);
		ime_tima[std::strlen(tim.ime_tima)] = '\0';
		broj_odigranih = tim.broj_odigranih;
		broj_pobjeda = tim.broj_pobjeda;
		broj_nerijesenih = tim.broj_nerijesenih;
		broj_poraza = tim.broj_poraza;
		broj_datih = tim.broj_datih;
		broj_primljenih = tim.broj_primljenih;
		broj_poena = tim.broj_poena;
	}


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
		std::cout <<   std::right << std::setw(4) << broj_odigranih <<
		          std::right << std::setw(4) << broj_pobjeda <<
		          std::right << std::setw(4) << broj_nerijesenih <<
		          std::right << std::setw(4) << broj_poraza <<
		          std::right << std::setw(4) << broj_datih <<
		          std::right << std::setw(4) << broj_primljenih <<
		          std::right << std::setw(4) << broj_poena << std::endl;
	}
};







class Liga
{
	int br_timova;
	const int max_br_timova;
	Tim **timovi;
	
	//metoda koja dealocira memorij
	static void DealocirajMemoriju(Tim **timovi, int br_timova)
	{
		for(int i = 0; i < br_timova; i++) delete timovi[i];
		delete[] timovi;
	}

public:
	//konstruktor sa jednim parametrom
	//u konstruktorskoj listi postavljam max broj timova na primljeni parametar
	//i broj timova na 0 jer nije niti jedan jos alociran
	explicit Liga(int velicina_lige): max_br_timova(velicina_lige), br_timova(0)
	{
		timovi = nullptr;
		try {
			timovi = new Tim*[velicina_lige] {};
		} catch(std::bad_alloc) {
			DealocirajMemoriju(timovi, velicina_lige);
			std::cout << "Losa alokacija - nema memorije!";
		}
	}

	//konstruktor sa inicijalizacionom listom
	explicit Liga(std::initializer_list<Tim> lista_timova): br_timova(lista_timova.size()), max_br_timova(lista_timova.size())
	{
		timovi = nullptr;
		try {
			//kreira niz nullptr pokazivaca 
			timovi = new Tim*[lista_timova.size()] {};
			int i(0);
			//koristim iteratore koji se krecu kroz listu jer je ne mogu indeksirati
			for(auto it = lista_timova.begin(); it < lista_timova.end(); it++) {
				timovi[i] = new Tim((*it).DajImeTima());
				i++;
			}
		} catch(std::bad_alloc) {
			DealocirajMemoriju(timovi, lista_timova.size());
			std::cout << "Losa alokacija - nema memorije!";
		}
	}


//destruktor
	~Liga()
	{
		for(int i = 0; i < br_timova; i++) delete timovi[i];
		delete[] timovi;
	}


	//kopirajuci konstruktor
	Liga(const Liga &l): max_br_timova(l.DajMaxBrojTimova()), br_timova(l.DajBrojTimova())
	{
		timovi = nullptr;
		//plitka kopija?
		try {
			timovi = new Tim*[l.DajBrojTimova()] {};
			Tim **temp = l.DajTimove();
			for(int  i = 0; i < l.DajBrojTimova(); i++) {
				timovi[i] = new Tim(*temp[i]);
			}
		} catch(std::bad_alloc) {
			DealocirajMemoriju(timovi, l.DajBrojTimova());
			std::cout << "Losa alokacija - nema memorije!";
		}
	}

	
	//pomjerajuci kosntruktor (move konstruktor)
	Liga(Liga &&l): br_timova(l.DajBrojTimova()), max_br_timova(l.max_br_timova)
	{
		//timovi pozvanog objekat sada poakzuju na isti blok memorije
		//na koji je pokazivao l.timovi
		timovi = l.timovi;
		//l.timovi sada ne pokazuju nigdje
		l.timovi = nullptr;
		//rucno mijenjamo broj alociranih timova na 0 jer pokazivac timovi ne pokazuje nigdje
		l.br_timova = 0;
	}

	
	//kopirajuci operator dodjele =
	Liga &operator =(const Liga &l)
	{
		if (l.max_br_timova != this->max_br_timova) {
			throw std::logic_error("Nesaglasni kapaciteti liga");
		}
		if (l.br_timova > this->br_timova) {
			try {
				Tim **temp = l.DajTimove();
				for(int i = br_timova; i < l.br_timova; i++) {
					timovi[i] = new Tim(*temp[i]);
				}
			} catch(std::bad_alloc) {
				for(int i = br_timova; i < l.br_timova; i++) {
					delete timovi[i];
					timovi[i] = nullptr;
				}
				std::cout << "Losa alokacija - nema memorije!";
				throw;
			}
		} else {
			for(int i = l.br_timova; i < br_timova; i++) {
				delete timovi[i];
				timovi[i] = nullptr;
			}
		}
		br_timova = l.br_timova;
		for (int i = 0; i < br_timova; i++) {
			*timovi[i] = *l.timovi[i];
		}
		return *this;
	}


	//pomjerajuci operator dodjele =
	Liga &operator =(Liga &&l)
	{
		if (l.max_br_timova != this->max_br_timova) {
			throw std::logic_error("Nesaglasni kapaciteti liga");
		}
		std::swap(br_timova, l.br_timova);
		std::swap(timovi, l.timovi);
		return *this;
		//ovdje se poziva destruktor za l koji ce da izbrise tj dealocira
		//zauzetu meoriju koju je objekat prvobitno imao
		//a koje sada ima objekat l
	}




	void DodajNoviTim(const char ime_tima[])
	{
		if (br_timova == max_br_timova) {
			throw std::range_error("Liga popunjena");
		} else {
			for (int i(0); i < br_timova; i++) {
				//strcmp ce da vrati engativnu virjednost ako je prvi niz manj po abecedi od drugog
				//nula ako su istio
				//jedan ako je drugi niz abecedno veci od prvog
				if (std::strcmp(ime_tima, timovi[i]->DajImeTima()) == 0) {
					throw std::logic_error("Tim vec postoji");
				}
			}
			timovi[br_timova] = new Tim(ime_tima);
			br_timova++;
		}
	}



	void RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1, int rezultat_2)
	{
		bool nadjen1 (false), nadjen2(false);
		Tim *team1, *team2;
		for (int i(0); i < br_timova; i++) {
			if (std::strcmp(tim1, (*timovi[i]).DajImeTima()) == 0) {
				nadjen1 = true;
				team1 = timovi[i];
			} else if (std::strcmp(tim2, (*timovi[i]).DajImeTima()) == 0) {
				nadjen2 = true;
				team2 = timovi[i];
			}
			if (nadjen1 && nadjen2) {
				break;
			}
		}
		if (!(nadjen1 && nadjen2)) {
			throw std::logic_error("Tim nije nadjen");
		}
		/*if (rezultat_1 < 0 || rezultat_2 < 0) {
			throw std::range_error("Neispravan broj golova");
		}*/
		(*team1).ObradiUtakmicu(rezultat_1, rezultat_2);
		(*team2).ObradiUtakmicu(rezultat_2, rezultat_1);
	}

	
	static bool Veci(Tim *tim1, Tim *tim2)
	{
		if (tim1->DajBrojPoena() == tim2->DajBrojPoena()) {
			if (tim1->DajGolRazliku() == tim2-> DajGolRazliku()) {
				int vrijednost = std::strcmp(tim1->DajImeTima(), tim2->DajImeTima());
				if (vrijednost <= 0) {
					return true;
				} else {
					return false;
				}
			} else {
				return tim1->DajGolRazliku() > tim2-> DajGolRazliku();
			}
		} else {
			return tim1->DajBrojPoena() > tim2->DajBrojPoena();
		}
	}

	//metoda koaj ispisuje tabelu
	void IspisiTabelu()
	{
		std::sort(timovi, timovi + br_timova, Veci);
		for (int i = 0; i < br_timova; i++) {
			timovi[i]->IspisiPodatke();
			/* code */
		}
	}




	int DajBrojTimova() const
	{
		return br_timova;
	}

	int DajMaxBrojTimova() const
	{
		return max_br_timova;
	}

	Tim **DajTimove() const
	{
		return timovi;
	}



};

int main ()
{
	//pravimo ligu timova uz pomoc inicializone liste
	Liga l1{"NK Zeljeznicar", "HSK Zrinjski", "FK Sarajevo", "FK Sloboda", "FK Krupa", "FK Radnik Bijeljina"};
	Liga l2{"NK Siroki Brijeg", "FK Mladost DK", "NK Celik", "NK Vitez", "NK Metalleghe BSI", "FK Olimpic"};
	//metoda koja registruje koja su 2 tima igrala i koji je rezultat utakmice
	l1.RegistrirajUtakmicu("FK Sloboda", "HSK Zrinjski",1,1);
	l1.RegistrirajUtakmicu("FK Sarajevo", "HSK Zrinjski",1,2);
	l1.RegistrirajUtakmicu("FK Krupa", "FK Radnik Bijeljina",1,1);
	l1.RegistrirajUtakmicu("NK Zeljeznicar","FK Krupa",1,0);
	l1.RegistrirajUtakmicu("FK Radnik Bijeljina", "FK Sloboda",0,1);
	l1.RegistrirajUtakmicu("FK Sarajevo", "NK Zeljeznicar",0,3);
	//poziva se kopirajuci operator dodjele
	l2 = l1;

	std::cout << "Orginalna Liga za Prvaka: " << std::endl;
	//ispisujemo tabelu svih urakmica, golova, poena
	l1.IspisiTabelu();
	std::cout << std::endl << "Kopija Lige za Prvaka: " << std::endl;
	l2.IspisiTabelu();
	return 0;
}

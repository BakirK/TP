#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <vector>

class Tim
{
	char ime_tima[20];
	int broj_odigranih, broj_pobjeda, broj_nerijesenih, 
		broj_poraza, broj_datih, broj_primljenih, broj_poena;

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
		std::cout << std::right << std::setw(4) << broj_odigranih <<
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
	std::vector<Tim*> timovi;

	static void DealocirajMemoriju(std::vector<Tim*> timovi)
	{
		for(int i = 0; i < timovi.size(); i++) delete timovi.at(i);
		//delete[] timovi;
	}

public:
	explicit Liga() = default;


	//konstruktor sa listom timova
	explicit Liga(std::initializer_list<Tim> lista_timova)
	{
		try {
			int i(0);
			for(auto it = lista_timova.begin(); it < lista_timova.end(); it++) {
				timovi.push_back(new Tim((*it).DajImeTima()));
				i++;
			}
		} catch(std::bad_alloc) {
			DealocirajMemoriju(timovi);
			std::cout << "Losa alokacija - nema memorije!";
		}
	}


//destruktor
	~Liga()
	{
		for(int i = 0; i < timovi.size(); i++) delete timovi.at(i);
		timovi.clear();
		//delete[] timovi;
	}


	//kopirajuci konstruktor
	Liga(const Liga &l)
	{
		try {

			for(int  i = 0; i < l.timovi.size(); i++) {
				timovi.push_back(new Tim(*l.timovi.at(i)));
			}
		} catch(std::bad_alloc) {
			DealocirajMemoriju(timovi);
			std::cout << "Losa alokacija - nema memorije!";
		}
	}


	Liga(Liga &&l)
	{
		timovi = l.timovi;
		//l.timovi.clear();
	}


	//kopirajuci operator dodjele =
	Liga &operator =(const Liga &l)
	{
		if (l.timovi.size() > this->timovi.size()) {
			try {
				for(int i = this->timovi.size(); i < l.timovi.size(); i++) {
					timovi.push_back(new Tim(*l.timovi.at(i)));
				}
			} catch(std::bad_alloc) {
				for(int i = this->timovi.size(); i < l.timovi.size(); i++) {
					delete timovi.at(i);
					timovi.at(i) = nullptr;
				}
				std::cout << "Losa alokacija - nema memorije!";
				throw;
			}
		} else {
			for(int i = l.timovi.size(); i < this->timovi.size(); i++) {
				delete timovi.at(i);
				timovi.at(i) = nullptr;
			}
		}
		this->timovi.resize(l.timovi.size());
		for (int i = 0; i < timovi.size(); i++) {
			*timovi.at(i) = *l.timovi.at(i);
		}
		return *this;
	}


	//pomjerajuci operator dodjele =
	Liga &operator =(Liga &&l)
	{
		std::swap(timovi, l.timovi);
		for(int i = 0; i < l.timovi.size(); i++){
			delete l.timovi.at(i);
		} 
		l.timovi.clear();
		return *this;
	}




	void DodajNoviTim(const char ime_tima[])
	{
		for (int i(0); i < this->timovi.size(); i++) {
			if (std::strcmp(ime_tima, timovi.at(i)->DajImeTima()) == 0) {
				throw std::logic_error("Tim vec postoji");
			}
		}
		timovi.push_back(new Tim(ime_tima));
	}





	void RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1, int rezultat_2)
	{
		bool nadjen1 (false), nadjen2(false);
		Tim *team1, *team2;
		for (int i(0); i < timovi.size(); i++) {
			if (std::strcmp(tim1, timovi.at(i)->DajImeTima()) == 0) {
				nadjen1 = true;
				team1 = timovi.at(i);
			} else if (std::strcmp(tim2, timovi.at(i)->DajImeTima()) == 0) {
				nadjen2 = true;
				team2 = timovi.at(i);
			}
			if (nadjen1 && nadjen2) {
				break;
			}
		}
		if (!(nadjen1 && nadjen2)) {
			throw std::logic_error("Tim nije nadjen");
		}
		team1->ObradiUtakmicu(rezultat_1, rezultat_2);
		team2->ObradiUtakmicu(rezultat_2, rezultat_1);
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


	void IspisiTabelu()
	{
		std::sort(timovi.begin(), timovi.end(), Veci);
		for (int i = 0; i < timovi.size(); i++) {
			timovi.at(i)->IspisiPodatke();
		}
	}

};

int main ()
{


	Liga l1{"NK Zeljeznicar", "HSK Zrinjski", "FK Sarajevo", "FK Sloboda", "FK Krupa", "FK Radnik Bijeljina"};
	l1.RegistrirajUtakmicu("FK Sloboda", "HSK Zrinjski",1,1);

	Liga l2{"NK Zeljeznicar", "HSK Zrinjski", "FK Sarajevo"};
	Liga l3{"NK Zeljeznicar", "HSK Zrinjski", "FK Sarajevo","NK Zeljeznicar", "HSK Zrinjski", "FK Sarajevo","NK Zeljeznicar", "HSK Zrinjski", "FK Sarajevo"};

	l3 = std::move(l1);
	l2 = l1;

	std::cout << "Liga 1:" << std::endl;
	l1.IspisiTabelu();
	std::cout << std::endl  << "Liga 2:" << std::endl;
	l2.IspisiTabelu();
	std::cout << std::endl  << "Liga 3:" << std::endl;
	l3.IspisiTabelu();
	return 0;
}

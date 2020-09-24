//TP 2018/2019: Zadaća 4, Zadatak 3
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <iomanip>
#include <algorithm>

class Datum {
    int d, m, g;
    public:
    void Postavi(int dan, int mjesec, int godina) {
        if (!provjeriDatum(dan, mjesec, godina)) {
            throw std::domain_error("Neispravan datum");
        }
        this->d = dan;
        this->m = mjesec;
        this->g = godina;
    }
    Datum(int dan, int mjesec, int godina) {
        Postavi(dan, mjesec, godina);
    }
    
    std::tuple<int, int, int> Ocitaj() const {
        return std::tuple<int, int, int>{d, m, g};
    }
    void Ispisi() const {
        std::cout << d << "/" << m << "/" << g;
    }
    
    bool provjeriDatum(int d, int m, int g)
    {
        int broj_dana[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if(g % 4 == 0 && (g % 100 != 0 || g % 400 == 0)) broj_dana[1]++;
        if(g < 1 || d < 1 || m < 1 || m > 12 || d > broj_dana[m - 1] ) {
            return false;
        }
        return true;
    }
    
    int getDay() const {
        return d;
    }
    int getMonth() const {
        return m;
    }
    int getYear() const {
        return g;
    }
    void setDay(int i) {
        d = i;
    }
    void setMonth(int i) {
        m = i;
    }
    void setYear(int i) {
        g = i;
    }
    inline bool operator ==(const Datum &d1) {
        return (d == d1.d && m == d1.m && g == d1.g);
    }
    
    inline bool operator !=(const Datum &d1) {
	 return !(*this == d1);
	}
    
};

class Vrijeme {
    int sati, minute;
    public:
    Vrijeme(int sati, int minute) {
       Postavi(sati, minute);
    }
    void Postavi(int sati, int minute) {
         if (sati > 59 || sati < 0 || minute > 59 || minute < 0) {
            throw std::domain_error("Neispravno vrijeme");
        }
        this->sati = sati;
        this->minute = minute;
    }
    std::pair<int, int> Ocitaj () const {
        return std::make_pair(sati, minute);
    }
    void Ispisi() const {
        std::cout << std::right << std::setw(2) << std::setfill('0') << sati << ":" << std::right << std::setw(2) << std::setfill('0') << minute;
    }
    int getSati() {
        return sati;
    }
    int getMinute() {
        return minute;
    }
};


class Pregled {
    std::string ime_pacijenta;
    Datum datum_pregleda;
    Vrijeme vrijeme_pregleda;
    public:
    Pregled(const std::string &ime_pacijenta, const Datum &datum_pregleda, const Vrijeme &vrijeme_pregleda): 
    datum_pregleda(datum_pregleda), vrijeme_pregleda(vrijeme_pregleda) {
        this->ime_pacijenta = ime_pacijenta;
    }
    Pregled(const std::string &ime_pacijenta, int dan_pregleda, int mjesec_pregleda,
        int godina_pregleda, int sati_pregleda, int minute_pregleda): datum_pregleda(dan_pregleda, mjesec_pregleda, godina_pregleda), 
        vrijeme_pregleda(sati_pregleda, minute_pregleda)  {
        this->ime_pacijenta = ime_pacijenta;
    }
    void PromijeniPacijenta(const std::string &ime_pacijenta) {
        this->ime_pacijenta = ime_pacijenta;
    }
    void PromijeniDatum(const Datum &novi_datum) {
        this->datum_pregleda = novi_datum;
    }
    void PromijeniVrijeme(const Vrijeme &novo_vrijeme) {
        this->vrijeme_pregleda = novo_vrijeme;
    }
    void PomjeriDanUnaprijed();
    void PomjeriDanUnazad();
    std::string DajImePacijenta() const {
        return ime_pacijenta;
    }
    Datum DajDatumPregleda() const {
        return datum_pregleda;
    }
    Vrijeme DajVrijemePregleda() const {
        return vrijeme_pregleda;
    }
    static bool DolaziPrije(const Pregled &p1, const Pregled &p2);
    void Ispisi() const {
        std::cout << std::left << std::setw(30) << std::setfill(' ') << ime_pacijenta;
        datum_pregleda.Ispisi();
        std::cout << " "; vrijeme_pregleda.Ispisi(); std::cout << std::endl;
    }
    inline bool operator ==(const Pregled &p1) {
        return this == &p1;
    }
    
    inline bool operator !=(const Pregled &p1) {
	 return !(*this == p1);
	}
};


void Pregled::PomjeriDanUnaprijed() {
    int broj_dana[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(datum_pregleda.getYear() % 4 == 0 && (datum_pregleda.getYear() % 100 != 0 || datum_pregleda.getYear() % 400 == 0)) broj_dana[1]++;
    datum_pregleda.setDay(datum_pregleda.getDay() + 1);
    if (datum_pregleda.getDay() > broj_dana[datum_pregleda.getMonth() - 1]) {
        datum_pregleda.setDay(1);
        datum_pregleda.setMonth(datum_pregleda.getMonth() + 1);
        if (datum_pregleda.getMonth() > 12) {
            datum_pregleda.setYear(datum_pregleda.getYear() + 1);
            datum_pregleda.setMonth(1);
        }
    }
}


void Pregled::PomjeriDanUnazad() {
    int broj_dana[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(datum_pregleda.getYear() % 4 == 0 && (datum_pregleda.getYear() % 100 != 0 || datum_pregleda.getYear() % 400 == 0)) broj_dana[1]++;
    datum_pregleda.setDay(datum_pregleda.getDay() - 1);
    if (datum_pregleda.getDay() < 1) {
        datum_pregleda.setMonth(datum_pregleda.getMonth() - 1);
        if (datum_pregleda.getMonth() < 1) {
            datum_pregleda.setYear(datum_pregleda.getYear() - 1);
            datum_pregleda.setMonth(12);
        }
        datum_pregleda.setDay(broj_dana[datum_pregleda.getMonth() - 1]);
    }
}


bool Pregled::DolaziPrije(const Pregled &p1, const Pregled &p2) {
    if (p1.DajDatumPregleda().getYear() == p2.DajDatumPregleda().getYear()) {
        if (p1.DajDatumPregleda().getMonth() == p2.DajDatumPregleda().getMonth()) {
            if (p1.DajDatumPregleda().getDay() == p2.DajDatumPregleda().getDay()) {
                if (p1.DajVrijemePregleda().getSati() == p2.DajVrijemePregleda().getSati()) {
                    return p1.DajVrijemePregleda().getMinute() < p2.DajVrijemePregleda().getMinute();
                } else {
                    return p1.DajVrijemePregleda().getSati() < p2.DajVrijemePregleda().getSati();
                }
            } else {
                return p1.DajDatumPregleda().getDay() < p2.DajDatumPregleda().getDay();    
            }
        } 
        else {
            return p1.DajDatumPregleda().getMonth() < p2.DajDatumPregleda().getMonth();
        }
    } 
    else {
        return p1.DajDatumPregleda().getYear() < p2.DajDatumPregleda().getYear();
    }
}



class Pregledi {
    int max_broj_pregleda;
    int brojAlociranih;
    Pregled **spisak;
  public:  
    explicit Pregledi(int max_broj_pregleda) {
        this->max_broj_pregleda = max_broj_pregleda;
        spisak = new Pregled*[max_broj_pregleda]{};
        brojAlociranih = 0;
    }
    Pregledi(std::initializer_list<Pregled> spisak_pregleda){
        max_broj_pregleda = spisak_pregleda.size();
        auto it = spisak_pregleda.begin();
        spisak = new Pregled*[max_broj_pregleda]{};
        int i(0);
        while(it != spisak_pregleda.end()) {
            spisak[i] = new Pregled(*it);
            it++;
            i++;
        }
        brojAlociranih = spisak_pregleda.size();
    }
    ~Pregledi() {
        IsprazniKolekciju();
    }
    Pregledi(const Pregledi &pregledi) {
        this->max_broj_pregleda = pregledi.max_broj_pregleda;
        this->brojAlociranih = pregledi.brojAlociranih;
        spisak = new Pregled*[pregledi.brojAlociranih]{};
        for(int i = 0; i < brojAlociranih; i++) {
            spisak[i] = new Pregled(*(pregledi.spisak[i]));
        }
    }
    Pregledi(Pregledi &&pregledi) {
        this->max_broj_pregleda = pregledi.max_broj_pregleda;
        this->brojAlociranih = pregledi.brojAlociranih;
        this->spisak = pregledi.spisak;
    }
    Pregledi &operator =(const Pregledi &pregledi);
    Pregledi &operator =(Pregledi &&pregledi) {
        std::swap(this->brojAlociranih, pregledi.brojAlociranih);
        std::swap(this->max_broj_pregleda, pregledi.max_broj_pregleda);
        std::swap(this->spisak, pregledi.spisak);
        return *this;
    }
    
    void RegistrirajPregled(const std::string &ime_pacijenta, const Datum &datum_pregleda, const Vrijeme &vrijeme_pregleda);
    void RegistrirajPregled(const std::string &ime_pacijenta, int dan_pregleda, 
                            int mjesec_pregleda, int godina_pregleda, int sati_pregleda,int minute_pregleda);
    void RegistrirajPregled(Pregled *pregled);
    
    int DajBrojPregleda() const {
        return brojAlociranih;
    }
    int DajBrojPregledaNaDatum(const Datum &datum) const;
    Pregled &DajNajranijiPregled();
    Pregled DajNajranijiPregled() const;
    void IsprazniKolekciju();
    void ObrisiNajranijiPregled();
    void ObrisiPregledePacijenta(const std::string &ime_pacijenta);
    void IspisiPregledeNaDatum(const Datum &datum) const;
    void IspisiSvePreglede() const;
};

Pregledi &Pregledi::operator =(const Pregledi &pregledi) {
    this->max_broj_pregleda = pregledi.max_broj_pregleda;
    this->brojAlociranih = pregledi.brojAlociranih;
    spisak = new Pregled*[pregledi.brojAlociranih]{};
    for(int i = 0; i < brojAlociranih; i++) {
        spisak[i] = new Pregled(*(pregledi.spisak[i]));
    }
    return *this;
}


void Pregledi::RegistrirajPregled(const std::string &ime_pacijenta, const Datum &datum_pregleda, const Vrijeme &vrijeme_pregleda) {
    if (max_broj_pregleda == brojAlociranih) {
        throw std::range_error("Dostignut maksimalni broj pregleda");
    } else {
        spisak[brojAlociranih] = new Pregled(ime_pacijenta, datum_pregleda, vrijeme_pregleda);
        brojAlociranih++;
    }
    
}


void Pregledi::RegistrirajPregled(const std::string &ime_pacijenta, int dan_pregleda,
int mjesec_pregleda, int godina_pregleda, int sati_pregleda, int minute_pregleda) {
    
    if (max_broj_pregleda == brojAlociranih) {
        throw std::range_error("Dostignut maksimalni broj pregleda");
    } else {
        spisak[brojAlociranih] = new Pregled(ime_pacijenta, dan_pregleda, mjesec_pregleda, godina_pregleda, sati_pregleda, minute_pregleda);
        brojAlociranih++;
    }
}


void Pregledi::RegistrirajPregled(Pregled *pregled) {
    if (max_broj_pregleda == brojAlociranih) {
        throw std::range_error("Dostignut maksimalni broj pregleda");
    } else {
        spisak[brojAlociranih] = pregled;
        brojAlociranih++;
    }
}

int Pregledi::DajBrojPregledaNaDatum(const Datum &datum) const {
    int k (0);
    for (int i = 0; i < brojAlociranih; i++) {
        if( spisak[i]->DajDatumPregleda() == datum) {
            k++;
        }
    }
    return k;
}

Pregled &Pregledi::DajNajranijiPregled() {
    Pregled **it;
    if (!brojAlociranih) {
        throw std::domain_error("Nema registriranih pregleda");
    } else {
        it = std::min_element(spisak, spisak + brojAlociranih, [](Pregled *p1, Pregled *p2) ->bool {
            return Pregled::DolaziPrije(*p1, *p2);
        });
        return **it;
    }
    
}

Pregled Pregledi::DajNajranijiPregled() const {
    Pregled **it;
    if (!brojAlociranih) {
        throw std::domain_error("Nema registriranih pregleda");
    } else {
        it = std::min_element(spisak, spisak + brojAlociranih, [](Pregled *p1, Pregled *p2) ->bool {
            return Pregled::DolaziPrije(*p1, *p2);
        });
        return **it;
    }
}

void Pregledi::IsprazniKolekciju() {
    for (int i = 0; i < brojAlociranih; i++) {
            delete spisak[i];            
        }
    delete[] spisak;
}


void Pregledi::ObrisiNajranijiPregled() {
    if (!brojAlociranih) {
        throw std::range_error("Prazna kolekcija");
    } else {
        Pregled **it;
        it = std::min_element(spisak, spisak + brojAlociranih, [](Pregled *p1, Pregled *p2) ->bool {
             return Pregled::DolaziPrije(*p1, *p2);
        });
        for (int i = 0; i < brojAlociranih; i++) {
            if ((spisak[i]) == *it) {
                delete spisak[i];
                for(int j = i; j < brojAlociranih - 1; j++) {
                    if (j == brojAlociranih - 2) {
                        auto temp = new Pregled(*(spisak[j+1]));
                        delete spisak[j + 1];
                        spisak[j] = temp;
                    } else {
                        spisak[j] = spisak[j + 1];
                    }
                }
                brojAlociranih--;
                break;
            }
        }
    }
}


void Pregledi::ObrisiPregledePacijenta(const std::string &ime_pacijenta) {
     for (int i = 0; i < brojAlociranih; i++) {
        if (spisak[i]->DajImePacijenta() == ime_pacijenta) {
            delete spisak[i];
            for(int j = i; j < brojAlociranih - 1; j++) {
                if (j == brojAlociranih - 2) {
                    auto temp = new Pregled(*(spisak[j+1]));
                    delete spisak[j + 1];
                    spisak[j] = temp;
                } else {
                    spisak[j] = spisak[j + 1];
                }
            }
            brojAlociranih--;
            i--;
        }
    }
}


void Pregledi::IspisiPregledeNaDatum(const Datum &datum) const {
    Pregledi kopija(*this);
    std::sort(kopija.spisak, kopija.spisak + kopija.brojAlociranih, [](Pregled *p1, Pregled *p2) ->bool {
        return Pregled::DolaziPrije(*p1, *p2);
    });
    for (int i = 0; i < kopija.brojAlociranih; i++) {
        if (kopija.spisak[i]->DajDatumPregleda() == datum) {
            kopija.spisak[i]->Ispisi();    
        }
    }
}


void Pregledi::IspisiSvePreglede() const {
    Pregledi kopija(*this);
    std::sort(kopija.spisak, kopija.spisak + brojAlociranih, [](Pregled *p1, Pregled *p2) ->bool {
        return Pregled::DolaziPrije(*p1, *p2);
    });
    for (int i = 0; i < brojAlociranih; i++) {
        kopija.spisak[i]->Ispisi();
    }
}

int main ()
{
    std::cout << "Unesite maksimalan broj pregleda: ";
    int n;
    std::cin >> n;
    Pregledi pregledi(n);
    std::string unos = "";
    int i(0);
    while(unos != "kraj" && i < n) {
        std::cout << "Unesite ime novog pacijenta ili 'kraj' za zavrsetak unosa: ";
        std::cin.ignore(1000, '\n');
        std::getline(std::cin, unos);
        if (unos == "kraj") {
            break;
        }
        std::cout << "Unesite dan mjesec i godinu pregleda: ";
        int sati, d, m, g, minute;
        std::cin >> d;
        std::cin >> m;
        std::cin >> g;
        std::cout << "Unesite sate i minute pregleda: ";
        std::cin >> sati;
        std::cin >> minute;
  
        i++;
        try{
            pregledi.RegistrirajPregled(unos, d, m, g, sati, minute);
        }
        catch(std::range_error e) {
            std::cout << e.what() << std::endl;
        }
        catch(std::domain_error e) {
            std::cout << e.what() << std::endl;
        }
        catch (...) {
            std::cout << "Nepoznata greska" << std::endl;
        }
    }
    
    std::cout << "Trenutno su registrovani sljedeci pregledi" << std::endl;
    pregledi.IspisiSvePreglede();
    int opcija = 2;
    while (opcija != 7) {
        std::cout << "\n\nOdaberite jednu od sljedecih opcija\n1 - Broj pregleda na datum\n2 - Najraniji pregled\n";
        std::cout << "3 - Obrisi pregled pacijenta\n4 - Obrisi najraniji pregled\n5 - Ispisi sve pregleda na datum";
        std::cout << "\n6 - Ispisi sve preglede\n7 - Kraj programa";
        std::cin >> opcija;
        switch(opcija) {
            case(1):{
                std::cout << std::endl << "Unesite dan mjesec i godinu : ";
                int d, m, g;
                std::cin >> d >> m >> g;
                try{
                    Datum datum(d, m, g);
                    std::cout << "Broj pregleda na datum " << d << " " << m << " " << g << " je: " << pregledi.DajBrojPregledaNaDatum(datum) << std::endl;
                } catch(std::range_error e) {
                    std::cout << e.what() << std::endl << std::endl;
                }
                catch(std::domain_error e) {
                    std::cout << e.what() << std::endl << std::endl;
                }
                catch (...) {
                    std::cout << "Nepoznata greska" << std::endl;
                } 
                break;
            }
            case(2):{
                std::cout << std::endl << "Najraniji pregled je:" << std::endl;
                try{
                    pregledi.DajNajranijiPregled().Ispisi();
                }
                catch(std::domain_error e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case(3):{
                std::cout << std::endl << "Unesite ime pacijenta: ";
                std::string ime;
                std::cin.ignore(1000,'\n');
                std::getline(std::cin, ime);
                int prije = pregledi.DajBrojPregleda();
                pregledi.ObrisiPregledePacijenta(ime);
                std::cout << "Uspjesno obrisano " << prije - pregledi.DajBrojPregleda() << " pregleda";
                break;
            }
            case(4):{
                try {
                    pregledi.ObrisiNajranijiPregled();
                    std::cout << std::endl << "Najraniji pregled uspjesno obrisan";
                }
                catch (std::range_error e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case(5):{
                std::cout << std::endl << "Unesite dan mjesec i godinu : ";
                int d, m, g;
                std::cin >> d >> m >> g;    
                try {
                    Datum datum(d, m, g);
                    std::cout << "Pregledi na datum " << d << " " << m << " " << g <<" su:" << std::endl;
                    pregledi.IspisiPregledeNaDatum(datum);
                } catch(std::domain_error e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case(6):{
                std::cout << std::endl;
                pregledi.IspisiSvePreglede();
                break;
            }
            case(7):{
                return 0;
                break;
            }
        }
    }
	return 0;
}
//TP 2018/2019: Zadaća 5, Zadatak 3
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <memory>
#include <fstream>
#include <cctype>

class Spremnik {
    protected:
        double tezina;
        std::string nazivSadrzaja;
    public:
    virtual double DajTezinu() const = 0;
    virtual double DajUkupnuTezinu() const = 0;
    virtual void Ispisi() const = 0;
    virtual ~Spremnik() = 0;
    virtual Spremnik *DajKopiju() const = 0;
};

class Sanduk: public Spremnik {
  std::vector<double> tezinePredmeta;
  public:
    Sanduk(double tezina, std::string naziv, std::vector<double> tezinePredmeta) {
        this->tezina = tezina;
        this->nazivSadrzaja = naziv;
        this->tezinePredmeta = tezinePredmeta;  
    }
    double DajTezinu() const override {
        return tezina;
    }
    double DajUkupnuTezinu() const override {
        double sum(tezina);
        for(double d: tezinePredmeta) {
            sum += d;
        }
        return sum;
    }
    void Ispisi() const override {
        std::cout << "Vrsta spremnika: Sanduk\n" << "Sadrzaj: " << nazivSadrzaja << std::endl;
        std::cout << "Tezine predmeta: ";
        for(double d: tezinePredmeta) {
            std::cout << d << " ";
        }
        std::cout << "(kg)\n" << "Vlastita tezina: " << tezina << " (kg)\n";
        std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " (kg)\n";
    }
    Spremnik *DajKopiju() const override{
        return new Sanduk(*this);
    }
};

class Vreca: public Spremnik {
    double tezinaPraha;
    public:
    Vreca(double tezina, std::string naziv, double tezinaPraha) {
        this->tezina = tezina;
        this->nazivSadrzaja = naziv;
        this->tezinaPraha = tezinaPraha;  
    }
    
    double DajTezinu() const override {
        return tezina;
    }
    double DajUkupnuTezinu() const override {
        return tezinaPraha + tezina;
    }
    void Ispisi() const override {
        std::cout << "Vrsta spremnika: Vreca\n" << "Sadrzaj: " << nazivSadrzaja << std::endl;
        std::cout << "Vlastita tezina: " << tezina << " (kg)\n";
        std::cout << "Tezina pohranjene materije: " << tezinaPraha << " (kg)\n";
        std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " (kg)\n";
    }
    Spremnik *DajKopiju() const override{
        return new Vreca(*this);
    }
};

class Bure: public Spremnik {
    double volumen, gustinaTekucine;
    public:
    Bure(double tezina, std::string naziv, double gustinaTekucine, double volumen) {
        this->tezina = tezina;
        this->nazivSadrzaja = naziv;
        this->gustinaTekucine = gustinaTekucine;  
        this->volumen = volumen;  
    }
    
    double DajTezinu() const override {
        return tezina;
    }
    double DajUkupnuTezinu() const override {
        return (gustinaTekucine/1000.) * volumen + tezina; 
    }
    void Ispisi() const override {
        std::cout << "Vrsta spremnika: Bure\n" << "Sadrzaj: " << nazivSadrzaja << std::endl;
        std::cout << "Vlastita tezina: " << tezina << " (kg)\n";
        std::cout << "Specificna tezina tecnosti: " << gustinaTekucine << " (kg/m^3)\n";
        std::cout << "Zapremina tecnosti: " << volumen << " (l)\n";
        std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " (kg)\n";
    }
    Spremnik *DajKopiju() const override{
        return new Bure(*this);
    }
};  

class Skladiste {
    std::vector<std::shared_ptr<Spremnik>> elementi;
    public:
    Skladiste() {
    }
    Skladiste(const Skladiste &s) {
        auto it = s.elementi.begin();
        while(it != s.elementi.end()) {
            elementi.push_back((std::shared_ptr<Spremnik>)(*it)->DajKopiju());
            it++;
        }
    }
    //TODO - FIX ME
    Skladiste(Skladiste &&s) {
        std::swap(elementi, s.elementi);
        s.elementi.resize(0);
    }
    
    Skladiste &operator= (const Skladiste &s) {
        elementi.resize(0); // automatski se brise 
        auto it = s.elementi.begin();
        while(it != s.elementi.end()) {
            if (*it) {
                elementi.push_back( (std::shared_ptr<Spremnik>) (*it)->DajKopiju() );
            } else {
                elementi.push_back(nullptr);
            }
            it++;
        }
        return *this;
    }
    
    Skladiste &operator= (Skladiste &&s) {
        std::swap(elementi, s.elementi); //auto brisanje
        s.elementi.resize(0);
        return *this;
    }
    
    Spremnik *DodajSanduk(double tezina, std::string naziv, std::vector<double> tezinePredmeta) {
        Spremnik *temp = new Sanduk(tezina, naziv, tezinePredmeta);
        elementi.push_back( (std::shared_ptr<Spremnik>) temp);
        return temp;
    }
    
    Spremnik *DodajVrecu(double tezina, std::string naziv, double tezinaPraha) {
        Spremnik *temp = new Vreca(tezina, naziv, tezinaPraha);
        elementi.push_back( (std::shared_ptr<Spremnik>) temp);
        return temp;
    }
    
    Spremnik *DodajBure(double tezina, std::string naziv, double gustinaTekucine, double volumen) {
        Spremnik *temp = new Bure(tezina, naziv, gustinaTekucine, volumen);
        elementi.push_back( (std::shared_ptr<Spremnik>) temp);
        return temp;
    }
    
    Spremnik *DodajSpremnik(Spremnik *p, bool zadrzati) {
        if(zadrzati) {
            std::shared_ptr<Spremnik> temp (p);
            elementi.push_back(temp);
            //elementi.push_back( std::make_shared<std::remove_reference(decltype(*p))> (*p));
        } else {
            elementi.push_back((std::shared_ptr<Spremnik>)(p->DajKopiju()));
            //elementi.push_back((std::shared_ptr<Spremnik>) p->DajKopiju());
        }
        return elementi.at(elementi.size() - 1).get();
    }
    
    void BrisiSpremnik(Spremnik *p) {
        auto it (elementi.begin());
        while(it != elementi.end()) {
            if((*it).get() == p) {
                elementi.erase(it);
                break;
            }
            it++;
        }
    }
    
    Spremnik &DajNajlaksi() {
        if(elementi.size() == 0) {
            throw std::range_error("Skladiste je prazno");
        }
        auto it(elementi.begin());
        double min ((*it)->DajTezinu());
        auto minIterator(it);
        while(it != elementi.end()) {
            if((*it)->DajTezinu() < min) {
                min = (*it)->DajTezinu();
                minIterator = it;
            }
            it++;
        }
        return **minIterator;
    }
    
     
    Spremnik &DajNajtezi() {
        if(elementi.size() == 0) {
            throw std::range_error("Skladiste je prazno");
        }
        auto it(elementi.begin());
        int max ((*it)->DajTezinu());
        auto maxIterator(it);
        while(it != elementi.end()) {
            if((*it)->DajTezinu() > max) {
                max = (*it)->DajTezinu();
                maxIterator = it;
            }
            it++;
        }
        return **maxIterator;
    }
    
    int BrojPreteskih(int value) const {
        int i(0);
        auto it(elementi.begin());
        while(it != elementi.end()) {
            if((*it)->DajUkupnuTezinu() > value) {
                i++;
            }
            it++;
        }
        return i;
    }
    
    void IzlistajSkladiste() const{
        auto temp(elementi);
        std::sort(temp.begin(), temp.end(), [](std::shared_ptr<Spremnik> p1, std::shared_ptr<Spremnik> p2)->bool {
            return p1->DajUkupnuTezinu() > p2->DajUkupnuTezinu();
        });
        for(std::shared_ptr<Spremnik> p: temp) {
            p->Ispisi();
        }
    }
    
    void UcitajIzDatoteke(std::string naziv) {
        elementi.clear();
        std::ifstream input(naziv);
        if(!input) {
            throw std::logic_error("Trazena datoteka ne postoji"); //Datoteka sadrzi besmislene podatke
        }
        
        while(!input.eof()) {
            char c;
            input >> c;
            if(input.eof()) {
                return;
            }
            if(input.bad()) {
                throw std::logic_error("Problemi pri citanju datoteke");
            }
            std::string nazivSadrzaja;
            if(input.peek() != ' ' || input.eof()) {
                throw std::logic_error("Datoteka sadrzi besmislene podatke");
            }
            input.get();
            if(!std::isalpha(input.peek()) || input.eof()) {
                throw std::logic_error("Datoteka sadrzi besmislene podatke");
            } else {
                std::getline(input, nazivSadrzaja);
                //input.get();//'\n
            }
            if(input.eof()) {
                throw std::logic_error("Datoteka sadrzi besmislene podatke");
            }
            switch(c) {
                case 'S': {
                    double tezina;
                    std::vector<double> tezinePredmeta;
                    if(!std::isdigit(input.peek()) || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    input >> tezina;
                    if (input.fail() || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    if(input.bad()) {
                        throw std::logic_error("Problemi pri citanju datoteke");
                    }
                    if(input.peek() == ' ') {
                        input.get();
                    } else {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    int n;
                    if(!std::isdigit(input.peek()) || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    input >> n;
                    if (input.fail() || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    if(input.bad()) {
                        throw std::logic_error("Problemi pri citanju datoteke");
                    }
                    
                    
                    double temp;
                    if(input.peek() == ' ') {
                        input.get();
                    } else {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    if(!std::isdigit(input.peek()) || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    input >> temp;
                    if (input.fail()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    if(input.bad()) {
                        throw std::logic_error("Problemi pri citanju datoteke");
                    }
                    tezinePredmeta.push_back(temp);
                    int i(1);
                    while(input.peek() != '\n' && input.peek() != EOF && i < n) {
                        input >> temp;
                        tezinePredmeta.push_back(temp);
                        if(input.peek() == ' ' ) {
                            input.get();
                        }
                        i++;
                    }
                    if (i != n) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    if(input.peek() == EOF) {
                        input.clear();
                    }
                    if (input.fail()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    if(input.bad()) {
                        throw std::logic_error("Problemi pri citanju datoteke");
                    }
                    elementi.push_back(std::make_shared<Sanduk>(tezina, nazivSadrzaja, tezinePredmeta));
                    break;
                }
                case 'V': {
                    double tezina;
                    if(!std::isdigit(input.peek()) || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    input >> tezina;
                    if (input.fail() || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    if(input.bad()) {
                        throw std::logic_error("Problemi pri citanju datoteke");
                    }
                    if(input.peek() == ' ') {
                        input.get();
                    } else {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    
                    double tezinaPraha;
                    if(!std::isdigit(input.peek()) || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    input >> tezinaPraha;
                    if(input.peek() == EOF) {
                        input.clear();
                    }
                    if (input.fail() || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    if(input.bad()) {
                        throw std::logic_error("Problemi pri citanju datoteke");
                    }
                    if(input.peek() == '\n') {
                        input.get();
                    }
                    elementi.push_back(std::make_shared<Vreca>(tezina, nazivSadrzaja, tezinaPraha));
                    break;
                }
                case 'B': {
                    double tezina;
                    if(!std::isdigit(input.peek()) || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    input >> tezina;
                    if (input.fail() || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    if(input.bad()) {
                        throw std::logic_error("Problemi pri citanju datoteke");
                    }
                    if(input.peek() == ' ') {
                        input.get();
                    } else {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    
                    double gustina;
                    if(!std::isdigit(input.peek()) || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    input >> gustina;
                    if (input.fail() || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    if(input.bad()) {
                        throw std::logic_error("Problemi pri citanju datoteke");
                    }
                    if(input.peek() == ' ') {
                        input.get();
                    } else {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    
                    double volumen;
                    if(!std::isdigit(input.peek()) || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    input >> volumen;
                    if(input.peek() == EOF) {
                        input.clear();
                    }
                    if (input.fail() || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                   
                    if(input.bad()) {
                        throw std::logic_error("Problemi pri citanju datoteke");
                    }
                    if(input.peek() == '\n') {
                        input.get();
                    }
                    elementi.push_back(std::make_shared<Bure>(tezina, nazivSadrzaja, gustina, volumen));
                    break;
                }
                default: {
                    input.close();
                    throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    break;
                }
            }
        }
    }
};

int main ()
{
    Skladiste s;
    try{
        s.UcitajIzDatoteke("ROBA.TXT");
        s.IzlistajSkladiste();
    } catch(std::logic_error e) {
        std::cout<< e.what();
    }
    catch(std::range_error re)
    {
        std::cout << re.what();
    }
    Skladiste s2 (s);
    auto p = s2.DodajSanduk(50, "Voce", {1,3,5,6});
    s2.BrisiSpremnik(p);
    //s.IzlistajSkladiste();
    s2 = std::move(s);
    s.IzlistajSkladiste();
	return 0;
}

//TP 2018/2019: Tutorijal 14, Zadatak 2
#include <iostream>
#include <stdexcept>
#include <vector>
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
    virtual ~Spremnik() {};
    virtual Spremnik *DajKopiju() const = 0;
};

class Sanduk: public Spremnik {
    double tezinaPredmeta;
    double brojPredmeta;
    public:
        Sanduk(double tezina, const std::string naziv, double brojPredmeta, double tezinaPredmeta) {
            this->tezina = tezina;
            this->nazivSadrzaja = naziv;
            this->tezinaPredmeta = tezinaPredmeta;
            this->brojPredmeta = brojPredmeta;
            
        }
        double DajTezinu() const override {
            return tezina;
        }
        double DajUkupnuTezinu() const override {
            double sum(tezina);
            sum += brojPredmeta * tezinaPredmeta;
            return sum;
        }
        void Ispisi() const override {
            std::cout << "Vrsta spremnika: Sanduk\n" << "Sadrzaj: " << nazivSadrzaja << std::endl;
            std::cout << "Vlastita tezina: " << tezina << " kg\n";
            std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " kg\n";
        }
        Spremnik *DajKopiju() const override {
            return new Sanduk(*this);
        }
        
};

class Bure: public Spremnik {
    double tezinaTecnosti;
    public:
    Bure(double tezina, const std::string naziv, double tezinaTecnosti) {
        this->tezina = tezina;
        this->nazivSadrzaja = naziv;
        this->tezinaTecnosti = tezinaTecnosti;
    }
    
    double DajTezinu() const override {
        return tezina;
    }
    double DajUkupnuTezinu() const override {
        return tezina + tezinaTecnosti;
    }
    void Ispisi() const override {
        std::cout << "Vrsta spremnika: Bure\n" << "Sadrzaj: " << nazivSadrzaja << std::endl;
        std::cout << "Vlastita tezina: " << tezina << " kg\n";
        std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " kg\n";
    }
    Spremnik *DajKopiju() const override {
        return new Bure(*this);
    }
};

class Skladiste {
    Spremnik **elementi;
    int alociranih;
    int max;
    public:
    explicit Skladiste(int max) {
        this->max = max;
        elementi = new Spremnik*[max]{};
        alociranih = 0;
    }
    
    ~Skladiste(){
        DealocirajMemoriju();
    }
    void DealocirajMemoriju() {
        for (int i = 0; i < alociranih; i++) {
            delete elementi[i];
        }
        delete[] elementi;
        alociranih = 0;
    }
    Skladiste(const Skladiste &s) {
        this->max = s.max;
        this->alociranih = s.alociranih;
        elementi = new Spremnik*[max]{};
        try{
            for (int i = 0; i < alociranih; i++) {
                elementi[i] = (s.elementi[i])->DajKopiju();
            }
        } catch(...) {
            DealocirajMemoriju();
        }
    }
    
    Skladiste(Skladiste &&s) {
        this->max = s.max;
        this->alociranih = s.alociranih;
        std::swap(elementi, s.elementi);
        s.DealocirajMemoriju();
    }
    
    Skladiste &operator=(const Skladiste &s) {
        for (int i = 0; i < alociranih; i++) {
            delete elementi[i];
        }
        delete[] elementi;
        alociranih = s.alociranih;
        max = s.max;
        try {
            elementi = new Spremnik*[max]{};
            for (int i = 0; i < alociranih; i++) {
                elementi[i] = s.elementi[i]->DajKopiju();
            }
        } catch(...) {
            DealocirajMemoriju();
        }
        return *this;
    } 
    
    
    Skladiste &operator= (Skladiste &&s) {
        this->max = s.max;
        this->alociranih = s.alociranih;
        std::swap(elementi, s.elementi);
        s.DealocirajMemoriju();
        return *this;
    }
    
   void DodajSanduk(double tezina, std::string naziv, double brojPredmeta, double tezinaPredmeta) {
        if(alociranih == max) {
            throw std::domain_error("Popunjeno skladiste");
        }
        elementi[alociranih] = new Sanduk(tezina, naziv, brojPredmeta, tezinaPredmeta);
        alociranih++;
    }
    
    void DodajBure(double tezina, std::string naziv, double tezinaTecnosti) {
        if(alociranih == max) {
            throw std::domain_error("Popunjeno skladiste");
        }
        elementi[alociranih] = new Bure(tezina, naziv, tezinaTecnosti);
        alociranih++;
    }
    
    Spremnik &DajNajlaksi() {
        if(alociranih == 0) {
            throw std::range_error("Skladiste je prazno");
        }
        double min = elementi[0]->DajTezinu();
        Spremnik *it = elementi[0];
        for (int i = 0; i < alociranih; i++) {
            if(elementi[i]->DajTezinu() < min) {
                min = elementi[i]->DajTezinu();
                it = elementi[i];
            }
        }
        return *it;
    }
    
    Spremnik &DajNajtezi() {
        if(alociranih == 0) {
            throw std::range_error("Skladiste je prazno");
        }
        double max = elementi[0]->DajTezinu();
        Spremnik *it = elementi[0];
        for (int i = 0; i < alociranih; i++) {
            if(elementi[i]->DajTezinu() > max) {
                max = elementi[i]->DajTezinu();
                it = elementi[i];
            }
        }
        return *it;
    }
    
    int BrojPreteskih(int value) const {
        int n(0);
        for (int i = 0; i < alociranih; i++) {
            if(elementi[i]->DajUkupnuTezinu() > value) {
                n++;
            }
            /* code */
        }
        return n;
    }
    
    void IzlistajSkladiste() const{
        std::vector<Spremnik*> temp;
        for(int i = 0; i< alociranih; i++) {
            temp.push_back(elementi[i]);
        }
        
        std::sort(temp.begin(), temp.end(), [](Spremnik *p1, Spremnik* p2) -> bool {
            return p1->DajUkupnuTezinu() > p2->DajUkupnuTezinu();
        });
        for (int i = 0; i < alociranih; i++) {
            temp[i]->Ispisi();
        }
    }
    
    void UcitajIzDatoteke(std::string naziv) {
        for (int i = 0; i < alociranih; i++) {
            delete elementi[i];
        }
        alociranih = 0;
        std::ifstream input(naziv);
        if(!input) {
            throw std::logic_error("Trazena datoteka ne postoji");
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
            }
            if(input.eof()) {
                throw std::logic_error("Datoteka sadrzi besmislene podatke");
            }
            switch(c) {
                case 'S': {
                    double tezina;
                    if(!std::isdigit(input.peek()) || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    input >> tezina;
                    if(input.fail() || input.eof()) {
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
                    int br;
                    if(!std::isdigit(input.peek()) || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    input >> br;
                    if(input.fail() || input.eof()) {
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
                    double t;
                    if(!std::isdigit(input.peek()) || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    input >> t;
                    if(input.peek() == EOF) {
                        input.clear();
                    }
                    if(input.fail()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    if(input.bad()) {
                        throw std::logic_error("Problemi pri citanju datoteke");
                    }
                    if(input.peek() != EOF && input.peek() != '\n') {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    //max++;
                    DodajSanduk(tezina, nazivSadrzaja, br, t);
                    break;    
                }
                case 'B': {
                    double tezina, tecnost;
                    if(!std::isdigit(input.peek()) || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    input >> tezina;
                    if(input.fail() || input.eof()) {
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
                    if(!std::isdigit(input.peek()) || input.eof()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    input >> tecnost;
                    if(input.peek() == EOF) {
                        input.clear();
                    }
                    if(input.fail()) {
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                    if(input.bad()) {
                        throw std::logic_error("Problemi pri citanju datoteke");
                    }
                    if(input.peek() == '\n') {
                        input.get();
                    }
                    //max++;
                    DodajBure(tezina, nazivSadrzaja, tecnost);
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
    Skladiste s (10);
    try{
        s.UcitajIzDatoteke("ROBA.TXT");
        s.IzlistajSkladiste();
    } catch(std::logic_error e) {
        std::cout << e.what();
    }
    catch(std::range_error r) {
        std::cout << r.what();
    }
    Skladiste s2 (s);
    std::cout << "------S2--------" << std::endl;
    s2.IzlistajSkladiste();
    s2 = std::move(s);
    std::cout<< "---NEMA ISPISA---" << std::endl;
    s.IzlistajSkladiste();
	return 0;
}
//TP 2018/2019: Zadaća 5, Zadatak 4
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>

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


class PolimorfniSpremnik {
    Spremnik *spremnik;
    public:
    PolimorfniSpremnik(){
        spremnik = nullptr;
    }
    ~PolimorfniSpremnik() {
        delete spremnik;
    }
    
    PolimorfniSpremnik(const Spremnik &s): spremnik(s.DajKopiju()) {
    }
    PolimorfniSpremnik(const PolimorfniSpremnik &p) {
        if(p.spremnik) {
            spremnik = (p.spremnik)->DajKopiju();
        } else {
            spremnik = nullptr;
        }
    }
    
    PolimorfniSpremnik(PolimorfniSpremnik &&p) {
        this->spremnik = p.spremnik;
        p.spremnik = nullptr;
    }
    
    PolimorfniSpremnik &operator=(const PolimorfniSpremnik &p) {
        delete spremnik;
        if(p.spremnik) {
            spremnik = (p.spremnik)->DajKopiju();
        } else {
            spremnik = nullptr;
        }
        return *this;
    }
    
    PolimorfniSpremnik &operator=(PolimorfniSpremnik &&p) {
        std::swap(spremnik, p.spremnik);
        return *this;
    }
    
    double DajTezinu() const {
        if(!spremnik) {
            throw std::logic_error("Nespecificiran spremnik");
        }
        return spremnik->DajTezinu();
    }
    double DajUkupnuTezinu() const {
        if(!spremnik) {
            throw std::logic_error("Nespecificiran spremnik");
        }
        return spremnik->DajUkupnuTezinu();
    }
    void Ispisi() const {
        if(!spremnik) {
            throw std::logic_error("Nespecificiran spremnik");
        }
        spremnik->Ispisi();
    }
};



int main ()
{
    try
    {
        PolimorfniSpremnik s1(Bure(20,"Red Bull", 800, 150));
        PolimorfniSpremnik s2(s1);
        PolimorfniSpremnik s3;
        s3=s2;
        s3.Ispisi();
    }
    catch(std::logic_error le)
    {
        std::cout << le.what();
    }
	return 0;
}

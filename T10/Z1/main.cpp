//TP 2018/2019: ZSR 1, Zadatak 5
#include <iostream>
#include <stdexcept>

class StedniRacun {
    double stanje_racuna;
public:
    StedniRacun(double pocetnaVrijednost) {
        if (pocetnaVrijednost < 0) {
            throw std::logic_error("Nedozvoljeno pocetno stanje");
        }
        stanje_racuna = pocetnaVrijednost;
    }
    
    StedniRacun() {
        stanje_racuna = 0;
    }
    
    void Ulozi(double value) {
        if ((value + stanje_racuna) <= 0) {
            throw std::logic_error("Transakcija odbijena");
        } else {
            stanje_racuna += value;
        }
    }
    
    void Podigni(double value) {
        if (value > stanje_racuna) {
            throw std::logic_error("Transakcija odbijena");
        } else {
            stanje_racuna -= value;
        }
    }
    
    double DajStanje() const {
        return stanje_racuna;
    }
    
    void ObracunajKamatu (double kamatnaStopa) {
        if (kamatnaStopa < 0) {
            throw std::logic_error("Nedozvoljena kamatna stopa");
        } 
        stanje_racuna += stanje_racuna * (kamatnaStopa / 100);
    }
};

int main ()
{
    StedniRacun s (0);
    s.Ulozi(25000);
    std::cout << "Stanje:" << s.DajStanje() << std::endl;
    s.Podigni(3000);
    std::cout << "Stanje:" << s.DajStanje() << std::endl;
    s.ObracunajKamatu(20);
    std::cout << "Stanje uvecano za 20%:" << s.DajStanje() << std::endl;
	return 0;
}
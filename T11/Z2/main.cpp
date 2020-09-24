//TP 2018/2019: ZSR 1, Zadatak 5
#include <iostream>
#include <stdexcept>



class StedniRacun {
    double stanje_racuna;
    static int brojAktivnih;
    static int brojKreiranih;
public:
    StedniRacun(double pocetnaVrijednost) {
        if (pocetnaVrijednost < 0) {
            throw std::logic_error("Nedozvoljeno pocetno stanje");
        }
        stanje_racuna = pocetnaVrijednost;
         brojAktivnih++;
         brojKreiranih++;
    }
    
    //destruktor smanjuje broj aktivnih, ali ne i broj kreiranih
    ~StedniRacun() {
    	brojAktivnih--;
    }
    
    StedniRacun() {
        stanje_racuna = 0;
        brojAktivnih++;
        brojKreiranih++;
    }
    
    StedniRacun(const StedniRacun &s) {
        stanje_racuna = s.DajStanje();
        brojAktivnih++;
        brojKreiranih++;
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
    
    static int DajBrojKreiranih(){
        return brojKreiranih;
    }
    
    static int DajBrojAktivnih(){
        return brojAktivnih;
    }
};
int StedniRacun::brojAktivnih = 0;
int StedniRacun::brojKreiranih = 0;

int main ()
{
    //pozivamo kosntruktor koji potavlja stanje na nula
    StedniRacun s (0);
    //pozivamo metodu koja povecava stanje racuna za 25000
    s.Ulozi(25000);
    //ispisujemo stanje pomuce gettera
    std::cout << "Stanje:" << s.DajStanje() << std::endl;
    //smanjujemo vrijednost racuna pozivom metode podigni
    s.Podigni(3000);
    std::cout << "Stanje:" << s.DajStanje() << std::endl;
    //povecavamo kamatu za 20%
    s.ObracunajKamatu(20);
    std::cout << "Stanje uvecano za 20%:" << s.DajStanje() << std::endl;
	return 0;
}
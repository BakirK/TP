//TP 2018/2019: Zadaća 5, Zadatak 6
#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <new>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cctype>
#include <functional>
#include <vector>

template <typename TipElemenata>
class DatotecniKontejner {
    std::fstream tok;
public:
    DatotecniKontejner(const std::string &ime_datoteke) {
        tok.open(ime_datoteke, std::ios::out | std::ios::binary | std::ios::trunc);
        tok.close();
        tok.open(ime_datoteke, std::ios::in | std::ios::out | std::ios::binary);
        if(!tok) {
            throw std::logic_error("Problemi prilikom otvaranja ili kreiranja datoteke");
        }
    }
    void DodajNoviElement(const TipElemenata &element) {
                //1?
        tok.seekp(0, std::ios::end);
        tok.write(reinterpret_cast<const char*>(&element), sizeof(element));
        if(!tok) {
            throw std::logic_error("Problemi prilikom otvaranja ili kreiranja datoteke");
        }
        tok.flush();
    }
    int DajBrojElemenata() {
        tok.flush();
        if(!tok) {
            throw std::logic_error("Probemi prilikom pristupa datoteci”");
        }
        tok.seekg(0, std::ios::end);
        //tok.seekg(-1, std::ios::end);
        int duzina = tok.tellg();
        return  duzina / sizeof(TipElemenata);
    }
    TipElemenata DajElement(int pozicija) {
        if(!tok) {
            throw std::logic_error("Probemi prilikom pristupa datoteci”");
        }
        if(pozicija >= DajBrojElemenata() || pozicija < 0) {
             throw std::range_error("Neispravna pozicija");
        }
        tok.seekg(0);
        tok.seekg(pozicija * sizeof(TipElemenata));
        TipElemenata temp;
        tok.read(reinterpret_cast<char*>(&temp), sizeof(TipElemenata));
        return temp;
    }
    void IzmijeniElement(int pozicija, const TipElemenata &element) {
        if(!tok) {
            throw std::logic_error("Probemi prilikom pristupa datoteci”");
        }
        if(pozicija >= DajBrojElemenata() || pozicija < 0) {
             throw std::range_error("Neispravna pozicija");
        }
        tok.seekg(0);
        tok.seekg(pozicija * sizeof(TipElemenata));
        tok.write(reinterpret_cast<const char*>(&element), sizeof(TipElemenata));
    }
    void Sortiraj(std::function<bool(const TipElemenata &, const TipElemenata &)> kriterij = std::less<TipElemenata>()) {
        tok.seekg(0);
        if(!tok) {
            throw std::logic_error("Probemi prilikom pristupa datoteci”");
        }
        int duzina = DajBrojElemenata();
        TipElemenata temp1, temp2;
        for (int i = 0; i < duzina; i++) {
            tok.seekg(0);
            for(int j = 0; j < duzina - 1; j++) {
                tok.read(reinterpret_cast<char*>(&temp1), sizeof(TipElemenata));
                if(!tok) {
                    throw std::logic_error("Probemi prilikom pristupa datoteci”");
                }
                tok.read(reinterpret_cast<char*>(&temp2), sizeof(TipElemenata));
                if(!tok) {
                    throw std::logic_error("Probemi prilikom pristupa datoteci”");
                }
                tok.seekg(-int(sizeof(TipElemenata)), std::ios::cur);
                //std::cout << "Temp1: " << temp1 << " Temp2: " << temp2 << std::endl;
                if(!kriterij(temp1, temp2)) {
                    tok.seekp(int(tok.tellg()) - int(sizeof(TipElemenata)));
                    tok.write(reinterpret_cast<char*>(&temp2), sizeof(TipElemenata));
                    if(!tok) {
                        throw std::logic_error("Probemi prilikom pristupa datoteci”");
                    }
                    tok.write(reinterpret_cast<char*>(&temp1), sizeof(TipElemenata));
                    if(!tok) {
                        throw std::logic_error("Probemi prilikom pristupa datoteci”");
                    }
                    tok.seekp(int(tok.tellp()) - sizeof(TipElemenata));
                    tok.seekg(tok.tellp());
                }
            }
        }
        tok.flush();
    }
        
        
};

int main ()
{
  
        DatotecniKontejner<double> dk1("ime14.DAT");
        std::vector<double> v{2.8,1.2,3,4,5.6};
        for(int i=0 ; i < v.size(); i++)
            dk1.DodajNoviElement(v[i]);
        std::cout<<"Sortiran niz: ";
        dk1.Sortiraj();
        for(int i=0 ; i < v.size(); i++)
            std::cout<<dk1.DajElement(i)<<" ";
	return 0;
}
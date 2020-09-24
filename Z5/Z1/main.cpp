//TP 2018/2019: Zadaća 5, Zadatak 1
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
#include <algorithm>
#include <string>
#include <deque>
#include <list>

template <typename TipEl, template <typename...> class Kontejner = std::vector>
class Tok {
    Kontejner<TipEl> kolekcija;
    public:
    template <typename TipEl2, template <typename...> class Kontejner2>
    friend class Tok; // Stvara prijateljstvo između različitih vrsta tokova
    
    template <typename IterTip>
    Tok(IterTip pocetak, const IterTip iza_kraja) {
        while(pocetak != iza_kraja) {
            kolekcija.insert(kolekcija.end(), *pocetak);
            pocetak++;
        }
    }
    
    template <typename IterabilniKontejner>
    Tok(const IterabilniKontejner &kontejner) {
        auto it (std::begin(kontejner));
        while(it != std::end(kontejner)) {
            kolekcija.insert(kolekcija.end(), *it);
            it++;
        }
    }
    
    Tok(std::initializer_list<TipEl> lista) {
        auto it (lista.begin());
        while(it != lista.end()) {
            kolekcija.insert(kolekcija.end(), *it);
            it++;
        }
    }
    static Tok<TipEl, Kontejner> Opseg(TipEl poc, TipEl kraj, TipEl korak = 1) {
        Kontejner<TipEl> kolekcijaTemp{};
        while(poc + korak <= kraj) {
            kolekcijaTemp.insert(kolekcijaTemp.end(), poc);
            poc += korak;
        }
        kolekcijaTemp.insert(kolekcijaTemp.end(), poc);
        return kolekcijaTemp;
    }
    
    unsigned int Velicina() const {
        auto temp = kolekcija.begin();
        int n(0);
        while(temp != kolekcija.end()) {
            n++;
            temp++;
        }
        return n;
    }
    bool Prazan() const {
        auto temp = kolekcija.begin();
        int n(0);
        while(temp != kolekcija.end()) {
            n++;
            temp++;
        }
        return !n;
    }
    Tok<TipEl, Kontejner> Limitiraj(unsigned int n) const {
        auto temp = kolekcija.begin();
        int size = DajVelicinu();
        if(n >= size) {
            return kolekcija;
        }
        int i(0);
        Kontejner<TipEl> kolekcijaTemp;
        auto it = kolekcija.begin();
        while(i < n) {
            kolekcijaTemp.insert(kolekcijaTemp.end(), *it);
            it++;
            i++;
        }
        return kolekcijaTemp;
    }
    
    Tok<TipEl, Kontejner> Preskoci(unsigned int n) const {
        Kontejner<TipEl> kolekcijaTemp;
        auto it = kolekcija.begin();
        int i(0);
        while(i < n && it != kolekcija.end()) {
            it++;
            i++;
        }
        while(it != kolekcija.end()) {
            kolekcijaTemp.insert(kolekcijaTemp.end(), *it);
            it++;
        }
        return kolekcijaTemp;
    }
    
    Tok<TipEl, Kontejner> Obrnut() const {
        Kontejner<TipEl> kolekcijaTemp;
        int vel = DajVelicinu();
        int temp = vel - 1;
        int i(0);
        while(i < vel) {
            int n(0);
            auto it = kolekcija.begin();
            while(n < temp) {
                n++;
                it++;
            }
            kolekcijaTemp.insert(kolekcijaTemp.end(), *it);
            temp--;
            i++;
        }
        
        return Tok<TipEl, Kontejner>(kolekcijaTemp);
    }
    
    Tok<TipEl, Kontejner> Akcija(std::function<void(void)> akcija) const {
        akcija();
        return kolekcija;
    }
    
    void ZaSvaki(std::function<void(TipEl)> akcija) const {
        auto it = kolekcija.begin();
        while(it != kolekcija.end()) {
           akcija(*it);
            it++;
        }
    }
    
    Tok<TipEl, Kontejner> Filtriraj(std::function<bool(TipEl)> predikat) const {
        Kontejner<TipEl> kolekcijaTemp;
        auto it = kolekcija.begin();
        while(it != kolekcija.end()) {
           if(predikat(*it)) {
               kolekcijaTemp.insert(kolekcijaTemp.end(), *it);
            }
            it++;
        }
        return kolekcijaTemp;
    }
    
    int DajVelicinu() const {
        auto temp = kolekcija.begin();
        int size(0);
        while(temp != kolekcija.end()) {
            size++;
            temp++;
        }
        return size;
    }
    
    TipEl PronadjiPrvi() const {
        int size = DajVelicinu();
        if (size == 0) {
            throw std::logic_error("Tok je prazan");
        }
        return *(kolekcija.begin());
    }
    
    TipEl PronadjiPosljednji() const {
        auto temp = kolekcija.begin();
        int size = DajVelicinu();
        if (size == 0) {
            throw std::logic_error("Tok je prazan");
        }
        std::advance(temp, size-1);
        return *temp;
    }
    
    bool ZadovoljavaBaremJedan(std::function<bool(TipEl)> kriterij) const {
        auto it = kolekcija.begin();
        while(it != kolekcija.end()) {
           if(kriterij(*it)) {
                return true;
            }
            it++;
        }
        return false;
    }
    
    bool ZadovoljavaNijedan(std::function<bool(TipEl)> kriterij) const {
        auto it = kolekcija.begin();
        while(it != kolekcija.end()) {
           if(kriterij(*it)) {
                return false;
            }
            it++;
        }
        return true;
    }
    bool ZadovoljavajuSvi(std::function<bool(TipEl)> kriterij) const {
        auto it = kolekcija.begin();
        while(it != kolekcija.end()) {
           if(!kriterij(*it)) {
                return false;
            }
            it++;
        }
        return true;
    }
    //TODO
    TipEl Akumuliraj(TipEl inicijalna, std::function<TipEl(TipEl, TipEl)> akumulator) const {
        int n = DajVelicinu();
        if (!n) {
            return inicijalna;
        }
        auto pocetak = kolekcija.begin();
        TipEl vracena = akumulator(inicijalna, *pocetak);
        pocetak++;
        while(pocetak != kolekcija.end()) {
            vracena = akumulator(vracena, *pocetak);
            pocetak++;
        }
        return vracena;
    }
    TipEl Akumuliraj(std::function<TipEl(TipEl, TipEl)> akumulator) {
        int n = DajVelicinu();
        if (n <= 1) {
            throw std::logic_error("Tok je prazan");
        }
        auto pocetak = kolekcija.begin();
        auto temp = kolekcija.begin();
        pocetak++;
        TipEl vracena = akumulator(*temp, *pocetak);
        pocetak++;
        while(pocetak != kolekcija.end()) {
            vracena = akumulator(vracena, *pocetak);
            pocetak++;
        }
        return vracena;
    }
    
    
    Tok<TipEl, Kontejner> Sortirano(std::function<bool(TipEl, TipEl)> komparator = [](TipEl x, TipEl y) { return x < y; }) const {
        Kontejner<TipEl> kolekcijaTemp;
        auto it = kolekcija.begin();
        while(it != kolekcija.end()) {
            kolekcijaTemp.insert(kolekcijaTemp.end(), *it);
            it++;
        }
        it = kolekcijaTemp.begin();
        std::advance(it, DajVelicinu()-1);
        //rucno sortiranje ako je container lista iako u zadatku pise da treba sort koristit? - sort je ispod zakomentarisan
        for (int i = 0; i < DajVelicinu(); i++) {
            auto it2 = kolekcijaTemp.begin();
            while(it2 != it) {
                auto it3 = it2;
                it3++;
                if(!komparator(*it2, *it3)) {
                    TipEl temp = *it2;
                    *it2 = *it3;
                    *it3 = temp;
                }
                it2++;
            }
        }
        //std::sort(kolekcijaTemp.begin(), kolekcijaTemp.end(), komparator);
        return kolekcijaTemp;
    }
    Tok<TipEl, Kontejner> Unikatno(std::function<bool(TipEl, TipEl)> komparator = [](TipEl x, TipEl y) { return x == y; }) const {
        Kontejner<TipEl> kolekcijaTemp;
        auto it = kolekcija.begin();
        while(it != kolekcija.end()) {
            bool set(true);
            auto it2 = kolekcijaTemp.begin();
            while(it2 != kolekcijaTemp.end()) {
                if(komparator(*it, *it2)) {
                    set = false;
                    break;
                }
                it2++;
            }
            if(set) {
                kolekcijaTemp.insert(kolekcijaTemp.end(), *it);
            }
            it++;
        }
        return kolekcijaTemp;
    }
    
    Tok<TipEl, Kontejner> Proviri(std::function<void(TipEl)> akcija) const {
        ZaSvaki(akcija);
        return *this;
    }
    
    TipEl Minimalan(std::function<bool(TipEl, TipEl)> komparator = [](TipEl x, TipEl y) { return x < y; }) const {
        int size = DajVelicinu();
        if (size == 0) {
            throw std::logic_error("Tok je prazan");
        }
        auto it = kolekcija.begin();
        TipEl min = *(kolekcija.begin());
        while(it != kolekcija.end()) {
            if(komparator(*it, min)) {
                min = *it;
            }
            it++;
        }
        return min;
    }
    
    TipEl Maksimalan(std::function<bool(TipEl, TipEl)> komparator = [](TipEl x, TipEl y) { return x > y; }) const {
        int size = DajVelicinu();
        if (size == 0) {
            throw std::logic_error("Tok je prazan");
        }
        auto it = kolekcija.begin();
        TipEl max = *(kolekcija.begin());
        while(it != kolekcija.end()) {
            if(komparator(*it, max)) {
                max = *it;
            }
            it++;
        }
        return max;
    }
    
    template <typename Kont2>
    Kont2 Sakupi(std::function<void(Kont2 &, TipEl)> kombinator) const {
        Kont2 container;
        auto it = kolekcija.begin();
        while(it != kolekcija.end()) {
            kombinator(container, *it);
            it++;
        }
        return container;
    }
    
    template <typename TipEl2>
    Tok<TipEl2, Kontejner> Mapiraj(std::function<TipEl2(TipEl)> maper) const {
        Tok<TipEl2, Kontejner> kolekcijaTemp{};
        auto it = kolekcija.begin();
        while(it != kolekcija.end()) {
            kolekcijaTemp.kolekcija.insert(kolekcijaTemp.kolekcija.end(), maper(*it));
            it++;
        }
        return kolekcijaTemp;
    }
    
    template <typename TipEl2>
    Tok<TipEl2, Kontejner> MapirajPoravnato(std::function<Tok<TipEl2, Kontejner>(TipEl)> maper) const {
        
        Tok<TipEl2, Kontejner> kolekcijaTemp({});
        auto it = kolekcija.begin();
        while(it != kolekcija.end()) {
            Tok<TipEl2, Kontejner> maperTemp = maper(*it);
             auto it2 = maperTemp.kolekcija.begin();
                while(it2 != maperTemp.kolekcija.end()) {
                 kolekcijaTemp.kolekcija.insert(kolekcijaTemp.kolekcija.end(), *it2);
                 it2++;
             }
            it++;
        }
        return kolekcijaTemp;
    }
    
};

int main ()
{
    if(Tok<int>{4, 3, 6}.ZadovoljavaNijedan([](int el) { return el % 2 == 1;})) {
        std::cout << "a" << std::endl;
    }
    int zadnji = Tok<int>{4, 3, 6}.PronadjiPosljednji();
    std::cout << zadnji << std::endl;
    Tok<double>{2.2, 2.2, 1.1, 0.1, 5.5, 4.8}.Sortirano().Obrnut().Preskoci(2).Unikatno().ZaSvaki([](const double &d) { std::cout << d << " "; });
    std::cout << std::endl;
    Tok<int>::Opseg(10, 200, 2).Filtriraj([](int el) { return el % 10 == 0; }).ZaSvaki([](const double &d) { std::cout << d << " "; });
	return 0;
}
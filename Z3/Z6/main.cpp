//TP 2018/2019: Zadaća 3, Zadatak 4
#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <ctype.h>
#include <stdexcept>
#include <memory>

struct Dijete {
    std::string ime;
    std::shared_ptr<Dijete> sljedeci;
};

std::shared_ptr<Dijete> KreirajPovezanuListu(const std::vector<std::string> &djeca)
{
    std::shared_ptr<Dijete> pocetak (nullptr), prethodni;
    int i(0);
    while (i < djeca.size()) {
        std::shared_ptr<Dijete> novi (new Dijete {djeca.at(i), nullptr});
        if (!pocetak) {
            pocetak = novi;
        } else {
            prethodni->sljedeci = novi;
        }
        prethodni = novi;
        i++;
    }
    return pocetak;

}

int duzinaImena(std::string s)
{
    auto it (s.begin());
    int brojac(0);
    while (it != s.end()) {
        if((std::isalpha(*it) || (*it >= '0' && *it <= '9')) && *it != ' ') {
            brojac++;
        }
        it++;
    }
    return brojac;
}

void advance(std::shared_ptr<Dijete> &pocetak, std::shared_ptr<Dijete> &d, int brojMjesta)
{
    if (!pocetak) {
        std::cout << "pocetak je nullptr u advance";
        return;
    }
    if (!d) {
        std::cout << "d je nullptr u advance";
        return;
    }
    int i(0);
    while (i < brojMjesta) {
        if (d->sljedeci == nullptr) {
            d = pocetak;
        } else {
            d = d->sljedeci;
        }
        i++;
    }
}


std::shared_ptr<Dijete> erase(std::shared_ptr<Dijete> &d, std::shared_ptr<Dijete> &pocetak)
{
     if (!pocetak) {
        std::cout << "pocetak je nullptr u erase";
        return nullptr;
    }
     if (!d) {
        std::cout << "d je nullptr u erase";
        return nullptr;
    }
    if (d == pocetak) {
        std::shared_ptr<Dijete> temp(pocetak);
        pocetak = pocetak -> sljedeci;
        temp = nullptr;
        return pocetak;
    }
    
    std::shared_ptr<Dijete> previous(pocetak);
    std::shared_ptr<Dijete> next(pocetak->sljedeci);
    while (next != nullptr && next != d) {
        next = next->sljedeci;
        previous = previous->sljedeci;
    }
    previous->sljedeci = d->sljedeci;
    d = d->sljedeci;
    if (!d) {
        d = pocetak;
    }
    next = nullptr;
    return d;
}


void unesi(std::vector<std::set<std::string>> &timovi, int timoviBroj, int brojClanova,
            std::shared_ptr<Dijete> &it, std::shared_ptr<Dijete> &lanac) {
                
    for (int i = 0; i < timoviBroj; i++) {
        std::set<std::string> tim;
        for (int j = 0; j < brojClanova; j++) {
            tim.insert(it -> ime);
            int duzina (duzinaImena(it -> ime));
            it = erase(it, lanac);
            if (!it) {
                if (lanac == nullptr) {
                    //std::cout << i << " " << j << " lanac2 je nullptr" << std::endl;
                    break;
                }
                else {
                   it = lanac;
                    advance(lanac, it, duzina - 2); 
                }
            } else {
                advance(lanac, it, duzina - 1);
            }
        }
        timovi.push_back(tim);
    }
}


std::vector<std::set<std::string>> Razvrstavanje (const std::vector<std::string> &djeca, int brojTimova)
{
    std::vector<std::set<std::string>> timovi;
    if (brojTimova < 1 || djeca.size() < brojTimova) {
        throw std::logic_error("Razvrstavanje nemoguce");
    }
    std::shared_ptr<Dijete> lanac (KreirajPovezanuListu(djeca));
    std::shared_ptr<Dijete> it (lanac);
    int veciTimovi (djeca.size() % brojTimova);
    int brojClanova (djeca.size() / brojTimova);
    unesi(timovi, veciTimovi, brojClanova + 1, it, lanac);
    int manjiTimovi (brojTimova - veciTimovi);
    unesi(timovi, manjiTimovi, brojClanova, it, lanac);
    return timovi;
}




int main ()
{
    std::cout << "Unesite broj djece: ";
    int brojDjece;
    std::cin >> brojDjece;
    std::cout << "Unesite imena djece: " << std::endl;
    int i(0);
    std::vector<std::string> djeca;
    std::cin.ignore(1, '\n');
    while (i < brojDjece) {
        std::string temp;
        std::getline(std::cin, temp);
        djeca.push_back(temp);
        i++;
    }
    std::cout << "Unesite broj timova: ";
    int brojTimova;
    std::cin >> brojTimova;
    try {
        std::vector<std::set<std::string>> timovi (Razvrstavanje(djeca, brojTimova));
        for (int i(0); i < timovi.size(); i++) {
            std::cout << "Tim " << i + 1 << ": ";
            int j(0);
            int n(timovi.at(i).size());
            for(std::string ime: timovi.at(i)) {
                if (j == n - 1) {
                    std::cout << ime;
                } else {
                    std::cout << ime << ", ";
                }
                j++;
            }
            std::cout << std::endl;
        }
    } catch (std::logic_error belaj) {
        std::cout << "Izuzetak: " << belaj.what();
    }
    return 0;
}

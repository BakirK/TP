//TP 2018/2019: Zadaća 3, Zadatak 4
#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <ctype.h>
#include <stdexcept>

int duzinaImena(const std::string &s)
{
    auto it (s.begin());
    int brojac(0);
    while (it!= s.end()) {
        if((std::isalpha(*it) || (*it >= '0' && *it <= '9')) && *it != ' ') {
            brojac++;
        }
        it++;
    }
    return brojac;
}


void advance(std::list<std::string> &lista, std::list<std::string>::iterator &it, int brojMjesta)
{
    int i(0);
    while (i < brojMjesta) {
        if (it == lista.end()) {
            it = lista.begin();
        }
        it++;
        if (it == lista.end()) {
            it = lista.begin();
        }
        i++;
    }

}


std::vector<std::set<std::string>> Razvrstavanje (const std::vector<std::string> &djeca, int brojTimova)
{
    std::vector<std::set<std::string>> timovi;
    if (brojTimova < 1 || djeca.size() < brojTimova) {
        throw std::logic_error("Razvrstavanje nemoguce");
    }
    std::list<std::string> lanac;
    auto itCopy (djeca.begin());
    while (itCopy != djeca.end()) {
        lanac.push_back(*itCopy);
        itCopy++;
    }
    auto it = lanac.begin();
    int veciTimovi (djeca.size() % brojTimova);
    int brojClanova (djeca.size() / brojTimova);


    for (int i = 0; i < veciTimovi; i++) {
        std::set<std::string> tim;
        for (int j = 0; j < brojClanova + 1; j++) {
            tim.insert(*it);
            int duzina (duzinaImena(*it));
            it = lanac.erase (it);
            advance(lanac, it, duzina - 1);
        }
        timovi.push_back(tim);
    }

    int manjiTimovi (brojTimova - veciTimovi);
    for (int i = 0; i < manjiTimovi; i++) {
        std::set<std::string> tim;
        for (int j = 0; j < brojClanova; j++) {
            tim.insert(*it);
            int duzina (duzinaImena(*it));
            it = lanac.erase (it);
            advance(lanac, it, duzina - 1);
        }
        timovi.push_back(tim);
    }
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

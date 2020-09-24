//TP 2018/2019: Zadaća 3, Zadatak 2
#include <iostream>
#include <set>
#include <map>
#include <string>
#include <stdexcept>

std::string toUpperSting (std::string &a)
{
    for (int i(0); i < a.size(); i++) {
        if (a.at(i) >= 'a' && a.at(i) <= 'z') {
            a.at(i) -= 'a' - 'A';
        }
    }
    return a;
}

std::string toLowerSting (std::string &a)
{
    for (int i(0); i < a.size(); i++) {
        if (a.at(i) >= 'A' && a.at(i) <= 'Z') {
            a.at(i) += 'a' - 'A';
        }
    }
    return a;
}

bool jeRazmak(char c)
{
    return !((c >= 'a' && c <= 'z')  || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}



std::map<std::string, std::set<int>> KreirajIndeksPojmova (std::string s)
{
    std::map<std::string, std::set<int>> povratna;
    auto pocetak (s.begin());
    std::string temp;
    int brojac(0);
    while(pocetak != s.end()) {
        if (jeRazmak(*pocetak)) {
            if (!temp.empty()) {
                povratna[toLowerSting(temp)].insert(brojac);
            }
            brojac = pocetak - s.begin() + 1;
            temp.clear();
        } else {
            temp += *pocetak;
        }
        pocetak++;
    }
    if (!temp.empty()) {
        povratna[toLowerSting(temp)].insert(brojac);
    }
    return povratna;
}


std::set<int> PretraziIndeksPojmova(std::string s, std::map<std::string, std::set<int>> pojmovi)
{
    auto it (pojmovi.find(toLowerSting(s)));
    if (it == pojmovi.end()) {
        throw std::logic_error("Unesena rijec nije nadjena!");
    } else {
        return it->second;
    }
}

void IspisiIndeksPojmova (std::map<std::string, std::set<int>> pojmovi)
{
    auto it (pojmovi.begin());
    while (it != pojmovi.end()) {
        std::cout << it->first << ": ";
        auto itSkup (it->second.begin());
        int i(1);
        while (itSkup != it->second.end()) {
            if (i == it->second.size()) {
                std::cout << *itSkup;
            } else {
                std::cout << *itSkup << ",";
            }
            i++;
            itSkup++;
        }
        it++;
        std::cout << std::endl;
    }
}

int main ()
{
    std::cout << "Unesite tekst: ";
    std::string s;
    std::getline(std::cin, s);
    std::map<std::string, std::set<int>> pojmovi (KreirajIndeksPojmova(s));
    IspisiIndeksPojmova(pojmovi);
    s.clear();
    while (true) {
        std::cout << "Unesite rijec: ";
        std::getline(std::cin, s);
        if (s == ".") {
            break;
        }
        try {
            std::set<int> temp (PretraziIndeksPojmova(s, pojmovi));
            auto it (temp.begin());
            while (it != temp.end()) {
                std::cout << *it << " ";
                it++;
            }
            std::cout << std::endl;
        } catch (std::logic_error belaj) {
            std::cout << belaj.what() << std::endl;
        }
    }
    return 0;
}

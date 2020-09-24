//TP 2018/2019: Tutorijal 8, Zadatak 4
#include <iostream>
#include <algorithm>
#include <map>

std::string ZamijeniPremaRjecniku(std::string s, std::map<std::string, std::string> mapa)
{
    std::string povratna;
    std::string temp;
    auto pocetak = s.begin();
    while(pocetak != s.end()) {
        if (*pocetak == ' ') {
            if (!temp.empty()) {
                auto it = mapa.find(temp);
                if (it == mapa.end()) {
                    povratna += temp;
                } else {
                    povratna += it->second;
                }
            }
            povratna += *pocetak;
            temp.clear();
        } else {
            temp += *pocetak;
        }
        pocetak++;
    }
    if (!temp.empty()) {
        auto it = mapa.find(temp);
        if (it == mapa.end()) {
            povratna += temp;
        } else {
            povratna += it->second;
        }
    }
    return povratna;
}


int main ()
{
    return 0;
}

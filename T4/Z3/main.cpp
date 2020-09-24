/* TP, 2017/2018, Tutorijal 4, Zadatak 3 */
#include <iostream>
#include <vector>
#include <cctype>
#include <boost/algorithm/string.hpp>
#include <string>



void IzdvojiKrajnjeRijeci (std::vector<std::string> rijeci, std::string &min, std::string &max) {
    if (rijeci.size() == 0 ) {
        min = ' ';
        max = ' ';
    }
    else {
        min = rijeci.at(0);
        max = rijeci.at(0);
        for (int i = 1; i < rijeci.size(); i++) {
            if (boost::to_upper_copy<std::string>(rijeci.at(i)) > boost::to_upper_copy<std::string>(max)) {
                max = rijeci.at(i);
            }
            if (boost::to_upper_copy<std::string>(rijeci.at(i)) < boost::to_upper_copy<std::string>(min)) {
                min = rijeci.at(i);
            }
        }
    }
 
}


bool isInside (std::string rijec, std::vector<std::string> duplikati) {
    for (int i = 0; i < duplikati.size(); i++) {
        if (duplikati.at(i) == rijec) {
            return true;
        }
    }
    return false;
}


void ZadrziDuplikate (std::vector<std::string> &rijeci) {
    std::vector<std::string> duplikati;
    for (int i = 0; i < rijeci.size(); i++) {
        std::string temp = rijeci.at(i);
        for (int j = i + 1; j < rijeci.size(); j++) {
            if (rijeci.at(j) == temp) {
                if (isInside(temp, duplikati)) {
                    continue;
                } 
                else {
                    duplikati.push_back(temp);
                    break;
                }
            }
        }
    }
    rijeci = duplikati;
}




int main ()
{
    std::cout << "Koliko zelite unijeti rijeci: ";
    int n;
    std::cin >> n;
    std::cout << "Unesite rijeci: ";
    int i (0);
    std::vector<std::string> rijeci;
    while (i < n) {
        std::string temp;
        std::cin >> temp;
        rijeci.push_back(temp);
        i++;
    }
    std::string min;
    std::string max;
    IzdvojiKrajnjeRijeci(rijeci, min, max);
    std::cout << "Prva rijec po abecednom poretku je: " << min;
    std::cout << "\nPosljednja rijec po abecednom poretku je: " << max;
    std::cout << "\nRijeci koje se ponavljaju su: ";
    ZadrziDuplikate(rijeci);
    for (int i = 0; i < rijeci.size(); i++) {
        std::cout << rijeci.at(i) << " ";
    }
    
	return 0;
	
}
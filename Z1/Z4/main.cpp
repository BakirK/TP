//TP 2017/2018: Tutorijal 3, Zadatak 8
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>

bool jeSimetricna (std::string s) {
	if (s.size() < 2) {
		return false;
	}
    int polovina = std::ceil(s.size()/2);
    for (int i = 0; i < polovina ; i++) {
        if (std::toupper(s.at(i)) != std::toupper( s.at(s.size() - 1 - i) ) ) {
        	return false;
        }
    }
    return true;
}

bool jeZnak (char c) {
	if (std::toupper(c) >= 'A' && std::toupper(c) <='Z') {
		return true;
	} 
	if (c >= 48 && c <= 57) {
		return true;
	}
	return false;
}

std::vector<std::string> NadjiSimetricneRijeci(std::string recenica) {
	    std::vector<std::string> simetricne;
	    std::vector<std::string> rijeci;
	    std::string rijec;
	    for (int i = 0; i < recenica.length(); i++) {
	        if ( jeZnak ( recenica.at(i) ) ) {
	        	rijec += recenica.at(i);
	        }
	        else if (!jeZnak (recenica.at(i)) ) {
	        	if (jeSimetricna(rijec)) {
	        		simetricne.push_back(rijec);
	        	}
	        	rijec.clear();
	        }
	    }
	    if (rijec.size() != 0) {
	    	if (jeSimetricna(rijec)) {
	        		simetricne.push_back(rijec);
	    	}
	    }
	    return simetricne;
}


int main ()
{
    std::cout << "Unesite recenicu: ";
    std::string recenica;
    std::getline (std::cin, recenica);
    std::vector<std::string> simetricne = NadjiSimetricneRijeci(recenica);
    if (simetricne.size() == 0) {
    	std::cout << "\nRecenica ne sadrzi simetricne rijeci!";
    }
    else {
    	std::cout << "\nSimetricne rijeci unutar recenice su:\n";
    	for (int i = 0; i < simetricne.size() ; i++) {
    		std::cout << simetricne.at(i) <<"\n";
		}
    }
	return 0;
}

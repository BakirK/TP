//TP 2017/2018: Tutorijal 3, Zadatak 8
#include <iostream>
#include <string>


std::string IzdvojiRijec (std::string recenica, int rednibr_rijeci) {
    try {
        /* code */
        if (rednibr_rijeci < 1) {
            throw std::range_error("Pogresan redni broj rijeci!");
        }
        
        bool rijec (false);
	    int brojac (0);
	    //brojanje rijeci
	    for (int i = 0; i < recenica.length()-1; i++) {
	        if (recenica.at(i) != ' ' && !rijec) {
	            rijec = true;
	            brojac++;
	        }
	        else if (recenica.at(i) == ' ' && rijec) {
	            rijec = false;
	        }
	    }
	    
	    //std::cout << "rijeci " << brojac;
	    
	    if (rednibr_rijeci > brojac) {
	       throw std::range_error("Pogresan redni broj rijeci!");
	    }
	    
	    std::string odvojena_rijec;
	    //trazenje n-te rijeci
	    brojac = 0;
	    rijec = false;
	    bool kopirati (false);
	    for (int i = 0; i < recenica.length(); i++) {
	        if (recenica.at(i) != ' ' && !rijec) {
	            rijec = true;
	            brojac++;
	        }
	        else if (recenica.at(i) == ' ' && rijec) {
	            rijec = false;
	            if (kopirati) {
	                break;
	            }
	            
	        }
	        
            if (brojac == rednibr_rijeci && !kopirati) {
                kopirati = true;
            }
            
            if (kopirati) {
                odvojena_rijec.push_back(recenica.at(i));
            }
	    }
	    return odvojena_rijec;
    }
    catch (std::range_error belaj) {
        //std::cout << belaj.what() << std::endl;
        throw std::range_error(belaj.what());
        return "";
    }
    catch (...) {
    	throw std::range_error("Pogresan redni broj rijeci!");
    }
}


int main ()
{
    int rednibr_rijeci;
    std::cout << "Unesite redni broj rijeci: ";
    std::cin >> rednibr_rijeci;
    std::cin.ignore(10000, '\n');
    std::cout << "Unesite recenicu: ";
    std::string recenica;
    std::getline (std::cin, recenica);
    try{
        std::string test = IzdvojiRijec(recenica, rednibr_rijeci);
        std::cout << "Rijec na poziciji " << rednibr_rijeci << " je " << test;
    }
    catch (std::range_error belaj) {
    std::cout << "IZUZETAK: " << belaj.what() << std::endl;
    }
    
	return 0;
}

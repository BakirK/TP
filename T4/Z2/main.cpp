/* TP, 2017/2018, Tutorijal 4, Zadatak 2 */
#include <iostream>
#include <cmath>

void IzvrniString (std::string &s) {
    //int polovina = std::floor((s.size() +1)/2) ;
    int polovina = std::ceil(s.size()/2);
    for (int i = 0; i < polovina ; i++) {
        char temp = s.at(i);
        s.at(i) = s.at(s.size() - 1 - i);
        s.at(s.size() - 1 - i) = temp;
    }
}

    

int main ()
{
    std::cout << "Unesi string: ";
    std::string recenica;
    std::getline(std::cin, recenica);
    IzvrniString(recenica);
    std::cout << "Izvrnuti string je: " << recenica;
    
	return 0;
}
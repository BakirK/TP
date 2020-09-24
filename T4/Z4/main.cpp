/* TP, 2017/2018, Tutorijal 4, Zadatak 4 */
#include <iostream>

template <typename nekiTip>
void UnosBroja (std::string ispis, std::string upozorenje, nekiTip &broj) {
    while (true) {
        std::cout << ispis;
        nekiTip temp;
        std::cin >> temp;
        if (!std::cin || std::cin.peek() != '\n') {
            //std::cin.ignore(10000, '\n');
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout  << std::endl << upozorenje << std::endl;
        }
        else {
            broj = temp;
            break; 
        }
    }
}




int main ()
{
    double baza;
    UnosBroja("Unesite bazu: ", "Neispravan unos, pokusajte ponovo...", baza);
    int eksponent;
    UnosBroja("\nUnesite cjelobrojni eksponent: ", "Neispravan unos, pokusajte ponovo...", eksponent);
    double rez = 1;
    if (eksponent == 0) {
        rez = 1;
    }
    else if (eksponent > 0) {
        int tempEksponent = eksponent ; 
        while (tempEksponent > 0) {
            rez *= baza;
            tempEksponent--;
        }
    }
    else {
        int tempEksponent = eksponent * -1;
        while (tempEksponent > 0) {
            rez *= baza;
            tempEksponent--;
        }
        rez = 1 / rez ;
    }
    std::cout << std::endl << baza << " na " << eksponent << " iznosi "<< rez;
	return 0;
}
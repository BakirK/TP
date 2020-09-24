#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>

int main() {
    std::ios::sync_with_stdio(false);
    //std::cout << std::numeric_limits<long unsigned int>::max();
    std::cout << "Unesite pocetnu i krajnju vrijednost: " << std::endl;
    unsigned int a, b;
    std::cin >> a >> b;
    std::cout << "+" << std::setw(10) << std::setfill('-') << "+" << std::setw(11) <<  std::setfill('-') << "+"
               << std::setw(11) << std::setfill('-') << "+" << std::setw(12) <<  std::setfill('-') << "+";
               
    std::cout << std::setfill(' ') << std::endl << std::setw(9) << "| Brojevi " << std::setw(10) << "| Kvadrati " << std::setw(10) << "| Korijeni "
              << std::setw(13) << "| Logaritmi |" << std::endl;    
              
    std::cout << "+" << std::setw(10) << std::setfill('-') << "+" << std::setw(11) <<  std::setfill('-') << "+"
               << std::setw(11) << std::setfill('-') << "+" << std::setw(12) <<  std::setfill('-') << "+" << std::setfill(' ') << std::endl;              
               
    for (int i = a ; i <= b ; i++) {
        int kvadrat = i * i ;
        double korjen = sqrt(i);
        double logaritam = log(i);
        std::cout << "| " << std::left << std::setw(7) << i << " |" << std::right << std::setw(9) << kvadrat << " |"
                  << std::fixed<< std::setprecision(3) << std::setw(9) << korjen << " |" << std::fixed<< std::setprecision(5)
                  << std::setw(10) << logaritam << " |" << std::endl;
    }               
    std::cout << "+" << std::setw(10) << std::setfill('-') << "+" << std::setw(11) <<  std::setfill('-') << "+"
               << std::setw(11) << std::setfill('-') << "+" << std::setw(12) <<  std::setfill('-') << "+";
    return 0;
}

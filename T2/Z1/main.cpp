//TP 2017/2018: Tutorijal 2, Zadatak 1
#include <iostream>
#include <vector>
#include <cmath>


bool DaLiJeProst ( int n) {
    if(n<=1) {
        return false;
    }
    for (unsigned int i=2 ; i < (static_cast<int>(std::sqrt(n)))+1 ; i++)  {
        if ( n%i == 0) {
            return false;
        }
    }
    return true;
}


std::vector<int> ProstiBrojeviUOpsegu (int a, int b) {
    std::vector<int> temp;
    for (long long int i=a ; i<=b; i++) {
        //da bi bio prost broj, njegov korjen ne smije biti cijeli broj
            if (std::ceil(std::sqrt(i))==std::floor(std::sqrt(i))) {
                continue;
            }
            if(DaLiJeProst(i)) {
                temp.push_back(i);
            }
    }
    return temp;
}



int main ()
{
    std::ios::sync_with_stdio(false);
    std::cout << "Unesite pocetnu i krajnju vrijednost: ";
    int a, b;
    std::cin >> a >> b;
    std::vector<int> prosti = ProstiBrojeviUOpsegu(a, b);
    if(!prosti.size()) {
        std::cout << "Nema prostih brojeva u rasponu od " << a 
        << " do " << b << "!";
    } else {
        std::cout << "Prosti brojevi u rasponu od " << a 
        << " do " << b << " su: ";
    
        for(int i=0 ; i<prosti.size() ; i++) {
            if(i==prosti.size()-1) {
                std::cout << prosti[i] << std::endl;
            } else {
                std::cout << prosti[i] << ", ";
            }
        }
    }
	return 0;
}

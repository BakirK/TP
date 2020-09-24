/* TP, 2018/2019
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <type_traits>
#include <deque>
#include <stdexcept>


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



void RastavaBroja (int n, int &p, int &q) {
    if (n <= 0) {
        throw std::domain_error ("Broj koji se rastavlja mora biti prirodan");
    }
    p = 1;
    q = 1;
    std::vector<int> prostiBrojevi = ProstiBrojeviUOpsegu(1, 10000);
    std::vector<int> prostiFaktori(1);
    int temp = n;
    int i (0);
    while(temp > 1) {
        int prostBroj = prostiBrojevi.at(i);
        if (temp % prostBroj == 0) {
            prostiFaktori.at(i)++;
            temp /= prostBroj;
        }
        else {
            prostiFaktori.resize(prostiFaktori.size() + 1);
            i++;
        }
    }
    for (int i = 0; i < prostiFaktori.size(); i++) {
        if (prostiFaktori.at(i) % 2 == 1 && prostiFaktori.at(i) != 0) {
            p *= prostiBrojevi.at(i);
            prostiFaktori.at(i)--;
        }
        else if (prostiFaktori.at(i) == 1) {
            p *= prostiBrojevi.at(i);
            prostiFaktori.at(i)--;
        }
    }
    for (int i = 0; i < prostiFaktori.size(); i++) {
        if (prostiFaktori.at(i) != 0) {
            prostiFaktori.at(i) = prostiFaktori.at(i) / 2;
            q *= std::pow(prostiBrojevi.at(i), prostiFaktori.at(i));
        }
    }
}

int main ()
{
    try{
    std::cout << "Unesite prirodan broj";
    int n;
    std::cin >> n;
    int p(1), q(1);
    RastavaBroja(n, p, q);
    std::cout  << std::endl << p << " " << q ;
    }
    catch (std::domain_error belaj) {
        std::cout << std::endl << "Izuzetak: Broj koji se rastavlja mora biti prirodan!" << std::endl;
    }
    catch (std::bad_alloc) {
        std::cout << std::endl << "Izuzetak: Neodvoljno memorije!" << std::endl;
    }
    catch(...) {
        std::cout << "Izuzetak: Nepoznati" << std::endl;
    }
	return 0;
}
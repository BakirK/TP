#include <iostream>
#include <stdexcept>
#include <vector>
#include <type_traits>

template <typename someType>
auto KreirajIzvrnutiNiz (someType begin, someType end) -> typename std::remove_reference<decltype(*begin)>::type* {
     //typename(*someType + *someType) noviNiz = new typename(*someType + *someType)[n];
    auto test = *begin;
    someType temp = begin;
    int n(0);
    while (temp != end) {
        n++;
        temp++;
    }
    
    decltype(test) *noviNiz (nullptr);
    decltype(test) *p1;
    try {
        noviNiz = new decltype(test)[n];
        p1 = noviNiz;
        for (int i = n - 1; i >= 0; i--) {
            int j(0);
            someType temp1 = begin;
            while (j < i) {
                temp1++;
                j++;
            }
            *p1 = *temp1;
            p1++;
        }
    }
    catch (std::bad_alloc a) {
        delete [] noviNiz;
        throw std::bad_alloc();
    }
    return noviNiz;
}


int main ()
{
    std::cout << "Koliko zelite elemenata: ";
    int n;
    std::cin >> n;
    double *p (nullptr);
    
    try {
        p = new double[n];
        double *p1 = p;
        std::cout << "Unesite elemente: ";
        for (int i = 0; i < n; i++) {
            std::cin >> *p1;
            p1++;
        }
        double *ispis (nullptr);
        ispis = KreirajIzvrnutiNiz(p, p1);
        double *temp = ispis;
        std::cout << "Kreirani niz: ";
        for (int i = 0; i < n; i++) {
            std::cout << *ispis << " ";
            ispis++;
        }
        delete[] temp;
        delete[] p;
    }
    catch (std::bad_alloc error) {
        std::cout <<"Nedovoljno memorije!" << std::endl;
        delete[] p;
    }
    catch (...) {
        std::cout <<"Nedovoljno memorije!" << std::endl;
        delete[] p;
    }
    
    
    
    
	return 0;
}
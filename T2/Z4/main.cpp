//TP 2017/2018: Tutorijal 2, Zadatak 3
#include <iostream>
#include <complex>


int main ()
{
    std::cout << "Unesite broj elemenata: ";
    int broj;
    std::cin >> broj;
    std::complex<double> suma(0,0);
    int i=1;
    std::cout << std::endl;
    while (i<=broj) {
        std::cout << "R" << i << " = ";
        double re, im;
        std::cin >> re;
        std::cout << "X" << i << " = ";
        std::cin >> im;
        std::complex<double> z(re, im);
        suma += 1. / z;
        i++;
        std::cout << std::endl;
    }
    suma = 1. / suma;
    std::cout << std::endl << "Paralelna veza ovih elemenata ima R = " << std::real(suma)
                << " i X = " << std::imag(suma) << ".";
	return 0;
}

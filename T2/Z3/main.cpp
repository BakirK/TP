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
        std::cout << "Z_" << i << " = ";
        double re, im;
        char c;
        std::cin >> c;
        std::cin >> re;
        std::cin >> c;
        std::cin >> im;
        std::cin >> c;
        std::complex<double> z(re, im);
        suma += 1. / z;
        i++;
    }
    suma = 1. / suma;
    std::cout << std::endl << "Paralelna veza ovih elemenata ima impedansu Z_ = (" << std::real(suma)
                << "," << std::imag(suma) << ").";
	return 0;
}

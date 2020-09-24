//TP 2017/2018: Tutorijal 2, Zadatak 3
#include <iostream>
#include <complex>
#include <cmath>


int main ()
{
    std::cout << "Unesi broj elemenata: ";
    int broj;
    std::cin >> broj;
    std::complex<double> suma(0,0);
    int i=1;
    std::cout << std::endl;
    double pi=4.*atan(1.);
    while (i<=broj) {
        std::cout << "Z" << i << " = ";
        double z, fi;
        std::cin >> z;
        std::cout << "fi" << i << " = ";
        std::cin >> fi;
        double fi_rad = fi * (pi/180.);
        std::complex<double> kompleksni (std::polar (z, fi_rad));
        suma += 1. / kompleksni;
        i++;
        std::cout << std::endl;
    }
    suma = 1. / suma;
    double fi_deg = std::arg(suma) * (180./pi);
    std::cout << std::endl << "Paralelna veza ovih elemenata ima Z = " << std::abs(suma)
                << " i fi = " << fi_deg << ".";
	return 0;
}

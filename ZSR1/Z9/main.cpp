//TP 2018/2019: ZSR 1, Zadatak 9
#include <iostream>

int main ()
{
        std::cout << "Unesite dan mjesec i godinu pregleda: ";
        int sati, d, m, g, minute;
        std::cin >> d;
        std::cin >> m;
        std::cin >> g;
        std::cout << "Unesite sate i minute pregleda: ";
        std::cin >> sati;
        std::cin >> minute;
        std::cout << "Dan :" << d <<std::endl;
        std::cout << "Dan :" << m <<std::endl;
        std::cout << "Dan :" << g <<std::endl;
        std::cout << "Dan :" << sati <<std::endl;
        std::cout << "Dan :" << minute <<std::endl;
	return 0;
}
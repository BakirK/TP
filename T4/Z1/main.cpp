/* TP, 2017/2018, Tutorijal 4, Zadatak 1 */
#include <iostream>
#include <cmath>

int Cifre (long long int n, int &c_min, int &c_max) {
    long long int temp (n);
    int broj_cifara (0);
    if (n == 0) {
        broj_cifara++;
    } else {
        while ( temp != 0) {
           broj_cifara++;
           temp /= 10;
        }
        
    }
    
    c_min = std::abs(n % 10);
    c_max = std::abs(n % 10);
    n /= 10;
    while (n != 0 ) {
        if (std::abs(n % 10) > c_max) {
            c_max = std::abs(n % 10);
        }
        if (std::abs(n % 10) < c_min) {
            c_min = std::abs(n % 10);
        }
        n /= 10;
    }
    return broj_cifara;
}


int main ()
{
    std::cout << "Unesite broj: ";
    long long int n;
    std::cin >> n;
    int c_min, c_max;
    int broj_cifara = Cifre(n, c_min, c_max);
    std::cout << "Broj " << n << " ima " << broj_cifara << " cifara, najveca je " << c_max << " a najmanja " << c_min <<".";
    
	return 0;
}
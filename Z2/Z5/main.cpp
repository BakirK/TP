/* TP, 2018/2019
*/
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <type_traits>
#include <deque>

template <typename someType>
bool ZaSve (someType pocetak, someType kraj, bool f(typename std::remove_reference<decltype(*pocetak)>::type)) {
    auto temp = pocetak;
    int n(0);
    while(temp != kraj) {
        n++;
        temp++;
    }
    return (n == std::count_if(pocetak, kraj, f) );
}

template <typename someType>
bool MakarJedan(someType pocetak, someType kraj, bool f(typename std::remove_reference<decltype(*pocetak)>::type)) {
    return (std::count_if(pocetak, kraj, f) > 0);
}



template <typename someType>
auto Akumuliraj (someType pocetak, someType kraj, typename std::remove_reference<decltype(*pocetak)>::type f(typename std::remove_reference<decltype(*pocetak)>::type, typename std::remove_reference<decltype(*pocetak)>::type), typename std::remove_reference<decltype(*pocetak)>::type init = 0) -> typename std::remove_reference<decltype(*pocetak)>::type {
    auto temp = pocetak;
    int n(0);
    while(temp != kraj) {
        n++;
        temp++;
    }
    if (!n) {
        return init;
    }
    typename std::remove_reference<decltype(*pocetak)>::type vracena = f(init, *pocetak);
    pocetak++;
    init = vracena;
    while(pocetak != kraj) {
        init = f (init, *pocetak);
        pocetak++;
    }
    return init;
}



void unos (int &p) {
	int temp;
	std::cin >> temp;
	p = temp;
}

void unosDek (double &p) {
	double temp;
	std::cin >> temp;
	p = temp;
}


int main ()
{
    std::cout << "Unesite string: " ;
    std::string s;
    std::getline(std::cin, s);
    //std::cout << typeid(*s.begin()).name() << std::endl;
    bool znakovi = ZaSve(s.begin(), s.end(), [](char c) -> bool {
        return (std::toupper(c) >= 65 && std::toupper(c) <= 90) || (c>=48 && c<=57);
    });
    
    if (znakovi) {
        std::cout << "Uneseni string sadrzi samo slova i cifre" << std::endl;
    }
    else {
        std::cout << "Uneseni string sadrzi i druge znakove osim slova i cifara" << std::endl;
    }
    std::cout << "Unesite niz od 10 brojeva: ";
    int niz[10];
    std::for_each(std::begin(niz), std::end(niz), unos);
    
    bool djeljiviSaSumom = MakarJedan(std::begin(niz), std::end(niz), [](int broj) -> bool {
        if (!broj) {
            return false;
        }
        int suma (0);
        int temp = broj;
        while (temp != 0) {
            suma += temp % 10;
            temp /= 10;
        }
        return (!(broj%suma));
    });
    
    if (djeljiviSaSumom) {
        std::cout << "U nizu ima brojeva djeljivih sa sumom svojih cifara" << std::endl;
    }
    else {
        std::cout << "U nizu nema brojeva djeljivih sa sumom svojih cifara" << std::endl;
    }
    std::cout << "Unesite dek od 10 elemenata: ";
    std::deque<double> dek;
    dek.resize(10);
    for_each(dek.begin(), dek.end(), unosDek);
    double suma (0);
    suma = Akumuliraj(dek.begin(), dek.end(), [](double broj1, double broj2) -> double {
        return broj1 + broj2;
    }, suma);
    
    double proizvod (1);
    proizvod = Akumuliraj(dek.begin(), dek.end(), [](double broj1, double broj2) -> double {
        if (!broj1 || !broj2) return 0;
        return (broj1 * broj2);
    }, proizvod);
    
    std::cout<< std::endl << "Suma deka: " << suma << std::endl;
    std::cout << "Produkt deka: " << proizvod << std::endl;
    auto min = std::min_element(dek.begin(), dek.end());
    auto max = std::max_element(dek.begin(), dek.end());
    std::cout << "Najveci elemenat deka: " << *max << std::endl;
    std::cout << "Najmanji elemenat deka: " << *min << std::endl;
	return 0;
}
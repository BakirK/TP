//TP 2017/2018: Tutorijal 3, Zadatak 1
#include <iostream>
#include <vector>

std::vector<int> IzdvojiElemente(std::vector<int> v, bool parnost) {
    std::vector<int> izdvojen;
    if(parnost) {
        for (int i : v) {
            int suma = 0;
            int temp = i;
            while(temp != 0) {
                suma += temp % 10;
                temp /= 10;
            }
            if (suma % 2 == 0) {
                izdvojen.push_back(i);
            }
        }
    } 
    else {
        for (int i : v) {
            int suma = 0;
            int temp = i;
            while(temp != 0) {
                suma += temp % 10;
                temp /= 10;
            }
            if (suma % 2 != 0) {
                izdvojen.push_back(i);
            }
        }
    }
    return izdvojen;
}


int main ()
{
    int n;
    while (true) {
        std::cout << "Koliko zelite unijeti elemenata: ";
        std::cin >> n;
        if (n <= 0) {
            std::cout << "Broj elemenata mora biti veci od 0!" << std::endl;
            return 0;
        }
        break;
    }
    std::cout << "Unesite elemente: ";
    int i = 0;
    std::vector<int> a;
    while (i < n) {
        int temp;
        std::cin >> temp;
        a.push_back(temp);
        i++;
    }
    std::vector<int> b = IzdvojiElemente(a, true);
    std::vector<int> c = IzdvojiElemente(a, false);
    int brojac = 1;
    
    
    /*
        "Ovaj put za ispis elemenata vektora nemojte koristiti rasponsku for-petlju, jer ćete u suprotnom
        teško postići da ne bude ispisan zarez iza posljednjeg elementa u svakom redu."
    */
    // CHALLANGE ACCEPTED!!!
    for (int i: b) {
        if(brojac == b.size()) {
            std::cout << i;
        } else {
            std::cout << i << ",";
        }
        brojac++;
    }
    std::cout << std::endl;
    brojac = 1;
     for (int i: c) {
        if(brojac == c.size()) {
            std::cout << i;
        } else {
            std::cout << i << ",";
        }
        brojac++;
    }
	return 0;
}

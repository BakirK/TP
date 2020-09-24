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
        if (n == 0) {
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
    for (int i: b) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
     for (int i: c) {
        std::cout << i << " ";
    }
	return 0;
}

//TP 2017/2018: Tutorijal 3, Zadatak 1
#include <iostream>
#include <deque>
#include <algorithm>

std::deque<int> IzdvojiElemente(std::deque<int> v, bool parnost) {
    std::deque<int> izdvojen;
    if(parnost) {
        for (int i : v) {
            int suma = 0;
            int temp = i;
            while(temp != 0) {
                suma += temp % 10;
                temp /= 10;
            }
            if (suma % 2 == 0) {
                izdvojen.push_front(i);
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
                izdvojen.push_front(i);
            }
        }
    }
    std::reverse(izdvojen.begin(), izdvojen.end());
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
    std::deque<int> a;
    while (i < n) {
        int temp;
        std::cin >> temp;
        a.push_back(temp);
        i++;
    }
    std::deque<int> b = IzdvojiElemente(a, true);
    std::deque<int> c = IzdvojiElemente(a, false);
     int brojac = 1;
    
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
    
    
    
    
    
    
    
    
    /*
    for (auto i = b.rbegin(); i != b.rend(); ++i) {
        if(i == b.rend()-1) {
            std::cout << *i ;
        } else {
            std::cout << *i << ",";
        }
            
        
    }
    std::cout << std::endl;
    for (auto i = c.rbegin(); i != c.rend(); ++i) {
        if(i == c.rend()-1) {
            std::cout << *i ;
        } else {
            std::cout << *i << ",";
        }
            
        
    }*/
    return 0;
}

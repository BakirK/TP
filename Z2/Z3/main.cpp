#include <iostream>
#include <type_traits>
#include <vector>
#include <deque>

template <typename type1, typename type2>
bool jeSadrzan(type1 elemenat, std::vector<type2> vektor) {
    for (int i = 0; i < vektor.size(); i++)  {
        if (elemenat == vektor.at(i)) {
            return true;
        }
    }
    return false;
}

template <typename type1, typename type2, typename type3>
type3 SimetricnaRazlikaBlokova (type1 p1, type1 p2, type2 p3, type2 p4, type3 p5) {
    std::vector<typename std::remove_reference<decltype(*p5)>::type > razlikaVektor;
    type1 p1Temp = p1;
    while(p1Temp != p2) {
        auto temp = *p1Temp;
        bool postoji (false);
        type2 p3Temp = p3;
        while(p3Temp != p4) {
            if (temp == *p3Temp) {
                postoji = true;
                break;
            }
            p3Temp++;
        }
        if (!postoji && !jeSadrzan(temp, razlikaVektor)) {
            razlikaVektor.push_back(temp);
        }
        p1Temp++;
    }
    
    
    type2 p3Temp = p3;
    while(p3Temp != p4) {
        auto temp = *p3Temp;
        bool postoji (false);
        type1 p1Temp = p1;
        while(p1Temp != p2) {
            if (temp == *p1Temp) {
                postoji = true;
                break;
            }
            p1Temp++;
        }
        if (!postoji && !jeSadrzan(temp, razlikaVektor)) {
            razlikaVektor.push_back(temp);
        }
        p3Temp++;
    }
    for (int i(0); i < razlikaVektor.size(); i++) {
        *p5 = razlikaVektor.at(i);
        p5++;
    }
    return p5;
}

int main ()
{
    std::cout << "Unesite broj elemenata niza";
    int brojClanovaNiza;
    std::cin >> brojClanovaNiza;
    int i (0);
    int niz[100];
    int *p = niz;
    std::cout << std::endl << "Unesite elemente niza";
    while (i < brojClanovaNiza) {
        int temp;
        std::cin >> temp;
        niz[i] = temp;
        i++;
        p++;
    }
    std::cout << std::endl << "Unesite broj elemenata deka";
    int brojClanovaDeque;
    std::cin >> brojClanovaDeque;
    i = 0;
    std::deque<int> dek;
    std::cout << std::endl << "Unesite elemente deka";
    while (i < brojClanovaDeque) {
        int temp;
        std::cin >> temp;
        dek.push_back(temp);
        i++;
    }
    std::vector<int> simetricnaRazlikaVector;
    simetricnaRazlikaVector.resize(100);
    std::vector<int>::iterator izaKraja = SimetricnaRazlikaBlokova(niz, p, dek.begin(), dek.end(), simetricnaRazlikaVector.begin());
    simetricnaRazlikaVector.resize(izaKraja - simetricnaRazlikaVector.begin());
    if (simetricnaRazlikaVector.size() == 0) {
        std::cout << std::endl << "Blokovi nemaju simetricnu razliku" << std::endl;
    } else {
        std::cout << std::endl << "Simetricna razlika blokova je: ";
        auto pocetak = simetricnaRazlikaVector.begin();
        int i (0);
        while (pocetak != izaKraja) {
            if (i == simetricnaRazlikaVector.size() - 1) {
                std::cout << *pocetak;
            }
            else {
                std::cout << *pocetak << " ";
            }
            pocetak++;
            i++;
        }
    }
	return 0;
}
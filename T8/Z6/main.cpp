//TP 2018/2019: Tutorijal 8, Zadatak 6
#include <iostream>

template <typename TipElemenata>
struct Cvor {
    TipElemenata element;
    Cvor *veza;
};


template <typename TipElemenata>
Cvor<TipElemenata> *KreirajPovezanuListu(TipElemenata zavrsni)
{
    Cvor<TipElemenata> *pocetak (nullptr), *prethodni;
    TipElemenata temp;
    std::cin >> temp;
    while (temp != zavrsni) {
        Cvor<TipElemenata> *novi = new Cvor<TipElemenata> {temp, nullptr};
        if (!pocetak) {
            pocetak = novi;
        } else {
            (*prethodni).veza = novi;
        }
        prethodni = novi;
        std::cin >> temp;
    }
    return pocetak;

}


template <typename TipElemenata>
int BrojElemenata(Cvor<TipElemenata> *pocetak)
{
    int i(0);
    auto trenutni = pocetak;
    while(trenutni != nullptr) {
        i++;
        trenutni = trenutni->veza;
    }
   // i++;
    return i;
}


template <typename TipElemenata>
TipElemenata SumaElemenata(Cvor<TipElemenata> *pocetak)
{
    double suma(0);
    auto trenutni = pocetak;
    while(trenutni->veza != nullptr) {
        suma += trenutni->element;
        trenutni = trenutni->veza;
    }
    suma += trenutni->element;
    return suma;

}


template <typename TipElemenata>
int BrojVecihOd(Cvor<TipElemenata> *pocetak, TipElemenata prag)
{
    int i(0);
    auto trenutni = pocetak;
    while(trenutni->veza != nullptr) {
        if (trenutni->element > prag) {
            i++;
        }
        trenutni = trenutni->veza;
    }
    if (trenutni->element > prag) {
        i++;
    }
    return i;

}


template <typename TipElemenata>
void UnistiListu(Cvor<TipElemenata> *pocetak)
{
    if (!pocetak) {
        return;
    }
    auto trenutni (pocetak);
    auto iduci (trenutni->veza);
    while(iduci->veza != nullptr) {
        delete trenutni;
        trenutni = iduci;
        iduci = iduci->veza;
    }
    delete trenutni;
    delete iduci;
}



int main ()
{
    std::cout << "Unesite slijed brojeva (0 za kraj): ";
    Cvor<double> *pocetak = KreirajPovezanuListu<double>(0);
    double prosjek (SumaElemenata<double>(pocetak) / BrojElemenata<double>(pocetak));
    double brojVecihOd (BrojVecihOd<double>(pocetak, prosjek));
    std::cout << "U slijedu ima " << brojVecihOd << " brojeva vecih od njihove aritmeticke sredine";
    UnistiListu<double>(pocetak);
    return 0;
}

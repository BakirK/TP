//TP 2018/2019: Zadaća 4, Zadatak 2
#include <iostream>
#include <sstream>
#include <iomanip>
class GradjaninBiH
{
public:
    enum Pol {Musko, Zensko};
private:
    std::string ime;
    long long int jmbg;
    int d, m, g;
    Pol pol;
    int regija;
public:
    GradjaninBiH *prethodni;
    static GradjaninBiH *zadnjiKreirani;
    GradjaninBiH(std::string ime_i_prezime, long long int jedinstveni)
    {
        this->ime = ime_i_prezime;
        this->jmbg = jedinstveni;
        this->prethodni = zadnjiKreirani;
        zadnjiKreirani = nullptr;
        zadnjiKreirani = &(*this);
        if (this->prethodni == zadnjiKreirani) {
            std::cout<<"ISIT SU";
        }
    }
    void Ispisi() { std::cout << ime << " " << jmbg << std::endl;}

};

GradjaninBiH *GradjaninBiH::zadnjiKreirani = nullptr;

int main ()
{
    std::cout << "Koliko gradjana zelite unijeti po JMBG? ";
    int n;
    std::cin >> n;
    int i(0);
    while (i < n) {
        std::cout << "\nUnesite ime i prezime (u istom redu): ";
        std::string ime;
        std::cin.ignore(1000, '\n');
        std::getline(std::cin, ime);
        std::cout << "\nUnesite JMBG: ";
        long long int jmbg;
        std::cin >> jmbg;
        try {
            GradjaninBiH gr1(ime, jmbg);
        } catch(std::logic_error e) {
            i--;
            std::cout << e.what();
        }
        i++;
    }


    std::cout << std::endl;
    GradjaninBiH *it = GradjaninBiH::zadnjiKreirani;
    while(it != nullptr) {
        it->Ispisi();
        it = it->prethodni;
    }



    return 0;
}

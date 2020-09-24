#include <iostream>

class NekaKlasa
{
private:
    int broj;
public:
    NekaKlasa *previousElement;
    static NekaKlasa *lastCreated;
    NekaKlasa(int broj)
    {
        this->broj = broj;
        previousElement = lastCreated;
        lastCreated = this;
        if (previousElement == lastCreated) {
            std::cout << "ISTI SU";
        }
    }
    void Ispisi()
    {
        std::cout << broj;
    }
};

NekaKlasa *NekaKlasa::lastCreated = nullptr;

int main ()
{
    NekaKlasa n1(1);
    NekaKlasa n2(2);
    NekaKlasa n3(3);

    NekaKlasa *it = NekaKlasa::lastCreated;
    while(it != nullptr) {
        it->Ispisi();
        it = it->previousElement;
    }
    return 0;
}

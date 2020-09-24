//TP 2018/2019: Tutorijal 8, Zadatak 2
#include <iostream>
#include <iomanip>

struct Vrijeme {
    int sati, minute, sekunde;
};


void TestirajVrijeme (Vrijeme v1) {
    if (v1.sati > 23 || v1.sati < 0 || v1.minute > 59 || v1.minute < 0 || v1.sekunde < 0 || v1.sekunde >59) {
        throw std::domain_error("Neispravno vrijeme");
    } 
}


void IspisiVrijeme (const Vrijeme &vrijeme) {
    TestirajVrijeme(vrijeme);
    std::cout << std::setfill('0') << std::setw(2) << vrijeme.sati << ":" << std::setfill('0') 
    << std::setw(2) << vrijeme.minute << ":" << std::setfill('0') 
    << std::setw(2) << vrijeme.sekunde << std::endl;
}

Vrijeme SaberiVrijeme (Vrijeme v1, Vrijeme v2) {
    TestirajVrijeme(v1);
    TestirajVrijeme(v2);
    int suma (0);
    suma += v1.sati * 3600 + v1.minute * 60 + v1.sekunde;
    suma += v2.sati * 3600 + v2.minute * 60 + v2.sekunde;
    Vrijeme v3;
    v3.sati = (suma / 3600) % 24;
    suma -= (suma / 3600) * 3600;
    v3.minute = suma / 60;
    suma -= v3.minute * 60;
    v3.sekunde = suma;
    if (v3.sati == 24) {
        v3.sati = 0;
    }
    return v3;
}




int main ()
{
    try{
        std::cout << "Unesite prvo vrijeme (h m s): ";
        Vrijeme v1;
        std::cin >> v1.sati >> v1.minute >> v1.sekunde;
        TestirajVrijeme(v1);
        std::cout<< "Unesite drugo vrijeme (h m s): ";
        Vrijeme v2;
        std::cin >> v2.sati >> v2.minute >> v2.sekunde;
        TestirajVrijeme(v2);
        Vrijeme v3 = SaberiVrijeme(v1, v2);
        std::cout << "Prvo vrijeme: ";
        IspisiVrijeme(v1);
        std::cout << "Drugo vrijeme: ";
        IspisiVrijeme(v2);
        std::cout << "Zbir vremena: ";
        IspisiVrijeme(v3);
    }
    catch (std::domain_error belaj) {
        std::cout << belaj.what() << std::endl;
        
    }
	return 0;
}
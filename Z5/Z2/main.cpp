//TP 2018/2019: Zadaća 5, Zadatak 2
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>


class Berza {
    std::vector<int> cijene;
    int min, max;
    public:
    Berza(int min, int max) {
        if (min <= 0 || max <= 0) {
            throw std::range_error("Ilegalne granicne cijene");
        }
        this->min = min;
        this->max = max;
    }
    explicit Berza (int max) {
        if (max <= 0) {
            throw std::range_error("Ilegalne granicne cijene");
        }
        this->min = 0;
        this->max = max;
    }
    void RegistrirajCijenu(int novaCijena) {
        if(novaCijena < min || novaCijena > max) {
            throw std::range_error("Ilegalna cijena");
        }
        cijene.push_back(novaCijena);
    }
    int DajBrojRegistriranihCijena() const{
        return cijene.size();
    }
    void BrisiSve() {
        cijene.clear();
    }
    
    
    double DajProsjecnuCijenu() {
        int sum = 0;
        for(int i = 0; i < broj; i++) {

            suma +- broj;
        }
        double konacno = sum / broj
    }
    
    
    
    int DajMaksimalnuCijenu() const{
        if (!cijene.size()) {
            throw std::range_error("Nema registriranih cijena");
        } 
        return *std::max_element(cijene.begin(), cijene.end());
    }
    int DajMinimalnuCijenu() const{
        if (!cijene.size()) {
            throw std::range_error("Nema registriranih cijena");
        } 
        return *std::min_element(cijene.begin(), cijene.end());
    }
    
    bool operator!() const{
        return !cijene.size();
    }
    
    int DajBrojCijenaVecihOd(int granica) const{
        if (!cijene.size()) {
            throw std::range_error("Nema registriranih cijena");
        }
        //return std::count_if(cijene.begin(), cijene.end(), std::bind1st(std::greater<int>(), granica));
        return std::count_if(cijene.begin(), cijene.end(), std::bind(std::greater<int>(),  std::placeholders::_1, granica));
    }
    
    void Ispisi() const{
        auto temp (cijene);
        std::sort(temp.begin(), temp.end(), std::bind(std::greater<int>(), std::placeholders::_1, std::placeholders::_2));
        for(double d: temp) {
            std::cout << std::setprecision(2) << std::fixed << d/100 << std::endl;
        }
    }
    
    int operator[](int index) {
        if (index > cijene.size() || index < 1) {
            throw std::range_error("Neispravan indeks");
        }
        return cijene.at(index - 1);
    }
    Berza &operator++() {
        int i = std::count_if(cijene.begin(), cijene.end(), std::bind(std::greater<int>(),  std::placeholders::_1, max-100));
        if (i > 0) {
            throw std::range_error("Prekoracen dozvoljeni opseg cijena");
        }
        std::transform(cijene.begin(), cijene.end(), cijene.begin(), std::bind(std::plus<int>(), 100, std::placeholders::_1));
        return *this;
    }
    friend Berza operator++(Berza &b, int);
    
    
    Berza &operator--() {
        int i = std::count_if(cijene.begin(), cijene.end(), std::bind(std::less<int>(), std::placeholders::_1, min + 100));
        if (i > 0) {
            throw std::range_error("Prekoracen dozvoljeni opseg cijena");
        }
        std::transform(cijene.begin(), cijene.end(), cijene.begin(), std::bind(std::minus<int>(), std::placeholders::_1, 100));
        return *this;
    }
    friend Berza operator--(Berza &b, int);
    
    friend Berza operator-(const Berza &b);
    
    friend Berza operator+(const Berza &berza, int broj);
    friend Berza operator+(int broj, const Berza &berza);
    //friend Berza operator+(const Berza &b1, const Berza &b2);
    Berza operator+(const Berza &b2) = delete;
    friend Berza operator-(const Berza &berza, const int broj);
    friend Berza operator-(const int broj, const Berza &berza);
    friend Berza operator-(const Berza &b1, const Berza &b2);
    
    Berza &operator+=(const int broj) {
        return *this = *this + broj;
    }
    Berza &operator-=(const int broj) {
        return *this = *this - broj;
    }
    Berza &operator-=(const Berza &berza) {
        return *this = *this - berza;
    }
    friend bool operator==(const Berza &b1, const Berza &b2);
    friend bool operator!=(const Berza &b1, const Berza &b2);
};

inline bool operator==(const Berza &b1, const Berza &b2) {
    if(b1.min != b2.min || b1.max != b2.max || b1.cijene.size() != b2.cijene.size()) {
        return false;
    }
    return std::equal(b1.cijene.begin(), b1.cijene.end(), b2.cijene.begin());
}

inline bool operator!=(const Berza &b1, const Berza &b2) {
    return !(b1==b2);
}

Berza operator-(const Berza &b1, const Berza &b2) {
    if(b1.min != b2.min || b1.max != b2.max || b1.cijene.size() != b2.cijene.size()) {
        throw std::domain_error("Nesaglasni operandi");
    }
    Berza b (b1);
    std::transform(b1.cijene.begin(), b1.cijene.end(), b2.cijene.begin(), b.cijene.begin(), std::bind(std::minus<int>(), std::placeholders::_1, std::placeholders::_2));
    int manjih = std::count_if(b.cijene.begin(), b.cijene.end(), std::bind(std::less<int>(), std::placeholders::_1, b.min));
    if (manjih != 0 ) {
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    }
    int vecih = std::count_if(b.cijene.begin(), b.cijene.end(), std::bind(std::greater<int>(), std::placeholders::_1, b.max));
    if (vecih != 0 ) {
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    }
    return b;
}
/*
Berza operator+(const Berza &b1, const Berza &b2) {
    if(b1.min != b2.min || b1.max != b2.max || b1.cijene.size() != b2.cijene.size()) {
        throw std::domain_error("Nesaglasni operandi");
    }
    Berza b (b1);
    std::transform(b1.cijene.begin(), b1.cijene.end(), b2.cijene.begin(), b.cijene.begin(), std::bind(std::plus<int>(), std::placeholders::_1, std::placeholders::_2));
    int manjih = std::count_if(b.cijene.begin(), b.cijene.end(), std::bind(std::less<int>(), std::placeholders::_1, b.min));
    if (manjih != 0 ) {
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    }
    int vecih = std::count_if(b.cijene.begin(), b.cijene.end(), std::bind(std::greater<int>(), std::placeholders::_1, b.max));
    if (vecih != 0 ) {
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    }
    return b;
}*/
Berza operator+(const Berza &b1, const Berza &b2) = delete;
Berza operator-(const Berza &berza, const int broj) {
    Berza b = berza;
    std::transform(b.cijene.begin(), b.cijene.end(), b.cijene.begin(), std::bind(std::minus<int>(), std::placeholders::_1, broj));
    int manjih = std::count_if(b.cijene.begin(), b.cijene.end(), std::bind(std::less<int>(), std::placeholders::_1, b.min));
    if (manjih != 0 ) {
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    }
    int vecih = std::count_if(b.cijene.begin(), b.cijene.end(), std::bind(std::greater<int>(), std::placeholders::_1, b.max));
    if (vecih != 0 ) {
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    }
    return b;
}

 Berza operator-(const int broj, const Berza &berza) {
    Berza b = berza;
    std::transform(b.cijene.begin(), b.cijene.end(), b.cijene.begin(), std::bind(std::minus<int>(), broj, std::placeholders::_1));
    int manjih = std::count_if(b.cijene.begin(), b.cijene.end(), std::bind(std::less<int>(), std::placeholders::_1, b.min));
    if (manjih != 0 ) {
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    }
    int vecih = std::count_if(b.cijene.begin(), b.cijene.end(), std::bind(std::greater<int>(), std::placeholders::_1, b.max));
    if (vecih != 0 ) {
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    }
    return b;
 }

Berza operator+(const Berza &berza, int broj) {
    Berza b = berza;
    std::transform(b.cijene.begin(), b.cijene.end(), b.cijene.begin(), std::bind(std::plus<int>(), broj, std::placeholders::_1));
    int manjih = std::count_if(b.cijene.begin(), b.cijene.end(), std::bind(std::less<int>(), std::placeholders::_1, b.min));
    if (manjih != 0 ) {
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    }
    int vecih = std::count_if(b.cijene.begin(), b.cijene.end(), std::bind(std::greater<int>(), std::placeholders::_1, b.max));
    if (vecih != 0 ) {
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    }
    return b;
}

Berza operator+(int broj, const Berza &b) {
    return b + broj;
}



Berza operator-(const Berza &b1) {
    Berza b = b1;
    std::transform(b.cijene.begin(), b.cijene.end(), b.cijene.begin(), std::bind(std::minus<int>(), b.min+b.max, std::placeholders::_1));
    return b;
}


Berza operator++(Berza &b, int) {
    auto temp = b;
    ++b;
    return temp;
}

Berza operator--(Berza &b, int) {
    auto temp = b;
    --b;
    return temp;
}

int main ()
{
    Berza b1 = Berza(1000);
    b1.RegistrirajCijenu(0);
    b1.RegistrirajCijenu(500);
    b1.RegistrirajCijenu(501);
    b1.RegistrirajCijenu(1000);
    b1.RegistrirajCijenu(999);
    std::cout << "Minimalna cijena: " << b1.DajMinimalnuCijenu() << std::endl;
    std::cout << "Maksimalna cijena: " << b1.DajMaksimalnuCijenu()<< std::endl;
    if(!b1) {
        std::cout << "ovo se nije trebalo ispisati - neradi operator !."<< std::endl;
    } else {
        std::cout << "radi operator !." << std::endl;
    }
    std::cout << "Broj cijena vecih od 500 treba bit 3 a tebi je: " << b1.DajBrojCijenaVecihOd(500) << std::endl;
    b1.Ispisi();
    std::cout << "Prva cijena je (0) " << b1[1] << " a zadnja (999) " << b1[5] << std::endl;
    
    try {
        b1[0];
         std::cout << "Ovo se nije trebalo ispisati" << std::endl;
    }
    catch (std::range_error e) {
        std::cout << "Ovo se trebalo ispisati" << std::endl;
    }
    
    try {
        b1[6];
         std::cout << "Ovo se nije trebalo ispisati" << std::endl;
    }
    catch (std::range_error e) {
        std::cout << "Ovo se trebalo ispisati" << std::endl;
    }
    b1.BrisiSve();
    b1.RegistrirajCijenu(900);
    b1++;
    std::cout << "Treba ispisat 1000 a tebi je: " << b1[1] << std::endl;
    try {
        b1++;
        std::cout << "Ovo se nije trebalo ispisati" << std::endl;
    }
    catch (std::range_error e) {
        std::cout << "Ovo se trebalo ispisati" << std::endl;
    }
    b1.RegistrirajCijenu(0);
    try {
        b1--;
        std::cout << "Ovo se nije trebalo ispisati" << std::endl;
    }
    catch (std::range_error e) {
        std::cout << "Ovo se trebalo ispisati" << std::endl;
    }
    b1.BrisiSve();
    b1.RegistrirajCijenu(500);
    std::cout << "Treba ispisat 600 a tebi je: " << (++b1)[1] << std::endl;
    std::cout << "Treba ispisat 500 a tebi je: " << (--b1)[1] << std::endl;
     b1.RegistrirajCijenu(0);
    try {
        --b1;
        std::cout << "Ovo se nije trebalo ispisati" << std::endl;
    }
    catch (std::range_error e) {
        std::cout << "Ovo se trebalo ispisati" << std::endl;
    }
     b1.RegistrirajCijenu(1000);
    try {
        ++b1;
        std::cout << "Ovo se nije trebalo ispisati" << std::endl;
    }
    catch (std::range_error e) {
        std::cout << "Ovo se trebalo ispisati" << std::endl;
    }
    b1.BrisiSve();
    b1.RegistrirajCijenu(800);
    Berza b2 = -b1;
    std::cout << "Treba ispisat 200 a tebi je: " << b2[1] << std::endl;
    b2 = 50 + b2;
    std::cout << "Treba ispisat 250 a tebi je: " << b2[1] << std::endl;
    b2 += 50;
    std::cout << "Treba ispisat 300 a tebi je: " << b2[1] << std::endl;
    b2 -= 50;
    std::cout << "Treba ispisat 250 a tebi je: " << b2[1] << std::endl;
    b2 =  b2 - 50;
    std::cout << "Treba ispisat 200 a tebi je: " << b2[1] << std::endl;
    b2 =  300 - b2;
    std::cout << "Treba ispisat 100 a tebi je: " << b2[1] << std::endl;
    try {
        b2 =  -100 - b2;
        std::cout << "Ovo se nije trebalo ispisati" << std::endl;
    }
    catch (std::domain_error e) {
        std::cout << "Ovo se trebalo ispisati" << std::endl;
    }
    if (b1 != b2) {
        std::cout << "Ovo se trebalo ispisati" << std::endl;
    } else {
        std::cout << "Ovo se nije trebalo ispisati" << std::endl;
    }
    b1 = b2;
    if (b1 == b2) {
        std::cout << "Ovo se trebalo ispisati" << std::endl;
    } else {
        std::cout << "Ovo se nije trebalo ispisati" << std::endl;
    }
    b1.BrisiSve();
    b1.RegistrirajCijenu(1000);
    if (b1 != b2) {
        std::cout << "Ovo se trebalo ispisati" << std::endl;
    } else {
        std::cout << "Ovo se nije trebalo ispisati" << std::endl;
    }
    Berza b3 = b1 - b2; // 1000 - 100
    std::cout << "Treba ispisat 900 a tebi je: " << b3[1] << std::endl;
    //ovo se ne treba compajlirati
    /*b3 = b3 + b2; // 900 + 100
    std::cout << "Treba ispisat 1000 a tebi je: " << b3[0] << std::endl;*/
	return 0;
}
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
        std::string jmbg = std::to_string(jedinstveni);
        if (jmbg.size() != 13) {
            throw std::logic_error("\nJMBG nije validan");
        }

        GradjaninBiH *it = zadnjiKreirani;
        while(it != nullptr && it->prethodni != it) {
            if (std::to_string(it->jmbg) == jmbg ) {
                throw std::logic_error("Vec postoji gradjanin sa istim JMBG");
            }
            it = it->prethodni;
        }
        int d = std::stoi(jmbg.substr(0,2));
        int m = std::stoi(jmbg.substr(2,2));
        int g = std::stoi(jmbg.substr(4,3));
        if (g <= 17) {
            g+=2000;
        } else {
            g += 1000;
        }
        if (!provjeriDatum(d, m, g, true)) {
            throw std::logic_error("\nJMBG nije validan");
        }
        int c13 = 11 - (7 * (std::stoi(jmbg.substr(0, 1)) + std::stoi(jmbg.substr(6, 1))) + 6 * (std::stoi(jmbg.substr(1, 1)) + std::stoi(jmbg.substr(7, 1)))
                        + 5 * (std::stoi(jmbg.substr(2, 1)) + std::stoi(jmbg.substr(8, 1))) + 4 * (std::stoi(jmbg.substr(3, 1)) + std::stoi(jmbg.substr(9, 1))) +
                        3 * (std::stoi(jmbg.substr(4, 1)) + std::stoi(jmbg.substr(10, 1))) + 2 * (std::stoi(jmbg.substr(5, 1)) + std::stoi(jmbg.substr(11, 1)))) % 11;
        if (c13 == 11) {
            c13 = 0;
        }
        if (c13 != std::stoi(jmbg.substr(12,1))) {
            throw std::logic_error("\nJMBG nije validan");
        }
        this->d = d;
        this->m = m;
        this->g = g;
        this->ime = ime_i_prezime;
        this->jmbg = jedinstveni;
        int spolBroj = std::stoi(jmbg.substr(9,3));
        if (spolBroj < 500) {
            pol = Musko;
        } else {
            pol = Zensko;
        }
        this->regija = std::stoi(jmbg.substr(7,2));
        this->prethodni = zadnjiKreirani;
        zadnjiKreirani = nullptr;
        zadnjiKreirani = this;
    }



    GradjaninBiH(std::string ime_i_prezime, int dan_rodjenja, int mjesec_rodjenja, int godina_rodjenja, int sifra_regije, Pol pol)
    {
        if (!provjeriDatum(dan_rodjenja, mjesec_rodjenja, godina_rodjenja, false) || sifra_regije < 0 || sifra_regije > 99) {
            throw std::logic_error("\nNeispravni podaci");
        }
        this->ime = ime_i_prezime;
        d = dan_rodjenja;
        m = mjesec_rodjenja;
        g = godina_rodjenja;
        regija = sifra_regije;
        this->pol = pol;
        std::stringstream ss;

        if (godina_rodjenja > 1000) godina_rodjenja -= 1000;
        ss << std::setw(2) << std::setfill('0') << dan_rodjenja << std::setw(2) << std::setfill('0') << mjesec_rodjenja
           << std::setw(3) << std::setfill('0') << godina_rodjenja << std::setw(2) << std::setfill('0') << sifra_regije
           << std::setw(3) << std::setfill('0') ;
        std::string s = ss.str();
        int kod = 0;
        if (pol == Zensko) kod = 500;
        GradjaninBiH *it = zadnjiKreirani;
        while(it != nullptr  && it->prethodni != it) {
            if (std::to_string(it->jmbg).substr(0, 9) == s && it->pol == pol) {
                kod = std::stoi(std::to_string(it->jmbg).substr(9, 3));
            }
            it = it->prethodni;
        }
        ss << std::setw(3) << std::setfill('0') << kod;
        s = ss.str();
        long long int c13 = 11 - ((7 * (std::stoi(s.substr(0, 1)) + std::stol(s.substr(6, 1))) + 6 * (std::stol(s.substr(1, 1)) + std::stol(s.substr(7, 1)))
                                   + 5 * (std::stol(s.substr(2, 1)) + std::stol(s.substr(8, 1))) + 4 * (std::stol(s.substr(3, 1)) + std::stol(s.substr(9, 1))) +
                                   3 * (std::stol(s.substr(4, 1)) + std::stol(s.substr(10, 1))) + 2 * (std::stol(s.substr(5, 1)) + std::stol(s.substr(11, 1)))) % 11);
        if (c13 == 11) {
            c13 = 0;
        }
        if (c13 == 10) {
            std::cout << "belaj, c13 je 10 - nije definisano u zadatku sta sad radit?!\n";
        }
        s += std::to_string(c13);
        this->jmbg = std::stol(s);
        this->prethodni = zadnjiKreirani;
        zadnjiKreirani = this;
    }

    ~GradjaninBiH()
    {
        if (this == zadnjiKreirani) {
            zadnjiKreirani = prethodni;
        }  else {
            GradjaninBiH *it = zadnjiKreirani;
            while(it->prethodni != nullptr && it->prethodni != this) {
                it = it->prethodni;
            }
            it->prethodni = this->prethodni;
        }
    }

    std::string DajImeIPrezime() const
    {
        return ime;
    }
    long long int DajJMBG() const
    {
        return jmbg;
    }
    int DajDanRodjenja() const
    {
        return d;
    }
    int DajMjesecRodjenja() const
    {
        return m;
    }
    int DajGodinuRodjenja() const
    {
        return g;
    }
    int DajSifruRegije() const
    {
        return regija;
    }
    Pol DajPol() const
    {
        return pol;
    }
    void PromijeniImeIPrezime(std::string novo_ime)
    {
        this->ime = novo_ime;
    }


    bool provjeriDatum(int d, int m, int g, bool ogranicenje)
    {
        int broj_dana[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if(g % 4 == 0 && (g % 100 != 0 || g % 400 == 0)) broj_dana[1]++;
        if(g < 1 || d < 1 || m < 1 || m > 12 || d > broj_dana[m - 1] ) {
            return false;
        }
        if (ogranicenje) {
            if (g < 1917 || g > 2017) return false;
        }
        return true;

    }

    void Ispisi1()
    {
        std::cout << "\nUnijeli ste gradjanina " << ime << " rodjenog " << d <<"."  << m <<"."  << g << " u regiji " << regija << ",";
        if (pol == Musko) {
            std::cout << " musko.";
        } else {
            std::cout << " zensko.";
        }
    }
    void Ispisi2()
    {
        std::cout << "\nUnijeli ste gradjanina " << ime << " JMBG: " << jmbg <<".";
    }

    GradjaninBiH(const GradjaninBiH&) = delete;
    GradjaninBiH(GradjaninBiH&&) = delete;
    GradjaninBiH &operator=(GradjaninBiH&) = delete;
    GradjaninBiH &operator=(GradjaninBiH&&) = delete;
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
            new GradjaninBiH (ime, jmbg);
            GradjaninBiH::zadnjiKreirani->Ispisi1();
        } catch(std::logic_error e) {
            i--;
            std::cout << e.what();
        }
        i++;
    }
    
    std::cout << "\nKoliko gradjana zelite unijeti po datumu rodjenja, regiji i polu? ";
    std::cin >> n;
    i = 0;
    while(i < n) {
        std::cout << "\nUnesite ime i prezime (u istom redu): ";
        std::string ime;
        std::cin.ignore(1000, '\n');
        std::getline(std::cin, ime);
        std::cout << "\nUnesite datum rodjenja (format dd/mm/gggg): ";
        int d, m,g;
        char c;
        std::cin >> d >> c >> m >> c >> g;
        std::cout << "\nUnesite sifru regije: ";
        int regija;
        std::cin >> regija;
        std::cout << "\nUnesite M za musko, Z za zensko: ";
        std::cin >> c;
        if (c == 'M' || c == 'm') {
            try {   
                new GradjaninBiH(ime, d, m, g, regija, GradjaninBiH::Pol::Musko);
                GradjaninBiH::zadnjiKreirani->Ispisi2();
            } catch(std::logic_error e) {
                std::cout << e.what();
                i--;
            }

        } else {
            try {
                new GradjaninBiH (ime, d, m, g, regija, GradjaninBiH::Pol::Zensko);
                GradjaninBiH::zadnjiKreirani->Ispisi2();
            } catch(std::logic_error e) {
                std::cout << e.what() << std::endl;;
            }

        }
        i++;
    }
    return 0;
}

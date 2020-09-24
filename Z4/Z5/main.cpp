//TP 2018/2019: Zadaća 4, Zadatak 5
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <ctype.h>
#include <map>

class Student
{
    int brojIndeksa;
    std::string imeStudenta, adresa, godinaStudija, telefon;
    std::string godine[11] {"1", "2", "3", "1/B", "2/B", "3/B", "1/M", "2/M", "1/D", "2/D", "3/D"};

public:
    Student(int brojIndeksa, std::string godinaStudija, std::string imeStudenta, std::string adresa, std::string telefon)
    {
        if (brojIndeksa <10000 || brojIndeksa > 99999) {
            throw std::domain_error("Neispravni parametri");
        } else if ((std::find(godine, godine + 11, godinaStudija) == godine+11) || !formatTelefona(telefon)) {
            throw std::domain_error("Neispravni parametri");
        } else {
            this->brojIndeksa = brojIndeksa;
            if (godinaStudija.size() == 1) {
                godinaStudija += "/B";
            }
            this->godinaStudija = godinaStudija;
            //boost::trim_right(imeStudenta);
            //boost::trim_left(imeStudenta);
            std::string::size_type pos;
            while((pos = imeStudenta.find("  ")) != std::string::npos) {
                imeStudenta.replace(pos, 2, " ");
            }
            
            if(*(imeStudenta.begin()) == ' ') {
                imeStudenta.erase(0,1);
            }
            if(*(imeStudenta.end()-1) == ' ') {
                imeStudenta.erase(imeStudenta.size()-1,1);
            }
            this->imeStudenta = imeStudenta;

            //boost::trim_right(adresa);
            //boost::trim_left(adresa);
            while((pos = adresa.find("  ")) != std::string::npos) {
                adresa.replace(pos, 2, " ");
            }
            if(*(adresa.begin()) == ' ') {
                adresa.erase(0,1);
            }
            if(*(adresa.end()-1) == ' ') {
                adresa.erase(imeStudenta.size()-1,1);
            }
            this->adresa = adresa;
            this->telefon = telefon;
        }

    }


    int DajIndeks() const
    {
        return brojIndeksa;
    }

    std::string DajGodinuStudija() const
    {
        return godinaStudija;
    }

    std::string DajImePrezime() const
    {
        return imeStudenta;
    }

    std::string DajAdresu() const
    {
        return adresa;
    }

    std::string DajTelefon() const
    {
        return telefon;
    }

    void Ispisi() const
    {
        std::cout << "Broj indeksa: " << brojIndeksa << std::endl
                  << "Godina studija: "<< godinaStudija << std::endl
                  << "Ime i prezime: " << imeStudenta << std::endl
                  << "Adresa: " << adresa << std::endl
                  << "Telefon: " << telefon << std::endl;
    }

    private:
    bool formatTelefona(std::string s)
    {
        if (s.size() < 5) {
            return false;
        }
        int i(0);
        auto it = s.begin();
        while(it != s.end()) {
            if (!std::isdigit(*it) && *it != '-' && *it != '/') {
                return false;
            }
            if(*it == '-') {
                i++;
            }
            if (*it == '/') {
                i++;
            }

            it++;
        }
        return i == 2;
    }
};




class Laptop
{
    int ev_broj;
    std::string naziv;
    std::string karakteristike;
    Student *kod_koga_je;
public:
    Laptop(int ev_broj, std::string naziv, std::string karakteristike)
    {
        if (ev_broj < 0) {
            throw std::domain_error("Neispravni parametri");
        }
        this->ev_broj = ev_broj;
        this->naziv = naziv;
        this->karakteristike = karakteristike;
        kod_koga_je = nullptr;
    }


    int DajEvidencijskiBroj() const
    {
        return ev_broj;
    }

    std::string DajNaziv() const
    {
        return naziv;
    }

    std::string DajKarakteristike() const
    {
        return karakteristike;
    }

    void Zaduzi(Student &student)
    {
        if (kod_koga_je) {
            throw std::domain_error("Laptop vec zaduzen");
        }
        kod_koga_je = &student;
    }

    void Razduzi()
    {
        kod_koga_je = nullptr;
    }

    bool DaLiJeZaduzen() const
    {
        return kod_koga_je;
    }

    Student &DajKodKogaJe() const
    {
        if (!kod_koga_je) {
            throw std::domain_error("Laptop nije zaduzen");
        }
        return *kod_koga_je;
    }

    Student *DajPokKodKogaJe() const
    {
        return kod_koga_je;
    }

    void Ispisi() const
    {
        std::cout << "Evidencijski broj: " << ev_broj << std::endl
                  << "Naziv: "<< naziv << std::endl
                  << "Karakteristike: " << karakteristike << std::endl;
    }
};



class Administracija
{
    std::map<int, Student*> studenti;
    std::map<int, Laptop*> laptopi;

public:
    Administracija() = default;

    Administracija(const Administracija &a)
    {
        auto it (a.studenti.begin());
        while (it != a.studenti.end()) {
            this->studenti[it->first] = new Student(*(it->second));
            it++;
        }
        auto it2 = a.laptopi.begin();
        while (it2 != a.laptopi.end()) {
            this->laptopi[it2->first] = new Laptop((it2->second)->DajEvidencijskiBroj(), (it2->second)->DajNaziv(), (it2->second)->DajKarakteristike());
            it2++;
        }
    }
    //ne treba ovo?
    Administracija(Administracija &&a)
    {
        this->studenti = a.studenti;
        this->laptopi = a.laptopi;
        a.studenti.clear();
        a.laptopi.clear();
    }

    Administracija &operator=(const Administracija &a)
    {
        auto it (a.studenti.begin());
        while (it != a.studenti.end()) {
            this->studenti[it->first] = new Student(*(it->second));
            it++;
        }
        auto it2 = a.laptopi.begin();
        while (it2 != a.laptopi.end()) {
            this->laptopi[it2->first] = new Laptop((it2->second)->DajEvidencijskiBroj(), (it2->second)->DajNaziv(), (it2->second)->DajKarakteristike());
            it2++;
        }
        return *this;
    }

    Administracija &operator=(Administracija &&a)
    {
        std::swap(this->laptopi, a.laptopi);
        std::swap(this->studenti, a.studenti);
        return *this;
    }

    ~Administracija()
    {
        auto it (studenti.begin());
        while (it != studenti.end()) {
            delete studenti[it->first];
            it++;
        }
        auto it2 = laptopi.begin();
        while (it2 != laptopi.end()) {
            delete laptopi[it2->first];
            it2++;
        }
        laptopi.clear();
        studenti.clear();
    }


    void RegistrirajNovogStudenta (int brojIndeksa, std::string godinaStudija, std::string imeStudenta, std::string adresa, std::string telefon)
    {
        if (studenti.find(brojIndeksa) != studenti.end()) {
            throw std::domain_error("Student s tim indeksom vec postoji");
        }
        studenti[brojIndeksa] = new Student(brojIndeksa, godinaStudija, imeStudenta, adresa, telefon);
    }

    void RegistrirajNoviLaptop(int ev_broj, std::string naziv, std::string karakteristike)
    {
        if (laptopi.find(ev_broj) != laptopi.end()) {
            throw std::domain_error("Laptop s tim evidencijskim brojem vec postoji");
        }
        laptopi[ev_broj] = new Laptop(ev_broj, naziv, karakteristike);
    }

    Student &NadjiStudenta(int brojIndeksa) 
    {
        if (studenti.find(brojIndeksa) == studenti.end()) {
            throw std::domain_error("Student nije nadjen");
        } else {
            return *(studenti[brojIndeksa]);
        }
    }

    Student NadjiStudenta(int brojIndeksa) const
    {
        if (studenti.find(brojIndeksa) == studenti.end()) {
            throw std::domain_error("Student nije nadjen");
        } else {
            return *(studenti.at(brojIndeksa));
        }
    }

    Laptop &NadjiLaptop(int ev_broj)
    {
        if (laptopi.find(ev_broj) == laptopi.end()) {
            throw std::domain_error("Laptop nije nadjen");
        } else {
            return *(laptopi[ev_broj]);
        }
    }

    Laptop NadjiLaptop(int ev_broj) const
    {
        if (laptopi.find(ev_broj) == laptopi.end()) {
            throw std::domain_error("Laptop nije nadjen");
        } else {
            return *(laptopi.at(ev_broj));
        }
    }


    void IzlistajStudente() const
    {
        int i(0);
        auto it = studenti.begin();
        while(it != studenti.end()) {
            if (i == 2) {
                std::cout << std::endl;
                i = 0;
            }
            (it->second)->Ispisi();
            it++;
            i++;
        }
    }

    void IzlistajLaptope() const
    {
        int i(0);
        auto it = laptopi.begin();
        while(it != laptopi.end()) {
            if (i == 2) {
                std::cout << std::endl;
                i = 0;
            }
            (it->second)->Ispisi();
            if ((it->second)->DaLiJeZaduzen()) {
                std::cout << "Zaduzio(la): " << ((it->second)->DajPokKodKogaJe())->DajImePrezime()
                          << " (" << ((it->second)->DajPokKodKogaJe())->DajIndeks()  << ")" << std::endl;;
            }
            std::cout << std::endl;
            it++;
            i++;
        }
    }


    void ZaduziLaptop(int brojIndeksa, int ev_broj)
    {
        if (studenti.find(brojIndeksa) == studenti.end()) {
            throw std::domain_error("Student nije nadjen");
        }
        if (laptopi.find(ev_broj) == laptopi.end()) {
            throw std::domain_error("Laptop nije nadjen");
        }
        auto it = laptopi.begin();
        while(it != laptopi.end()) {
            if ((it->second)->DajPokKodKogaJe() != nullptr) {
                if (((it->second)->DajPokKodKogaJe())->DajIndeks() == brojIndeksa) {
                    throw std::domain_error("Student je vec zaduzio laptop");
                }
            }
            it++;
        }
        laptopi[ev_broj] -> Zaduzi(*studenti[brojIndeksa]);
    }


    int NadjiSlobodniLaptop()
    {
        auto it = laptopi.begin();
        while(it != laptopi.end()) {
            if ((it->second)->DajPokKodKogaJe() == nullptr) {
                return (it->second)->DajEvidencijskiBroj();
            }
            it++;
        }
        throw std::domain_error("Nema slobodnih laptopa");
    }

    void RazduziLaptop(int ev_broj)
    {
        auto it (laptopi.find(ev_broj));
        if (it == laptopi.end()) {
            throw std::domain_error("Laptop nije nadjen");
        }
        if (!(it->second)->DaLiJeZaduzen()) {
            throw std::domain_error("Laptop nije zaduzen");
        }
        (it->second)->Razduzi();
    }

    void PrikaziZaduzenja()
    {
        bool zaduzenBaremJedan = false;
        auto it = laptopi.begin();
        while(it != laptopi.end()) {
            if ((it->second)->DajPokKodKogaJe() != nullptr) {
                zaduzenBaremJedan = true;
                std::cout << "Student " << ((it->second)->DajPokKodKogaJe())->DajImePrezime() << " ("
                          << ((it->second)->DajPokKodKogaJe())->DajIndeks()
                          << ") zaduzio/la laptop broj " << (it->second)->DajEvidencijskiBroj() << std::endl;
            }
            it++;
        }

        if (!zaduzenBaremJedan) {
            std::cout << "Nema zaduzenja";
        }
    }
};



int main ()
{
  
    
     Administracija etf;

    etf.RegistrirajNoviLaptop(123, "Dell", "CPU 3.0 GHz, 4 GB RAM");
    etf.RegistrirajNoviLaptop(331, "ASUS", "CPU 3.5 GHz, 2 GB RAM");
    etf.RegistrirajNoviLaptop(122, "Dell 2", "CPU 3.2 GHz, 6 GB RAM");


    etf.RegistrirajNovogStudenta(14212, "1","Benjamin", "Francuska revolucija 23", "12/34-56");
    etf.RegistrirajNovogStudenta(17528, "2","Ivan", "Trg vjecnih studenata 12", "048/597-585");
    etf.RegistrirajNovogStudenta(17525, "3", "Ante" ,"Trg vjecnih studenata 11", "062/582-757");

    etf.ZaduziLaptop(14212, 122);
    etf.ZaduziLaptop(17525,331);
    etf.IzlistajLaptope();
    etf.RazduziLaptop(122);
    std::cout << "POSLIJE" << std::endl << std::endl;
    etf.IzlistajLaptope();
    return 0;
}

#include <iostream>

class ApstraktniStudent
{
protected:
	std::string ime, prezime;
	int brIndexa, brPolozenihHispita;
	double prosjek;
public:
	ApstraktniStudent(std::string ime, std::string prezime, int indeks)
	{
		this->ime = ime;
		this->prezime = prezime;
		brIndexa = indeks;
		brPolozenihHispita = 0;
		this->prosjek = 5;
	}
	std::string DajIme() const
	{
		return ime;
	}
	std::string DajPrezime() const
	{
		return prezime;
	}
	int DajBrojIndeksa() const
	{
		return brIndexa;
	}
	int DajBrojPolozenih() const
	{
		return brPolozenihHispita;
	}
	double DajProsjek() const
	{
		return prosjek;
	}

	void RegistrirajIspit(int ocjena)
	{
		if (ocjena < 5 || ocjena > 10) {
			throw std::domain_error("Neispravna ocjena");
		}
		if (ocjena > 5) {
			double zbir = brPolozenihHispita * prosjek;
			zbir += ocjena;
			brPolozenihHispita++;
			prosjek = zbir / brPolozenihHispita;
		}
	}

	void PonistiOcjene()
	{
		brPolozenihHispita = 0;
		prosjek = 5;
	}
	virtual void IspisiPodatke() const = 0;
	virtual ApstraktniStudent *DajKopiju() const = 0;
	virtual ~ApstraktniStudent() {}
};


class StudentBachelor: public ApstraktniStudent
{
public:
	StudentBachelor(std::string ime, std::string prezime, int indeks): ApstraktniStudent(ime, prezime, indeks) {};
	void IspisiPodatke() const override
	{
		std::cout << "Student bachelor studija " << ime << " " << prezime <<", sa brojem indeksa " << brIndexa << ","
		          << std::endl << "ima prosjek " << prosjek << "." << std::endl;
	}
	ApstraktniStudent *DajKopiju() const override
	{
		return new StudentBachelor(*this);
	};
};

class StudentMaster: public ApstraktniStudent
{
	int godina;
public:
	StudentMaster(std::string ime, std::string prezime, int indeks, int godina): ApstraktniStudent(ime, prezime, indeks)
	{
		this->godina = godina;
	};
	void IspisiPodatke() const override
	{
		std::cout << "Student master studija " << ime << " " << prezime <<", sa brojem indeksa " << brIndexa << ","
		          << std::endl << "zavrsio bachelor studij godine " << godina << ",ima prosjek " << prosjek << "." << std::endl;
	}
	ApstraktniStudent *DajKopiju() const override
	{
		return new StudentMaster(*this);
	};
};

int main ()
{
	ApstraktniStudent *ps, *pskopija;
	ps = new StudentBachelor("Dusko", "Dugousko", 1234);
	ps->RegistrirajIspit(7);
	ps->RegistrirajIspit(6);
	ps->RegistrirajIspit(5);
	ps->RegistrirajIspit(10);
	ps->RegistrirajIspit(7);
	std::cout << "Originalni student: " << std::endl;
	std::cout << "-----------------" << std::endl;
	ps->IspisiPodatke();
	pskopija = ps->DajKopiju();
	std::cout << "Kopija student: " << std::endl;
	std::cout << "-----------------" << std::endl;
	pskopija->IspisiPodatke();
	ps->RegistrirajIspit(10);
	std::cout << "Originalni student nakon izmjene: " << std::endl;
	std::cout << "-----------------" << std::endl;
	ps->IspisiPodatke();
	std::cout << "Kopija student: " << std::endl;
	std::cout << "-----------------" << std::endl;
	pskopija->IspisiPodatke();
	delete pskopija;
	delete ps;
	return 0;
}

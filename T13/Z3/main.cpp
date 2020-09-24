#include <iostream>
#include <vector>
#include <algorithm>

class ApstraktniStudent
{
protected:
	std::string ime, prezime;
	//husmeni ispit hehe
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




class Fakultet
{
	std::vector<ApstraktniStudent*> v;
public:
	Fakultet() {}
	~Fakultet()
	{
		for(int i(0); i < v.size();  i++) {
			delete v.at(i);
		}
		//std::cout << "Izvrsio se destruktor" << v.size() << std::endl;
		//v.clear();
		v.resize(0);
	}
	Fakultet(const Fakultet &f);
	Fakultet &operator=(const Fakultet &f);
	Fakultet &operator=(Fakultet &&f);
	Fakultet(Fakultet &&f);
	void UpisiStudenta(std::string ime, std::string prezime, int indeks);
	void UpisiStudenta(std::string ime, std::string prezime, int indeks, int godina);
	void ObrisiStudenta(int indeks);
	const ApstraktniStudent &operator[](int index) const
	{
		bool found(false);
		auto it = v.begin();
		while (it != v.end()) {
			if((*it)->DajBrojIndeksa() == index) {
				found = true;
				return **it;
				break;
			}
			it++;
		}
		if (!found) {
			throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
		}
	}

	ApstraktniStudent &operator[](int index)
	{
		bool found(false);
		auto it = v.begin();
		while (it != v.end()) {
			if((*it)->DajBrojIndeksa() == index) {
				found = true;
				return **it;
				break;
			}
			it++;
		}
		if (!found) {
			throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
		}
		return *(v.at(index));
	}
	void IspisiSveStudente() const
	{
		Fakultet temp (*this);
		std::sort(temp.v.begin(), temp.v.end(), [](ApstraktniStudent *s1, ApstraktniStudent *s2) ->bool {
			if (s1->DajProsjek() == s2->DajProsjek())
			{
				return s1->DajBrojIndeksa()	< s2->DajBrojIndeksa();
			}
			return s1->DajProsjek()	> s2->DajProsjek();
		});

		auto it = temp.v.begin();
		while (it != temp.v.end()) {
			(*it)->IspisiPodatke();
			it++;
		}
	}
};


void Fakultet::ObrisiStudenta(int indeks)
{
	bool found (false);
	auto it = v.begin();
	while (it != v.end()) {
		if((*it)->DajBrojIndeksa() == indeks) {
			delete *it;
			v.erase(it);
			found = true;
			//std::cout << "erased" << " " << v.size();
			break;
		}
		it++;
	}
	if (!found) {
		throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
	}

}

void Fakultet::UpisiStudenta(std::string ime, std::string prezime, int indeks)
{
	auto it = v.begin();
	while (it != v.end()) {
		if((*it)->DajBrojIndeksa() == indeks) {
			throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
		}
		it++;
	}
	int index = v.size();
	v.resize(v.size() + 1);
	v.at(index) = new StudentBachelor(ime, prezime, indeks);
}

void Fakultet::UpisiStudenta(std::string ime, std::string prezime, int indeks, int godina)
{
	auto it = v.begin();
	while (it != v.end()) {
		if((*it)->DajBrojIndeksa() == indeks) {
			throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
		}
		it++;
	}
	v.push_back(new StudentMaster(ime, prezime, indeks, godina));
}

Fakultet::Fakultet(const Fakultet &f)
{
	v.resize(f.v.size());
	for(int i = 0; i < v.size(); i++) {
		v.at(i) = nullptr;
	}
	try {
		for(int i = 0; i < v.size(); i++)
			v.at(i) = (f.v.at(i))->DajKopiju();
	} catch(...) {
		for(int i = 0; i <  v.size(); i++) delete v.at(i);
		throw;
	}
}

Fakultet &Fakultet::operator=(const Fakultet &f)
{
	for(int i = 0; i < v.size(); i++) {
		delete v.at(i);
	}
	v.resize(f.v.size());
	for(int i = 0; i < v.size(); i++) {
		v.at(i) = nullptr;
	}
	try {
		for(int i = 0; i < v.size(); i++)
			v.at(i) = (f.v.at(i))->DajKopiju();
	} catch(...) {
		for(int i = 0; i < v.size(); i++) delete v.at(i);
		throw;
	}
	return *this;
}


Fakultet &Fakultet::operator=(Fakultet &&f)
{
	std::cout << "Fakultet &&f" << std::endl;
	std::swap(v, f.v);
	for(int i(0); i < f.v.size();  i++) {
		delete f.v.at(i);
	}
	f.v.clear();
	return *this;
}

Fakultet::Fakultet(Fakultet &&f)
{
	std::cout << "Fakultet &*adsasdasdasf" << std::endl;
	std::swap(v, f.v);
	for(int i(0); i < f.v.size();  i++) {
		delete f.v.at(i);
	}
	f.v.clear();
}



int main ()
{


	Fakultet f3; //3 studenta
	f3.UpisiStudenta("Meho", "Mehic", 3412);
	f3.UpisiStudenta("Ibro", "Ibric", 3124, 2015);
	f3.UpisiStudenta("Pero", "Peric", 1243);
f3.IspisiSveStudente();
	Fakultet f4 = std::move(f3);  //2 studenta
	std::cout << "ISPISSS" << std::endl;
	f3.IspisiSveStudente();
	f4.UpisiStudenta("Meho", "Mehic", 1111);
	f4.UpisiStudenta("Ibro", "Ibric", 2222, 2015);

	std::cout << std::endl << std::endl;
	f3 = std::move(f4);  //dodjela manjeg većem, sadai f3 i f4 imaju 2 elementa
	std::cout << "POMIJERAJUCI OPERATOR DODJELE - manji većem" << std::endl;
	f4.IspisiSveStudente(); //f4 je prazno

	f4.UpisiStudenta("Meho", "Mehic", 3412);
	f4.UpisiStudenta("Ibro", "Ibric", 3124, 2015);
	f4.UpisiStudenta("Pero", "Peric", 1243);
	f3 = std::move(f4);  //f3 je prazno
	f4.IspisiSveStudente();
	return 0;
}

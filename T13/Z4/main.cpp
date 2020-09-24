#include <iostream>
#include <vector>
#include <algorithm>

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




class Fakultet
{
	std::vector<ApstraktniStudent*> v;
public:
	Fakultet() {}
	~Fakultet()
	{
		for(int i(0); i < v.size();  i++) {
			//std::cout << "Izvrsio se destruktor" << v.size() << std::endl;
			delete v.at(i);
		}
		v.clear();
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
	std::swap(v, f.v);
	for(int i(0); i < f.v.size();  i++) {
		delete f.v.at(i);
	}
	f.v.clear();
	return *this;
}

Fakultet::Fakultet(Fakultet &&f)
{
	std::swap(v, f.v);
	for(int i(0); i < f.v.size();  i++) {
		delete f.v.at(i);
	}
	f.v.clear();
}


class Student{
    ApstraktniStudent *student;
    public:
    Student() : student(nullptr) {}
    ~Student() {delete student;}
    Student(const ApstraktniStudent &a): student(a.DajKopiju()) {}
    Student(const Student &a) {
        if(a.student) {
            student = a.student->DajKopiju();
        } else {
            student = nullptr;
        }
    }
    Student(Student &&a) {
        this->student = a.student;
        a.student = nullptr;
    }
    Student &operator =(const Student &s) {
        delete student;
        if (s.student) {
            student = s.student->DajKopiju();
        } else {
            student = nullptr;
        }
        return *this;
    }
    
    Student &operator =(Student &&s) {
        std::swap(student, s.student);
        return *this;
    }
    
    void IspisiPodatke() const {
        student->IspisiPodatke();
    }
    
    void RegistrirajIspit(int ocjena) {
        student->RegistrirajIspit(ocjena);
    }
    
    std::string DajIme() const
	{
		return student->DajIme();
	}
	std::string DajPrezime() const
	{
		return student->DajPrezime();
	}
	int DajBrojIndeksa() const
	{
		return student->DajBrojIndeksa();
	}
	int DajBrojPolozenih() const
	{
		return student->DajBrojPolozenih();
	}
	double DajProsjek() const
	{
		return student->DajProsjek();
	}
	void PonistiOcjene()
	{
	    student->PonistiOcjene();
	}
	
};



int main ()
{
    Student s1, s2;
    s1 = StudentBachelor("Dusko", "Dugousko", 1234); // s1 je bachelor
    s2 = StudentMaster("Paja", "Patak", 4312, 2015); // a s2 master
    s1.RegistrirajIspit(6); s1.RegistrirajIspit(9);
    s2.RegistrirajIspit(8);
    s1.IspisiPodatke(); s2.IspisiPodatke();
    s1 = s2; // sad je i s1 master
    s1.IspisiPodatke();
	return 0;
}

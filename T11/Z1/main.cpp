#include <iostream>

class NeobicnaKlasa {
	int broj;
public:
	explicit NeobicnaKlasa(int broj) {
		this->broj = broj;
		std::cout << "Direktna inicijalizacija" << std::endl;
	}
	
	NeobicnaKlasa(short  broj) {
		this->broj = broj;
		std::cout << "Kopirajuca inicijalizacija";
	}
	
	
	//ne radi nista u ovom primjeru
	const NeobicnaKlasa &operator =(const NeobicnaKlasa &b) {
		this->broj = b.broj;
		std::cout << "Kopirajuca inicijalizacija";
		return *this;
	}
	
	//ne radi nista u ovom primjeru
	NeobicnaKlasa(const NeobicnaKlasa &b) {
		this->broj = b.broj;
		std::cout << "Kopirajuca inicijalizacija";
	}
};




int main ()
{
	//eksplicitno pozivamo konstrutkor koji prima int kao parametar
	NeobicnaKlasa k1(5);
	//ovdje se broj 5 pokusava pretvorit u tip NeobicnKlasa pomocu neeksplicitnog konstruktora
	NeobicnaKlasa k2 = 5;
	return 0;
}
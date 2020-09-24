#include <iostream>
#include <stdexcept>
#include <iomanip>

class Sat
{
	int sekunde;
public:
	static bool DaLiJeIspravno (int sati, int minute, int sekunde)
	{
		return !(sati > 23 || sati < 0 || minute > 59 || minute < 0 || sekunde < 0 || sekunde >59);
	}
	void Postavi (int sati, int minute, int s)
	{
		if (DaLiJeIspravno(sati, minute, s)) {
			this->sekunde = sati * 3600 + minute * 60 + s;
		} else {
			throw std::domain_error("Neispravno vrijeme");
		}
	}
	
	void PostaviNormalizirano (int sati, int minute, int sekunde)
	{
		
		int suma (0);
		if (sati < 0) {
			sati = 24 - std::abs((sati % 24));
		}
		suma += sati * 3600 + minute * 60 + sekunde;
		this->sekunde = suma % 86400;
	}

	Sat Sljedeci()
	{
		sekunde++;
		if (sekunde == 86400) sekunde = 0;
		return *this;
	}

	Sat Prethodni()
	{
		sekunde--;
		if (sekunde == -1) sekunde = 86399;
		return *this;
	}

	Sat PomjeriZa(int s)
	{
		sekunde += s;
		return *this;
	}

	void Ispisi() const
	{
		std::cout << std::setfill('0') << std::setw(2) << DajSate() << ":" << std::setfill('0')
		          << std::setw(2) << DajMinute() << ":" << std::setfill('0')
		          << std::setw(2) << DajSekunde() << std::endl;
	}
	int DajSate() const
	{
		int temp = (sekunde / 3600) % 24;
		if (temp <= 0 && sekunde < 0) {
			temp = 23 - (std::abs(temp) % 24);
		}
		return temp;
	}
	int DajMinute() const
	{
		int temp = ((sekunde - ((sekunde / 3600) * 3600)) / 60 ) % 60;
		if (temp <= 0 && sekunde < 0) {
			temp = 59 -(std::abs(temp) % 60);
		}
		return temp;
	}
	int DajSekunde() const
	{
		int temp = (sekunde - ((sekunde - (sekunde / 3600) * 3600) / 60 ) * 60) % 60;
		if (temp < 0) {
			temp = 60 -(std::abs(temp) % 60);
		}
		return temp;
	}
	friend int BrojSekundiIzmedju(Sat s1, Sat s2);

	static int Razmak(Sat s1, Sat s2)
	{
		return s1.sekunde - s2.sekunde;
	}

};

int main ()
{
	Sat s;
	s.Postavi(0,0,0);
	s.PomjeriZa(-5).Ispisi();
	std::cout << std::endl;
	return 0;
}


int BrojSekundiIzmedju(Sat s1, Sat s2)
{
	return s1.sekunde - s2.sekunde;
}

#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <cmath>

class Sat
{
	int sati, minute, sekunde;
public:
	Sat() {
		sati = 0;
		minute = 0;
		sekunde = 0;
	}
	
	
	Sat(int sati, int minute, int sekunde) {
		PostaviNormalizirano(sati, minute, sekunde);
	}



	static bool DaLiJeIspravno (int sati, int minute, int sekunde)
	{
		return !(sati > 23 || sati < 0 || minute > 59 || minute < 0 || sekunde < 0 || sekunde >59);
	}
	void Postavi (int sati, int minute, int sekunde)
	{
		if (DaLiJeIspravno(sati, minute, sekunde)) {
			this->sati = sati;
			this->minute = minute;
			this->sekunde = sekunde;
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
		this->sati = (suma / 3600) % 24;
		suma -= (suma / 3600) * 3600;
		this->minute = (suma / 60) % 60;
		suma -= this->minute * 60;
		this->sekunde = suma % 60;
		if (this->sati == 24) {
			this->sati = 0;
		}
	}


	Sat &operator++()
	{
		sekunde++;
		if (sekunde == 60) {
			sekunde = 0;
			minute++;
		}
		if (minute == 60) {
			sati++;
			minute = 0;
		}
		if (sati == 24) {
			sati = 0;
		}
		return *this;
	}


	Sat operator++ (int)
	{
		Sat pomocni = *this;
		++(*this);
		return pomocni;
	}



	Sat &operator--()
	{
		sekunde--;
		if (sekunde == -1) {
			sekunde = 59;
			minute--;
		}
		if (minute == -1) {
			sati--;
			minute = 59;
		}
		if (sati == -1) {
			sati = 23;
		}
		return *this;
	}

	Sat operator--(int)
	{
		Sat pomocni = *this;
		--(*this);
		return pomocni;
	}


	Sat &operator+=(int s)
	{
		int i(0);
		if (s < 0) {
			s *= -1;
			while (i < s) {
				operator --();
				i++;
			}
		} else {
			while (i < s) {
				operator ++();
				i++;
			}
		}
		return *this;
	}


	Sat &operator -=(int s)
	{
		return operator +=(-s);
	}

	friend std::ostream &operator<<(std::ostream &tok, const Sat &s);
	
	
	Sat operator+(int s) {
		return {sati, minute, sekunde + s};
	}
	
	Sat operator-(int s) {
		return {sati, minute, sekunde - s};
	}
	
	friend Sat operator+(const Sat &s1, const Sat &s2);
	friend int operator-(const Sat &s1, const Sat &s2);
	

	int DajSate() const
	{
		return sati;
	}
	int DajMinute() const
	{
		return minute;
	}
	int DajSekunde() const
	{
		return sekunde;
	}
	friend int BrojSekundiIzmedju(Sat s1, Sat s2);

	static int Razmak(Sat s1, Sat s2)
	{
		int suma1 (0);
		suma1 += s1.sati * 3600 + s1.minute * 60 + s1.sekunde;
		int suma2 (0);
		suma2 += s2.sati * 3600 + s2.minute * 60 + s2.sekunde;
		return suma1 - suma2;
	}



};


std::ostream &operator<<(std::ostream &tok, const Sat &s)
{
	tok << std::setfill('0') << std::setw(2) << s.sati << ":" << std::setfill('0')
	    << std::setw(2) << s.minute << ":" << std::setfill('0')
	    << std::setw(2) << s.sekunde;
	return tok;
}

Sat operator+(const Sat &s1, const Sat &s2) {
	return {s1.sati + s2.sati, s1.minute + s2.minute, s1.sekunde + s2.sekunde};
}

int operator-(const Sat &s1, const Sat &s2) {
	return BrojSekundiIzmedju(s1, s2);
}

int main ()
{
/*
	Sat s;
	s.PostaviNormalizirano(-2, 3, 10);
	s.Ispisi();
	std::cout << std::endl;
	s.PostaviNormalizirano(15, -30, 0);
	s.Ispisi();
	std::cout << std::endl;
	s.PostaviNormalizirano(20, 30, -15);
	s.Ispisi();
	std::cout << std::endl;

	s.PostaviNormalizirano(30, 10, 15);
	s.Ispisi();
	std::cout << std::endl;
	s.PostaviNormalizirano(20, 70, 15);
	s.Ispisi();
	std::cout << std::endl;
	s.PostaviNormalizirano(20, 10, 360);
	s.Ispisi();
	std::cout << std::endl;

	s.PostaviNormalizirano(-1234, 1234, 2134);
	s.Ispisi();*/
	return 0;
}


int BrojSekundiIzmedju(Sat s1, Sat s2)
{
	int suma1 (0);
	suma1 += s1.sati * 3600 + s1.minute * 60 + s1.sekunde;
	int suma2 (0);
	suma2 += s2.sati * 3600 + s2.minute * 60 + s2.sekunde;
	return suma1 - suma2;
}

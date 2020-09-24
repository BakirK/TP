#include <iostream>
#include <cmath>
#include <iomanip>

class Ugao
{
	double vrijednostUgla;
public:
	Ugao(double radijani = 0)
	{
		Postavi(radijani);
	}
	Ugao(int stepeni, int minute, int sekunde)
	{
		Postavi(stepeni, minute, sekunde);
	}
	void Postavi(double radijani)
	{
		while (radijani < 0) {
			radijani += 2. * std::atan(1) * 4.;
		}
		vrijednostUgla = std::fmod(radijani, 2. * std::atan(1) * 4. );
	}

	void Postavi(int stepeni, int minute, int sekunde)
	{
		double sum = static_cast<double>(stepeni) +
		             (1. / 60.) * static_cast<double>(minute) +
		             (1. / 60.) * (1. / 60.) * static_cast<double>(sekunde);
		while (sum < 0) {
			sum += 360.;
		}
		vrijednostUgla = sum * ((std::atan(1) * 4.) / 180.);
		vrijednostUgla = std::fmod(vrijednostUgla, std::atan(1) * 8.);
	}
	double DajRadijane() const
	{
		return vrijednostUgla;
	}
	void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde)
	{
		stepeni = DajStepene();
		minute = DajMinute();
		sekunde = DajSekunde();
	}
	int DajStepene() const
	{
		return static_cast<int> (vrijednostUgla * (180. / (std::atan(1) * 4.) ) );
		//return (static_cast<int>(vrijednostUgla * 3600 * 180  / (std::atan(1) * 4.)) ) / 3600;

	}
	int DajMinute() const
	{
		//return static_cast<int> ( (vrijednostUgla * (180. / (std::atan(1) * 4.) )  - DajStepene() ) * 60. );
		return ((static_cast<int>(vrijednostUgla * 3600 * 180  / (std::atan(1) * 4.)) ) / 60) % 60;

	}


	int DajSekunde() const
	{
		/*
		double t = std::atan(1) * 4.;
		double temp = (180. / t);
		double temp1 = vrijednostUgla * temp;
		double temp2 = temp1 - DajStepene();
		double temp3 = temp2 * 60.;
		double temp4 = temp3 - DajMinute();
		double temp5 = temp4 * 60.;
		return static_cast<int>((((vrijednostUgla * (180. / (std::atan(1) * 4.) )  - DajStepene() ) * 60. ) - DajMinute()) * 60.);*/
		return (static_cast<int>(vrijednostUgla * 3600 * 180  / (std::atan(1) * 4.)) ) % 60;


	}
	void Ispisi() const
	{
		std::cout << std::fixed << std::setprecision(5) << vrijednostUgla;

	}
	void IspisiKlasicno() const
	{
		std::cout << std::fixed << std::setprecision(5) << DajStepene() << "deg " <<
		          std::fixed << std::setprecision(5) << DajMinute() << "min " <<
		          std::fixed << std::setprecision(5) << DajSekunde() << "sec";
	}
	Ugao &SaberiSa(const Ugao &u)
	{
		this->Postavi(this->vrijednostUgla + u.DajRadijane() + 0.000000000001);
		return *this;
	}
	Ugao &PomnoziSa(double x)
	{
		this->Postavi(this->vrijednostUgla * x);
		return *this;
	}
	friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
	friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);

};


int main ()
{
	Ugao u(50, 25, 12), v(500, 300, 200), f(50, 30, 10);
	u.SaberiSa(f);
	u.IspisiKlasicno();
	std::cout << std::endl;
	u.SaberiSa(v);
	u.IspisiKlasicno();
	std::cout << std::endl;
	u.PomnoziSa(2);
	u.IspisiKlasicno();
	return 0;
}



Ugao ZbirUglova(const Ugao &u1, const Ugao &u2)
{
	return Ugao(u1.DajRadijane() + u2.DajRadijane());
}

Ugao ProduktUglaSaBrojem(const Ugao &u, double x)
{
	return Ugao(u.DajRadijane() * x);
}

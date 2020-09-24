#include <iostream>
#include <cmath>
#include <iomanip>

class Ugao
{
	int stepeni, minute, sekunde;
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
		radijani = std::fmod(radijani, 2. * std::atan(1) * 4. );
		double sum = radijani * (180. / (std::atan(1) * 4.));
		stepeni = sum;
		sum -= stepeni;
		sum *= 60;
		minute = sum;
		sum -= minute;
		sum *= 60;
		sekunde = sum;
	}

	void Postavi(int stepeni, int minute, int sekunde)
	{
		int sum = stepeni * 3600 + minute * 60 + sekunde;
		while (sum < 0.) {
			sum += 1296000;
		}
		sum %= 1296000;
		this->stepeni = sum / 3600;
		sum -= this->stepeni * 3600;
		this->minute = sum / 60;
		sum -= this->minute * 60;
		this->sekunde = sum;
	}
	double DajRadijane() const
	{
		double sum = static_cast<double>(stepeni) +
		             (1. / 60.) * static_cast<double>(minute) +
		             (1. / 60.) * (1. / 60.) * static_cast<double>(sekunde);
		while (sum < 0) {
			sum += 360.;
		}
		sum = sum * ((std::atan(1) * 4.) / 180.);
		return std::fmod(sum, std::atan(1) * 8.);
	}
	void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde)
	{
		stepeni = DajStepene();
		minute = DajMinute();
		sekunde = DajSekunde();
	}
	int DajStepene() const
	{
		return this->stepeni;
	}
	int DajMinute() const
	{
		return this->minute;
	}


	int DajSekunde() const
	{
		return this->sekunde;
	}
	void Ispisi() const
	{
		std::cout << std::fixed << std::setprecision(5) << DajRadijane();

	}
	void IspisiKlasicno() const
	{
		std::cout << std::fixed << std::setprecision(5) << DajStepene() << "deg " <<
		          std::fixed << std::setprecision(5) << DajMinute() << "min " <<
		          std::fixed << std::setprecision(5) << DajSekunde() << "sec";
	}
	Ugao &SaberiSa(const Ugao &u2)
	{
		this->Postavi(this->DajStepene() + u2.DajStepene(), this->DajMinute() + u2.DajMinute(), this->DajSekunde() + u2.DajSekunde());
		return *this;
	}
	Ugao &PomnoziSa(double x)
	{
		this->Postavi(DajRadijane() * x);
		return *this;
	}
	friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
	friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);

};


int main ()
{
	Ugao u(90, 0, 0), v(180, 0, 0), f(90, 0, 0);
	u=ZbirUglova(u, v);
	u.IspisiKlasicno();
	std::cout << std::endl;
	ZbirUglova(u, f).IspisiKlasicno();
	std::cout << std::endl;
	u=ZbirUglova(u, 90);
	u.IspisiKlasicno();
	std::cout << std::endl;
	f.Postavi(std::atan(1) * 4.);
	std::cout << "Vrijednost pi u radijanima: ";
	f.Ispisi();
	std::cout << std::endl << "Vrijednost pi u stepenima: ";
	f.IspisiKlasicno();
	return 0;
}



Ugao ZbirUglova(const Ugao &u1, const Ugao &u2)
{
	return Ugao(u1.DajStepene() + u2.DajStepene(), u1.DajMinute() + u2.DajMinute(), u1.DajSekunde() + u2.DajSekunde());
}

Ugao ProduktUglaSaBrojem(const Ugao &u, double x)
{
	return Ugao(u.DajRadijane() * x);
}

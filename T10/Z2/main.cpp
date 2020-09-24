#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <iomanip>


class Krug
{
  double poluprecnik;
public:
  //Krug() = delete;
  explicit Krug(double value)
  {
    if (value <= 0) {
      throw std::domain_error("Neispravan poluprecnik");
    }
    poluprecnik = value;
  }

  void Postavi (double value)
  {
    if (value <= 0) {
      throw std::domain_error("Neispravan poluprecnik");
    }
    poluprecnik = value;
  }

  double DajPoluprecnik() const
  {
    return poluprecnik;
  }

  double DajObim() const
  {
    return 2 * poluprecnik * std::atan(1) * 4;
  }

  double DajPovrsinu() const
  {
    return poluprecnik * poluprecnik * std::atan(1) * 4;
  }

  void Skaliraj(double skalar)
  {
    if (skalar <= 0 ) {
      throw std::domain_error("Neispravan faktor skaliranja");
    }
    poluprecnik *= skalar;
  }

  void Ispisi() const
  {
    std::cout << "R=" << std::fixed << std::setprecision(5) <<  poluprecnik <<
              " O=" << std::fixed << std::setprecision(5) <<  DajObim() <<
              " P=" << std::fixed << std::setprecision(5) <<  DajPovrsinu();
  }
};



class Valjak
{
  Krug baza;
  double visina;
public:
//eksplicitno zabranjuje koristenje default kosntruktora iako u ovom slucaju takav
//konskruktor nece biti kreiran zbog postojanja drugog kosntruktora sa jednim parametrom
  Valjak() = delete;
  Valjak(double poluprecnikBaze, double visina):
    baza (poluprecnikBaze)
  {
    if (poluprecnikBaze <= 0) {
      throw std::domain_error("Neispravan poluprecnik");
    }
    if (visina <= 0) {
      throw std::domain_error("Neispravna visina");
    }
    this->visina = visina;
  }

  void Postavi(double poluprecnikBaze, double visina)
  {
    if (poluprecnikBaze <= 0) {
      throw std::domain_error("Neispravan poluprecnik");
    }
    if (visina <= 0) {
      throw std::domain_error("Neispravna visina");
    }
    baza = Krug(poluprecnikBaze);
    this->visina = visina;
  }



  Krug DajBazu () const
  {
    return baza;
  }

  double DajPoluprecnikBaze() const
  {
    return baza.DajPoluprecnik();
  }

  double DajVisinu() const
  {
    return visina;
  }

  double DajPovrsinu() const
  {
    return 2 * baza.DajPovrsinu() + visina * baza.DajObim();

  }

  double DajZapreminu() const
  {
    return baza.DajPovrsinu() * visina;
  }

  void Skaliraj(double skalar)
  {
    if (skalar <= 0 ) {
      throw std::domain_error("Neispravan faktor skaliranja");
    }
    baza.Postavi(baza.DajPoluprecnik() * skalar);
    visina *= skalar;
  }

  void Ispisi() const
  {
    std::cout<< "R=" << std::setprecision(5) << std::fixed << baza.DajPoluprecnik() <<
             " H=" << std::setprecision(5) << std::fixed <<  visina <<
             " P=" << std::setprecision(5) << std::fixed << this->DajPovrsinu() <<
             " V=" << std::setprecision(5) << std::fixed<< DajZapreminu();
  }
};

int main ()
{
  Krug k(5);
  k.Skaliraj(10);
  Valjak v(5,5);
  v.Skaliraj(10);
  std::cout<<k.DajPoluprecnik()<<std::endl;
  std::cout<<v.DajBazu().DajPoluprecnik()<<std::endl;
  try{
    Krug k2(-16);
  }
  catch(std::domain_error belaj) {
    std::cout << belaj.what() << std::endl;
  }
  try{
    //konverziaj iz long int u double
    Valjak k2(-2147483648, -2147483648);
  }
  catch(std::domain_error belaj) {
    std::cout << belaj.what() << std::endl;
  }
  
  
  return 0;
}

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>


class Krug {
  double poluprecnik;
public:
  Krug() = delete;
  explicit Krug(double value) {
    if (value <= 0) {
      throw std::domain_error("Neispravan poluprecnik");
    }
    poluprecnik = value;
  }
  
  void Postavi (double value) {
    if (value <= 0) {
      throw std::domain_error("Neispravan poluprecnik");
    }
    poluprecnik = value;
  }
  
  double DajPoluprecnik() const{
    return poluprecnik;
  }
  
  double DajObim() const{
    return 2 * poluprecnik * std::atan(1) * 4;
  }
  
  double DajPovrsinu() const{
    return poluprecnik * poluprecnik * std::atan(1) * 4;
  }
  
  void Skaliraj(double skalar) {
    if (skalar <= 0 ) {
      throw std::domain_error("Neispravan faktor skaliranja");
    }
    poluprecnik *= skalar;
  }
  
  void Ispisi() const {
    std::cout << "R=" << poluprecnik << " O=" << DajObim() << " P=" << DajPovrsinu();
  }
};



class Valjak {
  Krug baza;
  double visina;
public:
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
  
  Krug DajBazu () const{
    return baza;
  }
  
  double DajPoluprecnikBaze() const {
    return baza.DajPoluprecnik();
  }
  
  double DajVisinu() const {
    return visina;
  }
  
  double DajPovrsinu() const {
    return 2 * baza.DajPovrsinu() + visina * baza.DajObim();
    
  }
  
  double DajZapreminu() const {
    return baza.DajPovrsinu() * visina;
  }
  
  void Skaliraj(double skalar) {
    if (skalar <= 0 ) {
      throw std::domain_error("Neispravan faktor skaliranja");
    }
    baza.Postavi(baza.DajPoluprecnik() * skalar);
    visina *= skalar;
  }
  
  void Ispisi() const {
    std::cout << "R=" << baza.DajPoluprecnik() << " H=" << visina << " P=" << this->DajPovrsinu() << " V=" << DajZapreminu();
  }
};

int main ()
{

	return 0;
}

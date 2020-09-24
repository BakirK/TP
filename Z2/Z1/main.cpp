/* TP, 2018/2019
*/
#include <iostream>


bool active = true;

enum class Pravci {Sjever, Istok, Jug, Zapad, END_OF_LIST};

Pravci& operator++( Pravci &c ) {
  using IntType = typename std::underlying_type<Pravci>::type;
  c = static_cast<Pravci>( static_cast<IntType>(c) + 1 );
  if ( c == Pravci::END_OF_LIST )
    c = static_cast<Pravci>(0);
  return c;
}
// Special behavior for Pravci++
Pravci operator++( Pravci &c, int ) {
  Pravci result = c;
  ++c;
  return result;
}

enum class KodoviGresaka {PogresnaKomanda, NedostajeParametar, SuvisanParametar,
 NeispravanParametar, END_OF_LIST};
enum class Komande {Aktiviraj, Deaktiviraj, Nalijevo, Nadesno, Idi, Kraj}; 
enum class Smjer {Nalijevo, Nadesno};









void AktivirajRobota() {
    active = true;
}
void DeaktivirajRobota() {
    active = false;
}


void Rotiraj(Pravci &orijentacija, Smjer na_koju_stranu) {
    if (na_koju_stranu == Smjer::Nalijevo) {
        if (orijentacija == Pravci(0)) {
            orijentacija = Pravci(3);
        }
        else {
            orijentacija++;
        }
    }
    else orijentacija++;
}

void Idi(int &x, int &y, Pravci orijentacija, int korak);
void IspisiPoziciju(int x, int y, Pravci orijentacija) {
    std::string aktivan = "aktivan";
    if (!active) {
        aktivan ="neaktivan";
    }
    std::string pravac;
    switch (orijentacija) {
        case Pravci(0):{
            pravac = "sjever";
            break;
        }
        case Pravci(1):{
            pravac = "istok";
            break;
        }
        case Pravci(2):{
            pravac = "jug";
            break;
        }
        case Pravci(3):{
            pravac = "zapad";
            break;
        }
        case Pravci(4):{
            break;
        }
    }
    std::cout << "Robot je trenutno " << aktivan <<", nalazi se na poziciji ( " << x << ", " << y << " ) i gleda na " << pravac << "." << std::endl;
}
void PrijaviGresku(KodoviGresaka kod_greske);
void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y, Pravci &orijentacija) {
    
}



bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske) {
    
}
int main ()
{
    bool aktivan;
	return 0;
}
#include <iostream>
using namespace std;
int main()
{
	std::ios::sync_with_stdio(false);
	int duzina, sirina, dubina;
	int plocica;
	int potrebno;
	cout << "Unesite duzinu, sirinu i dubinu bazena u metrima: ";
	cin >> duzina >> sirina >> dubina;
	cout << "Unesite sirinu plocice u centimetrima: ";
	//prvo clear mora ici, pa onda ignore
	//std::cin.clear();
	//std::cin.ignore(10000, '\n');
	cin >> plocica;
	
	if ((duzina*100) % plocica == 0 && (sirina*100) % plocica == 0 && (dubina*100) % plocica == 0) {
		potrebno=(2*100*duzina*dubina*100) + (2*100*sirina*dubina*100) + (100*duzina*sirina*100);
		potrebno/=plocica*plocica;
		cout << "\nZa poplocavanje bazena dimenzija " << duzina << "x" << sirina << "x" << dubina << "m" << " sa plocicama dimenzija " 
			 << plocica << "x" << plocica << "cm" << "\npotrebno je " << potrebno << " plocica.";
	}
	else {
		cout << "\nPoplocavanje bazena dimenzija " << duzina << "x" << sirina << "x" << dubina << "m" <<" sa plocicama dimenzija "
			 << plocica << "x" << plocica << "cm"<< "\nnije izvodljivo bez lomljenja plocica!" << endl;
	}
	return 0;	
}

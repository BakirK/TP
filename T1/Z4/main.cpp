#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	std::ios::sync_with_stdio(false);
	double broj;
	int suma=0;
	int i;
	
	for(;;) {
	    cout << "Unesite prirodan broj ili 0 za kraj: ";
	    for(;;) {
	        cin >> broj;
	        int temp = int(broj);
	        if ( temp != broj ) {
	        	cout << "Niste unijeli prirodan broj!" << endl;
	        	cin.clear();
	        	cin.ignore(10000, '\n');
	        	cout << "Unesite prirodan broj ili 0 za kraj: ";
	        }
	        else if (cin && broj>=0 && broj==temp) {
	            break;
	        }
	        else {
	        	cout << "Niste unijeli prirodan broj!" << endl;
	        	cin.clear();
	        	cin.ignore(10000, '\n');
	        	cout << "Unesite prirodan broj ili 0 za kraj: ";
	        }
	    }
	    
	    if( broj == 0) {
	        std::cout << "Dovidjenja!" << std::endl;
	        break;
	    }
	    suma=0;
	    for(i = 1 ; i < broj ; i++) {
	        if(std::fmod(broj, i) == 0) {
	            suma+=i;
	        }
	    }
	    
	    if(suma < broj) {
	        std::cout << "Broj " << broj << " je manjkav!" << std::endl;
	    }
	    else if (suma==broj) {
	        std::cout << "Broj " << broj << " je savrsen!" << std::endl;
	    }
	    else {
	        std::cout << "Broj " << broj << " je obilan!" << std::endl;
	    }
	}
	return 0;	
}
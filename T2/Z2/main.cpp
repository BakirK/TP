//TP 2017/2018: Tutorijal 2, Zadatak 2
#include <iostream>
#include <vector>


bool TestPerioda (std::vector<double> v, int n) {
    if (n<1 || n>v.size()-1) {
        return false;
    }
    bool test = false;
    for (int i = 0 ; i<v.size() ; i++) {
        if (i+n==v.size()) {
            break;
        }
        if ( v[i] != v[i+n]) {
           return test;
        }
    }
    return true;
}

int OdrediOsnovniPeriod ( std::vector<double> v) {
    //max period
    int n { static_cast<int> (v.size()-1) };
    if (n<1) {
        return 0;
    }
    for (int i=0 ; i<=n ; i++) {
        if (TestPerioda(v, i)) {
            return i;
        }
    }
    return 0;
}

int main ()
{
    std::vector<double> slijed;
    std::cout << "Unesite slijed brojeva (0 za kraj): ";
    double broj;
    do {
        std::cin >> broj;
        if(broj != 0){
            slijed.push_back(broj);
        } 
    } while(broj != 0);
    int periodicnost = OdrediOsnovniPeriod(slijed);
    if (!periodicnost) {
        std::cout << "Slijed nije periodican!";
    } else {
        std::cout << "Slijed je periodican sa osnovnim periodom " << periodicnost << ".";
    }
	return 0;
}
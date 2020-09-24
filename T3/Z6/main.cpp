//TP 2017/2018: Tutorijal 3, Zadatak 6
#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <cmath>
#include<limits>

typedef std::vector<std::vector<int>> matrica;

int NajvecaSirina (std::vector<std::vector<int>> matrica) {
	if (matrica.size() == 0) {
		return 0;
	} else if (matrica[0].size() == 0) {
		return 0;
	}
	long long int max (0);
	for (int i = 0; i < matrica.size(); i++) {
    	for (int j = 0; j < matrica[i].size(); j++) {
    	    if (std::abs(static_cast<long long int>(matrica[i][j])) > max) {
    	        max = std::abs(matrica[i][j]);    
    	    }
    	}
	}
	int sirina (0);
	while(max != 0) {
		sirina++;
		max /= 10;
	}
	
	for (int i = 0; i < matrica.size(); i++) {
    	for (int j = 0; j < matrica[i].size(); j++) {
    	    int sirinaTemp = 0;
    	    unsigned int temp = std::abs(matrica.at(i).at(j));
    	    while (temp != 0) {
    	        sirinaTemp++;
    	        temp /= 10;
    	    }
    	    if (sirinaTemp == sirina && matrica.at(i).at(j) < 0) {
    	        sirina++;
    	        break;
    	    }
    	}
	}
	return sirina;
}


matrica KroneckerovProizvod (std::vector<int> m1, std::vector<int> m2) {
	matrica m3 (m1.size());
    //std::cout << "m2:" << m2.size() << " m1" << m1.size();
	for (int i = 0; i < m1.size(); i++) {
	    m3[i].resize(m2.size());
	}
	for (int i = 0; i < m3.size(); i++) {
    	for (int j = 0; j < m2.size(); j++) {
    	    m3[i][j] = m1[i] * m2[j];
    	}
	}
	return m3;
}

int main ()
{
	//unos prvog
	int n1;
    while (true) {

        std::cout << "Unesite broj elemenata prvog vektora: ";
        std::cin >> n1;
        if (n1 <= 0) {
            std::cout << "Broj elemenata mora biti veci od 0!" << std::endl;
            return 0;
        }
        break;
    }
	int i (0);
    std::vector<int> a;
    std::cout << "Unesite elemente prvog vektora: ";
    while (i < n1) {
        int temp;
        std::cin >> temp;
        a.push_back(temp);
        i++;
    }
    
    //unos drugog
	int n2;
    while (true) {
        std::cout << "Unesite broj elemenata drugog vektora: ";
        std::cin >> n2;
        if (n2 <= 0) {
            std::cout << "Broj elemenata mora biti veci od 0!" << std::endl;
            return 0;
        }
        break;
    }
	i = 0;
    std::vector<int> b;
    std::cout << "Unesite elemente drugog vektora: ";
    while (i < n2) {
        int temp;
        std::cin >> temp;
        b.push_back(temp);
        i++;
    }
    std::cout << std::endl;
    matrica proizvod = KroneckerovProizvod(a, b);
    int sirina = NajvecaSirina(proizvod) + 1;
    
    
	
	for (int i = 0; i < proizvod.size(); i++) {
		for (int j = 0; j < proizvod[0].size(); j++) {
			std::cout << std::setw(sirina) << std::right << proizvod[i][j];
		}	
		std::cout << std::endl;
	}	
	
	
	//std::cout << "Sirina: " << NajvecaSirina({{11, -232, 555}, {1423, 23211}, {-66, 437, 1231240, -1231239}});
	return 0;
}
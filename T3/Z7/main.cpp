//TP 2017/2018: Tutorijal 3, Zadatak 7
#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>

int NajvecaSirina (std::vector<std::vector<int>> matrica) {
	if (matrica.size() == 0) {
		return 0;
	} else if (matrica[0].size() == 0) {
		return 0;
	}
	int index = matrica[matrica.size()-1].size();
	index = (index / 2) + 1;
	int broj = matrica[matrica.size()-1][index-1];
	int sirina = 0;
	while(broj != 0) {
		sirina++;
		broj /= 10;
	}
	return sirina;
}




std::vector<std::vector<int>> PascalovTrougao (int n) {
	try {
		if (n > 0) {
			std::vector<std::vector<int>> trougao (n);
			for (int i = 1; i <= n; i++) {
				trougao[i-1].resize(i);
			}
			for (int i = 0; i < n; i++) {
				trougao[i][0] = 1;
			}
			for (int i = 1; i < n; i++) {
				for (int j = 1; j <= i; j++) {
					if (j == i) {
						trougao[i][j] = trougao[i-1][j-1];
					} else {
						trougao[i][j] = trougao[i-1][j-1] + trougao[i-1][j];
					}
				}	
			}
			return trougao;
		} else if (n == 0) {
			return std::vector<std::vector<int>> (0);
		} else {
			throw std::domain_error("Broj redova ne smije biti negativan");
		}
		 
	}
	catch(std::domain_error izuzetak) {
		std::cout << izuzetak.what() << std::endl;
	}
	return std::vector<std::vector<int>> (0);
	
}

int main ()
{
	std::cout << "Unesite broj redova: ";
	int n;
	std::cin >> n;
	std::vector<std::vector<int>> trougao = PascalovTrougao(n);
	int sirina = NajvecaSirina(trougao) + 1;
	std::cout << std::endl;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			std::cout << std::setw(sirina) << std::right << trougao[i][j];
		}	
		std::cout << std::endl;
	}	
	
	
	
	return 0;
}